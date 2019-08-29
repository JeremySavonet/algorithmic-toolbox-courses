// author: j.savonet
// version: 1.0

#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#define RELEASE

using namespace std;

// Fail case:
// 4
// 0 0
// 5 6
// 3 4
// 7 2
// Your output:
// 4.472136021
//
// Correct output:
// 2.828427125

class Point
{
public:
    Point( long long x, long long y )
        : _x( x )
        , _y( y )
    {
    }

public:
    long long _x;
    long long _y;
};

inline std::ostream& operator<<( std::ostream& o, Point p )
{
    o << "(" << p._x << ", " << p._y << ")";
    return o;
}

// Utilities

long long min( long long a, long long b )
{
    if( a < b )
    {
        return a;
    }

    return b;
}

void debugPrint( vector< Point > points )
{
    for( int i = 0; i < points.size(); ++i )
    {
        std::cout
            << "(" << points[ i ]._x << ";"
            << points[ i ]._y << ")"
            << std::endl;
    }
}

double dist( Point a, Point b )
{
    return sqrtf( ( float ) ( a._x - b._x ) * ( a._x - b._x ) +
        ( a._y - b._y ) * ( a._y - b._y ) );
}

// This function will do the merge based on differents critera
void merge( vector< Point >& a, int l, int m, int r, bool xCompare )
{
    //std::cout << ">>> HERE: l: " << l << " r: " << r << " m: " << m << std::endl;

    // First create left and right sub-array from array a
    int size1 = m - l;
    int size2 = r - m;
    vector< Point > left;
    vector< Point > right;

    for( int i = 0 ; i < size1; ++i )
    {
        left.push_back( a[ l + i ] );
    }

    for( int i = 0; i < size2; ++i )
    {
        right.push_back( a[ m + i ] );
    }

    int i = 0;
    int j = 0;
    int k = l;

    // While both list are non-empty
    while( i < size1 && j < size2 )
    {
        if( xCompare )
        {
            if( left[ i ]._x <= right[ j ]._x )
            {
                a[ k ] = left[ i ];
                i++;
            }
            else
            {
                a[ k ] = right[ j ];
                j++;
            }
        }
        else
        {
            if( left[ i ]._y <= right[ j ]._y )
            {
                a[ k ] = left[ i ];
                i++;
            }
            else
            {
                a[ k ] = right[ j ];
                j++;
            }
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
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted.
void mergeSort( vector< Point >& arr, int l, int r, bool xCompare )
{
    if( r <= l + 1 )
    {
        return;
    }

    int m = l + ( r - l ) / 2;

    //std::cout << "l: " << l << " r: " << r << " m: " << m << std::endl;

    mergeSort( arr, l, m, xCompare );
    mergeSort( arr, m, r, xCompare );

    merge( arr, l, m, r, xCompare );
}

// 1- First approach. Runtime is O(n2)
double minimal_distance_simple( vector< Point >& points )
{
    long long size = points.size();
    double minDistance = DBL_MAX;
    double temp = 0;

    for( long long i = 0; i < size; ++i )
    {
        for( long long j = i + 1; j < size; ++j )
        {
            temp = dist( points[ i ], points[ j ] );
            if( minDistance > temp )
            {
                minDistance = temp;
            }
        }
    }

    return minDistance;
}

// 2- Second approach try in O(n log(n))
double minimal_distance( vector< Point > points )
{
    // Corner case
    if( points.size() <= 3 )
    {
        return minimal_distance_simple( points );
    }

    // a- Split into 2 halves.
    int m = points.size() / 2;

    vector< Point > xLeft;
    for( int i = 0; i < m; ++i )
    {
        xLeft.push_back( points[ i ] );
        //std::cout << xLeft[ i ] << std::endl;
    }

    //std::cout << "====================" << std::endl;

    vector< Point > xRight;
    for( int i = m; i < points.size(); ++i )
    {
        xRight.push_back( points[ i ] );
        //std::cout << xRight[ i - m ] << std::endl;
    }

    // b- Find min distance in both halves
    // Here are steps explained in the problem description
    double d1 = minimal_distance( xLeft );
    double d2 = minimal_distance( xRight );

    // c- Find the min distance between halves
    double d = min( d1, d2 );

    //std::cout << ">>> Dists: d1: " << d1 << " d2: " << d2 << " d:" << d << std::endl;

    // Reduce search in interval [ -d; d ]
    // d- Build the [-d,d] array
    vector< Point > reduced;
    for( int i = 0; i < points.size(); ++i )
    {
        if( abs( ( points[ m ]._x - points[ i ]._x ) ) <= d )
        {
            reduced.push_back( points[ i ] );
        }
    }

    // e- Order the reduced array by their y-coordinates
    mergeSort( reduced, 0, reduced.size(), false );

    //std::cout << "======== redu ==========" << std::endl;
    //debugPrint( reduced );
    //std::cout << "====================" << std::endl;

    long long size = reduced.size();
    long long limit = 0;
    double best_distance = 0;
    double minimum_distance = d;
    for(long long olc = 0; olc < size; olc++)
    {
        limit = min(7, size - olc);
        for(long long ilc = 1; ilc < limit; ilc++)
        {
            best_distance = dist( reduced[olc], reduced[olc + ilc]);
            if(best_distance < minimum_distance)
            {
                minimum_distance = best_distance;
            }
        }
    }

    return min( d, minimum_distance );
}

void test_function()
{
    // TODO: XXX compare simple and fast approach
}

int main()
{
#ifdef RELEASE
    size_t nbPoints;
    std::cin >> nbPoints;

    vector< Point > points;

    long long tmpX;
    long long tmpY;

    for( size_t i = 0; i < nbPoints; ++i )
    {
        std::cin >> tmpX >> tmpY;
        points.push_back( Point( tmpX, tmpY ) );
    }

    //debugPrint( points );

    //std::cout << "====================" << std::endl;

    mergeSort( points, 0, points.size(), true );

    //std::cout << "===== sorted =====" << std::endl;
    //debugPrint( points );
    //std::cout << "====================" << std::endl;

    // Result
    std::cout << std::fixed;
    std::cout
        << std::setprecision( 9 )
        << minimal_distance( points )
        << "\n";

#else

    test_function();

#endif

    return 0;
}
