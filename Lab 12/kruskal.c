#include <stdio.h>
#include <stdlib.h>

#define MAX_EDGES 100
#define MAX_VERTICES 50

typedef struct {
    int u;
    int v;
    int weight;
} Edge;

/* Disjoint Set Union (DSU) Find function with path compression */
int findRoot(int parent[], int i)
{
    if (parent[i] == i)
        return i;
    return parent[i] = findRoot(parent, parent[i]);
}

/* Disjoint Set Union function */
void unionSets(int parent[], int rank[], int rootU, int rootV)
{
    if (rank[rootU] < rank[rootV])
    {
        parent[rootU] = rootV;
    }
    else if (rank[rootU] > rank[rootV])
    {
        parent[rootV] = rootU;
    }
    else
    {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

/* Bubble sort to sort edges in non-decreasing order of weight */
void sortEdges(Edge edges[], int numEdges)
{
    int i, j;
    Edge temp;
    for (i = 0; i < numEdges - 1; i++)
    {
        for (j = 0; j < numEdges - i - 1; j++)
        {
            if (edges[j].weight > edges[j + 1].weight)
            {
                temp = edges[j];
                edges[j] = edges[j + 1];
                edges[j + 1] = temp;
            }
        }
    }
}

/* Kruskal's Algorithm */
void kruskalMST(Edge edges[], int numVertices, int numEdges)
{
    int parent[MAX_VERTICES];
    int rank[MAX_VERTICES];
    Edge mst[MAX_VERTICES];
    int mstEdgeCount = 0;
    int totalCost = 0;
    int i;

    /* Initialize Disjoint Sets: each vertex is its own parent */
    for (i = 0; i < numVertices; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    /* Step 1: Sort all edges in non-decreasing order of their weight */
    sortEdges(edges, numEdges);

    printf("\nSorted Edges:\n");
    printf("%-6s | %-12s | %-8s\n", "Index", "Edge (u - v)", "Weight");
    printf("-------------------------------\n");
    for (i = 0; i < numEdges; i++)
    {
        printf("%-6d | %2d - %-2d      | %-8d\n", i + 1, edges[i].u, edges[i].v, edges[i].weight);
    }

    printf("\n--- Edge Selection Trace ---\n");
    printf("%-12s | %-8s | %-12s | %-20s\n", "Edge", "Weight", "Status", "Reason / Action");
    printf("------------------------------------------------------------------\n");

    /* Step 2: Iterate through sorted edges and select edges that don't form cycles */
    for (i = 0; i < numEdges; i++)
    {
        int rootU = findRoot(parent, edges[i].u);
        int rootV = findRoot(parent, edges[i].v);

        /* If including this edge does not cause a cycle */
        if (rootU != rootV)
        {
            mst[mstEdgeCount++] = edges[i];
            totalCost += edges[i].weight;
            unionSets(parent, rank, rootU, rootV);
            printf("(%2d, %2d)     | %-8d | %-12s | Added to MST (No cycle)\n", 
                   edges[i].u, edges[i].v, edges[i].weight, "SELECTED");

            /* If we have picked V-1 edges, MST is complete */
            if (mstEdgeCount == numVertices - 1)
            {
                break;
            }
        }
        else
        {
            printf("(%2d, %2d)     | %-8d | %-12s | Rejected (Forms cycle)\n", 
                   edges[i].u, edges[i].v, edges[i].weight, "DISCARDED");
        }
    }
    printf("------------------------------------------------------------------\n");

    /* Check if graph was connected */
    if (mstEdgeCount < numVertices - 1)
    {
        printf("\nWarning: Graph is disconnected! Spanning tree could not be formed.\n");
        return;
    }

    /* Print MST Results */
    printf("\n============================================\n");
    printf("     MINIMUM SPANNING TREE (MST) RESULT     \n");
    printf("============================================\n");
    printf("%-6s | %-12s | %-8s\n", "No.", "Edge (u - v)", "Weight");
    printf("--------------------------------------------\n");
    for (i = 0; i < mstEdgeCount; i++)
    {
        printf("%-6d | %2d - %-2d      | %-8d\n", i + 1, mst[i].u, mst[i].v, mst[i].weight);
    }
    printf("--------------------------------------------\n");
    printf("Minimum Total Cost of Spanning Tree = %d\n", totalCost);
    printf("============================================\n");
}

int main()
{
    int numVertices, numEdges, i;
    Edge edges[MAX_EDGES];

    printf("============================================\n");
    printf("           KRUSKAL'S MST ALGORITHM          \n");
    printf("============================================\n");

    printf("\nEnter number of vertices: ");
    if (scanf("%d", &numVertices) != 1) return 0;

    printf("Enter number of edges: ");
    if (scanf("%d", &numEdges) != 1) return 0;

    printf("\nEnter each edge as: <Source> <Destination> <Weight>\n");
    printf("(Vertices are numbered 0 to %d or 1 to %d)\n\n", numVertices - 1, numVertices);

    for (i = 0; i < numEdges; i++)
    {
        printf("Edge %d: ", i + 1);
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskalMST(edges, numVertices, numEdges);

    return 0;
}
