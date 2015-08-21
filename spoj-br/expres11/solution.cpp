#include <stdio.h>

char input[(int)1e5 + 1]; // Need an extra char for the null terminator
char stack[(int)1e5 + 1]; // Need an extra char for the sentinel

bool solve() {
    char * c = input;
    stack[0] = ' '; // sentinel
    int top = 0;
    /* Note that stack[top] will always point to a valid address,
     * due to the sentinel. */
    while( *c != '\0' ) {
        switch( *c ) {
            case '(':
            case '[':
            case '{':
                stack[++top] = *c;
                break;
            case ')':
                if( stack[top--] != '(' )
                    return false;
                break;
            case ']':
                if( stack[top--] != '[' )
                    return false;
                break;
            default: // case '}'
                if( stack[top--] != '{' )
                    return false;
        }

        ++c;
    }
    // Return true if the stack is empty.
    return top == 0;
}

int main() {
    int t; // test cases
    scanf( "%d\n", &t );
    while( t-- ) {
        scanf( "%s\n", input );
        printf( solve() ? "S\n" : "N\n" );
    }
    return 0;
}
