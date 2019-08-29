// author: j.savonet
// version: 1.0

#include <cassert>
#include <cstdlib>
#include <iostream>
#include <vector>

#define RELEASE

using std::vector;

enum class Type
{
    Start = -1,
    Point = 0,
    End = 1
};

inline std::ostream& operator<<( std::ostream& o, Type t )
{
    switch( t )
    {
    case Type::Start:
        o << "Start";
        break;

    case Type::Point:
        o << "Point";
        break;

    case Type::End:
        o << "End";
        break;
    }

    return o;
}

class Coordinate
{
public:
    Coordinate( long long data, Type type, unsigned long long index )
        : _data( data )
        , _type( type )
        , _index( index )
    {
    }

public:
    long long _data;
    Type _type;
    unsigned long long _index;
};

// User functions
void debugPrint( vector< Coordinate > coords )
{
    for( int i = 0; i < coords.size(); ++i )
    {
        std::cout << "(" << coords[ i ]._data << "," << coords[ i ]._type << ")" << std::endl;
    }
}

// This will merge two subarray of array a
// First is: [ 1; m ]
// Second is: [ m + 1; r ]
//
// @Param a: the array to be merged
// @Param: l: left part of the array
// @Param: m: mid part of the array
// @Param: r: right part of the array
void merge( vector< Coordinate >& coords, int l, int m, int r )
{
    //std::cout << ">>> HERE: l: " << l << " r: " << r << " m: " << m << std::endl;

    // First create left and right sub-array from array a
    int size1 = m - l;
    int size2 = r - m;
    vector< Coordinate > left;
    vector< Coordinate > right;

    for( int i = 0 ; i < size1; ++i )
    {
        left.push_back( coords[ l + i ] );
    }

    for( int i = 0; i < size2; ++i )
    {
        right.push_back( coords[ m + i ] );
    }

    int i = 0;
    int j = 0;
    int k = l;

    // While both sub-array are non-empty
    while( i < size1 && j < size2 )
    {
        // This part is a little bit different than the classical merge sort
        // We need to handle redundancy and type of each element here
        if( left[ i]._data == right[ j ]._data )
        {
            if( left[ i ]._type < right[ j ]._type )
            {
                coords[ k++ ] = left[ i++ ];
            }
            else if( left[ i ]._type > right[ j ]._type )
            {
                coords[ k++ ] = right[ j++ ];
            }
            else if( left[ i ]._type == right[ j ]._type )
            {
                coords[ k++ ] = left[ i++ ];
                coords[ k++ ] = right[ j++ ];
            }
        }
        else if( left[ i ]._data < right[ j ]._data )
        {
            coords[ k++ ] = left[ i++ ];
        }
        else
        {
            coords[ k++ ] = right[ j++ ];
        }
    }

    // Move remaining elements
    while( i < size1 )
    {
        coords[ k ] = left[ i ];
        i++;
        k++;
    }

    while( j < size2 )
    {
        coords[ k ] = right[ j ];
        j++;
        k++;
    }
}

// l is for left index and r is right index of the
// sub-array of arr to be sorted
void mergeSort( vector< Coordinate >& coords, int l, int r )
{
    if( r <= l + 1 )
    {
        return;
    }

    int m = l + ( r - l ) / 2;

    //std::cout << "l: " << l << " r: " << r << " m: " << m << std::endl;

    mergeSort( coords, l, m );
    mergeSort( coords, m, r );

    merge( coords, l, m, r );
}

vector< long long > countIterations(
    vector< Coordinate > coords,
    long long segments,
    long long points )
{

    //  Since there are two points in segements it takes
    //  2 * segments + points
    long long n = ( 2 * segments ) + points;
    vector< long long> result( points );

    //  This layer indicates the number of segments in
    //  which the point lies.
    long long segment_layer = 0;
    for( unsigned long long i = 0; i < n; ++i )
    {
        if( coords[ i ]._type == Type::Start )
        {
            segment_layer++;
        }

        if( coords[ i ]._type == Type::End )
        {
            segment_layer--;
        }

        if( coords[ i ]._type == Type::Point )
        {
            // Here the index is actually used.
            result[ coords[ i ]._index ] = segment_layer;
        }
    }

    return result;
}

int main()
{
#ifdef RELEASE
    int segments;
    int nbPoints;
    std::cin >> segments >> nbPoints;

    long long tmpStart;
    long long tmpEnd;

    vector< Coordinate > coords;

    for( unsigned long long i = 0; i < segments; ++i )
    {
        std::cin >> tmpStart >> tmpEnd;
        coords.push_back( Coordinate( tmpStart, Type::Start, -1 ) );
        coords.push_back( Coordinate( tmpEnd, Type::End, -1 ) );
    }

    long long tmpPoint;
    for( unsigned long long i = 0; i < nbPoints; ++i )
    {
        std::cin >> tmpPoint;
        coords.push_back( Coordinate( tmpPoint, Type::Point, i ) );
    }

    // ====================================================================== //
    // Do the magic here...
    // Sort based on Coordinate::_data value
    mergeSort( coords, 0, coords.size() );

    //debugPrint( coords );

    vector< long long > result;
    result = countIterations( coords, segments, nbPoints );

    for( unsigned long long i = 0; i < nbPoints; ++i )
    {
        std::cout << result[ i ] << " ";
    }

    std::cout << "\n";

#else

#endif

    return 0;
}
