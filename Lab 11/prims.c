#include <stdio.h>
#include <limits.h>

#define MAX 50
#define INF 999999

/* Find vertex with minimum key value from the set of vertices not yet included in MST */
int minKey(int key[], int mstSet[], int numVertices)
{
    int min = INF, min_index = -1;
    int v;

    for (v = 0; v < numVertices; v++)
    {
        if (mstSet[v] == 0 && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

/* Prim's Algorithm to construct and print MST for a graph represented using adjacency matrix */
void primMST(int graph[MAX][MAX], int numVertices)
{
    int parent[MAX];  /* Array to store constructed MST */
    int key[MAX];     /* Key values used to pick minimum weight edge in cut */
    int mstSet[MAX];  /* To represent set of vertices included in MST */
    int i, count, v;
    int totalCost = 0;

    /* Initialize all keys as INFINITE and mstSet[] as 0 */
    for (i = 0; i < numVertices; i++)
    {
        key[i] = INF;
        mstSet[i] = 0;
        parent[i] = -1;
    }

    /* Always include first vertex in MST */
    key[0] = 0;     /* Make key 0 so that this vertex is picked as first vertex */
    parent[0] = -1; /* First node is always root of MST */

    printf("\n--- Step-by-Step Prim's MST Construction Trace ---\n");
    printf("%-6s | %-12s | %-12s | %-25s\n", "Step", "Picked Node", "Edge Added", "Edge Weight / Status");
    printf("----------------------------------------------------------------------\n");

    /* The MST will have numVertices vertices */
    for (count = 0; count < numVertices; count++)
    {
        /* Pick the minimum key vertex from the set of vertices not yet included in MST */
        int u = minKey(key, mstSet, numVertices);

        if (u == -1) break;

        /* Add the picked vertex to the MST Set */
        mstSet[u] = 1;

        if (parent[u] != -1)
        {
            printf("%-6d | Vertex %-6d | (%2d, %2d)     | Added to MST (Weight: %d)\n", 
                   count, u, parent[u], u, graph[u][parent[u]]);
        }
        else
        {
            printf("%-6d | Vertex %-6d | Root (None)  | Starting Node (Key: 0)\n", 
                   count, u);
        }

        /* Update key value and parent index of the adjacent vertices of the picked vertex.
           Consider only those vertices which are not yet included in MST */
        for (v = 0; v < numVertices; v++)
        {
            /* graph[u][v] is non-zero only for adjacent vertices of m
               mstSet[v] is false for vertices not yet included in MST
               Update key only if graph[u][v] is smaller than key[v] */
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }
    printf("----------------------------------------------------------------------\n");

    /* Print the constructed MST */
    printf("\n============================================\n");
    printf("        MINIMUM SPANNING TREE (MST)         \n");
    printf("============================================\n");
    printf("%-6s | %-12s | %-8s\n", "No.", "Edge (u - v)", "Weight");
    printf("--------------------------------------------\n");

    for (i = 1; i < numVertices; i++)
    {
        if (parent[i] != -1)
        {
            printf("%-6d | %2d - %-2d      | %-8d\n", i, parent[i], i, graph[i][parent[i]]);
            totalCost += graph[i][parent[i]];
        }
    }

    printf("--------------------------------------------\n");
    printf("Minimum Total Cost of Spanning Tree = %d\n", totalCost);
    printf("============================================\n");
}

int main()
{
    int numVertices, i, j;
    int graph[MAX][MAX];

    printf("============================================\n");
    printf("            PRIM'S MST ALGORITHM            \n");
    printf("============================================\n");

    printf("\nEnter number of vertices: ");
    if (scanf("%d", &numVertices) != 1) return 0;

    printf("\nEnter Adjacency Matrix (size %d x %d):\n", numVertices, numVertices);
    printf("(Enter 0 if there is no edge between vertices)\n\n");

    for (i = 0; i < numVertices; i++)
    {
        for (j = 0; j < numVertices; j++)
        {
            scanf("%d", &graph[i][j]);
        }
    }

    primMST(graph, numVertices);

    return 0;
}
