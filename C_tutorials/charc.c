#include <stdio.h>
#include <stdlib.h>

int main() {
    char input[10];
    char status[10];
    printf("Please enter your name: ");
    scanf("%s", input);
    printf("Hello, %s\n", input);
    printf("How are you today? ");
    scanf("%s", status);
    printf("Your status is: %s\n", status);
    
}