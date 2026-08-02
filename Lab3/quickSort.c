#include<stdio.h>

int partition(int a[], int lb, int ub); 

void quicksort(int a[], int lb, int ub)
{
    int location;

    if(lb < ub)
    {
        location = partition(a, lb, ub); 
        quicksort(a, lb, location - 1);
        quicksort(a, location + 1, ub);
    }
}

int partition(int a[], int lb, int ub)
{
    int start, end, pivot, temp, temp2;
    start = lb;
    end = ub;
    pivot = a[lb];

    while(start < end)
    {
        while(a[start] <= pivot)
        {
            start++;
        }
        while(a[end] > pivot)   
        {
           end--;                
        }
        if(start < end)           
        {
            temp = a[start];
            a[start] = a[end];
            a[end] = temp;
        }
    }
    temp2 = a[lb];
    a[lb] = a[end];             
    a[end] = temp2;
    return end;                 
}

void main()
{
    int no, i, a[100], lb, ub;
    printf("Enter the number of elements:");
    scanf("%d", &no);

    for(i = 0; i < no; i++)
    {
        printf("\n Enter the element[%d] : ", i + 1);
        scanf("%d", &a[i]);
    }
    lb = 0;
    ub = no - 1;               

    quicksort(a, lb, ub);

    printf("\n Quick sort:");
    for(i = 0; i < no; i++)     
    {
        printf("%3d", a[i]);   
    }
}
