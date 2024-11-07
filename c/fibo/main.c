#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int fibo(int num) {
    if (num <= 1) 
        return 1;
    else
        return fibo(num - 1) + fibo(num - 2);
}

int main() {
    for (int num = 0; num < 10; num++)
        printf("(%d) %d\n", num, fibo(num));
    return 0;
}