.PHONY: all

all:
	g++ -std=c++11 main.cpp scanner.cpp automaton_lexer.cpp init_grammar.cpp -O2 -o lxq
