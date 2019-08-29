// author: j.savonet
// version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int get_change( int money )
{
    int moneyLeft = money;
    int pieceCount = 0;
    int rest = 0;

    if( moneyLeft % 10 == 0 )
    {
        pieceCount = moneyLeft / 10;
        moneyLeft = 0;
        return pieceCount;
    }

    if( moneyLeft % 10 != 0 && moneyLeft % 10 != moneyLeft )
    {
        rest = ( moneyLeft % 10 );
        pieceCount += moneyLeft / 10;
        moneyLeft = rest;
    }

    if( moneyLeft % 5 == 0 )
    {
        pieceCount += ( moneyLeft / 5 );
        moneyLeft = 0;
        return pieceCount;
    }

    if( moneyLeft % 5 != 0 && moneyLeft % 5 != moneyLeft )
    {
        rest = ( moneyLeft % 5 );
        pieceCount += moneyLeft / 5;
        moneyLeft = rest;
    }

    if( moneyLeft % 1 == 0 )
    {
        pieceCount += moneyLeft / 1;
        moneyLeft = 0;
        return pieceCount;
    }

    return pieceCount;
}

void test_solution()
{
    // TODO: XXX
}

int main()
{
    int money = 0;
    scanf( "%d", &money );

    printf( "%d\n", get_change( money ) );

    //test_solution();
    return 0;
}
