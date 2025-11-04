CC=gcc
MFLAGS=-lm
TFLAGS=-pthread

#use only one line (1st for demonstration or benchmarking, 2nd for profiling)
CFLAGS=-Wall -O2
#CFLAGS=-Wall -O0 -g

#use only one line, depending on the versions to be compiled
all: nbody-serial.exe
#all: nbody-serial.exe nbody-serial-gui.exe
#all: nbody-serial.exe nbody-threads.exe

#uncomment to compile the non-GUI serial version
nbody-serial.exe: nbody-serial.c
	$(CC) $(CFLAGS) nbody-serial.c $(MFLAGS) -o nbody-serial.exe 
	
#uncomment to compile the GUI serial version
nbody-serial-gui.exe: nbody-serial-gui.c
	$(CC) $(CFLAGS) nbody-serial-gui.c $(MFLAGS) -lSDL_bgi -lSDL2 -o nbody-serial-gui.exe
	
#uncomment to compile the non-GUI Pthreads version
#nbody-threads.exe: nbody-threads.c
#	$(CC) $(CFLAGS) nbody-threads.c $(MFLAGS) $(TFLAGS) -o nbody-threads.exe

clean:
	rm -rf *.exe *.o a.out *.er
