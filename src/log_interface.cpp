#include "log_interface.hpp"

#include "log_timestamp.hpp"
#include "log_core.hpp"
#include "log_config.hpp"

#include <unistd.h>

log::LogInterface::LogInterface(const char *file, const char *func,
	const int line, const LogLevel level) :level_(level) {
	if(!LogConfig::getInstance().check_level(level_)) {
		return;
	}
	log::LogFormatter(prefix_, level_) << '[' << LogTimeStamp::getInstance().get_time_stamp_str()
		<< "] {" << ::gettid() << "->" << func << "} ["
		<< get_log_level_str(level) << "] ";
	log::LogFormatter(suffix_, level_) << " [" << file << ':' << line << "]\n";
}

log::LogInterface::~LogInterface() {
	if(!LogConfig::getInstance().check_level(level_)) {
		return;
	}
	commit();
}

void log::LogInterface::commit() {
	LogCore::getInstance().append(prefix_ + suffix_);
}

void log::LogInterface::close() {
	LogCore::getInstance().close();
}