#include <stdio.h>

void Heapsort(int [],int);
void MaxHeapify(int [],int,int);

void Heapsort(int A[],int n)
{
    int i,temp;


    for(i=n/2;i>=1;i--)
    {
        MaxHeapify(A,n,i);
    }

    for(i=n;i>=1;i--)
    {
        temp=A[i];
        A[i]=A[1];
        A[1]=temp;
        MaxHeapify(A,i-1,1);
    }
}

void MaxHeapify(int A[],int n,int i)
{
    int largest,l,r,temp;

    largest=i;
    l=2*i;
    r=2*i+1;


    while(l<=n && A[l]>A[largest])
    {
        largest=l;
    }

    while(r<=n && A[r]>A[largest])
    {
        largest=r;
    }

    if(i!=largest)
    {
        temp=A[largest];
        A[largest]=A[i];
        A[i]=temp;
        MaxHeapify(A,n,largest);
    }
}

void main()
{
    int n,i,A[100];

    printf("\nHow many elements you want to sort: ");
    scanf("%d",&n);


    for(i=1;i<=n;i++)
    {
        printf("\nEnter Elements: ");
        scanf("%d",&A[i]);
    }

    Heapsort(A,n);

    printf("\nHeapsort Element:");

    for(i=1;i<=n;i++)
    {
        printf("%5d",A[i]);
    }
}
