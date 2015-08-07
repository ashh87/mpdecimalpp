#include "mpdecpp.hpp"

#include <memory>

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
	}

	mpd_c::mpd_c() : mpd_c(default_context) {}
	
	mpd_c::~mpd_c()
	{
		mpd_del(number);
	}
}
