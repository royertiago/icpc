#include <stdio.h>
#include <algorithm>

int numbers[10000];
int N, M;

bool precedes( int a, int b ) {
    if( a % M < b % M )
        return true;

    if( a % M > b % M )
        return false;

    // Their values mod M are equal.
    if( a % 2 == 0 ) {
        if( b % 2 == 0 ) {
            // Both are even.
            return a < b;
        }
        // a is even, b is odd
        return false;
    }

    // a is odd.
    if( b % 2 == 0 ) {
        // a is odd, b is even
        return true;
    }

    // both are odd
    return a > b;
}

int main() {
    while( scanf( "%d%d", &N, &M ) != EOF ) {
        printf( "%d %d\n", N, M );
        if( N == 0 )
            return 0;

        for( int i = 0; i < N; i++ )
            scanf( "%d", &numbers[i] );

        std::sort( numbers, numbers + N, precedes );

        for( int i = 0; i < N; i++ )
            printf( "%d\n", numbers[i] );
    }
    return 0;
}
