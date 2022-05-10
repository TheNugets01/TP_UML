EXTFLAGS = -ansi -pedantic -Wall -std=c++11

all: main

MAP: EXTFLAGS += -DMAP
MAP: main

GETSET: EXTFLAGS += -DGETSET
GETSET: main

main : Utilisateur.o main.o 
		g++ -o main Utilisateur.o main.o $(EXTFLAGS)

Utilisateur.o : Utilisateur.cpp
		g++ -c -g $(EXTFLAGS) Utilisateur.cpp

main.o : main.cpp
		g++ -c -g $(EXTFLAGS) main.cpp
