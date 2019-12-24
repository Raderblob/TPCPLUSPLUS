
CC = g++
DEBUG=yes
ifeq ($(DEBUG),yes)
	CFLAGS=-Wall -Werror -ansi -pedantic -std=c++11 -g -D MAP
	LDFLAGS=
else
	CFLAGS=-Wall -Werror -ansi -pedantic -std=c++11
	LDFLAGS=
endif
EXEC = TestMain
SRC= TP3.cpp Catalogue.cpp ComplexeTrip.cpp Town.cpp Trip.cpp
OBJ= $(SRC:.cpp=.o)
HEDR = $(SRC:.cpp=.h)


all: $(EXEC)
ifeq ($(DEBUG),yes)
	@echo "Génération en mode debug"
else
	@echo "Génération en mode release"
endif


$(EXEC): $(OBJ)
	g++ -o $@ $^ $(LDFLAGS)

TP3.o: TP3.cpp
	g++ -c $< $(CFLAGS)

%.o: %.cpp %.h
	g++ -c $< $(CFLAGS)

.PHONY = clean

clean:
	rm -rf *.o
