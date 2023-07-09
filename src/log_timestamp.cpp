#include "log_timestamp.hpp"

#include <sys/timeb.h>

log::LogTimeStamp::LogTimeStamp() {
}

std::string log::LogTimeStamp::get_time_stamp_str() {
	char buffer[24];
	timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	strftime(buffer, sizeof(buffer), "%Y/%m/%d %H:%M:%S.", gmtime(&(t.tv_sec)));
	t.tv_nsec /= 1000000;
	buffer[22] = (t.tv_nsec % 10) + '0';
	t.tv_nsec /= 10;
	buffer[21] = (t.tv_nsec % 10) + '0';
	t.tv_nsec /= 10;
	buffer[20] = (t.tv_nsec % 10) + '0';
	buffer[23] = '\0';
	return buffer;
}

std::string log::LogTimeStamp::get_time_stamp_str_in_file_name() {
	char buffer[36];
	timespec t;
	clock_gettime(CLOCK_REALTIME, &t);
	strftime(buffer, sizeof(buffer), "%Y-%m-%d_%H-%M-%S_", gmtime(&(t.tv_sec)));
	snprintf(buffer + 20, sizeof(buffer) - 20, "%lu", t.tv_nsec % 10000000000);
	return buffer;
}