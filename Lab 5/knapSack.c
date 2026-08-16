#include <stdio.h>

void main()
{
    int no, i, cap, j;
    float w[100], v[100], ratio[100], temp, x[100], profit;
    profit = 0;
    printf("\nEnter the number of item to loot: ");
    scanf("%d", &no);

    // Inputs of weights and profit values of items
    for (i = 1; i <= no; i++)
    {
        printf("\n---------------Item[%d]---------------\n", i);
        printf("Enter the weight of the item : ");
        scanf("%f", &w[i]);
        printf("Enter the values of the item : ");
        scanf("%f", &v[i]);
    }

    printf("\nEnter the CAPACITY of KNAPSACK : ");
    scanf("%d", &cap);

    // Calculate the ratios(vi/wi)
    for (i = 1; i <= no; i++)
    {
        ratio[i] = v[i] / w[i];
    }

    printf("\nScenario Before Sorting\n");

    printf("\n");
    printf("Weight : ");
    for (i = 1; i <= no; i++)
    {
        printf("%7.0f", w[i]);
    }

    printf("\n");
    printf("Values : ");
    for (i = 1; i <= no; i++)
    {
        printf("%7.0f", v[i]);
    }

    printf("\n");
    printf("Ratios : ");
    for (i = 1; i <= no; i++)
    {
        printf("%7.1f", ratio[i]);
    }

    // Sort the ratios into descending order
    for (i = 1; i <= no; i++)
    {
        for (j = 1; j <= no; j++)
        {
            if (ratio[i] > ratio[j])
            {
                // sorted the ratios
                temp = ratio[i];
                ratio[i] = ratio[j];
                ratio[j] = temp;

                // Sort the weight
                temp = w[i];
                w[i] = w[j];
                w[j] = temp;

                // sort the values
                temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }
    }

    printf("\n\nScenario After Sorting\n");

    printf("\n");
    printf("Weight : ");
    for (i = 1; i <= no; i++)
    {
        printf("%7.0f", w[i]);
    }

    printf("\n");
    printf("Values : ");
    for (i = 1; i <= no; i++)
    {
        printf("%7.0f", v[i]);
    }

    printf("\n");
    printf("Ratios : ");
    for (i = 1; i <= no; i++)
    {
        printf("%7.1f", ratio[i]);
    }

    for (i = 1; i <= no; i++)
    {
        x[i] = 0.0;
    }

    // Greedy algorithm for knapsack
    for (i = 1; i <= no; i++)
    {
        if (w[i] <= cap)
        {
            x[i] = 1.0;
            profit = profit + (x[i] * v[i]);
            cap = cap - w[i];
        }
        else
        {
            x[i] = cap / w[i];
            profit = profit + (x[i] * v[i]);
            break;
        }
    }

    printf("\n");
    printf("Xarray : ");
    for (i = 1; i <= no; i++)
    {
        printf("%7.1f", x[i]);
    }

    printf("\nOptimal Profit :  %1.2f", profit);
}
