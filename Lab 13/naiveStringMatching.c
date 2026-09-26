#include <stdio.h>
#include <string.h>

void naiveStringMatcher(char text[], char pattern[])
{
    int n = strlen(text);
    int m = strlen(pattern);
    int i, j, found = 0;

    for (i = 0; i <= n - m; i++)
    {
        for (j = 0; j < m; j++)
        {
            if (text[i + j] != pattern[j])
                break;
        }

        if (j == m)
        {
            printf("Pattern found at index %d\n", i);
            found = 1;
        }
    }

    if (!found)
    {
        printf("Pattern not found\n");
    }
}

int main()
{
    char text[1000];
    char pattern[100];

    printf("Enter text: ");
    scanf("%s", text);

    printf("Enter pattern: ");
    scanf("%s", pattern);

    naiveStringMatcher(text, pattern);

    return 0;
}
