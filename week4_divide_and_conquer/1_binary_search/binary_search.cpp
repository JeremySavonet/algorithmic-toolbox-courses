// author: j.savonet
// version: 1.0

#include <cassert>
#include <cmath>
#include <iostream>
#include <time.h>
#include <vector>

#define RELEASE

using std::vector;

int binary_search( const vector< unsigned long long > &a, unsigned long long x )
{
    int left = 0;
    int right = ( int ) a.size();

    int mid;
    while( left <= right )
    {
        mid = std::floor( ( left + right ) / 2 );

        // search in upper part of the tab
        if( x > a[ mid ] )
        {
            left = mid + 1;
        }
        // search in lower part of the tab
        else if( x < a[ mid ] )
        {
            right = mid - 1;
        }
        else
        {
            return mid;
        }
    }

    return -1;
}

int linear_search( const vector< unsigned long long > &a, unsigned long long x) {
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] == x) return i;
  }
  return -1;
}

void test_function()
{
    srand( time( NULL ) );   // Initialization, should only be called once.

    int n = rand() % 10000 + 1;
    vector< unsigned long long > tab1( n );
    for( int i = 0; i < n; ++i )
    {
        tab1[ i ] = rand() % 1000000000 + 1;
    }

    int m = rand() % 10000 + 1;
    vector< unsigned long long > tab2( m );
    for( int i = 0; i < m; ++i )
    {
        tab2[ i ] = rand() % 100000000 + 1;
    }

    for( int i = 0; i < m; ++i )
    {
        assert( binary_search( tab1, tab2[ i ] ) == linear_search( tab1, tab2[ i ] ) );
    }
}

int main()
{
#ifdef RELEASE
    int n;
    std::cin >> n;
    vector< unsigned long long > a( n );

    for( size_t i = 0; i < a.size(); ++i )
    {
        std::cin >> a[ i ];
    }

    int m;
    std::cin >> m;
    vector< unsigned long long > b( m );

    for( int i = 0; i < m; ++i )
    {
        std::cin >> b[ i ];
    }

    for( int i = 0; i < m; ++i )
    {
        std::cout << binary_search( a, b[ i ] ) << ' ';
    }
#else

    test_function();

#endif

    return 0;
}
