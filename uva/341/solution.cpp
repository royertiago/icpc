#include <stdio.h>
#include <vector>
#include <set>

#define MAX 10
#define target first
#define cost second

bool visited[MAX];
int previous[MAX];
int delay[MAX];
std::vector< std::pair<int, int> > intersections[10];

int N;

/* To implement Dijkstra, we will use a std::set as our priority queue.
 * We will not use the unicity properties of std::set,
 * but the ordering guarantees --- in particular, the fact that
 * *std::set::begin() is always the smaller element in the set.
 *
 * Therefore, we must impose a strict total ordering over the nodes.
 * cmp will be the comparison functor.
 * The node with smaller delay will always be treated as "smaller",
 * so *std::set::begin() retrieves it.
 *
 * There is a detail we must be aware:
 * no two equal nodes can be inserted in a std::set.
 * Thus, if two nodes have the same delay,
 * we must have a criterion to break the tie,
 * otherwise the std::set will silently throw one of the values away.
 * That's why, when the delays are the same,
 * we add the additional predicate 'a < b'.
 *
 * (There is nothing special about 'a < b' other than it imposing some strict ordering;
 * the algorithm would be perfectly corret if we had replaced it with (say) 'a > b'.)
 */
struct cmp {
    bool operator()( int a, int b ) {
        if( delay[a] != delay[b] )
            return delay[a] < delay[b];
        return a < b;
    }
};

// Runs Dijkstra's algorithm
void dijkstra( int starting ) {
    for( int i = 0; i < N; i++ )
        delay[i] = 1 << 30;
    for( int i = 0; i < N; i++ )
        visited[i] = false;

    delay[starting] = 0;
    previous[starting] = starting;
    /* No need to set other values of "previous",
     * since all values of "delay" are "infinity";
     * thus, every intersection will eventually have its "previous"
     * set to some valid intersection.
     */

    std::set< int, cmp > queue;
    queue.insert( starting );
    while( !queue.empty() ) {
        int current = *queue.begin();
        queue.erase( queue.begin() );
        visited[current] = true;

        for( auto street : intersections[current] ) {
            if( delay[current] + street.cost < delay[street.target] ) {
                /* First, remove the node (Cost: log N)
                 * If street.target were not actually in the queue,
                 * since it is a std::set, the insertion fails silently.
                 */
                queue.erase( street.target );
                // Then, update the cost
                delay[street.target] = delay[current] + street.cost;
                /* And finally, insert the node back,
                 * with the cost updated. (Cost: log N)
                 */
                queue.insert( street.target );

                // Must not forget to update the vector "previous".
                previous[street.target] = current;
            }
        }
    }
}

int print_buffer[MAX];

// Reconstructs the smallest possible path from the start to "destiny".
void print( int destiny ) {
    print_buffer[0] = destiny;
    int i = 0;
    do {
        i++;
        print_buffer[i] = previous[print_buffer[i-1]];
    } while( previous[print_buffer[i]] != print_buffer[i] );

    printf( "%d", print_buffer[i] + 1 );
    for( i--; i >= 0; i-- )
        printf( " %d", print_buffer[i] + 1 );

    printf( "; %d second delay\n", delay[destiny] );
}

int main() {
    int t = 1;
    while( scanf( "%d", &N ) != 0 && N != 0 ) {
        for( int i = 0; i < N; i++ )
            intersections[i].clear();

        for( int i = 0; i < N; i++ ) {
            int streets;
            scanf( "%d", &streets );
            for( int j = 0; j < streets; j++ ) {
                int target, cost;
                scanf( "%d %d", &target, &cost );
                target--;
                intersections[i].push_back( std::make_pair(target, cost) );
            }
        }
        int source, target;
        scanf( "%d %d", &source, &target );
        source--; target--;
        dijkstra( source );
        printf( "Case %d: Path = ", t++ );
        print( target );
    }
}
