CC = gcc -O

all: phases

clean:
	rm -f phases a.out core *.o

phases: phases.o moonphase.o jd.o misc.o
	$(CC) -o $@ phases.o moonphase.o jd.o misc.o -lm

phases.o: moon.h 
moonphase.o: moon.h 
jd.o: jd.h 
misc.o: moon.h 
