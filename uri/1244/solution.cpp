#include <vector>
#include <algorithm>
#include <string>
#include <stdio.h>

bool cmp( const std::string & a, const std::string & b ) {
    return a.size() > b.size();
}

int main() {
    int t;
    scanf( "%d", &t );
    while( t-- ) {
        std::vector<std::string> strings;
        char str[51]; // Extra buffer space to hold the '\0'
        char last;
        do {
            scanf( "%s%c", str, &last );
            /* If we reach the end of the line,
             * last will contain '\n'. */
            strings.emplace_back( str );
        } while( last != '\n' );

        std::stable_sort( strings.begin(), strings.end(), cmp );

        const char * sep = "";
        for( auto string : strings ) {
            printf( "%s%s", sep, string.c_str() );
            sep = " ";
        }
        printf( "\n" );
    }
    return 0;
}
