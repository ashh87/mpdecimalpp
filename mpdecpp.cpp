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

	/////////////////////////
	// Constructors
	/////////////////////////

	//normal constructors
	mpd_c::mpd_c(std::shared_ptr<mpd_context_t> context)
	{
		number = mpd_new(context.get());
		//use quiet version?
		//init to 0
		mpd_set_i32(number, 0, context.get());
	}

	mpd_c::mpd_c() : mpd_c(default_context) {}

	//copy constructor
    mpd_c::mpd_c(const mpd_c& other)
    {
        number = mpd_new(default_context.get());
		//TODO: copy and swap
		mpd_copy(number, other.number,  default_context.get());
    }

	//copy assignment
    mpd_c& mpd_c::operator=(const mpd_c& other)
    {
		//TODO: copy and swap
		number = mpd_new(default_context.get());
		mpd_copy(number, other.number,  default_context.get());
		return *this;
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

