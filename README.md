# A simple stack library

A simple implementation of a stack library. It uses [Unity](http://www.throwtheswitch.org/unity)
for unit testing. The stack uses void pointers to support all data types.

## Functionality

* Create a new stack
* Push an item on the stack
* Pop an item from the stack
* Duplicate the head of the stack
* Peek at the head of the stack
* Get the size of the stack

Of course, every function is unit tested when committed to the master branch.

Currently stack_alloc(unsigned long max_allocated)

## How to use this library

Create a new stack:
```c
#include <stdlib.h>
#include "stack.h"
  
int main(int argc, char *arv[])
{
    int max_stack_size = 10;
    struct s_stack *stack = stack_alloc(max_stack_size);
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
    struct s_stack *stack = stack_alloc(max_stack_size);
    float some_data = 12.44445;
    // push data on the stack, the NULL argument is a pointer to a function that can free allocated memory.
    // NULL suffices here becuase float is a simple non allocated data type.
    stack_push(stack, &some_data, NULL);
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
    struct s_stack *stack = stack_alloc(max_stack_size);
    int data = 10;
    stack_push(stack, &data, NULL);
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
    struct s_stack *stack = stack_alloc(max_stack_size);
    char data = 'A';
    stack_push(stack, &data, NULL);
    printf("The stack contains: %c\n", (* (char *) stack_peek(stack)));
    // Stack should still have a size of 1;
    printf("The stack has a size of %d\n", stack_size(stack));
    stack_free(stack);
    free(stack);
}
```

Putting data on the stack that is pointing to `malloc` 'ed memory, requires a little bit more work. Because the
stack_free(struct s_stack *) function doesn't free the memory of the data pointer, so you need to provide your
own function that is able to handle your allocated data.
```c
...
 
// A simple function that is required to free the allocated data on the stack.
void free_malloced_data(void *data)
{
    free(data);
}
  
int main(int argc, char *arv[])
{
    struct s_stack *stack = stack_alloc(max_stack_size);
    struct my_struct *my_struct = malloc(sizeof(struct mystruct));
    stack_push(stack, data, free_malloced_data);
    stack_free(stack);
    free(stack);
}
```

## License

This library is provided under the MIT license.
