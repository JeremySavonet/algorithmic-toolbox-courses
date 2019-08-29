// author: j.savonet
// version: 1.0

#include <iostream>
#include <vector>

using namespace std;

#define RELEASE

std::vector< int > distributePrize( int number )
{
    std::vector< int > res;

    if( number == 1 )
    {
        res.push_back( 1 );
        return res;
    }

    int remaining = number;
    for( int i = 1; i < number; ++i )
    {
        if( remaining > i * 2 )
        {
            res.push_back( i );
            remaining -= i;
        }
        else
        {
            res.push_back( remaining );
            break;
        }
    }

    return res;
}

int main()
{
#ifdef RELEASE

    int n;
    std::cin >> n;

    std::vector< int > summands = distributePrize( n );
    std::cout << summands.size() << '\n';

    for( int i = 0; i < summands.size(); ++i )
    {
        std::cout << summands[ i ] << ' ';
    }

    std::cout << '\n';

#else
    test_function();
#endif
}
