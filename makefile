EXTFLAGS = -ansi -pedantic -Wall -std=c++11

all: main

MAP: EXTFLAGS += -DMAP
MAP: main

GETSET: EXTFLAGS += -DGETSET
GETSET: main

main : Utilisateur.o Position.o Attribut.o Mesure.o Services.o ServiceInit.o main.o Capteur.o Test.o Timer.o
		g++ -o main Utilisateur.o Position.o Attribut.o Mesure.o main.o Services.o ServiceInit.o Capteur.o Test.o Timer.o  $(EXTFLAGS)

Utilisateur.o : ./models/Utilisateur.cpp
		g++ -c -g $(EXTFLAGS) ./models/Utilisateur.cpp

Position.o : ./models/Position.cpp
		g++ -c -g $(EXTFLAGS) ./models/Position.cpp

Attribut.o : ./models/Attribut.cpp
		g++ -c -g $(EXTFLAGS) ./models/Attribut.cpp

Mesure.o : ./models/Mesure.cpp
		g++ -c -g $(EXTFLAGS) ./models/Mesure.cpp

Services.o : ./models/Services.cpp
		g++ -c -g $(EXTFLAGS) ./models/Services.cpp

ServiceInit.o : ./controller/ServiceInit.cpp
		g++ -c -g $(EXTFLAGS) ./controller/ServiceInit.cpp

Capteur.o : ./models/Capteur.cpp
		g++ -c -g $(EXTFLAGS) ./models/Capteur.cpp

Test.o : ./tests/Test.cpp
		g++ -c -g $(EXTFLAGS) ./tests/Test.cpp

Timer.o : ./util/Timer.cpp
		g++ -c -g $(EXTFLAGS) ./util/Timer.cpp

main.o : ./view/main.cpp
		g++ -c -g $(EXTFLAGS) ./view/main.cpp

