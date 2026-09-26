#include <stdio.h>

#define MAX 50
#define INF 999999

int minKey(int key[], int mstSet[], int numVertices)
{
    int min = INF, min_index = -1, v;
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

void primMST(int graph[MAX][MAX], int numVertices)
{
    int parent[MAX], key[MAX], mstSet[MAX];
    int totalCost = 0;
    int i, count, v, u;

    for (i = 0; i < numVertices; i++)
    {
        key[i] = INF;
        mstSet[i] = 0;
        parent[i] = -1;
    }

    key[0] = 0;

    for (count = 0; count < numVertices - 1; count++)
    {
        u = minKey(key, mstSet, numVertices);
        mstSet[u] = 1;

        for (v = 0; v < numVertices; v++)
        {
            if (graph[u][v] && mstSet[v] == 0 && graph[u][v] < key[v])
            {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    printf("\nEdge \tWeight\n");
    for (i = 1; i < numVertices; i++)
    {
        printf("%d - %d \t%d\n", parent[i], i, graph[i][parent[i]]);
        totalCost += graph[i][parent[i]];
    }

    printf("Total Cost = %d\n", totalCost);
}

int main()
{
    int numVertices, i, j;
    int graph[MAX][MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &numVertices);

    printf("Enter adjacency matrix:\n");
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
