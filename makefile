#
# This is an example Makefile for a countwords program.  This
# program uses both the scanner module and a counter module.
# Typing 'make' or 'make count' will create the executable file.
#

# define some Makefile variables for the compiler and compiler flags
# to use Makefile variables later in the Makefile: $()
#
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
#
# for C++ define  CC = g++
CC = gcc
CFLAGS  = -g #-Wall

# typing 'make' will invoke the first target entry in the file 
# (in this case the default target entry)
# you can name this target entry anything, but "default" or "all"
# are the most commonly used names by convention
#
default: main

# To create the executable file count we need the object files
# countwords.o, counter.o, and scanner.o:
#
main:  main.o duom.o laivai.o lentele.o vartotojas.o
	$(CC) $(CFLAGS) -o main main.o duom.o laivai.o lentele.o vartotojas.o

unit_test: unit_test.o duom.o vartotojas.o
	$(CC) $(CFLAGS) -o unit_test unit_test.o duom.o vartotojas.o

duom.o:  duom.c models.h duom.h 
	$(CC) $(CFLAGS) -c duom.c

vartotojas.o:  vartotojas.c models.h vartotojas.h 
	$(CC) $(CFLAGS) -c vartotojas.c

laivai.o: laivai.c models.h laivai.h
	$(CC) $(CFLAGS) -c laivai.c

lentele.o: lentele.c models.h lentele.h
	$(CC) $(CFLAGS) -c lentele.c

unit_test.o: unit_test.c duom.h unit_test.h vartotojas.h
	$(CC) $(CFLAGS) -c unit_test.c

main.o:  main.c duom.h lentele.h laivai.h
	$(CC) $(CFLAGS) -c main.c

# To start over from scratch, type 'make clean'.  This
# removes the executable file, as well as old .o object
# files and *~ backup files:
#
clean: 
	$(RM) count *.o *~
