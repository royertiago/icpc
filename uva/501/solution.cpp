#include <stdio.h>
#include <set>

int m, n;
int a[30000];
int u[30001]; // One extra space for the sentinel

/* We will separate between deciding wether the next query is ADD or GET
 * and simulating the black box.
 */
int ai, ui; // a index, u index;
int current_value; // Current number to be pushed in the black box

/* Returns true if the next operation is ADD, and false otherwise.
 * Advances the state of the machine.
 */
bool next_is_add() {
    /* Note that u[ui] always points to a valid address,
     * due to the sentinel.
     * u[ui] > ai will always be false when we reach the sentinel,
     * so there are no "buffer overflows".
     */
    if( u[ui] > ai ) {
        current_value = a[ai++];
        return true;
    }
    else {
        ui++;
        return false;
    }
}

std::multiset<int> black_box;
std::multiset<int>::iterator pointer;
/* black_box is a multiset that will hold all values of the black box,
 * and pointer is an iterator that will point to the value
 * returned by the next GET instruction.
 *
 * We will add numbers to black_box one by one,
 * updating 'pointer' whenever necessary.
 */

void solve() {
    ui = ai = 0; // Reset next_is_add
    black_box.clear();
    pointer = black_box.end();
    for( int i = 0; i < m + n; i++ ) // There are n + m requested operations.
        if( next_is_add() ) {
            // Run add instruction
            black_box.insert( current_value );
            if( pointer == black_box.end() ) {
                /* The problem statement guarantees that there will always be
                 * enough ADDs before a GET. Thus, pointer == black_box.end()
                 * will only happen when there were exactly the same number of ADDs
                 * and GETs --- for instance, when the algorithm begins ---,
                 * so with this new insertion,
                 * the last element will be the next GET output.
                 * So, just decrement.
                 */
                --pointer;
            }
            else if( current_value < *pointer ) {
                /* Here, the inserted value was placed before the previous value
                 * that would be outputted in the next GET instruction,
                 * so we must decrement 'pointer' to compensate.
                 *
                 * C++11 guarantees that, if current_value is equivalent to *pointer,
                 * then it will be placed in the container after it,
                 * so we do not need to decrement in this case.
                 * (C++11 Standard, N3936, table 102, "a_eq.insert")
                 */
                --pointer;
            }
        }
        else { // GET instruction
            printf( "%d\n", *pointer );
            ++pointer;
        }
}

int main() {
    const char * sep = ""; // Separator between test cases

    int k;
    scanf( "%d", &k );
    while( k-- ) {
        scanf( "%d%d", &m, &n );
        for( int i = 0; i < m; i++ )
            scanf( "%d", &a[i] );
        for( int j = 0; j < n; j++ )
            scanf( "%d", &u[j] );
        u[n] = m; // sentinel

        printf( sep );
        sep = "\n";
        solve();
    }
}
