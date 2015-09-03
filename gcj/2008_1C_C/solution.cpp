#include <stdio.h>
#include <algorithm>

#define MOD ((int) 1e9 + 7)

/* limits will hold the sequence of speed limits,
 * after it had been generated from the sequence A.
 */
int input[(int) 5e5];
int n;

/* Part of the problem will require a binary indexed tree (Fenwick tree).
 * This vector will hold the tree data, and the two next functions
 * will take care of retrieving and modifying the tree.
 *
 * For convenience, the BIT functions will handle 0-indexing for us.
 */
int BIT[(int) 5e5 + 1];

int get( int index ) {
    index++;
    int ret = 0;
    for( int i = index; i != 0; i -= (i & -i) )
        ret = (ret + BIT[i]) % MOD;
    return ret;
}

void add( int index, int value ) {
    index++;
    for( int i = index; i <= n; i += (i & -i) )
        BIT[i] = (BIT[i] + value) % MOD;
}

// Structure used to simplify the sorting process.
struct pair {
    int value, index;
};
bool operator<( pair a, pair b ) {
    if( a.value != b.value )
        return a.value < b.value;
    return b.index < a.index;
}
pair limits[(int)5e5];

int solve() {
    /* We will keep the following invariant:
     * get(i) will say the number of all strictly increasing subsequences
     * that can be constructed using the first i speed limits
     * that were already processed.
     *
     * Reset the BIT first, since no value was already processed.
     */
    for( int i = 0; i <= n; i++ )
        BIT[i] = 0;

    /* We will process the speed limits in increasing order,
     * and then in decreasing index.
     * So, for example, if the limits are 1 2 1 3 2,
     * we will first process the second 1, then the first 1,
     * then the second 2, then the first 2, then the 3.
     *
     * This will guarantee that, when we process the speed limit
     * at index K, every increasing sequence that is represented by
     * the number get(K) will have had its last speed limit
     * strictly smaller than K's speed limit,
     * because all smaller values would have been processed,
     * no larger value were processed,
     * and equal values that occour before K have not been processed.
     */
    for( int i = 0; i < n; i++ )
        limits[i] = {input[i], i};
    std::sort( limits, limits + n );

    for( int i = 0; i < n; i++ ) {
        /* Now, keep the invariant.
         * For of the 'get(limits[i].index)' sequences
         * that can be built using the speed limits from the set
         * {1, 2, ..., limits[i].index} that were already analyzed,
         * we can create another sequence appending limits[i].value to it.
         * Thus, we have get(limits[i].index) new sequences,
         * plus the sequence consisting of only the current speed limit.
         */
        add( limits[i].index, (get(limits[i].index) + 1)%MOD );
    }
    return get( n-1 );
}

int A[100];

int main() {
    int N;
    scanf( "%d", &N );
    for( int c = 1; c <= N; c++ ) {
        int m;
        long long int X, Y, Z;
        scanf( "%d%d%lld%lld%lld", &n, &m, &X, &Y, &Z );
        for( int i = 0; i < m; i++ )
            scanf( "%d", &A[i] );

        /* Generate sequence of limits
         * Altough the final value of the modulo operation
         * will leave a number smaller than 2^31
         * (which would fit in an integer),
         * the intermediate results multiply two numbers
         * whose sizes are around 2^30, thus resulting in the value
         * 2^60, which needs a long long int to not overflow.
         * Choosing X, Y, and Z as long long implicitly converts
         * every value below to long long, thus simplifying the code.
         */
        for( int i = 0; i < n; i++ ) {
            input[i] = A[i % m];
            A[i % m] = (X * A[i % m] + Y * (i + 1)) % Z;
        }

        printf( "Case #%d: %d\n", c, solve() );
    }
    return 0;
}
