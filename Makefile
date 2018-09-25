all: mpdtest

mpdtest: main.o mpdecpp.o
	g++ -Wall -std=c++11 -O2 main.o mpdecpp.o -o mpdtest -lmpdec -lpthread

main.o: main.cpp include/mpdecpp.h
	g++ -Wall -std=c++11 -O2 -Iinclude -c main.cpp

mpdecpp.o: src/mpdecpp.cpp include/mpdecpp.h
	g++ -Wall -std=c++11 -O2 -Iinclude -c src/mpdecpp.cpp

clean:
	rm -rf *.o mpdtest
