#include <stdio.h>

void main()
{
    int n, i, j, w;
    int wt[100], value[100];
    int m[100][100];

    printf("\nHow many items: ");
    scanf("%d", &n);

    printf("\nEnter weight and value of each item:\n");

    for (i = 1; i <= n; i++)
    {
        printf("\nEnter weight of item %d: ", i);
        scanf("%d", &wt[i]);

        printf("Enter value of item %d: ", i);
        scanf("%d", &value[i]);
    }

    printf("\nEnter Knapsack Capacity: ");
    scanf("%d", &w);

    /* Initialize first row and first column */
    for (i = 0; i <= n; i++)
        m[i][0] = 0;

    for (j = 0; j <= w; j++)
        m[0][j] = 0;

    /* Dynamic Programming */
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= w; j++)
        {
            if (wt[i] <= j)
            {
                if (m[i - 1][j] > value[i] + m[i - 1][j - wt[i]])
                    m[i][j] = m[i - 1][j];
                else
                    m[i][j] = value[i] + m[i - 1][j - wt[i]];
            }
            else
            {
                m[i][j] = m[i - 1][j];
            }
        }
    }

    /* Print DP Table */
    printf("\n\nKnapsack DP Table:\n\n");

    for (i = 0; i <= n; i++)
    {
        for (j = 0; j <= w; j++)
        {
            printf("%5d", m[i][j]);
        }
        printf("\n");
    }

    /* Display Maximum Value */
    printf("\nMaximum Value = %d\n", m[n][w]);

    /* Backtracking */
    printf("\nSelected Items:\n");

    i = n;
    j = w;

    while (i > 0 && j > 0)
    {
        if (m[i][j] != m[i - 1][j])
        {
            printf("Item %d -> Weight = %d, Value = %d\n", i, wt[i], value[i]);
            j = j - wt[i];
        }
        i--;
    }
}