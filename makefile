CFLAGS ?= -std=c++11 -Wall -Wextra -Iinclude 

ALL = bin/systools

all: $(ALL)

clean: 
	rm -f obj/* bin/*

obj/tools.o : src/tools.cpp \
			  include/tools.hpp

	g++ $(CFLAGS) -c -o obj/tools.o src/tools.cpp

bin/systools: src/systools.cpp \
			  obj/tools.o \
			  lib/cxxopts.hpp 

	g++ $(CFLAGS) -o bin/systools src/systools.cpp obj/tools.o 
