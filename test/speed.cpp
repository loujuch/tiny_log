#include "log.hpp"

#include <thread>
#include <iostream>
#include <vector>

using namespace std;

int thread_num = 1024, loop_num = 1024;

void func() {
	static const std::string message("0123456789ABCDEF");
	for(int i = 0;i < loop_num;++i) {
		log::log_info << message << message << message << message
			<< message << message << message << message;
	}
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		thread_num = atoi(argv[1]);
		thread_num = thread_num > 0 ? thread_num : 1024;
	}
	if(argc > 2) {
		loop_num = atoi(argv[2]);
		loop_num = loop_num > 0 ? loop_num : 1024;
	}
	log::log_set_file_prefix(argv[0]);
	log::log_set_level(log::LOG_ALL);
	std::vector<std::thread> th;
	auto start = std::chrono::system_clock::now();
	for(int i = 0;i < thread_num;++i) {
		th.emplace_back(func);
	}
	for(auto &i : th) {
		i.join();
	}
	log::log_close();
	auto end = std::chrono::system_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	long double time_us = duration.count();
	long double time_ms = time_us / 1000;
	long double time_s = time_ms / 1000;

	long double data_B = 128;
	data_B *= thread_num;
	data_B *= loop_num;
	long double data_KB = data_B / 1024;
	long double data_MB = data_KB / 1024;
	long double data_GB = data_MB / 1024;
	std::cout << argv[0] << " Thread Number: " << thread_num << " Loop Number: " << loop_num
		<< "\n\tWrite Data: " << data_GB << "GB"
		<< "\n\tWrite Time: " << time_s << "s"
		<< "\n\tWrite Speed: " << data_GB / time_s << "GB/s" << std::endl;
	return 0;
}