#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int main()
{
    int target = 100;

    printf( "%d\n", 1 );
    printf( "%d\n", 2 );
    for( int num = 3; num <= target; num++ )
    {
        bool prime = true;
        for( int i = num - 1; i >= 2; i-- )
        {
            if( num % i == 0 )
            {
                prime = false;
                continue;
            }
        }
        if( prime )
        {
            printf( "%d\n", num );
        }
    }

    return 0;
}
