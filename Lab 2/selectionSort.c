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

    for(i=0; i<n-1; i++){
        int min_idx = i;
        for(j=i+1; j<n; j++){
            if(a[j] < a[min_idx]){
                min_idx = j;
            }
        }
        if(min_idx != i){
            temp = a[i];
            a[i] = a[min_idx];
            a[min_idx] = temp;
        }
    }

    printf("Sorted Array : ");
    for(i=0; i<n; i++){
        printf("%d ",a[i]);
    }
}