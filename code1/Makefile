
OBJS = Main.o Graphs.o Union_Find.o Tests.o Kruskal.o
CC = g++
DEBUG = -g
CFLAGS = -Wall -c -std=c++11 -Ofast $(DEBUG)
LFLAGS = -Wall $(DEBUG)

all: randmst

randmst : $(OBJS)
	$(CC) $(LFLAGS) $(OBJS) -o randmst

Main.o : Main.hpp Union_Find.hpp Graphs.hpp Tests.hpp Kruskal.hpp
	$(CC) $(CFLAGS) Main.cpp

Graphs.o : Graphs.hpp Union_Find.hpp
	$(CC) $(CFLAGS) Graphs.cpp

Union_Find.o : Union_Find.hpp Graphs.hpp
	$(CC) $(CFLAGS) Union_Find.cpp

Tests.o : Tests.hpp Graphs.hpp Union_Find.hpp Kruskal.hpp
	$(CC) $(CFLAGS) Tests.cpp

Kruskal.o : Kruskal.hpp Graphs.hpp Union_Find.hpp
	$(CC) $(CFLAGS) Kruskal.cpp

clean:
	rm ./*.o
