#include <iostream>
#include <thread>
#include <string>

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
	b = 5;
	a = 2;
	b /= 20000000000;
	c = !b;
	a = !c;
	{
		mpdecpp::mpd_localcontext localcontext(mpdecpp::BasicContext());
	}
	std::cout << "Hi: " << a << ", " << b << "... " << c << "... " << (c <= b) << "... " << (c <= c) << "... " << (c <= a) << std::endl;
	
	std::cout << mpdecpp::sci << b << ", " << mpdecpp::SCI << b << ", " << mpdecpp::eng << b << ", " << mpdecpp::ENG << b << std::endl;
	std::cout << "again: " << b << ", " << mpdecpp::SCI << b << ", " << mpdecpp::eng << b << ", " << mpdecpp::ENG << b << std::endl;
	
	auto ctx = mpdecpp::get_context();
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	
	std::thread first (foo);
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	std::thread second (foo);
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	
	first.join();
	second.join();
	
	std::cin >> c >> a;
	std::cout << "new c: " << c << std::endl;
	std::cout << "new a: " << a << std::endl;
	return 0;
}
