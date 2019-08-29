// Author: J.savonet
// Version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

unsigned long long fibonacci_naive( unsigned long long n )
{
    if( n <= 1 )
        return n;

    return fibonacci_naive( n - 1 ) + fibonacci_naive( n - 2 );
}

unsigned long long fibonacci_fast( int n )
{
    unsigned long long tab[ n ];

    if( n == 0 )
        return 0;

    if( n == 1 )
        return 1;

    tab[ 0 ] = 0;
    tab[ 1 ] = 1;

    for( int i = 2; i <= n; ++i )
    {
        //printf( "%lld %lld\r\n", tab[ i - 1 ], tab[ i - 2 ] );
        tab[ i ] = tab[ i - 1 ] + tab[ i - 2 ];
        //printf( "result = %lld\r\n", tab[ i ] );
    }

    return tab[ n ];
}

void test_solution()
{
    assert( fibonacci_fast( 3 ) == 2 );
    assert( fibonacci_fast( 10 ) == 55 );
    for( int n = 0; n < 20; ++n )
    {
        //printf( "FIB FAST: %lld", fibonacci_fast( n ) );
        assert( fibonacci_fast( n ) == fibonacci_naive( n ) );
    }
}

int main()
{
    int n = 0;
    scanf( "%d", &n );

    printf( "%lld\n", fibonacci_fast( n ) );

    //test_solution();
    return 0;
}
