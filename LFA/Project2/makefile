# MakeFile - Linux

SRC = main.cpp src/*.cpp
INC = inc/
flags_all = -std=c++11 -g -O0 -Wall -Wextra -fsanitize=address,undefined,signed-integer-overflow
flags_fast = -std=c++11 -O2

# make all creates sanitized binary, overflows, illegal memory accesses and undefined behaviour raise an exception
all:
	g++ $(flags_all) -I$(INC) $(SRC)

# make fast compiles with -O2 flag
fast: $(sources)
	g++ $(flags_fast) -I$(INC) $(SRC)
	
# removes a.out file
clean:
	rm a.out
