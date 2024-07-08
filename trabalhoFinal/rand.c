#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main(){

    srand(time(NULL));
    int a;
    a = rand() % 4;
    printf("%d", a);

    if(0.5 % 1 == 0){
        printf("pse ne");
    }

    return 0;
}
