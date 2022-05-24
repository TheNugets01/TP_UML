EXTFLAGS = -ansi -pedantic -Wall -std=c++11

all: main

MAP: EXTFLAGS += -DMAP
MAP: main

GETSET: EXTFLAGS += -DGETSET
GETSET: main

main : Utilisateur.o Position.o Attribut.o Mesure.o Services.o main.o 
		g++ -o main Utilisateur.o Position.o Attribut.o Mesure.o main.o Services.o Capteur.o$(EXTFLAGS)

Utilisateur.o : Utilisateur.cpp
		g++ -c -g $(EXTFLAGS) Utilisateur.cpp

Position.o : Position.cpp
		g++ -c -g $(EXTFLAGS) Position.cpp

Attribut.o : Attribut.cpp
		g++ -c -g $(EXTFLAGS) Attribut.cpp

Mesure.o : Mesure.cpp
		g++ -c -g $(EXTFLAGS) Mesure.cpp

Services.o : Services.cpp
		g++ -c -g $(EXTFLAGS) Services.cpp

Capteur.o : Capteur.cpp
		g++ -c -g $(EXTFLAGS) Capteur.cpp

main.o : main.cpp
		g++ -c -g $(EXTFLAGS) main.cpp
