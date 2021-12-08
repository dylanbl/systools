CFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude 

ALL = bin/pline

all: $(ALL)

clean: 
	rm -f obj/* bin/*

obj/io.o : src/io.cpp include/io.hpp
	g++ $(CFLAGS) -c -o obj/io.o src/io.cpp 

obj/main.o : src/main.cpp include/io.hpp 
	g++ $(CFLAGS) -c -o obj/main.o src/main.cpp

bin/pline: obj/io.o obj/main.o 
	g++ $(CFLAGS) -o bin/pline obj/main.o obj/io.o 
