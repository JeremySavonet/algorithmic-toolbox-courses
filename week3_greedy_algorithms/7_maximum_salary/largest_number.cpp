// author: j.savonet
// version: 1.0

#include <algorithm>
#include <sstream>
#include <iostream>
#include <vector>
#include <string>
#include <time.h>

using namespace std;

//#define RELEASE

bool isGreaterOrEqual2( string a, string b )
{
    int sizeA = a.size();
    int sizeB = b.size();

    int n = sizeA;
    int m = sizeB;

    string tmp;

    bool swap = false;

    bool isGreater = false;

    if( sizeA > sizeB )
    {
        swap = true;
        n = sizeB;
        m = sizeA;

        tmp = a;
        a = b;
        b = tmp;
    }
    if( sizeA == sizeB )
    {
        int A = stoi( a );
        int B = stoi( b );

        std::cout << A << " " << B << std::endl;
        return A >= B;
    }

    for( int i = 0; i < n; ++i )
    {
        for( int j = 0; j < m; ++j )
        {
            std::cout << "HERE: " << a[ i ] << " " << b[ i ] << std::endl;

            if( a[ i ] == b[ j ] )
            {
                std::cout << "HERE a = b" << std::endl;
            }
            else if( a[ i ] > b[ j ] )
            {
                std::cout << "HERE a > b" << std::endl;
                return swap ? false : true;;
            }
            else
            {
                std::cout << "HERE a < b" << std::endl;
                return swap ? true : false;
            }
        }
    }

    return true;
}

bool isGreaterOrEqual( string a, string b )
{
    return ( std::stoi( a + b ) >= std::stoi( b + a ) );
}

string largest_number( std::vector< string > a )
{
    string res;
    int pos = 0;

    while( a.size() > 0 )
    {
        string max = "0";

        for( int i = 0; i < a.size(); ++i )
        {
            if( isGreaterOrEqual( a[ i ], max ) )
            {
                max = a[ i ];
                pos = i;
            }
        }

        res += max;
        a.erase( a.begin() + pos );
    }

    return res;
}

string largest_number2( std::vector< string > a )
{
    string res;
    int pos = 0;

    while( a.size() > 0 )
    {
        string max = "-1";

        for( int i = 0; i < a.size(); ++i )
        {
            if( isGreaterOrEqual2( a[ i ], max ) )
            {
                max = a[ i ];
                pos = i;
            }
        }

        res += max;
        a.erase( a.begin() + pos );
    }

    return res;
}

void tests()
{
    srand( time( NULL ) );   // Initialization, should only be called once.

    while( 1){
    int n1 = rand() % 100 + 1;
    int n2 = rand() % 100 + 1;

    string s1 = to_string( n1 );
    string s2 = to_string( n2 );

    cout << "a: " << s1 << " b: " << s2 << endl;;
    bool res1 = isGreaterOrEqual( s1, s2 );
    bool res2 = isGreaterOrEqual2( s1, s2 );

    cout << "Ress: " << res1 << " " << res2 << endl;
    assert( res1 == res2 );
    }
    //for( int i = 0; i < 100; i++ )
    //{
    //    int n = rand() % 100 + 1;

    //    std::vector< std::string > tab( n );
    //    for( int i = 0; i < n; ++i )
    //    {
    //        int num = rand() % 1000 + 1;
    //        tab[ i ] = std::to_string( num );
    //        std::cout << tab[ i ] << " ";
    //    }

    //    std::cout << std::endl;

    //    std::cout << "========= > res: " << largest_number( tab ) << std::endl;
    //    //assert( largest_number( tab ) == largest_number2( tab ) );
    //}
}

int main()
{
#ifdef RELEASE
    int n;
    std::cin >> n;

    std::vector< std::string > a( n );

    for( int i = 0; i < a.size(); ++i )
    {
        std::cin >> a[ i ];
    }

    std::cout << largest_number( a ) << "\n";
#else
    tests();
#endif
}
