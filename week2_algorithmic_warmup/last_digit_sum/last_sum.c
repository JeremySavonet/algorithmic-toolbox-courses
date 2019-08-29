// Author: J.savonet
// Version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

// Test case:
// 832564823476
// res = 3

#define PISANO 60

unsigned long long get_fibonacci_sum_of_last_digit_fast( unsigned long long n )
{
    n = n % PISANO;

    if( n <= 1 )
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;
    unsigned long long currentSum = 1;

    for( int i = 0; i < n - 1; ++i )
    {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = ( tmp_previous + current ) % 10;
        currentSum += current;
    }

    return currentSum % 10;
}

int get_fibonacci_last_digit(long long n) {
    int first = 0;
    int second = 1;

    int res;

    for (int i = 2; i <= n; i++) {
        res = (first + second) % 10;
        first = second;
        second = res;
    }

    return res;
}

unsigned long long get_fibonacci_sum_of_last_digit_naive( int n )
{
    if( n <= 1 )
        return n;

    unsigned long long previous = 0;
    unsigned long long current  = 1;
    unsigned long long currentSum = 1;

    for( int i = 0; i < n - 1; ++i )
    {
        unsigned long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        currentSum += current;
    }

    return currentSum % 10;
}

void test_solution()
{
    assert( get_fibonacci_sum_of_last_digit_fast( 3 ) == 4 );
    assert( get_fibonacci_sum_of_last_digit_naive( 100 ) == 5 );

    for( int n = 0; n < 100; ++n )
    {
        assert( get_fibonacci_sum_of_last_digit_fast( n ) ==  get_fibonacci_sum_of_last_digit_naive( n ) );
    }
}

int main()
{
    unsigned long long n;

    scanf( "%lld", &n );

    printf( "%lld\n", get_fibonacci_sum_of_last_digit_fast( n ) );

    //test_solution();
}
