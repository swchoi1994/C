#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main() {
    int grades[10];
    int count = 10;
    long sum = 0;
    float average = 0.0f;
    
    printf("\nEnter the 10 grades:\n");

    int i;
    for (i = 0; i < count; ++i){
        printf("%2u> ", i + 1);
        scanf("%d", &grades[i]);
        sum += grades[i];
    }

    average = (float) sum/count;

    printf("\nAverage out of all grades: %.2f\n", average);
    return 0;
}