// author: j.savonet
// version: 1.0

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#define RELEASE

using std::vector;
using std::swap;

struct Pair
{
    int m1;
    int m2;
} typedef Pair_t;

int partition2( vector< unsigned long long >& a, int l, int r )
{
    unsigned long long x = a[ l ];
    int j = l;

    for( int i = l + 1; i <= r; ++i )
    {
        if( a[ i ] <= x )
        {
            j++;
            swap( a[ i ], a[ j ] );
        }
    }

    swap( a[ l ], a[ j ] );

    return j;
}

Pair_t partition3( vector< unsigned long long >& a, int l, int r )
{
    Pair_t res;

    res.m1 = l;
    res.m2 = l;

    // Pour l'incrementation de m2
    for( int i = l + 1; i <= r; ++i )
    {
        // Si m2 doit etre up
        if( a[ l ] >= a[ i ] )
        {
            swap( a[ res.m2 + 1 ], a[ i ] );
            res.m2++;
        }
    }

    swap( a[ l ], a[ res.m2 ] );

    // Pour l'incrementation de m1 maintenant vu qu'on connait la position de fin
    // de l'interval des valeurs egales: aka. m2
    for( int i = l; i <= res.m2; ++i )
    {
        // Si mon index est inferieur a ma borne sup
        // qui doit etre egale a la valeur de la borne inf egalement
        // vu que les valeurs sont dans l'intervale [m1, m2].
        if( a[ i ] < a[ res.m2 ] )
        {
            swap( a[ i ], a[ res.m1 ] );
            res.m1++;
        }
    }

    return res;
}

void randomized_quick_sort( vector< unsigned long long >& a, int l, int r )
{
    if( l >= r )
    {
        return;
    }

    int k = l + rand() % ( r - l + 1 );
    swap( a[ l ], a[ k ]);

    int m = partition2( a, l, r );

    randomized_quick_sort( a, l, m - 1 );
    randomized_quick_sort( a, m + 1, r );
}

void quicksort3( vector< unsigned long long >& a, int l, int r )
{
    if( l >= r )
    {
        return;
    }

    int k = l + rand() % ( r - l + 1 );
    swap( a[ l ], a[ k ]);

    Pair_t res = partition3( a, l, r );

    quicksort3( a, l, res.m1 - 1 );
    quicksort3( a, res.m2 + 1, r );
}

void test_function()
{
    srand( time( NULL ) );   // Initialization, should only be called once.
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

    //vector< unsigned long long > b( n );
    //b = a;

    //randomized_quick_sort( a, 0, a.size() - 1 );
    quicksort3( a, 0, a.size() - 1 );

    for( size_t i = 0; i < a.size(); ++i )
    {
        std::cout << a[ i ] << ' ';
    }

    //std::cout << std::endl;

    //for( size_t i = 0; i < b.size(); ++i )
    //{
    //    std::cout << b[ i ] << ' ';
    //}

#else

  test_function();

#endif
}
