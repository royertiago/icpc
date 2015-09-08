#include <stdio.h>
#include <utility>
#include <math.h>

/* First, start by factoring N, which is guaranteed to be a product of primes.
 * Since N < 1e9, using a brute-force approach
 * (testing every number until sqrt(N))
 * will suffice.
 */
std::pair<int, int> factorize( int N ) {
    if( N % 2 == 0 )
        return {2, N/2};

    int lim = sqrt(N) + 1; // Avoid rounding errors

    /* Small optimization: test every other number
     * (this avoids uselessly testing even numbers). */
    for( int i = 3; i <= lim; i+=2 )
        if( N % i == 0 )
            return {i, N / i};

    // Should never happen
    return {1, N};
}

/* Next, compute Phi(N), using the factorization.
 * We use the fact that N is a product of distinct primes.
 */
int phi( int N ) {
    auto pair = factorize( N );
    return (pair.first - 1)*(pair.second - 1);
}

/* To compute modular inverses, we will make use of
 * Extended Euclidean algorithm.
 * Since we only need the values X and Y,
 * our algorithm will just return a std::pair with these values,
 * instead of a triple with the GCD.
 *
 * Note that, altough there is a multiplication there,
 * there is no need to switch to long long integers
 * since the extended euclidean algorithm always return "small" numbers,
 * in the sense that both X and Y are smaller than
 * the maximum of a and b.
 */
std::pair<int, int> euclid( int a, int b ) {
    if( b == 0 )
        return {1, 0};
    auto pair = euclid( b, a%b );
    return { pair.second, pair.first - pair.second *(a/b) };
}

/* Now, we can recover the private number D from N and E.
 */
int extract_private( int N, int E ) {
    int phiN = phi(N);
    auto pair = euclid( E, phiN );
    /* pair == {x, y} such that x*E + y*phiN == 1.
     * Applying mod phiN to both sides of the equation yield
     * x*E == 1 (mod phiN),
     * so x is the desired private key.
     *
     * Note that the return value of the euclidean algorithm
     * may be negative, and, according to C rules for the operation %,
     * negative mod positive is negative.
     * Thus, we need to make it positive "by hand".
     */
    return (pair.first + phiN) % phiN;
}

/* To recover the original text, we will need to raise a number
 * to a potentially large other number, thus we will use
 * modular exponentiation (square-multiply).
 *
 * Here we need b to be 64-bits, because this value
 * is involved in every multiplication of the algorithm.
 */
int exp( long long int b, int e, int mod ) {
    int ret = 1;
    while( e != 0 ) {
        if( e % 2 == 1 )
            ret = (ret * b) % mod;
        b = (b * b) % mod;
        e >>= 1;
    }
    return ret;
}

/* Finally, we can break RSA!
 * First, recover the private key using extract_private.
 * Then, raise the text to the private key and return.
 */
int solve( int N, int E, int C ) {
    int D = extract_private( N, E );
    return exp( C, D, N );
}

int main() {
    int N, E, C;
    scanf( "%d%d%d", &N, &E, &C );
    printf( "%d\n", solve(N, E, C) );
    return 0;
}
