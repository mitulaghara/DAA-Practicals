#include <stdio.h>

#define MAX_EDGES 100
#define MAX_VERTICES 50

typedef struct {
    int u, v, weight;
} Edge;

int findRoot(int parent[], int i)
{
    if (parent[i] == i)
        return i;
    return parent[i] = findRoot(parent, parent[i]);
}

void unionSets(int parent[], int rank[], int rootU, int rootV)
{
    if (rank[rootU] < rank[rootV])
        parent[rootU] = rootV;
    else if (rank[rootU] > rank[rootV])
        parent[rootV] = rootU;
    else
    {
        parent[rootV] = rootU;
        rank[rootU]++;
    }
}

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

void kruskalMST(Edge edges[], int numVertices, int numEdges)
{
    int parent[MAX_VERTICES], rank[MAX_VERTICES];
    int mstEdgeCount = 0, totalCost = 0, i;

    for (i = 0; i < numVertices; i++)
    {
        parent[i] = i;
        rank[i] = 0;
    }

    sortEdges(edges, numEdges);

    printf("\nEdge \tWeight\n");
    for (i = 0; i < numEdges; i++)
    {
        int rootU = findRoot(parent, edges[i].u);
        int rootV = findRoot(parent, edges[i].v);

        if (rootU != rootV)
        {
            printf("%d - %d \t%d\n", edges[i].u, edges[i].v, edges[i].weight);
            totalCost += edges[i].weight;
            unionSets(parent, rank, rootU, rootV);
            mstEdgeCount++;
            if (mstEdgeCount == numVertices - 1)
                break;
        }
    }

    printf("Total Cost = %d\n", totalCost);
}

int main()
{
    int numVertices, numEdges, i;
    Edge edges[MAX_EDGES];

    printf("Enter number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter number of edges: ");
    scanf("%d", &numEdges);

    printf("Enter edges (source destination weight):\n");
    for (i = 0; i < numEdges; i++)
    {
        scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].weight);
    }

    kruskalMST(edges, numVertices, numEdges);

    return 0;
}
