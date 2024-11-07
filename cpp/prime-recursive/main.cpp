#include <stdio.h>
#include <stdlib.h>

bool isPrime( int num, int offset )
{
    if( offset == num )
    {
        return true;
    }
    else if( num % offset == 0 )
    {
        return false;
    }
    else
    {
        return isPrime( num, offset + 1 );
    }
}

int main()
{
    for( int num = 3; num < 20 ; num++ )
    {
        printf( "is (%d) prime? %s\n", num, isPrime( num, 2 ) ? "yes" : "no" );
    }
    printf( "\ndone.\n" );

    return 0;
}