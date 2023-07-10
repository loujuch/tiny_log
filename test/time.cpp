#include "log.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

int thread_num = 1024, loop_num = 1024;

void func(int p) {
	for(int i = 0;i < loop_num;++i) {
		log::log_fatal << p << ' ' << i << ' ' << 3.14 * p + i << ' ' << "hello world!";
	}
}

int main(int argc, char *argv[]) {
	if(argc > 1) {
		thread_num = atoi(argv[1]);
		thread_num = thread_num > 0 ? thread_num : 64;
	}
	if(argc > 2) {
		loop_num = atoi(argv[2]);
		loop_num = loop_num > 0 ? loop_num : 64;
	}
	std::fstream f("./test.log", std::ios::app);
	log::log_set_file_prefix(argv[0]);
	log::log_set_level(log::LOG_ALL);
	std::vector<std::thread> th;
	auto start = std::chrono::system_clock::now();
	for(int i = 0;i < thread_num;++i) {
		th.emplace_back(func, i);
	}
	for(auto &i : th) {
		i.join();
	}
	log::log_close();
	auto end = std::chrono::system_clock::now();
	auto duration =
		std::chrono::duration_cast<std::chrono::microseconds>(end - start);
	f << argv[0] << " thread_num: " << thread_num << " loop_num: "
		<< loop_num << " 运行耗时: " << duration.count() << "us" << std::endl;
	return 0;
}