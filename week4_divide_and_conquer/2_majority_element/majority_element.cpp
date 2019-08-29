// author: j.savonet
// version: 1.0

#include <algorithm>
#include <cassert>
#include <cmath>
#include <iostream>
#include <time.h>
#include <vector>

#define RELEASE

using namespace std;

using std::vector;

int get_majority_element( vector< unsigned long long >& a, int l, int r )
{
    if( l == r )
        return -1;

    if( l + 1 == r )
        return a[ l ];

    unsigned long long med = std::floor( ( l + r ) / 2 );

    int left = get_majority_element( a, l, med );
    int right = get_majority_element( a, med, r );

    int count1 = 0;
    int count2 = 0;
    for( int i = l; i < r; ++i )
    {
        if( a[ i ] == left )
            count1++;

        if( a[ i ] == right )
            count2++;
    }

    if( ( count1 > ( (r-l)/2 ) ) )
        return left;

    if( ( count2 > ( (r-l)/2 ) ) )
        return right;

    return -1;
}

int get_majority_element_naive( vector< unsigned long long >& a )
{
    unsigned long long curr = 0;
    int count = 0;
    for( int i = 0; i < a.size(); ++i )
    {
        curr = a[ i ];
        count = 0;
        for( int j = 0; j < a.size(); ++j )
        {
            if( a[ j ] == curr )
            {
                count++;
            }
        }

        if( count > a.size() / 2 )
        {
            return curr;
        }
    }

    return -1;
}

void test_function()
{
    srand( time( NULL ) );   // Initialization, should only be called once.

    int n = rand() % 100000 + 1;

    vector< unsigned long long > tab( n );
    for( int i = 0; i < n; ++i )
    {
        tab[ i ] = rand() % 1000000000;
    }

    assert( get_majority_element( tab, 0, tab.size() ) == get_majority_element_naive( tab ) );
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

    //std::cout << ( get_majority_element_naive( a ) != -1 ) << '\n';
    std::cout << ( get_majority_element( a, 0, a.size() ) != -1 ) << '\n';
#else

    test_function();

#endif
}
