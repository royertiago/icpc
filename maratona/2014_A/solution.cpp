#include <stdio.h>

int main() {
    int x, y;
    scanf( "%d%d", &x, &y );
    /* The first pilot needs X seconds to complete a lap;
     * thus, after t seconds, that pilot will have completed t/x laps,
     * rounded down.
     * (By the problem statement, t/x rounded up is the lap number.)
     * Similarly, after t seconds, the slowest pilot completes t/y laps.
     *
     * We wish to find the first t such that t/x = 1 + t/y.
     * Rearranging the terms, we reach the formula
     * t = xy/(y - x).
     *
     * But we are not after t, we want the lap number at time t.
     * So divide t by x, and we have
     * laps = y/(y - x), rounded up.
     *
     * To round up, we will use the trick that
     * p/q rounded up equals (p+q-1)/q rounded down.
     */
    printf( "%d\n", (y + (y-x) - 1)/(y-x) );
    return 0;
}
