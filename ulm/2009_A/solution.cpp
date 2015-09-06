#include <stdio.h>

/* Since the lottery prizes grow exponentially,
 * the participant that wins the last round
 * will have more money than everyone else.
 * Even if someone wins all the other prizes,
 * the last round winner will have one more Bytelandian dollar.
 *
 * Therefore, since the only important number
 * is the ticket count for the last round,
 * that is the only information we will leave avaliable to solve().
 */
int last_round_tickets[10000];
int n;

int gcd( int a, int b ) {
    if( b == 0 )
        return a;
    return gcd( b, a % b );
}

void solve() {
    /* The algorithm is, thus, simple: sum all tickets for each round,
     * and divide the ticket count of each participant by the sum.
     *
     * As the problem guarantees that the ticket count for any round
     * will be at most 1e9, an integer is enough to hold the sum.
     */
    int sum = 0;
    for( int i = 0; i < n; i++ )
        sum += last_round_tickets[i];

    /* To present this information in lowest terms,
     * just divide both the numerator and the denominator
     * by their greatest common divisor.
     */
    for( int i = 0; i < n; i++ ) {
        int gcd = ::gcd( last_round_tickets[i], sum );
        printf( "%d / %d\n", last_round_tickets[i]/gcd, sum/gcd );
    }
}

int main() {
    int m;
    while( scanf( "%d%d", &n, &m ) != EOF && n != 0 ) {
        for( int i = 0; i < n; i++ ) {
            /* We need to store just the last read value in the array
             * last_round_tickets. Thus, we will just read everything
             * to that array;
             * the last read value is the one that will remain.
             */
            for( int j = 0; j < m; j++ )
                scanf( "%d", &last_round_tickets[i] );
        }
        solve();
    }
    return 0;
}
