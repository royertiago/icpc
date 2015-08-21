#include <stdio.h>
#include <vector>
#include <string>

using namespace std;
std::vector<int> input;
std::vector<int> capacity;
std::vector<int> size;

bool solve() {
    /* We will use two stacks;
     * one will store the "remaining capacity" of the current doll,
     * and the other will store the opening size (to guarantee correct nesting).
     */
    capacity.clear();
    size.clear();

    // Sentinels
    capacity.push_back( 0 );
    size.push_back( 0 );

    for( int m : input ) {
        if( m < 0 ) { // push
            capacity.back() += m;
            size.push_back( -m );
            capacity.push_back( -m );
        }
        else { // pop
            if( m != size.back() || capacity.back() <= 0 )
                return false;
            size.pop_back();
            capacity.pop_back();
        }
    }
    // Return true if the vector size contains only the sentinel
    return size.size() == 1;
}

int main() {
    int i;
    char c;
    /* scanf( "%d%c" ) will scan the next integer
     * and the character right after it.
     * Then, if the character is '\n', we reached the end of the line,
     * and must process the respective matrioshka.
     */
    while( scanf( "%d%c", &i, &c ) != EOF ) {
        input.push_back(i);
        if( c == '\n' ) {
            // Reached the end of the line
            printf( solve() ? ":-) Matrioshka!\n" : ":-( Try again.\n" );
            input.clear();
        }
    }
    return 0;
}
