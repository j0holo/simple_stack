CC = clang
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -g

.PHONY: clean
.PHONY: test

all: clean build test

build: test_stack.o
	$(CC) $(CFLAGS) stack.o test_stack.o unity.o -o test_stack

test_stack.o: unity.o
	$(CC) $(CFLAGS) -c test_stack.c

unity.o: stack.o
	$(CC) $(CFLAGS) -c unity.c

stack.o: ../src/stack.c
	$(CC) $(CFLAGS) -c ../src/stack.h ../src/stack.c

clean:
	rm -f stack stack.o test_stack.o unity.o

test:
	./test_stack

// TODO(j0holo): Restructure folders to inlcude bin/
