#include "mpdecpp.hpp"

#include <memory>
#include <string>

#include <mpdecimal.h>

/*
TODO:
math.h functions
cmath - set errno correctly
complex?
http://cpptruths.blogspot.co.uk/2011/09/tale-of-noexcept-swap-for-user-defined.html?_sm_au_=iVVH7JHtFMZM8rZF
*/

namespace mpdecpp
{
	thread_local static std::shared_ptr<mpd_context_t> default_context;
	
	//set_context
	void set_context(std::shared_ptr<mpd_context_t> new_context)
	{
		default_context = std::move(new_context);
	}
	
	std::shared_ptr<mpd_context_t> get_context() noexcept
	{
		return default_context;
	}
	
	std::shared_ptr<mpd_context_t> get_context_ctor() noexcept
	{
		if (!default_context) //compare to nullptr
			default_context = DefaultContext();
		return default_context;
	}
	
	//pre-defined contexts
	std::shared_ptr<mpd_context_t> DefaultContext()
	{
		auto tmp_context = std::make_shared<mpd_context_t>();
		mpd_defaultcontext(tmp_context.get());
		return tmp_context;
	}

	std::shared_ptr<mpd_context_t> BasicContext()
	{
		auto tmp_context = std::make_shared<mpd_context_t>();
		mpd_basiccontext(tmp_context.get());
		return tmp_context;
	}

	std::shared_ptr<mpd_context_t> MaxContext()
	{
		auto tmp_context = std::make_shared<mpd_context_t>();
		mpd_maxcontext(tmp_context.get());
		return tmp_context;
	}

	std::shared_ptr<mpd_context_t> IEEEContext(int bits)
	{
		//The 'bits' argument must be a multiple of 32 and less than IEEE_CONTEXT_MAX_BITS.
		//e.g. MPD_DECIMAL32, MPD_DECIMAL64, MPD_DECIMAL128
		auto tmp_context = std::make_shared<mpd_context_t>();
		mpd_ieee_context(tmp_context.get(), bits);
		return tmp_context;
	}

	//context manager
	mpd_localcontext::mpd_localcontext(std::shared_ptr<mpd_context_t> new_context)
	{
		saved_context = get_context();
		set_context(new_context);
		std::cout << "in" << std::endl;
	}

	mpd_localcontext::~mpd_localcontext()
	{
		set_context(saved_context);
		std::cout << "out" << std::endl;
	}


	//number type class functions

	/////////////////////////
	// Constructors
	/////////////////////////

	//no assignment constructor
	mpd_c::mpd_c(nullptr_t nt) noexcept
	{
		number = mpd_new(get_context_ctor().get());
	}
	
	//normal constructors
	//normal, full constructors
	mpd_c::mpd_c(int32_t value, std::shared_ptr<mpd_context_t> context) noexcept
	{
		number = mpd_new(context.get());
		mpd_set_i32(number, value, context.get());
	}

	mpd_c::mpd_c(int64_t value, std::shared_ptr<mpd_context_t> context) noexcept
	{
		number = mpd_new(context.get());
		mpd_set_i64(number, value, context.get());
	}

	mpd_c::mpd_c(uint32_t value, std::shared_ptr<mpd_context_t> context) noexcept
	{
		number = mpd_new(context.get());
		mpd_set_u32(number, value, context.get());
	}

	mpd_c::mpd_c(uint64_t value, std::shared_ptr<mpd_context_t> context) noexcept
	{
		number = mpd_new(context.get());
		mpd_set_u64(number, value, context.get());
	}

	mpd_c::mpd_c(std::string value, std::shared_ptr<mpd_context_t> context) noexcept
	{
		number = mpd_new(context.get());
		mpd_set_string(number, value.c_str(), context.get());
	}

	mpd_c::mpd_c(const char* value, std::shared_ptr<mpd_context_t> context) noexcept
	{
		number = mpd_new(context.get());
		mpd_set_string(number, value, context.get());
	}

	//constructors given a value
	mpd_c::mpd_c(int32_t value) noexcept : mpd_c(value, get_context_ctor()) {}
	mpd_c::mpd_c(int64_t value) noexcept : mpd_c(value, get_context_ctor()) {}
	mpd_c::mpd_c(uint32_t value) noexcept : mpd_c(value, get_context_ctor()) {}
	mpd_c::mpd_c(uint64_t value) noexcept : mpd_c(value, get_context_ctor()) {}
	mpd_c::mpd_c(std::string value) noexcept : mpd_c(value, get_context_ctor()) {}
	mpd_c::mpd_c(const char* value) noexcept : mpd_c(value, get_context_ctor()) {}

