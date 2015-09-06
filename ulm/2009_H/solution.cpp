#include <stdio.h>
#include <set>
#include <vector>
#include <utility>

#define target first
#define cost second
#define INF (1 << 30)

typedef std::vector<std::pair<int, int> > node;
typedef node graph[10000];

int n, h, m;
bool has_hotel[10000];

graph cities;
graph hotels; // We will call "hotels" the cities with hotels.

/* We will have two graphs.
 * The first graph is the one given by the problem.
 * The second graph will be built upon the first,
 * but with only the cities that have hotels.
 *
 * The idea is that the edges in this second graph
 * represents the routes the driver can do in a single day of work.
 * To build this graph, we will run Dijkstra algorithm
 * starting from every node that has an hotel.
 *
 * Since we only interested in edges that can be reached
 * under 600 minutes of travel, our Dijkstra algorithm will be limited
 * in working with cities whose distance is below 600.
 * (This optimization is actually needed to make this code be accepted.)
 */

int cost[10000];
bool cheaper( int a, int b ) {
    if( cost[a] == cost[b] )
        return a < b;
    return cost[a] < cost[b];
}
// We include the graph as an argument to simplify the code below.
void dijkstra( ::graph & graph, int start ) {
    for( int i = 0; i < n; i++ )
        cost[i] = INF;

    std::set< int, bool (*) (int, int) > queue( cheaper );
    cost[start] = 0;
    queue.insert( start );

    while( !queue.empty() ) {
        int current = *queue.begin();
        queue.erase( queue.begin() );

        for( int k = 0; k < graph[current].size(); k++ ) {
            std::pair<int, int> road = graph[current][k];
            int alternative = cost[current] + road.cost;

            if( alternative < cost[road.target] && alternative <= 600 ) {
                queue.erase( road.target );
                cost[road.target] = alternative;
                queue.insert( road.target );
            }
        }
    }
}

int solve() {
    for( int i = 0; i < n; i++ )
        hotels[i].clear();

    for( int i = 0; i < n; i++ ) {
        if( !has_hotel[i] )
            continue;
        dijkstra( cities, i );
        /* For each city that has an hotel, run Dijkstra.
         * Then, for each city that has an hotel,
         * if the distance between the two cities is within 600,
         * add an edge in the graph 'hotels'.
         */
        for( int j = 0; j < n; j++ ) {
            if( has_hotel[j] && cost[j] <= 600 ) {
                hotels[i].push_back(std::make_pair(j, 1));
            }
        }
    }
    /* Note every edge we added has cost 1,
     * which means "one day of travel".
     * Running Dijkstra now degenerates to a breadth-first search,
     * but, well, the code for Dijkstra is already written...
     * (Since the problem guarantees there is at most 100 hotels,
     * the limitation by 600 of our Dijkstra will not affect the result.)
     *
     * Since the problem asks for the hotels booked
     * instead of the travel days, just decrement the output by one.
     */
    dijkstra( hotels, 0 );
    if( cost[n-1] == INF )
        return -1;
    return cost[n-1] - 1;
}

int main() {
    while( scanf( "%d", &n ) != EOF && n != 0 ) {
        for( int i = 0; i < n; i++ ) {
            has_hotel[i] = false;
            cities[i].clear();
        }
        scanf( "%d", &h );
        // We will treat the begin and end cities as having hotels.
        has_hotel[0] = has_hotel[n-1] = true;

        for( int i = 0; i < h; i++ ) {
            int hn;
            scanf( "%d", &hn );
            has_hotel[hn-1] = true;
        }

        scanf( "%d", &m );
        for( int i = 0; i < m; i++ ) {
            int a, b, t;
            scanf( "%d%d%d", &a, &b, &t );
            a--; b--;
            cities[a].push_back(std::make_pair(b, t));
            cities[b].push_back(std::make_pair(a, t));
        }
        printf( "%d\n", solve() );
    }
    return 0;
}
