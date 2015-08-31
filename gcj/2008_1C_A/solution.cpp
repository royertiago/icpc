#include <stdio.h>
#include <algorithm>

int P, K, L;
int freq[1000];

long long int solve() {
    /* Simply put the most used letters in the first position;
     * then the most used letters among the remaining in the second position;
     * and so on.
     * Any key assignment that does not follow this strategy
     * may be improved by swapping an highly used letter in a distant position
     * for a less used letter in a position closer to the start,
     * strictly reducing the minimum number of key presses.
     * Thus, this strategy yields the best value.
     */
    std::sort( freq, freq + L, [](int a, int b){ return a > b; } );
    /* The largest possible total happens when the frequency of each letter
     * is exactly 1e6 (the maximum), and there are a single key
     * for a thousand letters (also the maximum).
     * Thus, the total key presses is
     *  1e6 + 2e6 + 3e6 + ... + 1000e6 = (1000*1001/2) * 1e6
     * which is 5.005e12.
     * Thus, we need a long long integer to sum everything.
     */
    long long int total = 0;
    /* The first K values are going to contribute with 1 key press
     * per letter use; the next K are going to contribute with 2 key presses,
     * and so on.
     * Thus, the value in position i contributes with 1+i/K key presses,
     * rounded down, per letter use.
     */
    for( int i = 0; i < L; i++ )
        total += freq[i] * (1 + i / K);

    return total;
}

int main() {
    int N;
    scanf( "%d", &N );
    for( int i = 1; i <= N; i++ ) {
        scanf( "%d%d%d", &P, &K, &L );
        for( int j = 0; j < L; j++ )
            scanf( "%d", &freq[j] );

        printf( "Case #%d: %lld\n", i, solve() );
    }
    return 0;
}
