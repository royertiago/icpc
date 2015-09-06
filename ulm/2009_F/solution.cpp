#include <stdio.h>

int a, b, n;
int y[1000];

int min( int i, int j ) { return i < j ? i : j; }
int max( int i, int j ) { return i > j ? i : j; }

/* How many times a student that eats food_amount needs to fetch food
 * given the size of the portion.
 * Note this still gives the correct answer even if both food_amount
 * and portion are multiplied by 6.
 */
int fetches( int food_amount, int portion ) {
    return (food_amount + portion - 1)/ portion;
}

// Total cost given the portion
int cost( int portion ) {
    int c = 0;
    for( int i = 0; i < n; i++ )
        c += (a * portion + 6 * b) * fetches(y[i], portion) - a * y[i];
    return c;
}

int solve() {
    // We assume y is already multiplied by 6.
    int max_y = 0;
    for( int i = 0; i < n; i++ )
        max_y = max( max_y, y[i] );

    int min_portion = max_y / 3;

    int min_cost = 1 << 30;

    for( int i = 0; i < n; i++ )
        for( int div = 1; div <= 3; div++ ) {
            int portion = y[i]/div;
            if( portion < min_portion )
                continue;
            min_cost = min( min_cost, cost(portion) );
        }

    return min_cost;
}

int main() {
    while( scanf("%d", &n) != EOF && n != 0 ) {
        scanf( "%d%d", &a, &b );
        for( int i = 0; i < n; ++i ) {
            scanf( "%d", &y[i] );
            y[i] *= 6;
        }
        int ans = solve();
        /* Solve will return 6 times the actual answer.
         * Here we will divide it by 6 and print it in lowest terms.
         */
        int numerator = 6;
        if( ans % 2 == 0 ) {
            numerator /= 2;
            ans /= 2;
        }
        if( ans % 3 == 0 ) {
            numerator /= 3;
            ans /= 3;
        }
        if( numerator == 1 )
            printf( "%d\n", ans );
        else
            printf( "%d / %d\n", ans, numerator );
    }
}
