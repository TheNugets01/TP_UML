EXTFLAGS = -ansi -pedantic -Wall -std=c++11

all: main

MAP: EXTFLAGS += -DMAP
MAP: main

GETSET: EXTFLAGS += -DGETSET
GETSET: main

main : Utilisateur.o Position.o main.o 
		g++ -o main Utilisateur.o Position.o main.o $(EXTFLAGS)

Utilisateur.o : Utilisateur.cpp
		g++ -c -g $(EXTFLAGS) Utilisateur.cpp

Position.o : Position.cpp
		g++ -c -g $(EXTFLAGS) Position.cpp

main.o : main.cpp
		g++ -c -g $(EXTFLAGS) main.cpp
