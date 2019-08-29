// Author: J.savonet
// Version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int get_fibonacci_last_digit_fast( int n )
{
    if( n <= 1 )
        return n;

    int previous = 0;
    int current  = 1;

    for( int i = 0; i < n - 1; ++i )
    {
        int tmp_previous = previous;
        previous = current;
        current = ( tmp_previous + current ) % 10;
    }

    return current;
}

unsigned long long get_fibonacci_last_digit_naive( int n )
{
    if( n <= 1 )
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;

    for( int i = 0; i < n - 1; ++i )
    {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
    }

    return current % 10;
}

void test_solution()
{
    assert( get_fibonacci_last_digit_fast( 3 ) == 2 );
    assert( get_fibonacci_last_digit_fast( 10 ) == 5 );

    //for( int n = 0; n < 100; ++n )
    //{
    //    assert( get_fibonacci_last_digit_fast( n ) ==  get_fibonacci_last_digit_naive( n ) );
    //}
}

int main()
{
    int n;

    scanf( "%d", &n );

    printf( "%d\n", get_fibonacci_last_digit_fast( n ) );

    //test_solution();
}
