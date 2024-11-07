#include <stdio.h>

void printArray( int* array, int len )
{
    for( int i = 0; i < len; i++ )
    {
        printf( "%d ", array[i] );
    }
    printf( "\n" );
}

void bubbleSort( int* array, int len )
{
    for( int i = 0; i < len; i++ )
    {
        for( int j = 0; j < len; j++ )
        {
            if( array[i] < array[j] )
            {
                int temp = array[i];
                array[i] = array[j];
                array[j] = temp;
            }
        }
    }
}

int main()
{
    int nums[] = { 4, 6, 1, 3, 2, 5 };
    int len = sizeof( nums ) / sizeof( int );

    printArray( nums, len );
    bubbleSort( nums, len );
    printArray( nums, len );

    return 0;
}