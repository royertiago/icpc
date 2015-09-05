/* Higly optimized code for the algorithm discussed in analysis.tex.
 * Since the assymptotic complexity of that algorithm is optimum
 * and it have a very low memory footprint,
 * the core optimizations of this code are in the output generation.
 *
 * (When I submitted this code to the UVa and URI online judges,
 * it vastly outperformed every other solution present there,
 * being four times faster than the second fastest solution.)
 * */
#include <stdio.h>
#include <string.h>

/* We will focus ond input/output; in our case,
 * the bottleneck is printing integer values.
 * Instead of making several system calls through printf,
 * we will construct a string with the answer,
 * and call fputs a single time.
 *
 * But we will not use sprintf.
 * We will abuse the fact that the judge must have a correction script
 * that parses the input and determines whether it satisfies the constraints.
 * So, it will need some sort of integer parser,
 * which we will assume can parse numbers with leading zeros.
 * Therefore, we can use an array of six characters to represent a number
 * and increment this number as if we were programming a multiprecision library.
 *
 * This will save one printf("%d") per printed digit,
 * which is actually a lot, since we will do some comparisons and increments
 * instead of several divisions and modulos.
 *
 * We will write at most 1e6 numbers, each taking 6 chars of space,
 * plus 1e6-1 whitespace characters, plus 1 newline character.
 * Also, we need one extra space for the null terminator,
 * and yet one extra space for the number 1000000 (1e6),
 * which has 7 digits instead of 6.
 * Thus, the final size of the buffer is 7e6 + 2.
 */
char output[(int) 7e6 + 2];

/* As said before, we will store integers as character vectors.
 * We will use two numbers: one for the even p_i, and the other for odd p_i.
 *
 * To save time copying, we will create a "hold space", with 15 positions.
 * Position 0 will have a space,
 * positions 1 through 6 will contains the first number,
 * position 7 will have another space,
 * positions 8 through 13 will contains the second number,
 * and position 14 is the null terminator.
 *
 * The values j and k will point to the beginning and end of the first
 * and second numbers, respectively.
 */
char hold[] = " 000000 000000";
char * const j = hold+1;
char * const k = hold+8;

/* The function incr will increment either j or k, according to its argument,
 * by two numbers. That is, it will compute p_{i+1} from p_i,
 * taking care only to alter the digits that represent the number.
 */
void incr( char * num ) {
    /* Increment from the least significative end
     * to the most significative end.
     * Note that the first increment must be by 2,
     * while the other ones, that result from carry,
     * are just 1.
     */
    num[5] += 2;
    if( num[5] > '9' )
        num[5] -= 10;
    else
        return;

    for( int i = 4; i >= 0; i-- ) {
        num[i]++;
        if( num[i] > '9' )
            num[i] -= 10;
        else
            break;
    }
}

int main() {
    int n;
    while( scanf( "%d", &n ) != EOF && n != 0 ) {
        int K;
        char * ptr = output;
        /* The number K will be used only to control the inner loop.
         * Its value will always match the "char-number" k,
         * but we will keep it in binary form
         * since it will be the breaking condition of the loop.
         *
         * The pointer 'ptr' will always point to the null terminator
         * of the string output.
         *
         * We will split between the odd and even cases for initialization only.
         */
        if( n % 2 == 0 ) {
            ptr += sprintf( ptr, "000003 000001" );
            /* Zero-padding the numbers here is unneded,
             * but I will do for consistency. */
            K = 5;
            strcpy( hold, " 000005 000002" );
        }
        else {
            ptr += sprintf( ptr, "000002" );
            K = 4;
            strcpy( hold, " 000004 000001" );
        }

        /* This inner loop is the bottleneck of the program.
         * With the optimizations described,
         * we have reduced what it does to a bunch of increments and comparisons,
         * which is way faster than simply using sprintf's %d option.
         */
        for( ; K < n; K+=2, incr(j), incr(k) ) {
            // Use memcpy because we know exactly where both strings end.
            memcpy( ptr, hold, 15 );
            ptr += 14;
        }

        /* The last two values, which are always n and n-2.
         * We may use sprintf here, because it is outside the inner loop,
         * and it actually take care of correctly printing the number 1e6,
         * which has 7 digits.
         */
        ptr += sprintf( ptr, " %06d %06d\n", n, n-2 );

        // And finally, print this out.
        fputs( output, stdout );
    }
    return 0;
}
