#include <stdio.h>
#include <stdlib.h>

#define FUNDLEN 1000

struct funds {
    char bank[FUNDLEN];
    double bankfund;
    char save[FUNDLEN];
    double savefund;
};

double sum(struct funds moolah) {
    return (moolah.bankfund + moolah.savefund);
}

int main(void){
    struct funds choi = {
        "Shinhan Bank",
        4032.27,
        "Choi's Savings and Check",
        8543.94
    };
    
    printf("Seongwoo has a total of $%.2f.\n", sum(choi));
    
    return 0;
}