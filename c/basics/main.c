#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

struct integers
{
    uint32_t ui32;
    uint64_t ui64;
};

typedef long long int bigInt;

struct moreIntegers
{
    uint32_t ui32;
    uint64_t ui64;
};

typedef struct moreIntegers moreInts;

union UnionType 
{
    uint32_t ui32;
    uint64_t ui64;
    char* string;
};

enum States
{
    IDLE = 0,
    WORKING,
    RESTING
};

int main()
{
    int i = 1;
    printf( "%d %d %d\n", ++i, i++, i );
    
    struct integers *ints = (struct integers *)0x01;
    printf( "%d\n", ints );
    ints++;
    printf( "%d\n", ints );

    bigInt* bInt;
    printf( "%d\n", bInt );
    bInt++;
    printf( "%d\n", bInt );
    
    moreInts* pMoreInts;
    printf( "%d\n", pMoreInts );
    pMoreInts++;
    printf( "%d\n", pMoreInts );

    union UnionType unionType;
    unionType.string = "ABC";
    printf( "%lld %s\n", unionType.ui64, unionType.string );

    enum States myState = IDLE;
    printf( "IDLE:%d\n", myState );

    volatile uint64_t a,b,c;
    register uint64_t aa,bb,cc;
    
    struct timeval tv;
    unsigned long time_then = 0;
    unsigned long time_elapsed = 0;

    a = 0; b = 0; c = 0;
    gettimeofday( &tv, NULL );
    time_then = 1000000 * tv.tv_sec + tv.tv_usec;
    for( size_t idx = 0; idx < 0x0fffffff; idx++ )
    {
        a++;
        if( a % 2 == 0 ) b++;
        else c++;
    }
    gettimeofday( &tv, NULL );
    time_elapsed = ( 1000000 * tv.tv_sec + tv.tv_usec ) - time_then;
    printf( "v:(%lu) %llu %llu %llu\n", time_elapsed, a, b, c );

    aa = 0; bb = 0; cc = 0;
    gettimeofday( &tv, NULL );
    time_then = 1000000 * tv.tv_sec + tv.tv_usec;
    for( size_t idx = 0; idx < 0x0fffffff; idx++ )
    {
        aa++;
        if( aa % 2 == 0 ) bb++;
        else cc++;
    }
    printf( "r:(%lld) %llu %llu %llu\n", time_elapsed, aa, bb, cc );

    return 0;
}
