#include <stdio.h>
#include <string.h>

char x[100],y[100],b[100][100];
int c[100][100],m,n,i,j;

int print(int i, int j)
{
          if(i==0 || j==0)
                    return 0;

          if(b[i][j]=='d')
          {
                    print(i-1,j-1);
                    printf("%c",x[i-1]);
          }
          else if(b[i][j]=='u')
          {
                    print(i-1,j);
          }
          else
          {
                    print(i,j-1);
          }

          return 0;
}

int main()
{
          printf("\n Enter the string 1: ");
          scanf("%s",x);

          printf("\n Enter the string 2: ");
          scanf("%s",y);

          m=strlen(x);
          n=strlen(y);

          printf("\n String length for x=%d and y=%d\n",m,n);

          for(i=1; i<=m; i++)
          {
                    for(j=1; j<=n; j++)
                    {
                              if(x[i-1]==y[j-1])
                              {
                                        c[i][j]=c[i-1][j-1]+1;
                                        b[i][j]='d';
                              }
                              else
                              {
                                        if(c[i-1][j]>c[i][j-1])
                                        {
                                                  c[i][j]=c[i-1][j];
                                                  b[i][j]='u';
                                        }
                                        else
                                        {
                                                  c[i][j]=c[i][j-1];
                                                  b[i][j]='l';
                                        }
                              }
                    }
          }

          printf("\nValue Table:\n");

          for(i=0; i<=m; i++)
          {
                    for(j=0; j<=n; j++)
                    {
                              printf("%4d",c[i][j]);
                    }
                    printf("\n");
          }

          printf("\nDirection Table:\n");

          for(i=0; i<=m; i++)
          {
                    for(j=0; j<=n; j++)
                    {
                              printf("%4c",b[i][j]);
                    }
                    printf("\n");
          }

          printf("\nLongest Common Subsequence: ");
          print(m,n);

          printf("\n");

          return 0;
}