# A simple stack library

A simple implementation of a stack library. It uses [Unity](http://www.throwtheswitch.org/unity)
for unit testing. The stack uses void pointers to support all data types.

## Functionality

* [x] Create a new stack
* [x] Push an item on the stack
* [x] Pop an item from the stack
* [x] Duplicate the head of the stack
* [x] Peek at the head of the stack
* [x] Get the size of the stack

Of course, every function is unit tested when committed to the master branch.

## How to use this library

Create a new stack:
```c
#include <stdlib.h>
#include "stack.h"
  
int main(int argc, char *arv[])
{
    struct s_stack *stack = stack_alloc();
    free(stack);
}
```

Push and pop data on and off the stack:
```c
#include <stdlib.h>
#include <stdio.h>
#include "stack.h"
  
int main(int argc, char *arv[])
{
    struct s_stack *stack = stack_alloc();
    float some_data = 12.44445;
    // push data on the stack
    stack_push(stack, &some_data);
    // get data from the top of the stack and convert it to a float
    printf("item on the stack %f.2\n", (* (float *) stack_pop(stack)));
    free(stack);
}
```

Create a duplicate of the head:
```c
...
  
int main(int argc, char *arv[])
{
    struct s_stack *stack = stack_alloc();
    int data = 10;
    stack_push(stack, &data);
    stack_duplicate(stack);
    // remove all elements from the stack
    stack_free(stack);
    // still need to free the stack pointer itself
    free(stack);
}
```

Take a peek at the stack:
```c
...
  
int main(int argc, char *arv[])
{
    struct s_stack *stack = stack_alloc();
    char data = 'A';
    stack_push(stack, &data);
    printf("The stack contains: %c\n", (* (char *) stack_peek(stack)));
    // Stack should still have a size of 1;
    printf("The stack has a size of %d\n", stack_size(stack));
    stack_free(stack);
    free(stack);
}
```

## License

This library is provided under the MIT license.
