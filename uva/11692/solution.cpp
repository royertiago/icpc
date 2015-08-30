#include <stdio.h>
#include <math.h>

int main() {
    int t;
    scanf( "%d", &t );
    while( t-- ) {
        double L, K, R, D, H;
        scanf( "%lf%lf%lf%lf%lf", &L, &K, &R, &D, &H );

        if( L > H ) {
            printf( "%.6lf %.6lf\n", H, H );
            continue;
        }

        double b = H + K*R + K*D;
        double max = (b + sqrt(b*b - 4*R*K*L)) / 2;
        if( L < H )
            printf( "%.6lf %.6lf\n", max, max );
        else
            printf( "%.6lf %.6lf\n", H, max );
    }
    return 0;
}
