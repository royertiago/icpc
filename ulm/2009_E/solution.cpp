#include <stdio.h>

#define INF (1 << 30)
int min( int i, int j ) { return i < j ? i : j; }

int c[128];

// s[i][j] = c[i] + c[i+1] + ... + c[j]
int s[128][128];

/* dp[i][j] is the least amount of bits needed to encode
 * all numbers with size between 1 and i+1
 * using at exactly j+1 different prefix sizes.
 * (The "exactly" part will reduce the search effort.)
 *
 * Note we will always have j <= i.
 */
int dp[128][128];
int n;

int solve() {
    // Precompute s[i][j]
    for( int i = 0; i < n; i++ ) {
        s[i][i] = c[i];
        for( int j = i + 1; j < n; j++ )
            s[i][j] = s[i][j-1] + c[j];
    }

    /* Base case: i == 0.
     * The only way of encoding all numbers
     * is to use 1 bit to the prefix and 1 bit to encode the number,
     * thus resulting in 2 bits per number.
     * As we have c[0] different numbers to encode,
     *  2*c[0]
     * is the optimum value.
     */
    dp[0][0] = 2*c[0];

    // Induction: i > 0.
    for( int i = 1; i < n; i++ ) {
        /* "Sub-base" case: j == 0,
         * so everything have the same unary prefix
         * (remember dp[i][j] is the optimum with j+1 different prefixes).
         *
         * We have s[0][i] different numbers,
         * and each will need to be encoded with i+1 bits,
         * plus one bit for the prefix.
         */
        dp[i][0] = s[0][i] * (i+1 + 1);

        // Induction: j > 0.
        for( int j = 1; j <= i; j++ ) {
            /* For each k >= 1, we will try to create a new block
             * with the last k number sizes
             * and assign a single prefix to them.
             * The prefix has size j+1,
             * and the numbers have to be coded with i+1 bits.
             *
             * The last k numbers are i-(k-1), i-(k-2), ..., i-(k-k),
             * so we have s[i-k+1][i] numbers in this new block;
             * the other i-k+1 number sizes
             * have minimum cost dp[i-k][j-1].
             *
             * This last observation imposes the upper bound on k:
             * as we must have j-1 <= i-k, we also must have
             *  k <= i+1-j.
             */
            dp[i][j] = INF;
            for( int k = 1; k <= i+1-j; k++ )
                dp[i][j] = min( dp[i][j],
                                dp[i-k][j-1] + s[i-k+1][i] * (i+1 + j+1) );
        }
    }

    /* Then, just minimize the value of dp[n-1][j]
     * for every possible number of prefix sizes j.
     */
    int ans = INF;
    for( int j = 0; j < n; j++ )
        ans = min( ans, dp[n-1][j] );
    return ans;
}

int main() {
    while( scanf("%d", &n) != EOF && n != 0 ) {
        for( int i = 0; i < n; i++ )
            scanf( "%d", &c[i] );
        printf( "%d\n", solve() );
    }
    return 0;
}
