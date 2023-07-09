#include "log_buffer_list.hpp"

#include <iostream>

log::LogBufferList::LogBufferList() :front_(new LogBuffer), cur_(front_), back_(cur_) {
}

bool log::LogBufferList::append(const std::string &s) {
	bool out = false;
	if(!(back_->append(s))) {
		add_new();
		out = true;
		if(!(back_->append(s))) {
			std::cerr << __FILE__ << ' ' << __func__ << ' ' << __LINE__ << ": append line log fail\n";
		}
	}
	return out;
}