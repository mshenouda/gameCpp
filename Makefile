# the compiler: g++ for C++
CXX=g++
CPPFLAGS=-I -g
DEPS=game.h
all:  main.out
main.out: game.o implement.o
	$(CXX) -o main.out *.o 
implement.o:  game.cpp  game.h
	$(CXX) -c $(CPPFLAGS) implement.cpp
game.o: game.h
	$(CXX) -c $(CPPFLAGS) game.cpp
clean:
	rm  -f  *.o main.out