proj_1: proj_1.o timer.o tool.o
	g++ -o proj_1 timer.o proj_1.o tool.o -lncurses

timer.o: timer.h timer.cpp
	g++ -c timer.cpp

tool.o: tool.h tool.cpp
	g++ -c tool.cpp

proj_1.o: tool.h timer.h proj_1.cpp
	g++ -c proj_1.cpp

clean:
	rm tool timer *.o

