all: create run

create: $(wildcard *.cpp) $(wildcard *.h)
	@g++ 								\
	src/*.cpp 								\
	-o main 							\
	-pedantic-errors -Wall -Weffc++ -Wextra -Wconversion -Wsign-conversion

run:
	@./main