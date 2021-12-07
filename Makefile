LDLIBS = -lpcap -liw -lpthread
CC = g++

all: airodump

airodump: main.o utils.o airodump.o Gheader/mac.o

main.o: main.cpp airodump.h utils.h

utils.o: utils.cpp utils.h airodump.h

airodump.o: airodump.cpp airodump.h Gheader/mac.h

clean: 
	rm -f *.o airodump Gheader/*.o