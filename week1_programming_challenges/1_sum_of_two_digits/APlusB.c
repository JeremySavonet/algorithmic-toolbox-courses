#include <stdlib.h>
#include <stdio.h>

int sum( int a, int b )
{
    return a + b;
}

int main()
{
    int a = 0;
    int b = 0;

    scanf( "%d%d", &a, &b );

    printf( "%d", sum( a, b ) );

    return 0;
}
