#include <iostream>
#include <thread>

#include "mpdecpp.hpp"

void foo() 
{
	mpdecpp::mpd_c a;
	auto ctx = mpdecpp::get_context();
	a += 44;
	std::cout << "foo: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	std::cout << "threaded: " << a << std::endl;
}

int main()
{
	//mpdecpp::set_context(mpdecpp::DefaultContext());
	mpdecpp::mpd_c a, b, c;
	b += 6;
	a += 2;
	c = +b;
	std::cout << "Hi: " << a << ", " << b << "... " << c << std::endl;
	
	auto ctx = mpdecpp::get_context();
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	
	std::thread first (foo);
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	std::thread second (foo);
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	
	first.join();
	second.join();
	return 0;
}
