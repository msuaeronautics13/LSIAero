CC=g++
CFLAGS=-std=gnu++11 -O2 -Wall -I./include 
LDFLAGS=-lgfortran
OBJECTS = main.o ReadMesh.o ComputeNormals.o ModNewt.o OutputToVTK.o Config.o

LSIAero: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o LSIAero

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o

install:
	cp LSIAero ~/bin
