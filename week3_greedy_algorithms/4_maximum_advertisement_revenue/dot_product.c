// author: j.savonet
// version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


#define RELEASE

static char *qtoa(__int128_t n) {
    static char buf[40];
    unsigned int i, j, m = 39;
    memset(buf, 0, 40);
    for (i = 128; i-- > 0;) {
        int carry = !!(n & (( __int128_t)1 << i));
        for (j = 39; j-- > m + 1 || carry;) {
            int d = 2 * buf[j] + carry;
            carry = d > 9;
            buf[j] = carry ? d - 10 : d;
        }
        m = j;
    }
    for (i = 0; i < 38; i++) {
        if (buf[i]) {
            break;
        }
    }
    for (j = i; j < 39; j++) {
        buf[j] += '0';
    }
    return buf + i;
}

int compare( void const* a, void const* b )
{
   int const *pa = a;
   int const *pb = b;

   // trie decroissant
   return *pb - *pa;
}

__int128_t maximize_profit_simple( int n, int* profitPerClick, int* averageClick )
{
    //printf( "======= NEW TEST\n" );
    qsort( profitPerClick, n, sizeof( int ), & compare );
    qsort( averageClick, n, sizeof( int ), & compare );

    __int128_t sum = 0;
    for( int i = 0; i < n; ++i )
    {
        //printf( "%d - %d \n" , profitPerClick[ i ], averageClick[ i ] );
        sum += ( __int128_t ) profitPerClick[ i ] * (__int128_t) averageClick[ i ];
    }

    return sum;
}

void test_function()
{
    //srand( time( NULL ) );   // Initialization, should only be called once.

    //while( 1 )
    //{
    //    int n = rand() % 1000;

    //    int profitPerClick[ n ];
    //    int averageClick[ n ];
    //    for( int i = 0; i < n; ++i )
    //    {
    //        profitPerClick[ i ] = rand() % ( 2 * 100000 ) - 10000;
    //        averageClick[ i ] = rand() % ( 2 * 100000 ) - 10000;
    //    }

    //    long long res = maximize_profit_simple( n, profitPerClick, averageClick );
    //    long long res2 = maximize_profit_simple2( n, profitPerClick, averageClick );
    //    printf( "===== > Result 1: %lld \n" , res );
    //    printf( "===== > Result 2: %lld \n" , res2 );

    //    assert( res ==  res2 );
    //}
}

int main()
{
#ifdef RELEASE
    int n;
    scanf( "%d", &n );

    int profitPerClick[ n ];
    for( int i = 0; i < n; i++ )
    {
        scanf("%d", & profitPerClick[ i ] );
    }

    int averageClick[ n ];
    for( int i = 0; i < n; i++ )
    {
        scanf("%d", & averageClick[ i ] );
    }

    __int128_t res = maximize_profit_simple( n, profitPerClick, averageClick );

    printf( "%s\n", qtoa( res ) );

#else
    test_function();
#endif
}
