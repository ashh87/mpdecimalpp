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

			//addition overloads
			mpd_c& operator+=(const mpd_c &rhs);
			mpd_c& operator+=(const int32_t &rhs);

			friend std::ostream &operator<<(std::ostream &output, const mpd_c &D);
	};
}

#endif
