CC=gcc
CFLAGS=-Wall
#OPT=
OPT=-O0
#DEBUG=
DEBUG=-g
PROFILE=
#PROFILE=-pg
LFLAGS=-pthread -lm
MFLAGS=-mcmodel=medium

EXECUTABLES = $(patsubst %.c,%.exe,$(wildcard *.c))

all: $(EXECUTABLES)

%.exe: %.c
	$(CC) $(CFLAGS) $(OPT) $(DEBUG) $(PROFILE) $< -o $@ $(LFLAGS) $(MFLAGS) 

clean:
	rm -rf *.exe *.o test*.er a.out
