#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main()
{
    char* str = {"This is a sentence."};

    printf( "%s\n", str );
    printf( "%20.5s\n", str );
    printf( "%-20.5s\n", str );

    int i = 123456;
    printf( "%d\n", i );
    printf( "%08d\n", i );
    printf( "%*d\n", 8, i );

    return 0;
}