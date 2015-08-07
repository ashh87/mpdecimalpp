#include <iostream>

#include "mpdecpp.hpp"

int main()
{
	mpdecpp::set_context(mpdecpp::DefaultContext());
	mpdecpp::mpd_c a;
	std::cout << "Hi" << std::endl;
	return 0;
}
