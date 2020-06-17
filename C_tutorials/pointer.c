#include <stdio.h>
#include <stdlib.h>


int main (void) {
    int number = 0;
    int num = 150;
    int *pNum = NULL;
    int *pnumber = NULL;

    pNum = &num;

    printf("\n-----------Part One-----------\n");
    printf("num address is: %p\n", &num);
    printf("Value of pNum: %p\n", &pNum);
    printf("value of the pNum: %p\n", pNum);
    printf("value of what pNum is pointing to: %d\n", *pNum);
    printf("---------------------------------\n");

    number = 10;

    printf("\n-----------Part Two-----------\n");
    printf("\nNumber's address: %p\n", &number);
    printf("Number's value: %d\n\n", number);

    pnumber = &number;

    printf("pnumber's address: %p\t\n", (void*)&pnumber);
    printf("pnumber's size: %zd bytes\n", sizeof(pnumber));
    printf("pnumber's value: %p\n", pnumber);
    printf("value pointed to: %d\n\n", *pnumber);
    printf("---------------------------------\n");
    return 0;

}