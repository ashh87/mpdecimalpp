#ifndef MPDECPP_HPP
#define MPDECPP_HPP

#include <memory>

#include <mpdecimal.h>

namespace mpdecpp
{
	void set_context(std::shared_ptr<mpd_context_t> new_context);
	std::shared_ptr<mpd_context_t> get_context();

	std::shared_ptr<mpd_context_t> DefaultContext();
	
	class mpd_c {
		public:
			mpd_t *number;

			mpd_c(std::shared_ptr<mpd_context_t>);
			mpd_c();

			mpd_c(const mpd_c& other);
			mpd_c& operator=(const mpd_c& other);

			~mpd_c();

			//addition overloads
			//   mpd_c& operator+=(const mpd_ssize_t &rhs); //is i64...
			mpd_c& operator+=(const mpd_c &rhs);
			mpd_c& operator+=(const int32_t &rhs);
			mpd_c& operator+=(const int64_t &rhs);
			mpd_c& operator+=(const uint32_t &rhs);
			mpd_c& operator+=(const uint64_t &rhs);

			const mpd_c operator+(const mpd_c &other) const;
			const mpd_c operator+(const int32_t &other) const;
			const mpd_c operator+(const int64_t &other) const;
			const mpd_c operator+(const uint32_t &other) const;
			const mpd_c operator+(const uint64_t &other) const;

			//subtraction overloads
			mpd_c& operator-=(const mpd_c &rhs);
			mpd_c& operator-=(const int32_t &rhs);
			mpd_c& operator-=(const int64_t &rhs);
			mpd_c& operator-=(const uint32_t &rhs);
			mpd_c& operator-=(const uint64_t &rhs);

			const mpd_c operator-(const mpd_c &other) const;
			const mpd_c operator-(const int32_t &other) const;
			const mpd_c operator-(const int64_t &other) const;
			const mpd_c operator-(const uint32_t &other) const;
			const mpd_c operator-(const uint64_t &other) const;

			//multiplication overloads
			mpd_c& operator*=(const mpd_c &rhs);
			mpd_c& operator*=(const int32_t &rhs);
			mpd_c& operator*=(const int64_t &rhs);
			mpd_c& operator*=(const uint32_t &rhs);
			mpd_c& operator*=(const uint64_t &rhs);

			const mpd_c operator*(const mpd_c &other) const;
			const mpd_c operator*(const int32_t &other) const;
			const mpd_c operator*(const int64_t &other) const;
			const mpd_c operator*(const uint32_t &other) const;
			const mpd_c operator*(const uint64_t &other) const;

			//division overloads
			mpd_c& operator/=(const mpd_c &rhs);
			mpd_c& operator/=(const int32_t &rhs);
			mpd_c& operator/=(const int64_t &rhs);
			mpd_c& operator/=(const uint32_t &rhs);
			mpd_c& operator/=(const uint64_t &rhs);

			const mpd_c operator/(const mpd_c &other) const;
			const mpd_c operator/(const int32_t &other) const;
			const mpd_c operator/(const int64_t &other) const;
			const mpd_c operator/(const uint32_t &other) const;
			const mpd_c operator/(const uint64_t &other) const;

			friend std::ostream &operator<<(std::ostream &output, const mpd_c &D);
	};
}

#endif