	//constructors given a context, default to 0
	mpd_c::mpd_c(std::shared_ptr<mpd_context_t> context) noexcept : mpd_c(0, context) {}

	//default values, no arguments
	mpd_c::mpd_c() noexcept : mpd_c(0, get_context_ctor()) {}

	//copy constructor
    mpd_c::mpd_c(const mpd_c& other) noexcept : mpd_c(nullptr)
    {
		mpd_copy(number, other.number,  get_context_ctor().get());
    }
	
	//move constructor
	mpd_c::mpd_c(mpd_c&& other) noexcept
	{
		this->number = other.number;
		other.number = 0; //C style
	}

	//copy/move assignment
    mpd_c& mpd_c::operator=(mpd_c other) noexcept
    {
		swap(*this, other);
		return *this;
    }

	void swap(mpd_c& first, mpd_c& second) noexcept
	{
		// enable ADL (not necessary in our case, but good practice)
		using std::swap; 

		// by swapping the members of two classes,
		// the two classes are effectively swapped
		swap(first.number, second.number); 
	}

	/////////////////////////
	// Destructor
	/////////////////////////
	
	mpd_c::~mpd_c()
	{
		mpd_del(number);
	}

	/////////////////////////
	// Addition
	/////////////////////////
	
	//unary plus
	const mpd_c mpd_c::operator+() const
	{
		return mpd_c(*this);
	}

	//increments
    mpd_c& mpd_c::operator++()
    {
		mpd_add_u32(this->number, this->number, 1, default_context.get());
		return *this;
    }

	const mpd_c mpd_c::operator++(int) const
    {
		return mpd_c(*this) += (uint32_t)1;
    }

	//addition

