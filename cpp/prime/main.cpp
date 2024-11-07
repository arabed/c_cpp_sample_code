#include <stdio.h>
#include <stdlib.h>

int main( int argc, char* argv[] )
{
    int primeCnt = 0;
    int maxPrimeCnt = 100;
    int primeNums[maxPrimeCnt];

    bool isPrime = false;
    
    int cnt = 1;
    primeCnt = 1;
    primeNums[0] = 2;

    printf( "(%d)\'%d\' ", primeCnt, 2 );
    while( primeCnt < maxPrimeCnt )
    {
        cnt += 2;
        for( int j = 0; j < primeCnt; j++ )
        {
            if( cnt % primeNums[j] == 0 )
            {
                isPrime = false;
                break;
            }
            isPrime = true;
        }
        if( isPrime )
        {
            primeNums[primeCnt] = cnt;
            printf( "(%d)\'%d\' ", primeCnt, cnt );
            primeCnt++;
        }
    }

    printf( "\ndone.\n" );

    return 0;
}