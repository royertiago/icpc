#include <stdio.h>
#include <algorithm>

/* We will need an Union-Find data structure.
 * (Union and Find are uppercase because "union" is a C keyword.)
 */
int parent[(int)2e5];
int rank[(int)2e5];

int Find( int node ) {
    if( parent[node] != node )
        parent[node] = Find(parent[node]);
    return parent[node];
}

void Union( int left, int right ) {
    left = Find(left);
    right = Find(right);

    if( left == right )
        return;

    if( rank[left] < rank[right] )
        parent[left] = right;
    else if( rank[left] > rank[right] )
        parent[right] = left;
    else {
        parent[left] = right;
        rank[left]++;
    }
}

int n, m;
struct road {
    int a, b;
    int cost;
};
bool operator<( road lhs, road rhs ) {
    return lhs.cost < rhs.cost;
}

road roads[(int)2e5];

int solve() {
    /* Minimum spanning tree.
     * The problem asks for the sum of what is not in the minimum tree,
     * not the tree itself; we will use this to simplify the code.
     *
     * To "find" the minimum spanning tree,
     * we will use Kruskal's algorithm;
     * that is, sort the edges by cost, and add the cheapest edge;
     * then, the next-cheapest edge that does not generate a cycle,
     * and so on.
     *
     * The union-find data structure will be used
     * to simplify this cycle search.
     * We will put in the same set all cities that are on the same
     * connected component; any new edge between two nodes on the same set
     * would lead to a cycle.
     *
     * We just then need to add the cost of every edge not in the tree,
     * which are exactly the rejected edges on the step above.
     */
    int sum = 0;

    // Reset the union-find structure
    for( int i = 0; i < n; i++ ) {
        parent[i] = i;
        rank[i] = 0;
    }

    // This is actually the algorithm's bottleneck...
    std::sort( roads, roads + m );

    for( int i = 0; i < m; i++ ) {
        /* Everything depends on the relation between roads[i].a
         * and roads[i].b. If they belong the same set,
         * reject the edge and add the cost;
         * otherwise, join both sets.
         */
        if( Find(roads[i].a) == Find(roads[i].b) )
            sum += roads[i].cost;
        else
            Union(roads[i].a, roads[i].b);
    }
    return sum;
}

int main() {
    while( scanf( "%d%d", &n, &m ) != EOF && n != 0 ) {
        for( int i = 0; i < m; i++ )
            scanf( "%d%d%d", &roads[i].a, &roads[i].b, &roads[i].cost );
        printf( "%d\n", solve() );
    }
    return 0;
}
