#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int i = 50;

void foo()
{
    extern int i;
    i = 20;
}

int main( int argc, char* argv[] )
{
    extern int i;
    i = 10;
    printf( "%d\n", i );
    foo();
    printf( "%d\n", i );

    long double *num;
    long double numval = 10;
    num = &numval;

    printf( "%ld %Lf\n", num, *num );
    num++;
    printf( "%ld %Lf\n", num, *num );

    float fl = 1234;
    printf( "%f\n", fl );

    bool bl = true;
    printf( "%d\n", bl );

    for( unsigned char cidx = 0; cidx != 0xff; cidx++ )
    {
        printf( "(%d) %c %x %02X\n", cidx, cidx, cidx, cidx );
    }

    return 0;
}