#include <stdio.h>
#include <stdlib.h>

struct employee {
    char name[30];
    char date[15];
    float salary;
};

int main() {

    struct employee emp = {"Mike", "7/16/15", 76909.00f};

    printf("\nName: %s", emp.name);
    printf("\nDate: %s", emp.date);
    printf("\nSalary: %f\n", emp.salary);

    printf("\nEnter employee information: \n");
    printf("Name: \n");
    scanf("%s", emp.name);
    printf("")
    return 0;
}