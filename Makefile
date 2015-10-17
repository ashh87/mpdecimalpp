all: mpdtest

mpdtest: main.o mpdecpp.o
	g++ -Wall -std=c++11 -O2 main.o mpdecpp.o -o mpdtest -lmpdec -lpthread

main.o: main.cpp mpdecpp.hpp
	g++ -Wall -std=c++11 -O2 -c main.cpp

mpdecpp.o: mpdecpp.cpp mpdecpp.hpp
	g++ -Wall -std=c++11 -O2 -c mpdecpp.cpp

clean:
	rm -rf *.o mpdtest
