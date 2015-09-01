#include <stdio.h>

char digits[41];

/* rem(i, j) returns the value of digits[i, ..., j] % 210.
 * This function will be useful later on.
 */
int rem( int i, int j ) {
    int S = 0, ten = 1;
    for( int k = j; k >= i; k-- ) {
        S = (S + (digits[k] - '0') * ten) % 210;
        ten = (ten * 10) % 210;
    }
    return S;
}

/* We will solve this problem through a dynamic programming algorithm.
 * dp[i][j] is how many numbers that can be formed from the prefix
 * digits[0, ..., i] such that its remainder modulo 210 is j.
 *
 * We have chosen the remainder to be modulo 210 because we want,
 * actually, to extract separately the number of expressions
 * whose value modulo 2, 3, 5 and 7 are zero. As 210 = 2*3*5*7,
 * we extract the value modulo all these digits at once,
 * while also taking into account overlaps between them.
 */
long long int dp[40][210];

long long int solve() {
    /* Base case: i == 0. We can build only one expression,
     * and its value modulo 210 equals digits[0].
     */
    for( int j = 0; j < 210; j++ )
        dp[0][j] = 0;
    dp[0][digits[0] - '0'] = 1;

    /* Inductive case: we will split the string in position k,
     * for 0 <= k < i, forming two numbers: digits[0, ..., k]
     * and digits[k+1, ..., i].
     * (k will be the latest split in the prefix digits[0, ..., i].)
     * The counting of all possible expressions constructible from
     * the number digits[0, ..., k] we will retrieve from dp[k],
     * and the value of digits[k+1, ..., i] modulo 210 will be stored in S
     * (the value of the Suffix).
     */
    int i;
    for( i = 1; digits[i] != '\0'; i++ ) {
        for( int j = 0; j < 210; j++ )
            dp[i][j] = 0;

        for( int k = i-1; k >= 0; k-- ) {
            /* We could have built S iteratively,
             * thus eliminating the need for the function 'rem',
             * but the bottleneck of the code is in the nested loop,
             * not in this function call.
             */
            int S = rem( k+1, i );

            for( int j = 0; j < 210; j++ ) {
                /* S is digits[k+1, ..., i] % 210.
                 * dp[k][j] gives how many splittings of digits[0, ..., k]
                 * leave j modulo 210.
                 * If we put a '+' between these two numbers,
                 * the remainder of the expression will be j+S,
                 * so we cann add dp[k][j] expressions to dp[i][j+S].
                 */
                dp[i][(j+S) % 210] += dp[k][j];
                /* And if we put a '-' between these two numbers,
                 * the remainder is j-S.
                 */
                dp[i][(j-S+210) % 210] += dp[k][j];
            }
        }
        /* We have computed all possible splittings of digits[0, ..., i];
         * it just remain the trivial case of no splitting at all.
         */
        dp[i][rem(0, i)]++;
    }
    long long int total = 0;
    // Finally, just count the ugly numbers.
    for( int j = 0; j < 210; j++ )
        if( j % 2 == 0 || j % 3 == 0 || j % 5 == 0 || j % 7 == 0 )
            total += dp[i-1][j];

    return total;
}

int main() {
    int n;
    scanf( "%d", &n );
    for( int i = 1; i <= n; i++ ) {
        scanf( "%s", digits );
        printf( "Case #%d: %lld\n", i, solve() );
    }
    return 0;
}
