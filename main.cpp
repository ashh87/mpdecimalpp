#include <iostream>
#include <thread>
#include <string>
#include <cmath>
#include <vector>

#include "mpdecpp.h"

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
	std::cout << "again: " << b << ", " << mpdecpp::SCI << b << ", " << mpdecpp::eng << b << ", " << mpdecpp::ENG << b << mpdecpp::sci << std::endl;
	
	auto ctx = mpdecpp::get_context();
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	
	std::thread first (foo);
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	std::thread second (foo);
	std::cout << "main: (addr)" << ctx.get() << ", (usecount)" << ctx.use_count() << std::endl;
	
	first.join();
	second.join();
	
	float fla, flb, flc;
	fla = 2.0;
	flb = 4.0;
	flc = 8.0;
	std::cout << "fla: " << fla << " flb: " << flb << " flc: " << flc << std::endl;
	using std::pow;
	using std::exp;
	using std::log;
	using std::sqrt;
	flc = pow(flb, fla);
	fla = exp(5.0);
	flb = log(fla);
	std::cout << "fla: " << fla << " flb: " << flb << " flc: " << flc << std::endl;
	
	a = 2;
	b = 4;
	c = 8;
	std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
	c = pow(b, a);
	a = exp((mpdecpp::mpd_c)5);
	b = log(a);
	std::cout << "a: " << a << " b: " << b << " c: " << c << std::endl;
	
	a = 2;
	std::cout << "a: " << sqrt(a) << std::endl;
	
	fla = 1.2;
	flb = 3.3;
	flc = 7;
	a = "1.2";
	b = "3.3";
	c = 7;
	
	std::cout << "fma: " << fma(fla, flb, flc) << ", " << fma(a, b, c) << std::endl;
	
	std::cout << "create vec" << std::endl;
	std::vector<mpdecpp::mpd_c> vec;
	std::cout << "push a" << std::endl;
	vec.push_back(a);
	std::cout << "push b" << std::endl;
	vec.push_back(b);
	return 0;
}
