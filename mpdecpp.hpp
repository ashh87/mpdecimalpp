#ifndef MPDECPP_HPP
#define MPDECPP_HPP

#include <memory>
#include <string>
#include <iostream>

#include <mpdecimal.h>

namespace mpdecpp
{
	void set_context(std::shared_ptr<mpd_context_t> new_context);
	std::shared_ptr<mpd_context_t> get_context() noexcept;
	std::shared_ptr<mpd_context_t> get_context_ctor() noexcept;

	std::shared_ptr<mpd_context_t> DefaultContext();
	std::shared_ptr<mpd_context_t> BasicContext();
	std::shared_ptr<mpd_context_t> MaxContext();
	std::shared_ptr<mpd_context_t> IEEEContext(int);
	
	//a local context manager
	class mpd_localcontext {
		private:
			std::shared_ptr<mpd_context_t> saved_context;
		public:
			mpd_localcontext(std::shared_ptr<mpd_context_t>);
			~mpd_localcontext();
			mpd_localcontext(const mpd_localcontext&) = delete; //no copies
			mpd_localcontext(const mpd_localcontext&&) = delete; //no moves
	};
	
	class mpd_c {
		private:
			//private constructor for memory assignment only
			mpd_c(nullptr_t) noexcept;

		public:
			mutable mpd_t *number;

			//constructors
			mpd_c(int32_t, std::shared_ptr<mpd_context_t>) noexcept;
			mpd_c(int64_t, std::shared_ptr<mpd_context_t>) noexcept;
			mpd_c(uint32_t, std::shared_ptr<mpd_context_t>) noexcept;
			mpd_c(uint64_t, std::shared_ptr<mpd_context_t>) noexcept;
			mpd_c(std::string, std::shared_ptr<mpd_context_t>) noexcept;
			mpd_c(const char*, std::shared_ptr<mpd_context_t>) noexcept;

			mpd_c(int32_t value) noexcept;
			mpd_c(int64_t value) noexcept;
			mpd_c(uint32_t value) noexcept;
			mpd_c(uint64_t value) noexcept;
			mpd_c(std::string value) noexcept;
			mpd_c(const char* value) noexcept;

			mpd_c(std::shared_ptr<mpd_context_t>) noexcept;

			mpd_c() noexcept;

			mpd_c(const mpd_c&) noexcept;
			mpd_c(mpd_c&&) noexcept;

			mpd_c& operator=(mpd_c other) noexcept;
			friend void swap(mpd_c&, mpd_c&) noexcept;

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
			
			//digitwise overloads - use with care!
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
			friend std::istream &operator>>(std::istream &input, mpd_c &D);
	};

	//stream manipulation
	enum ExponentFormat
	{
		MPD_EXP_FMT_SCI = 0,
		MPD_EXP_FMT_ENG
	};

	enum ExponentCapitalisation
	{
		MPD_EXP_CAP_LOWER = 0,
		MPD_EXP_CAP_UPPER
	};
	
	std::ostream& sci(std::ostream&);
	std::ostream& SCI(std::ostream&);
	std::ostream& eng(std::ostream&);
	std::ostream& ENG(std::ostream&);
}

#endif
