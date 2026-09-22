#include <stdio.h>
#include <string.h>

void main()
{
    char x[100], y[100];
    int m, n, i, j, c[100][100];
    printf("\nEnter the string 1: ");
    scanf("%s", x);

    printf("\nEnter the string 2: ");
    scanf("%s", y);

    m = strlen(x);
    n = strlen(y);

    printf("\nLength of string1  = %d and String 2 = %d", m, n);

    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            c[i][j] = 0;
        }
    }

    for (i = 1; i <= m; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (x[i - 1] == y[j - 1])
            {
                c[i][j] = c[i - 1][j - 1] + 1;
            }
            else if (x[i - 1] != y[j - 1])
            {
                if (c[i - 1][j] > c[i][j - 1])
                {
                    c[i][j] = c[i - 1][j];
                }
                else
                {
                    c[i][j] = c[i][j - 1];
                }
            }
        }
    }

    printf("\n");
    for (i = 0; i <= m; i++)
    {
        for (j = 0; j <= n; j++)
        {
            printf("%5d", c[i][j]);
        }
        printf("\n\n");
    }

    //Back tracking
    

}