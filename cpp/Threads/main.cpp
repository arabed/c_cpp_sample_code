#include <stdio.h>
#include <stdlib.h>

int fibonacci( int num )
{
    if( num == 0 || num == 1 )
    {
        return 1;
    }
    else
    {
        return fibonacci( num - 1 ) + fibonacci( num - 2 );
    }
}

int main( int argc, char* argv[] )
{
    int maxNum = 21;
    if( argc > 1 )
    {
        maxNum = atoi( argv[1] );
    }
    printf( "\n" );
    for( int num = 0; num < maxNum; num++ )
    {
        int fiboNum = fibonacci( num );
        printf( "%d ", fiboNum );
    }
    printf( "\n\n" );

    return 0;
}