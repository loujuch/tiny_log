#ifndef _LOG_LEVEL_HPP__
#define _LOG_LEVEL_HPP__

#include <string>

#include <cstdint>

namespace log {

enum class LogLevel : uint8_t {
	LOG_OFF = 0,
	LOG_FATAL = 1,
	LOG_ERROR = 2,
	LOG_WARN = 3,
	LOG_INFO = 4,
	LOG_DEBUG = 5,
	LOG_TRACE = 6,
	LOG_ALL = 7
}; // class LogLevel

inline bool vaild(LogLevel base, LogLevel repeat) {
	return (repeat <= base) && (base != LogLevel::LOG_OFF);
}

inline std::string get_log_level_str(LogLevel repeat) {
	static std::string log_level_str[8] = {
		"OFF", "FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE", "ALL"
	};
	return log_level_str[static_cast<unsigned>(repeat)];
}

} // namespace log

#endif // _LOG_LEVEL_HPP__