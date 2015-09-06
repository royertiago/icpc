#include <stdio.h>

#define INF (1 << 30)
int min( int i, int j ) { return i < j ? i : j; }

int c[129];

// s[i][j] = c[i] + c[i+1] + ... + c[j]
int s[129][129];

/* dp[i][j][k] is the cheapest way of coding the numbers c[1],...,c[i],
 * such that exactly j different prefixes are used,
 * and forcing the last prefix to cover the last k digit count
 * (that is, the last prefix must represent all numbers
 * with i-k+1, i-k+2, ..., i-1 and i digits).
 *
 * Note we always have j, k <= i.
 * Note also j + k >= i + 1:
 * as the last group have k elements, the remaining i-k
 * must form at most j-1 groups. Thus, i-k <= j-1,
 * or i+1 <= j+k.
 * So we have the lower bound i+1-j for k:
 *   i+1-j <= k <= i.
 */
int dp[129][129][129];

int n;

int solve() {
    // Precompute s[i][j]
    for( int i = 1; i <= n; i++ ) {
        s[i][i] = c[i];
        for( int j = i + 1; j <= n; j++ )
            s[i][j] = s[i][j-1] + c[j];
    }

    // To simplify the solution, set to INF impossible values.
    for( int i = 0; i <= n; i++ )
    for( int j = 0; j <= n; j++ )
    for( int k = 0; k <= n; k++ )
        dp[i][j][k] = INF;

    // Base case: i == 1.
    dp[1][1][1] = 2*c[1];

    // Induction
    for( int i = 2; i <= n; i++ ) {
        for( int j = 1; j <= i; j++ ) {
            /* Two subcases. First, when k == 1,
             * we must allocate a new prefix for the numbers with i digits,
             * so we will brute-force through all possible values of k
             * to minimize dp[i-1][j-1].
             *
             * The value, for each case, is dp[i-1][j-1][k]
             * plus the cost of encoding each of the c[i] numbers
             * which have size i, using a prefix of size j.
             */
            dp[i][j][1] = INF;
            for( int k = 1; k <= i; k++ )
                dp[i][j][1] = min( dp[i][j][1],
                                   dp[i-1][j-1][k] + c[i]*(i+j) );
            /* Now, when k > 1.
             * To compute dp[i][j][k],
             * we are forced to build upon dp[i-1][j][k-1],
             * because we will not create another group.
             * The value is then dp[i-1][j][k-1]
             * plus the cost of encoding the c[i] i-sized numbers
             * using a prefix of size j,
             * plus the padding of the numbers in the previous group,
             * which amounts to one extra digit per number.
             */
            for( int k = 2; k <= i; k++ )
                dp[i][j][k] = dp[i-1][j][k-1] +
                    s[i-k+1][i-1] + c[i]*(i + j);
        }
    }
    int ans = INF;
    for( int j = 1; j <= n; j++ )
    for( int k = 1; k <= n; k++ )
        ans = min( ans, dp[n][j][k] );
    return ans;
}

int main() {
    while( scanf("%d", &n) != EOF && n != 0 ) {
        for( int i = 1; i <= n; i++ )
            scanf( "%d", &c[i] );
        printf( "%d\n", solve() );
    }
    return 0;
}
