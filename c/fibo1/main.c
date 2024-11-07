#include <stdio.h>

int main()
{
    int max_seq = 60;

    long long int last_last_num = 0;
    long long int last_num = 1;
    long long int num = 0;
    float ratio = 0.0;

    for( int i = 0; i < max_seq; i++ )
    {
        num = last_last_num + last_num;
        printf( "(%lld) %lld [%f]\n", i, num, ratio );
        last_last_num = last_num;
        last_num = num;
        ratio = (float)last_num / (float)last_last_num;
    }
    
    return 0;
}