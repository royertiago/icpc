#include <queue>
#include <stack>
#include <stdio.h>

int main() {
    int n;
    while( scanf( "%d", &n ) != EOF ) {
        bool maybe_stack = true;
        bool maybe_queue = true;
        bool maybe_priority_queue = true;
        std::stack< int > stack;
        std::queue< int > queue;
        std::priority_queue<int> priority_queue;

        for( int i = 0; i < n; i++ ) {
            int type, value;
            scanf( "%d%d", &type, &value );
            if( type == 1 ) {
                stack.push( value );
                queue.push( value );
                priority_queue.push( value );
            }
            else {
                if( stack.top() != value )
                    maybe_stack = false;
                if( queue.front() != value )
                    maybe_queue = false;
                if( priority_queue.top() != value )
                    maybe_priority_queue = false;
                queue.pop();
                stack.pop();
                priority_queue.pop();
            }
        }
        if( maybe_stack + maybe_queue + maybe_priority_queue > 1 )
            printf( "not sure\n" );
        else if( maybe_stack + maybe_queue + maybe_priority_queue == 0 )
            printf( "impossible\n" );
        else if( maybe_stack )
            printf( "stack\n" );
        else if( maybe_queue )
            printf( "queue\n" );
        else
            printf( "priority queue\n" );
    }
    return 0;
}
