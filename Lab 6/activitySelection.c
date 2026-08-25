#include <stdio.h>

void main()
{
    int n, i, j, last, selected[100];
    int s[100], f[100], temp;

    printf("\nEnter the number of activities: ");
    scanf("%d", &n);

    // Input start and finish times
    for (i = 1; i <= n; i++)
    {
        printf("\n---------------Activity[%d]---------------\n", i);
        printf("Enter the Start  time : ");
        scanf("%d", &s[i]);
        printf("Enter the Finish time : ");
        scanf("%d", &f[i]);
    }

    printf("\nScenario Before Sorting\n");

    printf("\n");
    printf("Activity : ");
    for (i = 1; i <= n; i++)
    {
        printf("%5d", i);
    }

    printf("\n");
    printf("Start    : ");
    for (i = 1; i <= n; i++)
    {
        printf("%5d", s[i]);
    }

    printf("\n");
    printf("Finish   : ");
    for (i = 1; i <= n; i++)
    {
        printf("%5d", f[i]);
    }

    // Sort activities in ascending order of finish time
    for (i = 1; i <= n; i++)
    {
        for (j = 1; j <= n; j++)
        {
            if (f[i] < f[j])
            {
                // Sort the finish times
                temp = f[i];
                f[i] = f[j];
                f[j] = temp;

                // Sort the start times accordingly
                temp = s[i];
                s[i] = s[j];
                s[j] = temp;
            }
        }
    }

    printf("\n\nScenario After Sorting (by Finish Time)\n");

    printf("\n");
    printf("Activity : ");
    for (i = 1; i <= n; i++)
    {
        printf("%5d", i);
    }

    printf("\n");
    printf("Start    : ");
    for (i = 1; i <= n; i++)
    {
        printf("%5d", s[i]);
    }

    printf("\n");
    printf("Finish   : ");
    for (i = 1; i <= n; i++)
    {
        printf("%5d", f[i]);
    }

    // Activity Selection (Greedy Algorithm)
    // Select first activity always
    selected[1] = 1;
    last = 1;
    int count = 1;

    for (j = 2; j <= n; j++)
    {
        // If start time of j-th activity >= finish time of last selected activity
        if (s[j] >= f[last])
        {
            selected[j] = 1;
            last = j;
            count++;
        }
        else
        {
            selected[j] = 0;
        }
    }

    printf("\n\nSelected Activities : ");
    for (i = 1; i <= n; i++)
    {
        if (selected[i] == 1)
        {
            printf("\n  Activity[%d] -> Start: %d, Finish: %d", i, s[i], f[i]);
        }
    }

    printf("\n\nTotal Activities Selected : %d", count);
}
