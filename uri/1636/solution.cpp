#include <stdio.h>
#include <utility>

int p[(int) 1e6];
int n;

void solve() {
    int start;
    if( n % 2 == 0 ) {
        p[0] = 2;
        p[1] = 1;
        start = 2;
    }
    else {
        start = 3;
        p[0] = 2;
        p[1] = 3;
        p[2] = 1;
    }
    for( int j = start; j < n; j+=2 ) {
        p[j] = j+2;
        p[j+1] = j+1;
        std::swap( p[j+1], p[j-2] );
    }
}

int main() {
    while( scanf( "%d", &n ) != EOF && n != 0 ) {
        solve();
        printf( "%d", p[0] );
        for( int i = 1; i < n; i++ )
            printf( " %d", p[i] );
        printf( "\n" );
    }
}
