#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <sys/time.h>

int gvar = 100;

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
    enum NUMS { ONE = 1, TWO, THREE };

    enum NUMS num = TWO;

    printf( "=== p1 ===\n" );
    printf( "%d\n", num );

    printf( "gvar:%d\n", gvar );
    int gvar = 200;
    printf( "gvar:%d\n", gvar );
    {
        extern int gvar;
        printf( "gvar:%d\n", gvar );
        extern int gvar2; // declared here but defined in the foo.c file
        printf( "gvar2:%d\n", gvar2 );
    }

    uint32_t* ui32_v = (uint32_t*)0x01;
    printf( "*ui32_v:[%u][%d]\n", ui32_v, ui32_v);
    ui32_v = ui32_v + 1;
    printf( "*ui32_v:[%u][%d]\n", ui32_v, ui32_v);
    ui32_v++;
    printf( "*ui32_v:[%u][%d]\n", ui32_v, ui32_v);
}

int main2()
{
    int i = 10;
    int j = 20;

    printf( "=== p1 ===\n" );
    const int* p1 = (int*)0x1;
    printf( "%d\n", p1 );
    p1++;
    printf( "%d\n", p1 );
    //*p1 = 100;
    //printf( "%d\n", p1 );
    p1 = &i;
    printf( "%d %d\n", p1, *p1 );
    p1 = &j;
    printf( "%d %d\n", p1, *p1 );

    printf( "=== p2 ===\n" );
    int* const p2 = (int*)0x1;
    printf( "%d\n", p2 );
    //p2++;
    //printf( "%d\n", p2 );
    *p2 = 100;
    printf( "%d\n", p2 );
    //p2 = &i;
    //printf( "%d %d\n", p2, *p2 );
    //p2 = &j;
    //printf( "%d %d\n", p2, *p2 );
}

int main1()
{
    int i = 10;
    int j = 20;

    int* pi = (int*)0x1;
    printf( "%d\n", pi );
    pi++;
    printf( "%d\n", pi );
    *pi = 100;
    printf( "%d\n", pi );

    pi = &i;
    printf( "%d %d\n", pi, *pi );

    pi = &j;
    printf( "%d %d\n", pi, *pi );
}
