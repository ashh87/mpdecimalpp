#include "mpdecpp.hpp"

#include <memory>
#include <string>

#include <mpdecimal.h>

namespace mpdecpp
{
	thread_local static std::shared_ptr<mpd_context_t> default_context = DefaultContext();
	
	//local context manager
	
	//set_context
	void set_context(std::shared_ptr<mpd_context_t> new_context)
	{
		default_context = std::move(new_context);
	}
	
	std::shared_ptr<mpd_context_t> get_context()
	{
		return default_context;
	}
	
	//pre-defined contexts
	std::shared_ptr<mpd_context_t> DefaultContext()
	{
		auto tmp_context = std::make_shared<mpd_context_t>();
		mpd_defaultcontext(tmp_context.get());
		return tmp_context;
	}
	
	//number type class functions

	/////////////////////////
	// Constructors
	/////////////////////////

	//no assignment constructor
	mpd_c::mpd_c(nullptr_t nt)
	{
		number = mpd_new(default_context.get());
	}
	
	//normal constructors
	//normal, full constructors
	mpd_c::mpd_c(int32_t value, std::shared_ptr<mpd_context_t> context)
	{
		number = mpd_new(context.get());
		mpd_set_i32(number, value, context.get());
	}

	mpd_c::mpd_c(int64_t value, std::shared_ptr<mpd_context_t> context)
	{
		number = mpd_new(context.get());
		mpd_set_i64(number, value, context.get());
	}

	mpd_c::mpd_c(uint32_t value, std::shared_ptr<mpd_context_t> context)
	{
		number = mpd_new(context.get());
		mpd_set_u32(number, value, context.get());
	}

	mpd_c::mpd_c(uint64_t value, std::shared_ptr<mpd_context_t> context)
	{
		number = mpd_new(context.get());
		mpd_set_u64(number, value, context.get());
	}

	//constructors given a value
	mpd_c::mpd_c(int32_t value) : mpd_c(value, default_context) {}
	mpd_c::mpd_c(int64_t value) : mpd_c(value, default_context) {}
	mpd_c::mpd_c(uint32_t value) : mpd_c(value, default_context) {}
	mpd_c::mpd_c(uint64_t value) : mpd_c(value, default_context) {}

	//constructors given a context, default to 0
	mpd_c::mpd_c(std::shared_ptr<mpd_context_t> context) : mpd_c(0, context) {}

	//default values, no arguments
	mpd_c::mpd_c() : mpd_c(0, default_context) {}

	//copy constructor
    mpd_c::mpd_c(const mpd_c& other) : mpd_c(nullptr)
    {
		//is this function exception safe?
		mpd_copy(number, other.number,  default_context.get());
    }
	
	//move constructor
	mpd_c::mpd_c(mpd_c&& other)
	{
		this->number = other.number;
		other.number = 0; //C style
	}

	//copy/move assignment
    mpd_c& mpd_c::operator=(mpd_c other)
    {
		swap(*this, other);
		return *this;
    }

	void swap(mpd_c& first, mpd_c& second)
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
	const mpd_c mpd_c::operator+()
	{
		return mpd_c(*this);
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
	const mpd_c mpd_c::operator-()
	{
		mpd_c tmp(*this);
		mpd_minus(tmp.number, tmp.number, default_context.get());
		return tmp;
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

	std::ostream &operator<<(std::ostream &output, const mpd_c &D)
	{ //we want to change this to be more flexible
		std::string tosci(mpd_to_sci((D.number), 1));
		output << tosci;
		return output;
	}
}

