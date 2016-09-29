# A simple stack library

A simple implementation of a stack library. It uses [Unity](http://www.throwtheswitch.org/unity)
for unit testing. The stack uses void pointers to support all data types.

## Functionality

* [x] Create a new stack
* [x] Push an item on the stack
* [x] Pop an item from the stack
* [ ] Duplicate the head of the stack
* [ ] Peek at the head of the stack
* [ ] Get the size of the stack

Of course, every function is unit tested when committed to the master branch.

## How to use

Create a new stack:
```c
#include <stdlib.h>
#include "stack.h"
  
int main(int argc, char *arv[])
{
    struct stack_t *stack = stack_new();
    free(stack);
}
```

## License

This library is provided under the MIT license.
