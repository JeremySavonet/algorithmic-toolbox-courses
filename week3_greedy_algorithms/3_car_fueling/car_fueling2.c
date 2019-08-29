// author: j.savonet
// version: 1.0

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 * Test Cases:
 *
 * Input 1:
 * 950
 * 400
 * 4
 * 200 375 550 750
 *
 * Output 1:
 * 2
 *
 *
 * Input 2:
 * 10
 * 3
 * 4
 * 1 2 5 9
 *
 * Output 2:
 * -1
 *
 */

#define RELEASE

int compare( void const* a, void const* b )
{
   int const *pa = a;
   int const *pb = b;

   // trie croissant
   return *pa - *pb;
}

int compute_fast(
    int tripDistance,
    int tankCapacity,
    int nbGazStation,
    int stations[] )
{
    int count = 0;
    int i = 0;
    int distCovered = 0;

    if( i == 0 && distCovered + tankCapacity < stations[ 0 ] )
    {
        return -1;
    }

    if( tripDistance <= tankCapacity )
    {
        return 0;
    }

    // While we complete the whole journey.
    while( distCovered < tripDistance )
    {
        if( i < nbGazStation && stations[ i ] <= ( distCovered + tankCapacity ) )
        {
            //printf( ">>>> stations[ %d ] %d\r\n", i, stations[ i ] );

            // can we go to the next station ?
            for( int j = i + 1; j < nbGazStation; ++j )
            {
                if( j < nbGazStation && stations[ j ] <= ( distCovered + tankCapacity ) )
                {
                    //printf( ">>>> CAN GO FURTHER stations[ %d ] %d\r\n", j, stations[ j ] );
                    if( j == nbGazStation - 1 )
                    {
                        distCovered = stations[ j ];
                        i = nbGazStation;
                    }
                }
                else
                {
                    if( distCovered + stations[ j - 1 ] > tankCapacity )
                    {
                        //printf( ">>>> NO STATION CAN BE REACH\r\n" );
                        return -1;
                    }

                    distCovered = stations[ j - 1 ];
                    i = j - 1;
                    break;
                }
            }
        }

        if( i == nbGazStation && distCovered + tankCapacity < tripDistance )
        {
            return -1;
        }

        //printf( ">>>> DIST COVERED %d\r\n", distCovered );

        // Counting the number of refill.
        if( distCovered + tankCapacity >= tripDistance )
        {
            return ++count;
        }
        else
        {
            count++;
        }
    }

    return count;
}

int getRefills( int tripDistance, int capacity, int n, int* stations )
{
    int numRefills = 0;
    int currentRefills = 0;
    int lastRefills = 0;

    int cumulTrip = 0;

    int stationsFull[ n + 2 ];
    stationsFull[ 0 ] = 0;
    stationsFull[ n + 1 ] = tripDistance;

    for( int i = 1; i < n + 1; ++i )
    {
        stationsFull[ i ] = stations[ i - 1 ];
    }

    if( tripDistance < capacity )
    {
        return 0;
    }

    if( capacity == 0 )
    {
        return -1;
    }

    while( currentRefills < n + 1 )
    {
        lastRefills = currentRefills;

        int currentStation = stationsFull[ lastRefills ];
        int nextStation = stationsFull[ currentRefills + 1 ];

        //printf( ">>>> CURR: %d NEXT: %d\r\n", currentStation, nextStation );

        while( currentRefills < n + 1 &&
               stationsFull[ currentRefills + 1 ] - stationsFull[ lastRefills ] <= capacity )
        {
            //printf( ">>>> POSSIBLE CANDIDATE: %d\r\n", stationsFull[ currentRefills + 1 ] );

            cumulTrip = stationsFull[ currentRefills + 1 ];
            currentRefills++;
        }

        if( currentRefills == lastRefills )
        {
            //printf( ">>>> NEXT STATION TO FAR\r\n" );
            return -1;
        }

        numRefills++;

        if( cumulTrip + capacity > tripDistance && n < currentRefills )
        {
            return numRefills - 1;
        }

        if( currentRefills == n )
        {
            //printf( ">>>> LAST STATION: REFILL NEEDED: %d\r\n", stationsFull[ currentRefills ] );
            cumulTrip = stationsFull[ currentRefills ];

            if( cumulTrip + capacity < tripDistance )
            {
                //printf( ">>>> CANNOT FINISH THE TRIP\r\n" );
                return -1;
            }

            break;
        }
    }

    return numRefills;
}

void test_function()
{
    srand(time(NULL));   // Initialization, should only be called once.

    /*
    int dist = 950;
    int capa = 400;
    int n = 4;
    int stations[ 4 ] = { 200, 375, 550, 750 };

    getRefills( dist, capa, n, stations );
    */

    //int dist = 950;
    //int capa = 400;
    //int n = 4;
    //int stations[ 4 ] = { 200, 375, 550, 750 };

    //assert( getRefills( dist, capa, n, stations ) == 2 );

    //dist = 10;
    //capa = 3;
    //n = 4;
    //int stations2[ 4 ] = { 1, 2, 5, 9 };

    //assert( getRefills( dist, capa, n, stations2 ) == -1 );

    //dist = 700;
    //capa = 200;
    //n = 4;
    //int stations3[ 4 ] = { 100, 200, 300, 400 };

    for( int i = 0; i < 20; ++i )
    {
        int dist = rand() % 10000;
        int capa = rand() % 400;
        int n = rand() % 300;

        int stations[ n ];
        for( int i = 0; i < n; ++i )
        {
            int val = rand() % ( dist - 1 );
            stations[ i ] = val;
        }

        qsort( stations, n, sizeof( int ), & compare );

        printf( "Dist: %d capa: %d, nb: %d\r\n", dist, capa, n );

        for( int i = 0; i < n; ++i )
        {
            printf( "%d ", stations[ i ] );
        }

        printf( "\r\n======== > Result 1: %d\r\n", getRefills( dist, capa, n, stations ) );
        printf( "\r\n======== > Result 2: %d\r\n", compute_fast( dist, capa, n, stations ) );
        assert( getRefills( dist, capa, n, stations ) == compute_fast( dist, capa, n, stations ) );
    }

    //assert( getRefills( dist, capa, n, stations3 ) == -1 );
    //printf( ">>>> Test Success\r\n" );
}

int main()
{
#ifdef RELEASE
    int tripDistance;
    scanf( "%d", &tripDistance );

    int tankCapacity;
    scanf( "%d", &tankCapacity );

    int nbGazStation;
    scanf( "%d", &nbGazStation );

    int gazStation[ nbGazStation ];
    for( int i = 0; i < nbGazStation; i++ )
    {
        scanf("%d", & gazStation[ i ] );
    }

    printf(
        "%d\n",
        getRefills(
            tripDistance,
            tankCapacity,
            nbGazStation,
            gazStation ) );
#else
    test_function();
#endif
}
