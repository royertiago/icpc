#include <stdio.h>

char S[(int)1e5 + 1]; // Extra space for null terminator
char R[101];

bool solve() {
    char * s = S;
    char * r = R;
    /* We will iterate through S and R using the two pointers s and r.
     * 's' will be advanced once per iteration.
     * 'r' will be advanced only when the values *r and *s are equal.
     * If we reach the end of R, then every character of R appeared in S
     * and in the correct order, so return true.
     * Otherwise, if we reach the end of S,
     * there are some characters of R that were left out,
     * so return false.
     *
     * To prove correctness, use the following loop invariant:
     * The prefix R[0,...,r) is the largest prefix of R
     * that is a subsequence of S[0,...,s).
     */
    for( ; *s != '\0'; ++s ) {
        if( *s == *r ) {
            r++;
            if( *r == '\0' )
                return true;
        }
    }
    return false;
}

int main() {
    int t;
    scanf( "%d", &t );
    while( t-- ) {
        scanf( "%s", S );
        int Q;
        scanf( "%d", &Q );
        while( Q-- ) {
            scanf( "%s", R );
            printf( solve() ? "Yes\n" : "No\n" );
        }
    }
    return 0;
}
