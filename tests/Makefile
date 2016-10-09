CC = clang
CFLAGS = -std=c99 -Wall -Werror -Wpedantic -g
USANITIZE = -fsanitize=undefined
MSANITIZE = -fsanitize=address -fno-omit-frame-pointer

.PHONY: clean
.PHONY: test

all: clean build test

build: test_stack.o
	$(CC) $(CFLAGS) $(USANITIZE) stack.o test_stack.o unity.o -o test_stack

test_stack.o: unity.o
	$(CC) $(CFLAGS) $(USANITIZE) -c test_stack.c

unity.o: stack.o
	$(CC) $(CFLAGS) $(USANITIZE) -c unity.c

stack.o: ../src/stack.c
	$(CC) $(CFLAGS) $(USANITIZE) -c ../src/stack.h ../src/stack.c

clean:
	rm -f stack stack.o test_stack.o unity.o

test:
	./test_stack

// TODO(j0holo): Restructure folders to inlcude bin/
