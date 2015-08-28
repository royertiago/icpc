#include <stdio.h>

int gcd( int a, int b ) {
    while( b != 0 ) {
        int tmp = a;
        a = b;
        b = tmp % b;
    }
    return a;
}

void simplify( int& a, int& b ) {
    /* We may assume b is never negative.
     * The following test guarantees that div is always positive.
     */
    int div = a > 0 ? gcd(a, b) : gcd(-a, b);
    a /= div;
    b /= div;
}

int main() {
    int a, b, c, d, p, q;
    char op;
    int t;
    scanf( "%d\n", &t );
    while( t-- ) {
        scanf( "%d / %d %c %d / %d\n", &a, &b, &op, &c, &d );
        switch( op ) {
            case '+':
                p = a*d + b*c;
                q = b*d;
                break;
            case '-':
                p = a*d - b*c;
                q = b*d;
                break;
            case '*':
                p = a*c;
                q = b*d;
                break;
            case '/':
                p = a*d;
                q = b*c;
        }
        printf( "%d/%d = ", p, q );
        simplify( p, q );
        printf( "%d/%d\n", p, q );
    }
    return 0;
}
