#include <stdio.h>
void main() {
  int n, i, j, temp;

  printf("Enter Size of Array : ");
  scanf("%d", &n);
  int a[n];

  printf("Enter Value of Array : ");
  for (i = 0; i < n; i++) {
    scanf("%d", &a[i]);
  }

  for (i = 0; i < n - 1; i++) {
    for (j = 0; j < n - 1 - i; j++) {
      if (a[j] > a[j + 1]) {
        temp = a[j];
        a[j] = a[j + 1];
        a[j + 1] = temp;
      }
    }
  }

  printf("Sorted Array : ");
  for (i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
}