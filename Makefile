CC 		= g++

all : caballos hipodromo

hipodromo : hipodromo.c funciones.h definiciones.h funciones.o
	cc -o hipodromo hipodromo.c funciones.o

caballos : caballos.c funciones.h definiciones.h funciones.o
	cc -o caballos caballos.c funciones.o -pthread

funciones.o : funciones.c funciones.h
	cc -c funciones.c

clean:                                            
	rm -rf *o caballos hipodromo *~
