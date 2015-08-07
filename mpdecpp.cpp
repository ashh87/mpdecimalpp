#include "mpdecpp.hpp"

#include <memory>
#include <string>

#include <mpdecimal.h>

namespace mpdecpp
{
	thread_local std::shared_ptr<mpd_context_t> default_context;
	
	//local context manager
	
	//set_context
	void set_context(std::shared_ptr<mpd_context_t> new_context)
	{
		default_context = std::move(new_context);
	}
	
	//pre-defined contexts
	std::shared_ptr<mpd_context_t> DefaultContext()
	{
		auto tmp_context = std::make_shared<mpd_context_t>();
		mpd_defaultcontext(tmp_context.get());
		return tmp_context;
	}
	
	//number type class functions
	mpd_c::mpd_c(std::shared_ptr<mpd_context_t> context)
	{
		number = mpd_new(context.get());
		//use quiet version?
		//init to 0
		mpd_set_i32(number, 0, context.get());
	}

	mpd_c::mpd_c() : mpd_c(default_context) {}
	
	mpd_c::~mpd_c()
	{
		mpd_del(number);
	}

	mpd_c& mpd_c::operator+=(const mpd_c &rhs) {
		mpd_add(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator+=(const int32_t &rhs)
	{
		mpd_add_i32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	std::ostream &operator<<(std::ostream &output, const mpd_c &D)
	{ //we want to change this to be more flexible
		std::string tosci(mpd_to_sci((D.number), 1));
		output << tosci;
		return output;
	}
}

