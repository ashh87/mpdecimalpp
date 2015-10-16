#ifndef MPDECPP_HPP
#define MPDECPP_HPP

#include <memory>
#include <string>

#include <mpdecimal.h>

namespace mpdecpp
{
	void set_context(std::shared_ptr<mpd_context_t> new_context);
	std::shared_ptr<mpd_context_t> get_context();

	std::shared_ptr<mpd_context_t> DefaultContext();
	
	class mpd_c {
		private:
			//private constructor for memory assignment only
			mpd_c(nullptr_t);

		public:
			mutable mpd_t *number;

			//constructors
			mpd_c(int32_t, std::shared_ptr<mpd_context_t>);
			mpd_c(int64_t, std::shared_ptr<mpd_context_t>);
			mpd_c(uint32_t, std::shared_ptr<mpd_context_t>);
			mpd_c(uint64_t, std::shared_ptr<mpd_context_t>);
			mpd_c(std::string, std::shared_ptr<mpd_context_t>);
			mpd_c(const char*, std::shared_ptr<mpd_context_t>);

			mpd_c(int32_t value);
			mpd_c(int64_t value);
			mpd_c(uint32_t value);
			mpd_c(uint64_t value);
			mpd_c(std::string value);
			mpd_c(const char* value);

			mpd_c(std::shared_ptr<mpd_context_t>);

			mpd_c();

			mpd_c(const mpd_c&);
			mpd_c(mpd_c&&);

			mpd_c& operator=(mpd_c other);
			friend void swap(mpd_c&, mpd_c&);

			//destructor
			~mpd_c();

			//addition overloads
			//   mpd_c& operator+=(const mpd_ssize_t &rhs); //is i64...

			const mpd_c operator+() const;
			mpd_c& operator++();
			const mpd_c operator++(int) const;

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

			const mpd_c operator-() const;
			mpd_c& operator--();
			const mpd_c operator--(int) const;

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

			//modulo overloads
			mpd_c& operator%=(const mpd_c &rhs);
			const mpd_c operator%(const mpd_c &other) const;
			
			//comparison overloads
			bool operator==(mpd_c const&) const;
			bool operator!=(mpd_c const&) const;
			bool operator>(mpd_c const&) const;
			bool operator<(mpd_c const&) const;
			bool operator>=(mpd_c const&) const;
			bool operator<=(mpd_c const&) const;
			
			//bitwise overloads - use with care!
			const mpd_c operator~();
			mpd_c& operator&=(const mpd_c &);
			mpd_c& operator|=(const mpd_c &);
			mpd_c& operator^=(const mpd_c &);
			mpd_c& operator<<=(const mpd_c &);
			mpd_c& operator>>=(const mpd_c &);
			const mpd_c operator&(const mpd_c &) const;
			const mpd_c operator|(const mpd_c &) const;
			const mpd_c operator^(const mpd_c &) const;
			const mpd_c operator<<(const mpd_c &) const;
			const mpd_c operator>>(const mpd_c &) const;

			//logical overloads
			const mpd_c operator!() const;

			friend std::ostream &operator<<(std::ostream &output, const mpd_c &D);
	};
}

#endif
