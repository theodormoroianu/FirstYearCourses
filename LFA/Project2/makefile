all:
	g++ -std=c++11 -O0 -g -fsanitize=address,undefined,signed-integer-overflow -Wall -Wextra Project2.cpp DFA.hpp DFA.cpp
	./a.out
fast:
	g++ -std=c++11 -O2 Project2.cpp DFA.hpp DFA.cpp
	./a.out