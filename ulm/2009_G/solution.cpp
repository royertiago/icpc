#include <stdio.h>

/* Generate the next "random" number from the current one.
 */
int next( int current ) {
    current *= current;
    current /= 100;
    /* Dividing by 1000 discards the last two decimal digits,
     * and shifts the other digits to the right.
     * Then, by computing the number modulo 10000,
     * we have the middle 4 digits. */
    return current % 10000;
}

bool scanned[10000];

int solve( int n ) {
    for( int i = 0; i < 10000; i++ )
        scanned[i] = false;

    /* Brute force solution: just generate every random number
     * until some number repeats.
     * As there are only 10000 different numbers with four digits,
     * this solution is fast enough.
     */
    int count = 1;
    scanned[n] = true;
    while( true ) {
        n = next(n);
        if( scanned[n] )
            return count;
        scanned[n] = true;
        count++;
    }
}

int main() {
    int n;
    while( scanf( "%d", &n ) != 0 && n != 0 )
        printf( "%d\n", solve(n) );
    return 0;
}
