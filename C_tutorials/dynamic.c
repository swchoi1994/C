#include <stdio.h>
#include <stdlib.h>
/* 
the simplest standard library function that allocates memory at runtime
is called malloc()
- need to include the stdlib.h header file
- you specify the number of bytes of memory that you want allocated
as the argument
- returns the address of the first byte of memory that is allocated
- because you get an address returned, a pointer is the only place to 
put it

int *pNumber = (int*)malloc(100);

-------------------------------------------------------------------
the calloc() function offers a couple of advantages over malloc()
- it allocates memory as a number of elements of a give size
- it initializes the memory that is allocated so that all bytes are 
zero.


calloc() function requires two argument values
- number of data items for which space is required
- size of each data item

int *pNumber = (int*)calloc(75, sizeof(int));

the return value wil be NULL if it was not possible to allocate the 
memory requested
- very similar to using malloc(), but the big plus is that you know the
memory are will be initialized to 0 

-------------------------------------------------------------------
the realloc() function enables you to reuse or extend memory that you
previosuly allocated using malloc() or calloc()

expects two argument values
- a pointer containing an address that was previously returned by a call to
malloc(), calloc()
- the size in bytes of the new memory that you want allocated

allocates the amount of memory you specify by the second argument
- transfers the contents of the previusly llocated memory referenced by 
the pointer that you supply as the first argument to the newly allocated 
memory
- returns a void* pointer to the new memory or NULL if the operation fails
for some reason. 


*/ 

int main() {
    int size;
    char *text = NULL;
    char *str;

    printf("Enter limit of the text: \n");
    scanf("%d", &size);

    text = (char *) malloc(size * sizeof(char));

    if(text != NULL) {
        printf("Enter some text: \n");
        scanf(" ");
        gets(text);

        printf("Inputted text is: %s\n", text);
    }

    free(text);
    text = NULL;
    
    // Creates 15 bytes 
    str = (char *) malloc(15);
    strcpy(str, "jason");
    printf("String = %s, Address = %u\n", str, str);

    // Re allocates extra 10 bytes; in total, 25 bytes
    str = (char *) realloc(str, 25);
    strcat(str, ".com");
    printf("String = %s, Address =%u\n", str, str);

    free(str);

    return 0;
}

/*
avoid allocating lots of small amounts of memory
- allocating memory on the heap carries some overhead with it 
- allocating many small blocks of memory will carry much more
overhead than allocating fewer larger blocks.

only hang on to the memory as long as you need it 
- as soon as you are finished with a block of memory on the heap, 
release the memory

always ensure that you provide for releasing memory that you have allocated
-deicde where in your code you will release the memory when you write
the code that allocates it. 
*/