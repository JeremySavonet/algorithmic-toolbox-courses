// author: j.savonet
// version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

//#define DEBUG

struct Item
{
    int weight;
    int value;
};

int compare( void const* a, void const* b )
{
    const struct Item *aV =  ( const struct Item *) a;
    const struct Item *bV =  ( const struct Item *) b;

    struct Item test1 = *aV;
    struct Item test2 = *bV;

    double ratio1 = (double) test1.value / test1.weight;
    double ratio2 = (double) test2.value / test2.weight;

    return ratio1 < ratio2;
}

double get_optimal_value_simple(
    int numItem,
    int capacity,
    int* weights,
    int* values )
{
    double value = 0.0;

    // CORNER CASES
    if( capacity == 0 )
    {
        return 0.0;
    }

    if( numItem == 1 )
    {
        if( weights[ 0 ] < capacity )
        {
            return values[ 0 ];
        }
        else
        {
            return (double) values[ 0 ] * (double) capacity / (double) weights[ 0 ];
        }
    }

    int remainingCapacity =  capacity;

    double unitPerItem[ numItem ];
    for( int i = 0; i < numItem; ++i )
    {
        unitPerItem[ i ] = values[ i ] / weights[ i ];
    }

    double computedValue = 0;

    int saveIndex = -1;
    while( remainingCapacity > 0 )
    {
        double max = 0;
        for( int i = 0; i < numItem; ++i )
        {
            if( max < unitPerItem[ i ] )
            {
                max = unitPerItem[ i ];
                saveIndex = i;
            }
        }

        if( remainingCapacity >= weights[ saveIndex ] )
        {
            computedValue += unitPerItem[ saveIndex ] * weights[ saveIndex ];
            remainingCapacity -= weights[ saveIndex ];
            unitPerItem[ saveIndex ] = 0;
        }
        else
        {
            computedValue += ( weights[ saveIndex ] / remainingCapacity ) * unitPerItem[ saveIndex ];
            remainingCapacity = 0;
        }
    }

    return computedValue;
}

double get_optimal_value_fast( int n, int capacity, struct Item* items )
{
    qsort( items, n, sizeof( struct Item ), & compare );

#ifdef DEBUG
    for( int i = 0; i < n; ++i )
    {
        printf( "%d : %d\n\r", items[ i ].weight, items[ i ].value );
    }

    printf( "=================== \r\n" );
#endif

    double computedValue = 0;
    int currCapa = 0;

    for( int i = 0; i < n; ++i )
    {
        //printf( ">>>> %d %f %d %d \r\n", currCapa, computedValue, items[ i ].weight, items[ i ].value );

        if( currCapa + items[ i ].weight <= capacity )
        {
            computedValue += items[ i ].value;
            currCapa += items[ i ].weight;
        }
        else
        {
            int remainingCapacity = capacity - currCapa;
            computedValue +=  (double)items[ i ].value * remainingCapacity / (double)items[ i ].weight;
            break;
        }
    }

    return computedValue;
}

int main()
{
    int n;
    int capacity;

    scanf( "%d %d", &n, & capacity );

    struct Item items[ n ]; //  = { { .value = 60, .weight = 20 }, { .value = 100, .weight = 50 }, { .value = 120, .weight = 30 } };

    for( int i = 0; i < n; i++ )
    {
        scanf("%d %d", & items[ i ].value, & items[ i ].weight );
    }

    double optimal_value = get_optimal_value_fast( n, capacity, items );
    printf( "%.4f\n", optimal_value );
    return 0;
}
