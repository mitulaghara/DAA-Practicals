#include<stdio.h>
void main(){
    int n,i,j,temp;

    printf("Enter Size of Array : ");
    scanf("%d",&n);
    int a[n];

    printf("Enter Value of Array : ");
    for(i=0; i<n; i++){
        scanf("%d",&a[i]);
    }

    for(i=1; i<n; i++){
        temp = a[i];
        j = i - 1;
        while(j >= 0 && a[j] > temp){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = temp;
    }

    printf("Sorted Array : ");
    for(i=0; i<n; i++){
        printf("%d ",a[i]);
    }
}