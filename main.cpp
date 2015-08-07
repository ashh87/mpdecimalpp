#include <iostream>

#include "mpdecpp.hpp"

int main()
{
	mpdecpp::set_context(mpdecpp::DefaultContext());
	mpdecpp::mpd_c a, b;
	b += 1;
	a += 2;
	a += b;
	std::cout << "Hi: " << a << ", " << b << std::endl;
	return 0;
}
