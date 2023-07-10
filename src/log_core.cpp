#include "log_core.hpp"

#include <functional>

#include "log_config.hpp"
#include "log_file.hpp"

std::atomic<bool> log::LogCore::running_(false);

log::LogCore::LogCore() :run_(true), write_status_(WriteThreadStatus::WAIT_CREATE), is_empty(true),
write_thread_(std::bind(&LogCore::func, this)) {
}

void log::LogCore::append(const std::string &s) {
	if(s.empty() || !LogConfig::getInstance().check_level(LogLevel::LOG_OFF)) {
		return;
	}
	bool is;
	core_mutex_.lock();
	is = buffer_.append(s);
	is_empty = false;
	core_mutex_.unlock();
	if(is) {
		core_cond_.notify_one();
	}
}

void log::LogCore::switch_buffer(LogBufferList &buf) {
	std::unique_lock<std::mutex> locker(core_mutex_);
	do {
		write_status_ = WriteThreadStatus::WAIT_SIGNAL;
		write_status_ = (core_cond_.wait_for(locker, LogConfig::getInstance().log_sync_time())
			== std::cv_status::timeout) ?
			WriteThreadStatus::TimeOut :
			WriteThreadStatus::NOTIFY;
	} while(is_empty && run_);
	if(run_) {
		write_status_ = WriteThreadStatus::WAIT_DATA;
		swap(buf, buffer_);
		is_empty = true;
		write_status_ = WriteThreadStatus::GET_DATA;
	}
	locker.unlock();
}

void log::LogCore::commit(const LogBuffer &buffer) {
	LogFile::getInstance().append(buffer);
}

void log::LogCore::wait_write_thread_done() {
	// 循环退出条件
	// 1. 写线程已关闭(write_status_ == WriteThreadStatus::END)
	// 2. 写线程阻塞在“等待前端提交数据”处但前端不存在提交数据
	//         (write_status_ == WriteThreadStatus::WAIT_SIGNAL && is_empty)
	while(!((write_status_ == WriteThreadStatus::END) ||
		(write_status_ == WriteThreadStatus::WAIT_SIGNAL && is_empty))) {
		std::this_thread::yield();
	}
}

void log::LogCore::close() {
	if(run_ == false) {
		return;
	}
	LogConfig::getInstance().set_base_level(LogLevel::LOG_OFF);
	wait_write_thread_done();
	run_ = false;
	core_cond_.notify_one();
	write_thread_.join();
	LogFile::getInstance().close();
}

void log::LogCore::func() {
	running_ = true;
	write_status_ = WriteThreadStatus::START;
	while(run_) {
		write_status_ = WriteThreadStatus::ONE_LOOP_START;
		LogBufferList link;
		write_status_ = WriteThreadStatus::READY_DATA;
		switch_buffer(link);
		write_status_ = WriteThreadStatus::READY_DATA_DONE;
		while(link.now() != nullptr && run_) {
			write_status_ = WriteThreadStatus::COMMIT_DATA_START;
			commit(*link.now());
			link.next();
			write_status_ = WriteThreadStatus::COMMIT_DATA_END;
		}
		LogFile::getInstance().flush();
		write_status_ = WriteThreadStatus::ONE_LOOP_END;
	}
	write_status_ = WriteThreadStatus::END;
	running_ = false;
}