	mpd_c& mpd_c::operator+=(const mpd_c &rhs) {
		mpd_add(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator+=(const int32_t &rhs)
	{
		mpd_add_i32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator+=(const int64_t &rhs)
	{
		mpd_add_i64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator+=(const uint32_t &rhs)
	{
		mpd_add_u32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator+=(const uint64_t &rhs)
	{
		mpd_add_u64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	const mpd_c mpd_c::operator+(const mpd_c &other) const {
		return mpd_c(*this) += other;
	}

	const mpd_c mpd_c::operator+(const int32_t &other) const {
		return mpd_c(*this) += other;
	}

	const mpd_c mpd_c::operator+(const int64_t &other) const {
		return mpd_c(*this) += other;
	}

	const mpd_c mpd_c::operator+(const uint32_t &other) const {
		return mpd_c(*this) += other;
	}

	const mpd_c mpd_c::operator+(const uint64_t &other) const {
		return mpd_c(*this) += other;
	}

	/////////////////////////
	// Subtraction
	/////////////////////////
	
	//negative
	const mpd_c mpd_c::operator-() const
	{
		mpd_c tmp(*this);
		mpd_minus(tmp.number, tmp.number, default_context.get());
		return tmp;
	}

	//decrements
    mpd_c& mpd_c::operator--()
    {
		mpd_sub_u32(this->number, this->number, 1, default_context.get());
		return *this;
    }

	const mpd_c mpd_c::operator--(int) const
    {
		return mpd_c(*this) -= (uint32_t)1;
    }
	
	//subtraction

	mpd_c& mpd_c::operator-=(const mpd_c &rhs) {
		mpd_sub(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator-=(const int32_t &rhs)
	{
		mpd_sub_i32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator-=(const int64_t &rhs)
	{
		mpd_sub_i64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator-=(const uint32_t &rhs)
	{
		mpd_sub_u32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator-=(const uint64_t &rhs)
	{
		mpd_sub_u64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	const mpd_c mpd_c::operator-(const mpd_c &other) const {
		return mpd_c(*this) -= other;
	}

	const mpd_c mpd_c::operator-(const int32_t &other) const {
		return mpd_c(*this) -= other;
	}

	const mpd_c mpd_c::operator-(const int64_t &other) const {
		return mpd_c(*this) -= other;
	}

	const mpd_c mpd_c::operator-(const uint32_t &other) const {
		return mpd_c(*this) -= other;
	}

	const mpd_c mpd_c::operator-(const uint64_t &other) const {
		return mpd_c(*this) -= other;
	}

	/////////////////////////
	// Multiplication
	/////////////////////////

	mpd_c& mpd_c::operator*=(const mpd_c &rhs) {
		mpd_mul(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator*=(const int32_t &rhs)
	{
		mpd_mul_i32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator*=(const int64_t &rhs)
	{
		mpd_mul_i64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator*=(const uint32_t &rhs)
	{
		mpd_mul_u32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator*=(const uint64_t &rhs)
	{
		mpd_mul_u64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	const mpd_c mpd_c::operator*(const mpd_c &other) const {
		return mpd_c(*this) *= other;
	}

	const mpd_c mpd_c::operator*(const int32_t &other) const {
		return mpd_c(*this) *= other;
	}

	const mpd_c mpd_c::operator*(const int64_t &other) const {
		return mpd_c(*this) *= other;
	}

	const mpd_c mpd_c::operator*(const uint32_t &other) const {
		return mpd_c(*this) *= other;
	}

	const mpd_c mpd_c::operator*(const uint64_t &other) const {
		return mpd_c(*this) *= other;
	}

	/////////////////////////
	// Division
	/////////////////////////

	mpd_c& mpd_c::operator/=(const mpd_c &rhs) {
		mpd_div(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator/=(const int32_t &rhs)
	{
		mpd_div_i32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator/=(const int64_t &rhs)
	{
		mpd_div_i64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator/=(const uint32_t &rhs)
	{
		mpd_div_u32(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator/=(const uint64_t &rhs)
	{
		mpd_div_u64(this->number, this->number, rhs, default_context.get());
		return *this;
	}

	const mpd_c mpd_c::operator/(const mpd_c &other) const {
		return mpd_c(*this) /= other;
	}

	const mpd_c mpd_c::operator/(const int32_t &other) const {
		return mpd_c(*this) /= other;
	}

	const mpd_c mpd_c::operator/(const int64_t &other) const {
		return mpd_c(*this) /= other;
	}

	const mpd_c mpd_c::operator/(const uint32_t &other) const {
		return mpd_c(*this) /= other;
	}

	const mpd_c mpd_c::operator/(const uint64_t &other) const {
		return mpd_c(*this) /= other;
	}

	/////////////////////////
	// Modulo
	/////////////////////////

	mpd_c& mpd_c::operator%=(const mpd_c &rhs) {
		mpd_rem(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	const mpd_c mpd_c::operator%(const mpd_c &other) const {
		return mpd_c(*this) %= other;
	}

	/////////////////////////
	// Comparison
	/////////////////////////

	bool mpd_c::operator==(mpd_c const& other) const
	{
		return (mpd_cmp(this->number, other.number, default_context.get()) == 0);
	}

	bool mpd_c::operator!=(mpd_c const& other) const
	{
		return !(*this == other);
	}

 	bool mpd_c::operator>(mpd_c const& other) const
	{
		return (mpd_cmp(this->number, other.number, default_context.get()) == 1);
	}

 	bool mpd_c::operator<(mpd_c const& other) const
	{
		return (mpd_cmp(this->number, other.number, default_context.get()) == -1);
	}

 	bool mpd_c::operator>=(mpd_c const& other) const
	{
		return (mpd_cmp(this->number, other.number, default_context.get()) >= 0);
	}

 	bool mpd_c::operator<=(mpd_c const& other) const
	{
		return (mpd_cmp(this->number, other.number, default_context.get()) <= 0);
	}

	/////////////////////////
	// Digitwise
	/////////////////////////

	const mpd_c mpd_c::operator~()
	{
		mpd_c result;
		mpd_invert(result.number, this->number, default_context.get());
		return result;
	}

	mpd_c& mpd_c::operator&=(const mpd_c &rhs) {
		mpd_and(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator|=(const mpd_c &rhs) {
		mpd_or(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator^=(const mpd_c &rhs) {
		mpd_xor(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator<<=(const mpd_c &rhs) {
		if (rhs > 0)
			mpd_shift(this->number, this->number, rhs.number, default_context.get());
		return *this;
	}

	mpd_c& mpd_c::operator>>=(const mpd_c &rhs) {
		if (rhs > 0)
			mpd_shift(this->number, this->number, (-rhs).number, default_context.get());
		return *this;
	}

	const mpd_c mpd_c::operator&(const mpd_c &other) const {
		return mpd_c(*this) &= other;
	}

	const mpd_c mpd_c::operator|(const mpd_c &other) const {
		return mpd_c(*this) |= other;
	}

	const mpd_c mpd_c::operator^(const mpd_c &other) const {
		return mpd_c(*this) ^= other;
	}

	const mpd_c mpd_c::operator<<(const mpd_c &other) const {
		return mpd_c(*this) <<= other;
	}

	const mpd_c mpd_c::operator>>(const mpd_c &other) const {
		return mpd_c(*this) >>= other;
	}

	/////////////////////////
	// Logical
	/////////////////////////

	const mpd_c mpd_c::operator!() const
	{
		mpd_c result; //defaults to 0
		if (*this == result) //compare to 0, saving a construction
			result = 1;
		return result;
	}

	//stream manipulation
	inline getExponentFormat_i() { //internal function, no prototype, comes before operator<<....
		static int ExponentFormat_xalloc = std::ios_base::xalloc();
		return ExponentFormat_xalloc;
	}

	inline getExponentCapitalisation_i() {
		static int ExponentCapitalisation_xalloc = std::ios_base::xalloc();
		return ExponentCapitalisation_xalloc;
	}

	std::ostream &operator<<(std::ostream &output, const mpd_c &D)
	{
		std::string tosci;
		int exp_fmt = output.iword(getExponentFormat_i());
		int is_capital = output.iword(getExponentCapitalisation_i());

		switch (exp_fmt) {
			case ExponentFormat::MPD_EXP_FMT_ENG:
				tosci = mpd_to_eng(D.number, is_capital);
				break;
			case ExponentFormat::MPD_EXP_FMT_SCI:
			default:
				tosci = mpd_to_sci(D.number, is_capital);
				break;
		}

		output << tosci;
		return output;
	}

	std::istream &operator>>(std::istream &input, mpd_c &D)
	{ //could be more robust to bad strings (which cause errors) and make sure string is split on whitespace
		std::string tmps;
		input >> tmps;
		mpd_set_string(D.number, tmps.c_str(), default_context.get());
		return input;
	}

	std::ostream& sci(std::ostream& os)
	{
		os.iword(getExponentFormat_i()) = ExponentFormat::MPD_EXP_FMT_SCI;
		os.iword(getExponentCapitalisation_i()) = ExponentCapitalisation::MPD_EXP_CAP_LOWER;
		return os;
	}

	std::ostream& SCI(std::ostream& os)
	{
		os.iword(getExponentFormat_i()) = ExponentFormat::MPD_EXP_FMT_SCI;
		os.iword(getExponentCapitalisation_i()) = ExponentCapitalisation::MPD_EXP_CAP_UPPER;
		return os;
	}

	std::ostream& eng(std::ostream& os)
	{
		os.iword(getExponentFormat_i()) = ExponentFormat::MPD_EXP_FMT_ENG;
		os.iword(getExponentCapitalisation_i()) = ExponentCapitalisation::MPD_EXP_CAP_LOWER;
		return os;
	}

	std::ostream& ENG(std::ostream& os)
	{
		os.iword(getExponentFormat_i()) = ExponentFormat::MPD_EXP_FMT_ENG;
		os.iword(getExponentCapitalisation_i()) = ExponentCapitalisation::MPD_EXP_CAP_UPPER;
		return os;
	}

	//cmath
	mpd_c exp(const mpd_c inp)
	{
		mpd_c result;
		mpd_exp(result.number, inp.number, default_context.get());
		return result;
	}

	mpd_c log(const mpd_c inp)
	{
		mpd_c result;
		mpd_ln(result.number, inp.number, default_context.get());
		return result;
	}

	mpd_c log10(const mpd_c inp)
	{
		mpd_c result;
		mpd_log10(result.number, inp.number, default_context.get());
		return result;
	}

	mpd_c pow(const mpd_c base, const mpd_c exponent)
	{
		mpd_c result;
		mpd_pow(result.number, base.number, exponent.number, default_context.get());
		return result;
	}

	mpd_c sqrt(const mpd_c inp)
	{
		mpd_c result;
		mpd_sqrt(result.number, inp.number, default_context.get());
		return result;
	}

	mpd_c fma(const mpd_c a, const mpd_c b, const mpd_c c)
	{
		mpd_c result;
		mpd_fma(result.number, a.number, b.number, c.number, default_context.get());
		return result;
	}
}

