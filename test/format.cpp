#include "log.hpp"

#include <fstream>

#include <cstdint>
#include <climits>

int main(int argc, char *argv[]) {
	std::fstream f("./test.log", std::ios::app);
	log::log_set_file_prefix(argv[0]);
	log::log_set_level(log::LOG_ALL);
	int n = 0;
	float fstep = 1e-6;
	float f0 = 0, f1 = 1e-4, f2 = 1e7,
		f3 = f0 + fstep, f4 = f1 + fstep, f5 = f2 + fstep,
		f6 = f0 - fstep, f7 = f1 - fstep, f8 = f2 - fstep,
		f9 = -f0, f10 = -f1, f11 = -f2,
		f12 = -f3, f13 = -f4, f14 = -f5,
		f15 = -f6, f16 = -f7, f17 = -f8,
		f18 = 12918.128, f19 = 12381.22222, f20 = 10090;
	double dstep = 1e-9;
	double d0 = 0, d1 = 1e-4, d2 = 1e7,
		d3 = d0 + dstep, d4 = d1 + dstep, d5 = d2 + dstep,
		d6 = d0 - dstep, d7 = d1 - dstep, d8 = d2 - dstep,
		d9 = -d0, d10 = -d1, d11 = -d2,
		d12 = -d3, d13 = -d4, d14 = -d5,
		d15 = -d6, d16 = -d7, d17 = -d8,
		d18 = 19272361.111128, d19 = -12380.00, d20 = 129000;
	char buffer[32] = "Hello World!";
	log::log_fatal << true << ' ' << false;
	log::log_fatal << 0 << ' ' << INT16_MAX << ' ' << INT16_MIN << ' ' << UINT16_MAX;
	log::log_fatal << 0 << ' ' << INT32_MAX << ' ' << INT32_MIN << ' ' << UINT32_MAX;
	log::log_fatal << 0 << ' ' << INT64_MAX << ' ' << INT64_MIN << ' ' << UINT64_MAX;
	log::log_fatal << f0 << ' ' << f1 << ' ' << f2 << ' ' << f3 << ' ' << f4
		<< ' ' << f5 << ' ' << f6 << ' ' << f7 << ' ' << f8;
	log::log_fatal << f9 << ' ' << f10 << ' ' << f11 << ' ' << f12 << ' ' << f13
		<< ' ' << f14 << ' ' << f15 << ' ' << f16 << ' ' << f17;
	log::log_fatal << f18 << ' ' << f19 << ' ' << f20;
	log::log_fatal << d0 << ' ' << d1 << ' ' << d2 << ' ' << d3 << ' ' << d4
		<< ' ' << d5 << ' ' << d6 << ' ' << d7 << ' ' << d8;
	log::log_fatal << d9 << ' ' << d10 << ' ' << d11 << ' ' << d12 << ' ' << d13
		<< ' ' << d14 << ' ' << d15 << ' ' << d16 << ' ' << d17;
	log::log_fatal << d18 << ' ' << d19 << ' ' << d20;
	log::log_fatal << buffer << ' ' << &n;
	log::log_close();
	f << argv[0] << std::endl;
}