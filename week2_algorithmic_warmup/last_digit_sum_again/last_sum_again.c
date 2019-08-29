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

int main()
{
    unsigned long long n;
    unsigned long long m;

    scanf( "%lld %lld", &n, &m );

    n %= PISANO_MOD_10;
    m %= PISANO_MOD_10;

    buildPisanoMods();

    if( m < n )
        m += PISANO_MOD_10;

    unsigned long long res = 0;

    for( int i = n; i < m + 1; ++i )
    {
        res += tab[ i % PISANO_MOD_10 ];
    }

    printf( "%lld\n", res % 10 );
}
