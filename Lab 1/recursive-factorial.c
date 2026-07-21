// #include<stdio.h>
// int n,i,fact=1,ans;

// int thor (int n){
//     if (n == 0)
//         return 1;
//     else
//         return n*thor(n-1);
// }

// void main(){
    
//     printf("Enter Number : ");
//     scanf("%d",&n);
    
//     ans=thor(n);

//     printf("factorial is %d",ans);
     
// }



#include<stdio.h>
int fact(int n)
{
    if (n==0){
        return 1;
    }
    else{
        return n*fact(n-1);
    }
}

void main()
{
    int n;
    printf("Enter the number:");
    scanf("%d", &n);

    fact(n);
    printf("factorial: %d", fact(n));
}