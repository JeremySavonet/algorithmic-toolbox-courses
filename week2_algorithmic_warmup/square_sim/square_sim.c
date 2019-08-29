// Author: J.savonet
// Version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define PISANO_MOD_10 60

unsigned long long tab[ PISANO_MOD_10 ];

void buildPisanoMods()
{
    tab[ 0 ] = 0;
    tab[ 1 ] =  1;
    for( int i = 2; i < PISANO_MOD_10 - 2; ++i )
    {
        tab[ i ] = ( tab[ i - 1 ] + tab[ i - 2 ] ) % 10;
    }
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

int main()
{
    unsigned long long n;

    sqcanf( "%lld", &n );

    n %= PISANO_MOD_10;

    buildPisanoMods();

    unsigned long long res = 0;

    res = fibonacci_fast( n ) % 10 * fibonacci_fast( n + 1 ) % 10;
    //for( int i = 0; i < n - 1; ++i )
    //{
    //    res += ( tab[ i % PISANO_MOD_10 ] * tab[ ( i + 1 ) % 10 ] );
    //}

    printf( "%lld\n", res % 10 );
}
