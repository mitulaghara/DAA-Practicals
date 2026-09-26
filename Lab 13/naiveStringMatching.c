#include <stdio.h>
#include <string.h>

void naiveStringMatcher(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j;
    int count = 0;
    int comparisons = 0;

    printf("\n--- Step-by-Step Shift Trace ---\n");
    printf("%-8s | %-12s | %-12s | %-20s\n", "Shift (s)", "Window", "Match?", "Details");
    printf("------------------------------------------------------------\n");

    /* Loop through all possible valid shifts s from 0 to n - m */
    for (i = 0; i <= n - m; i++)
    {
        char window[100];
        strncpy(window, &text[i], m);
        window[m] = '\0';

        /* Check character by character */
        for (j = 0; j < m; j++)
        {
            comparisons++;
            if (text[i + j] != pattern[j])
            {
                break;
            }
        }

        /* If all m characters matched */
        if (j == m)
        {
            count++;
            printf("%-8d | %-12s | %-12s | Pattern matches at index %d\n", i, window, "MATCH", i);
        }
        else
        {
            printf("%-8d | %-12s | %-12s | Mismatch at char '%c' != '%c'\n", 
                   i, window, "MISMATCH", text[i + j], pattern[j]);
        }
    }

    printf("------------------------------------------------------------\n");
    printf("\nTotal Occurrences Found : %d\n", count);
    printf("Total Character Comparisons : %d\n", comparisons);

    if (count == 0)
    {
        printf("Result: Pattern does NOT occur in the given text.\n");
    }
}

int main()
{
    char text[1000];
    char pattern[100];

    printf("==================================================\n");
    printf("           NAIVE STRING MATCHING ALGORITHM        \n");
    printf("==================================================\n");

    printf("\nEnter Text string (T): ");
    if (scanf("%s", text) != 1) return 0;

    printf("Enter Pattern string (P): ");
    if (scanf("%s", pattern) != 1) return 0;

    printf("\nText Length (n)    : %lu\n", strlen(text));
    printf("Pattern Length (m) : %lu\n", strlen(pattern));

    if (strlen(pattern) > strlen(text))
    {
        printf("\nError: Pattern length (m) cannot be greater than text length (n)!\n");
        return 0;
    }

    naiveStringMatcher(text, pattern);

    return 0;
}
