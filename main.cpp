#include <iostream>

#include "mpdecpp.hpp"

int main()
{
	mpdecpp::set_context(mpdecpp::DefaultContext());
	mpdecpp::mpd_c a, b, c;
	b += 6;
	a += 2;
	c = b / a;
	std::cout << "Hi: " << a << ", " << b << "... " << c << std::endl;
	return 0;
}
