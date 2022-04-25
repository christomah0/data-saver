CC=gcc
CFLAGS=-Wall -c
ICON=windres -J rc -O coff -i

all: main.o manip_data.o
	$(ICON) resource.rc -o resource.res
	$(CC) -O3 resource.res main.o manip_data.o -o dist/dataSaver.exe -s
	rm include/manip_data.h.gch resource.res

main.o: source/main.c
	$(CC) $(CFLAGS) source/main.c

manip_data.o: source/manip_data.c include/manip_data.h
	$(CC) $(CFLAGS) source/manip_data.c include/manip_data.h

clean:
	rm *.o *.res
