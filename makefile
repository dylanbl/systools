CFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude 

ALL = bin/systools

all: $(ALL)

clean: 
	rm -f obj/* bin/*

obj/file_data.o: lib/file_data.cpp lib/file_data.hpp
	g++ $(CFLAGS) -c -o obj/file_data.o lib/file_data.cpp

obj/io.o : lib/io.cpp lib/io.hpp lib/file_data.cpp lib/file_data.hpp
	g++ $(CFLAGS) -c -o obj/io.o lib/io.cpp

obj/tools.o : src/tools.cpp lib/io.hpp 
	g++ $(CFLAGS) -c -o obj/tools.o src/tools.cpp

bin/systools: src/systools.cpp obj/io.o obj/tools.o obj/file_data.o lib/cxxopts.hpp
	g++ $(CFLAGS) -o bin/systools src/systools.cpp obj/tools.o obj/io.o obj/file_data.o
