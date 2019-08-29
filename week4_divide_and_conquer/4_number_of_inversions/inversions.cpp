// author: j.savonet
// version: 1.0

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#define RELEASE

using std::vector;

// failed case:
// 6
// 9 8 7 3 2 1
//
// output = 9
// correct = n n-1/2 = 15

static unsigned long long permut = 0;

// This will merge two subarray of array a
// First is: [ 1; m ]
// Second is: [ m + 1; r ]
//
// @Param a: the array to be merged
// @Param: l: left part of the array
// @Param: m: mid part of the array
// @Param: r: right part of the array
unsigned long long merge( vector< unsigned long long >& a, int l, int m, int r )
{
    unsigned long long invCount = 0;

    //std::cout << ">>> HERE: l: " << l << " r: " << r << " m: " << m << std::endl;

    // First create left and right sub-array from array a
    int size1 = m - l;
    int size2 = r - m;
    vector< unsigned long long > left( size1 );
    vector< unsigned long long > right( size2 );

    //std::cout << "Left:" << std::endl;
    for( int i = 0 ; i < size1; ++i )
    {
        left[ i ] = a[ l + i ];
        //std::cout << left[ i ] << " ";
    }
    //std::cout << std::endl;

    //std::cout << "Right:" << std::endl;
    for( int i = 0; i < size2; ++i )
    {
        right[ i ] = a[ m + i ];
        //std::cout << right[ i ] << " ";
    }
    //std::cout << std::endl;

    int i = 0;
    int j = 0;
    int k = l;

    // While both list are non-empty
    while( i < size1 && j < size2 )
    {
        // Take the smallest element from each side and place it on the resulting
        // array
        if( left[ i ] <= right[ j ] )
        {
            a[ k ] = left[ i ];
            i++;
        }
        else
        {
            a[ k ] = right[ j ];
            //std::cout << ">> PERMUT" << std::endl;
            invCount += left.size() - i;
            //permut++;
            j++;
        }

        k++;
    }

    // Move remaining elements
    while( i < size1 )
    {
        a[ k ] = left[ i ];
        i++;
        k++;
    }

    while( j < size2 )
    {
        a[ k ] = right[ j ];
        j++;
        k++;
    }

    //for( int i = 0; i < a.size(); ++i )
    //{
    //    std::cout << "i: " << a[ i ] << " ";
    //}

    //std::cout << std::endl;

    //std::cout << "======================" << std::endl;

    return invCount;
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort( vector< unsigned long long >& arr, int l, int r)
{
    if( r <= l + 1 )
    {
        return;
    }

    int m = l + ( r - l ) / 2;

    //std::cout << "l: " << l << " r: " << r << " m: " << m << std::endl;

    mergeSort( arr, l, m );
    mergeSort( arr, m, r );

    permut += merge( arr, l, m, r );
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

    mergeSort( a, 0, a.size() );
    std::cout << permut << '\n';

#else

#endif

  return 0;
}
