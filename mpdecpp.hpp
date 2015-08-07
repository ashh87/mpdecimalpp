#ifndef MPDECPP_HPP
#define MPDECPP_HPP

#include <memory>

#include <mpdecimal.h>

namespace mpdecpp
{
	void set_context(std::shared_ptr<mpd_context_t> new_context);
	std::shared_ptr<mpd_context_t> DefaultContext();
	
	class mpd_c {
		public:
			mpd_t *number;
			mpd_c(std::shared_ptr<mpd_context_t>);
			mpd_c();
			~mpd_c();
	};
}

#endif
