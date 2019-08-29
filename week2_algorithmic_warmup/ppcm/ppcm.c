// Author: J.savonet
// Version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long gcd_fast( unsigned long long a, unsigned long long b )
{
    // corner case first
    if( b == 0 )
        return a;

    unsigned long long aPrime = a % b;

    return gcd_fast( b, aPrime );
}

unsigned long long ppcm_naive( unsigned long long a, unsigned long long b )
{
    unsigned long long ppcm = 1;

    for( unsigned long long i = 1; i <= (a * b); ++i )
    {
        if( i % a == 0 && i % b == 0 )
        {
            return i;
        }
    }

    return a * b;
}

unsigned long long ppcm_fast( unsigned long long a, unsigned long long b )
{
    return (a * b) / gcd_fast( a, b );
}

void test_solution()
{
    srand( time( NULL ) );   // Initialization, should only be called once.

    assert( ppcm_fast( 6, 8 ) == 24 );
    assert( ppcm_fast( 761457, 614573 ) == 467970912861 );

    for( int n = 0; n < 20; ++n )
    {
        unsigned long long rand1 = rand() % 100000;
        unsigned long long rand2 = rand() % 100000;
        assert( ppcm_fast( rand1, rand2 ) == ppcm_naive( rand1, rand2 ) );
    }

    printf( "SUCCESS\r\n" );
}

int main()
{
    unsigned long long a = 0;
    unsigned long long b = 0;
    scanf( "%lld %lld", &a, &b );

    printf( "%lld\n", ppcm_fast( a, b ) );

    //test_solution();
    return 0;
}
