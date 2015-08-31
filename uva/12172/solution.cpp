#include <stdio.h>

// Prints the highest possible value.
void print_max( int n ) {
    /* To form the maximum number,
     * we need to maximize the amount of digits first,
     * and the number generated last.
     * Since the number constructible with the least amount of sticks
     * is '1', which uses 2 sticks (strictly the smallest),
     * we will separate between the odd and even cases.
     */
    if( n % 2 == 0 ) {
        /* For 'n' even, we can build a string with only ones.
         * Since any string that use a different digit will have less digits,
         * that is the highest possible value.
         */
        for( int i = 0; i < n/2; i++ )
            printf( "1" );
    }
    else {
        /* For odd 'n', we cannot use a string of ones
         * because it leaves one stick out.
         * Thus, the best is to create one seven
         * (using three sticks) and build ones with the rest.
         * (Note we maximize the number of digits;
         * and given this setup, we must build exactly n/2-1 ones
         * and one seven, so writing the seven first
         * gives the maximum number.)
         */
        printf( "7" );
        for( int i = 0; i < n/2 - 1; i++ )
            printf( "1" );
    }
}

// Prints the smallest possible value
void print_min( int n ) {
    /* Printing the minimum is harder.
     * Here, we need to build the least amount of digits,
     * and we must take care not to write leading zeros.
     * The number that takes the largest number of matchsticks is '8',
     * with seven sticks, so we will divide the cases
     * according to the value of n % 7.
     *
     * Note that the least amount of digits is n/7 rounded up.
     */
    switch( n % 7 ) {
    case 0:
        /* The easiest. We can create a string with just eights.
         */
        for( int i = 0; i < n/7; i++ )
            printf( "8" );
        break;

    case 6:
        /* Also easy. Only '0', '6' and '9' can be built with six matches;
         * so, any string with n/7+1 digits must have n/7 eights
         * and one of the other two digits.
         * As we cannot have a leading zero,
         * the smallest possible number for the leading digit is '6'.
         * Thus, the smallest number is a '6' followed by n/7 eights.
         */
        printf( "6" );
        for( int i = 0; i < n/7; i++ )
            printf( "8" );
        break;

    case 2:
        /* The minimum solution will have n/7 + 1 digits.
         * As we forbid leading zeros, the least leading digit is '1',
         * and there is only one string of n/7+1 digits,
         * using n matchsticks, with a leading '1'.
         * Therefore, this is the smallest possible number.
         */
        printf( "1" );
        for( int i = 0; i < n/7; i++ )
            printf( "8" );
        break;

    case 5:
        /* Still easy. Using five sticks, we can build '2', '3' and '5'.
         * Thus, using exactly n/7 + 1 matchsticks,
         * we can either create one '2', '3' or '5' and n/7 eights,
         * or two digits from the set {0, 6, 9} and n/7-1 eights.
         * Of these possibilities, the smallest leading digit is '2',
         * so we go with this option.
         */
        printf( "2" );
        for( int i = 0; i < n/7; i++ )
            printf( "8" );
        break;

    case 4:
        /* Things gets tricky now.
         * We can build a '4', and the rest all eights;
         * or build one from {2, 3, 5}, one from {6, 9, 0} and rest '8',
         * or three from {6, 9, 0} and rest '8'.
         * Since these solutions all have the same number of digits,
         * we will minimize the leading digit; thus, it will be a '2'.
         * We have the choice between {6, 8, 9, 0} for the second digit,
         * so we will first produce the digits "20",
         * and the remaining n/7 - 1 digits will be zeros.
         *
         * However, there is one special case: if n = 4,
         * we have not enough sticks to write "20",
         * so we are forced to build the number '4'
         * (indeed the only number that uses four matchsticks.)
         */
        if( n == 4 ) {
            printf( "4" );
            break;
        }
        printf( "20" );
        for( int i = 0; i < n/7 - 1; i++ )
            printf( "8" );
        break;

    case 3:
        /* As before, we have a combinatorial explosion of possibilities.
         * We will try to minimize it by imposing a condition
         * on the first digit. Note it cannot be a '1',
         * since then we would be left with an extra matchstick,
         * thus unable to attain the smallest number of digits
         * (which is our highest priority).
         * Thus it should be a '2'; as we saw in the previous case,
         * we can adjust the remaining digits to allow for a leading '2'
         * without violating the constraint on the number of digits.
         *
         * So, we use five sticks to build the leading '2',
         * leaving "-2 sticks" --- that is, we have a surplus of five sticks
         * until the next multiple of seven.
         * As in the 'case 5:', we can either build one digit from
         * {2, 3, 5}, or two digits from {6, 9, 0}.
         * Since we already have a leading digit,
         * we can actually use the zeros that we can create;
         * thus, the smallest possible number is made with a leading '200',
         * and the remaining n/7 - 2 digits are only eights.
         *
         * As before, we have two special cases,
         * when we have no enough sticks to create the leading '200':
         * 3 sticks and 10 sticks.
         * In the first case, the only possible number is '7',
         * so we have no choice.
         * For n = 10, we also must have a leading '2',
         * but the other digit must be from the set {2, 3, 5};
         * thus, the best is '22'.
         */
        if( n == 3 )
            printf( "7" );
        else if( n == 10 )
            printf( "22" );
        else {
            printf( "200" );
            for( int i = 0; i < n/7 - 2; i++ )
                printf( "8" );
        }
        break;

    case 1:
        /* The final case. Again, we will try to constrain the first digit;
         * but in this case, this approach renders an easy solution,
         * since the string "10" can be built with eight matchsticks,
         * and this string actually is
         * the smallest possible pair of leading digits.
         *
         * And we have no special cases, because the case n == 1 never happen.
         */
        printf( "10" );
        for( int i = 0; i < n/7-1; i++ )
            printf( "8" );
        break;
    } // end switch
}

int main() {
    int t;
    scanf( "%d", &t );
    while( t-- ) {
        int n;
        scanf( "%d", &n );
        print_min( n );
        printf( " " );
        print_max( n );
        printf( "\n" );
    }
    return 0;
}
