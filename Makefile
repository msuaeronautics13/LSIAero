CC=g++
CFLAGS=-std=gnu++11 -O2 -Wall -I./include
LDFLAGS=
OBJECTS = main.o ReadMesh.o ComputeNormals.o ModNewt.o OutputToVTK.o

ThermalROM: $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(OBJECTS) -o LSIAero

%.o : %.cpp
	$(CC) $(CFLAGS) -c $<

clean:
	rm *.o

install:
	cp LSIAero ~/bin
