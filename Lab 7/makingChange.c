#include <stdio.h>

void main()
{
    int no, d[100], a, i, j, c[100][100], sol[100], k;
    printf("\nHow many different denomination coins are required: ");
    scanf("%d", &no);

    for (i = 1; i <= no; i++)
    {
        printf("\nEnter the Denomination Coin[%d] : ", i);
        scanf("%d", &d[i]);
    }

    printf("\nHow much amount to be paid: ");
    scanf("%d", &a);

    // Create a two dimensional table
    for (i = 0; i <= no; i++)
    {
        for (j = 0; j <= a; j++)
        {
            c[i][j] = 0;
        }
    }

    for (i = 1; i <= no; i++)
    {
        for (j = 1; j <= a; j++)
        {
            if (i == 1 && j < d[i])
            {
                c[i][j] = 00;
            }
            else if (i == 1)
            {
                c[i][j] = 1 + c[i][j - d[i]];
            }
            else if (j < d[i])
            {
                c[i][j] = c[i - 1][j];
            }
            else
            {
                if (c[i - 1][j] < (1 + c[i][j - d[i]]))
                {
                    c[i][j] = c[i - 1][j];
                }
                else
                {
                    c[i][j] = 1 + c[i][j - d[i]];
                }
            }
        }
    }

    // printing of table
    printf("\n");
    for (i = 0; i <= a; i++)
    {
        printf("%4d", i);
    }
    printf("\n");
    for (i = 0; i <= a; i++)
    {
        printf("----");
    }
    printf("\n");
    for (i = 0; i <= no; i++)
    {
        for (j = 0; j <= a; j++)
        {
            printf("%4d", c[i][j]);
        }
        printf("\n");
    }

    printf("\nOptimal no. of coins : %d", c[no][a]);

    i = no;
    j = a;
    k = 1;
    while (j > 0)
    {
        if (c[i][j] == c[i - 1][j])
        {
            i = i - 1;
        }
        else
        {
            j = a - d[i];
            a = a - d[i];
            sol[k] = d[i];
            k++;
        }
    }

    printf("\nCoins used: ");
    for (i = 1; i < k; i++)
    {
        printf("%4d", sol[i]);
    }
    printf("\n");
}
