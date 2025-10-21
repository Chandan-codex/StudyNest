#include <stdio.h>
#include <stdlib.h>

int BF(int G[][20], int V, int E, int edge[][2]) {
    int i, u, v, k, dist[20], par[20], s;
    int flag = 1;

    // Initialize distances and parents
    for (i = 0; i < V; i++) {
        dist[i] = 1000;  // Set initial distances to a large number
        par[i] = -1;     // Initialize parents to -1 (no parent)
    }

    printf("Enter source vertex: ");
    scanf("%d", &s);
    s = s - 1;  // Adjust for 0-based index
    dist[s] = 0; // Distance from source to itself is 0

    // Relax all edges V-1 times
    for (i = 0; i < V - 1; i++) {
        for (k = 0; k < E; k++) {
            u = edge[k][0];
            v = edge[k][1];
            if (dist[u] + G[u][v] < dist[v]) {
                dist[v] = dist[u] + G[u][v];
                par[v] = u;
            }
        }
    }

    // Check for negative-weight cycles
    for (k = 0; k < E; k++) {
        u = edge[k][0];
        v = edge[k][1];
        if (dist[u] + G[u][v] < dist[v]) {
            flag = 0;  // Negative cycle detected
        }
    }

    // Output the results
    if (flag) {
        printf("\nShortest distances from source:\n");
        for (i = 0; i < V; i++) {
            printf("Vertex %d -> cost= %d  Parent =%d\n", i + 1, dist[i], par[i] + 1);
        }
    }

    return flag;
}

int main() {
    int v, k = 0, i, u, v2, weight;
    int G[20][20] = {0};  // Initialize the graph to zero
    int edge[20][2];       // Store edges as pairs of vertices
    
    printf("Enter total number of vertices: \n");
    scanf("%d", &v);

    // Get the number of edges
    int E;
    printf("Enter total number of edges: \n");
    scanf("%d", &E);

    // Input only the edges with weights
    printf("Enter the edge (u v) and weight (e.g., 1 2 10): ");
    for (k = 0; k < E; k++) {
        scanf("%d %d %d", &u, &v2, &weight);
        u--; v2--;  // Adjust for 0-based index (internally use 0-based indexing)
        G[u][v2] = weight;  // Set the weight of the edge in the graph
        edge[k][0] = u;     // Store the edge
        edge[k][1] = v2;
    }

    // Call the Bellman-Ford algorithm
    if (BF(G, v, E, edge))
        printf("\nNo negative-weight cycle detected.\n");
    else
        printf("\nNegative-weight cycle detected.\n");

    return 0;
}
