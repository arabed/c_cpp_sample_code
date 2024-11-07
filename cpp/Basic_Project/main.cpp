#include <stdio.h>

void print_nums( int* nums, size_t nums_size )
{
    printf( "\n" );
    for( size_t i = 0; i < nums_size; i++ )
    {
        printf( "%d ", *(nums + i) );
    }
    printf( "\n" );
}

int main( void )
{
    int nums[] = {4, 6, 9, 0, 1, 3, 2, -1, 23, -99, 4};
    size_t nums_size = sizeof( nums ) / sizeof( int );
   
    print_nums( nums, nums_size );

    for( size_t i = 0; i < nums_size / 2; i++ )
    {
        int tmp_num = nums[i];
        nums[i] = nums[nums_size - 1 - i];
        nums[nums_size - 1 - i] = tmp_num;
    }

    print_nums( nums, nums_size );

    return 0;
}