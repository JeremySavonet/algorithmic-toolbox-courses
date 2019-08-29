// Author: J.savonet
// Version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned long long get_pisano_period( unsigned long long m )
{
    unsigned long long a = 0, b = 1, c = a + b;
    for( int i = 0; i < m * m; i++ )
    {
        c = (a + b) % m;
        a = b;
        b = c;
        if( a == 0 && b == 1 )
            return i + 1;
    }

    return 0;
}

unsigned long long get_fibonacci_mod(
    unsigned long long n,
    unsigned long long m )
{
    unsigned long long per = get_pisano_period( m );
    n = n % per;

    if( n <= 1 )
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;

    for( unsigned long long i = 0; i < n - 1; ++i )
    {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = ( tmp_previous + current ) % m;
    }

    return current;
}

unsigned long long get_fibonacci_huge_naive(
    unsigned long long n,
    unsigned long long m) {
    if (n <= 1)
        return n;

    unsigned long long previous = 0;
    unsigned long long current = 1;

    for( unsigned long long i = 0; i < n - 1; ++i) {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        printf( "%lld %lld", current, m );
    }

    return current % m;
}

void test_solution()
{
    srand( time( NULL ) );   // Initialization, should only be called once.

    assert( get_fibonacci_mod( 2015, 3 ) == 1 );
    //assert( get_fibonacci_mod( 2816213588, 239 ) == 151 );

    if( get_fibonacci_huge_naive( 2015, 3 ) == 1 )
    {
        printf( "HELLO" );
    }
    //assert( get_fibonacci_huge_naive( 2816213588, 239 ) == 151 );

    //for( int n = 0; n < 20; ++n )
    //{
    //    unsigned long long rand1 = rand() % 10000;
    //    unsigned long long rand2 = rand() % 100;
    //    assert( get_fibonacci_mod( rand1, rand2 ) == get_fibonacci_huge_naive( rand1, rand2 ) );
    //}
}

int main()
{
    unsigned long long n = 0;
    unsigned long long m = 0;
    scanf( "%lld %lld", &n, &m );

    printf( "%lld\n", get_fibonacci_mod( n, m ) );

    //test_solution();
    return 0;
}
