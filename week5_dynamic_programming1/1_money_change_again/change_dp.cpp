// author: j.savonet
// version: 1.0

#include <climits>
#include <iostream>
#include <vector>

using namespace std;

// money = [ 1; 3; 4 ]
// minNumCoins = size(m + 1)
namespace
{
    vector< int > coins = { 1, 3, 4 };
}

int get_change( int m )
{
    vector< int > minNumCoins( m + 1 );
    int numCoins = INT_MAX;
    minNumCoins[ 0 ] = 0;

    for( int i = 1; i <= m; ++i )
    {
        minNumCoins[ i ] = INT_MAX;

        for( int j = 0; j < 3; ++j )
        {
            if( i >= coins[ j ] )
            {
                numCoins = minNumCoins[ i - coins[ j ] ] + 1;
                if( numCoins < minNumCoins[ i ] )
                {
                    minNumCoins[ i ] = numCoins;
                }
            }
        }
    }

    return minNumCoins[ m ];
}

int main()
{
    int money;
    std::cin >> money;

    std::cout << get_change( money ) << '\n';
}
