#include <stdio.h>

void isPrime(int a){
    for (int i = 2; i < a /2; i++){
        if (a % i == 0){
            printf("Number is not prime \n");
            return;
        }
    }
    printf("Number is Prime \n");
}

int main(){
    int a;
    scanf("%d", &a);
    isPrime(a);
    return 0;
}