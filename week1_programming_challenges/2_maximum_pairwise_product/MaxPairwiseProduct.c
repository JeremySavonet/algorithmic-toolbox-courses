#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long maxPairwiseProduct( int size, unsigned long long* numbers )
{
    // Special case
    if( size == 2 )
    {
        return numbers[ 0 ] * numbers[ 1 ];
    }

    unsigned long long max1 = 0;
    unsigned long long max2 = 0;
    int index = 0;

    for( int i = 0; i < size; ++i )
    {
        if( max1 < numbers[ i ] )
        {
            max1 = numbers[ i ];
            index = i;
        }
    }

    for( int i = 0; i < size; ++i )
    {
        if( i == index )
        {
            continue;
        }

        if( max2 < numbers[ i ] )
        {
            max2 = numbers[ i ];
        }
    }

    //printf( "FAST:%lld * %lld = %lld", max1, max2, max1 * max2 );

    return max1 * max2;
}

unsigned long long max( unsigned long long a, unsigned long long b )
{
    if( a > b )
        return a;
    else
        return b;
}

unsigned long long maxPairwiseSimple( int size, unsigned long long* numbers )
{
    unsigned long long product = 0;

    for( int i = 0; i < size; ++i )
    {
        for( int j = i + 1; j < size; ++j )
        {
            product = max( product, numbers[ i ] * numbers[ j ] );
        }
    }

    //printf( "SIMPLE: %lld\r\n", product );

    return product;
}

int main()
{
    int n = 0;

    scanf( "%d", &n );

    unsigned long long numbers[ n ];

    for( int i = 0; i < n; ++i )
    {
        scanf( "%lld", &numbers[ i ] );
    }

    printf( "%lld\n", maxPairwiseProduct( n, numbers ) );

    //srand(time(NULL));

    //while( 1 )
    //{
    //    int r = rand() % 20 + 2;
    //    unsigned long long A[ r ];

    //    printf( "%d\r\n", r );

    //    for( int i = 0; i < r; i++ )
    //    {
    //        A[ i ] = rand() % 10000;
    //        printf( "%lld ", A[ i ] );
    //    }

    //    printf( "\r\n" );

    //    unsigned long long res1 = maxPairwiseSimple( r, A );
    //    unsigned long long res2 = maxPairwiseProduct( r, A );

    //    if( res1 == res2 )
    //    {
    //        printf( "OK\r\n" );
    //    }
    //    else
    //    {
    //        printf( "WRONG:\r\n" );
    //        break;
    //    }
    //}

    return 0;
}

