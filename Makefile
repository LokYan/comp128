LIB_OBJ=libcomp128.o
MAIN_OBJ=main.o

CC=gcc
CFLAGS=-I. -L.

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main: $(MAIN_OBJ)
	$(CC) $(CFLAGS) $^ -lcomp128 -o $@ 

lib: $(LIB_OBJ)
	ar rcs libcomp128.a libcomp128.o

clean:
	rm -f *.o
	rm -f main

clean-all:
	rm -f libcomp128.a
	rm -f *.o
	rm -f main
