#include "log.hpp"

#include <chrono>
#include <iostream>
#include <thread>
#include <vector>
#include <fstream>

int thread_num = 1024, loop_num = 1024 * 32;

void func(int p) {
	for(int i = 0;i < loop_num;++i) {
		log::log_fatal << p << ' ' << i << ' ' << "hello world!";
	}
}

int main(int argc, char *argv[]) {
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