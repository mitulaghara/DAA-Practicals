#include <stdio.h>
#include <limits.h>

void main()
{
    int no, i, d[100], j, m[100][100], s, k, q;
    printf("\nHow many matrix to multiply : ");
    scanf("%d", &no);

    for (i = 0; i <= no; i++)
    {
        printf("Enter D[%d] : ", i);
        scanf("%d", &d[i]);
    }

    for (i = 1; i <= no; i++)
    {
        for (j = 1; j <= no; j++)
        {
            if (i == j)
            {
                m[i][i] = 0;
            }
            else if (i <= (no - 1) && j > i)
            {
                m[i][i + 1] = d[i - 1] * d[i] * d[i + 1];
            }
            else
            {
                m[i][j] = 11;
            }
        }
    }

    for (s = 2; s <= (no - 1); s++)
    {
        for (i = 1; i <= (no - s); i++)
        {
            q = INT_MAX;
            for (k = i; k <= (i + s - 1); k++)
            {
                if (q > (m[i][k] + m[k + 1][i + s] + (d[i - 1] * d[k] * d[i + s])))
                {
                    q = m[i][k] + m[k + 1][i + s] + (d[i - 1] * d[k] * d[i + s]);
                }
            }
            m[i][i + s] = q;
        }
    }

    // Print the table
    printf("\n");
    for (i = 1; i <= no; i++)
    {
        for (j = 1; j <= no; j++)
        {
            printf("%8d", m[i][j]);
        }
        printf("\n\n\n");
    }

    printf("\nMin. SM = %d\n", m[1][no]);
}
