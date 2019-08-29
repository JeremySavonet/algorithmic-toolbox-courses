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

unsigned long long gcd_naive( unsigned long long a, unsigned long long b )
{
    unsigned long long gcd = 1;

    for( unsigned long long i = 2; i < a + b; ++i )
    {
        if( a % i == 0 && b % i == 0 )
        {
            gcd = i;
        }
    }

    return gcd;
}

void test_solution()
{
    srand(time(NULL));   // Initialization, should only be called once.

    assert( gcd_naive( 18, 35 ) == 1 );
    assert( gcd_naive( 28851538, 1183019 ) == 17657 );

    for( int n = 0; n < 20; ++n )
    {
        unsigned long long rand1 = rand() % 100000;
        unsigned long long rand2 = rand() % 100000;
        assert( gcd_fast( rand1, rand2 ) == gcd_naive( rand1, rand2 ) );
    }

    printf( "SUCCESS\r\n" );
}

int main()
{
    unsigned long long a = 0;
    unsigned long long b = 0;
    scanf( "%lld %lld", &a, &b );

    printf( "%lld\n", gcd_fast( a, b ) );

    //test_solution();
    return 0;
}
