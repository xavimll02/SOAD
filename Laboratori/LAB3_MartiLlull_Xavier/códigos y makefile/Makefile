CFLAGS=-Wall -Wextra -pedantic -Werror -g

# To debug with valgrind:
#CFLAGS:=$(CFLAGS) -DVALGRIND

# To get debugging output
#CFLAGS:=$(CFLAGS) -DLF_DEBUG

PROGRAMS=basic-uc basic-sjlj example-Xavi example-Xavi1 example-uc example-sjlj example-clone example-asm
all: $(PROGRAMS)

clean:
	$(RM) *.o $(PROGRAMS) &> /dev/null || true
	
debug: clean
	make "CC=gcc -g -Wall -pedantic -DLF_DEBUG"

basic-uc: basic-uc.o
basic-sjlj: basic-sjlj.o

example-Xavi1: libfiber-sjlj.o example-Xavi1.o

	$(CC) $(LDFLAGS) libfiber-sjlj.o example-Xavi1.o -o example-Xavi1	
	
example-Xavi: libfiber-sjlj.o example-Xavi.o

	$(CC) $(LDFLAGS) libfiber-sjlj.o example-Xavi.o -o example-Xavi

example-uc: libfiber-uc.o example.o
	$(CC) $(LDFLAGS) libfiber-uc.o example.o -o example-uc

example-clone: libfiber-clone.o example.o
	$(CC) $(LDFLAGS) libfiber-clone.o example.o -o example-clone
	
example-sjlj: libfiber-sjlj.o example.o
	$(CC) $(LDFLAGS) libfiber-sjlj.o example.o -o example-sjlj

example-asm: libfiber-asm.o example.o
	$(CC) $(LDFLAGS) libfiber-asm.o example.o -o example-asm

libfiber-uc.o: libfiber.h
libfiber-clone.o: libfiber.h
libfiber-sjlj.o: libfiber.h
example-Xavi.o: libfiber.h
example.o: libfiber.h
