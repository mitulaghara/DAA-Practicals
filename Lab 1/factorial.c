// #include<stdio.h>
// void main(){
//     int n,i,fact=1;
//     printf("Enter Number : ");
//     scanf("%d",&n);
    
//     for(i=n;i>=1;i--){
//         fact*=i;
//     }
//     printf("Factorial of %d is %d\n", n, fact); 
// }


#include <stdio.h>
void main()
{
    int i,n,fact=1;
    printf("Enter the number:");
    scanf("%d", &n);

    for(i=n;i>=1;i--)
    {
       fact=fact*i;
    }

    printf("\n Enter the factorial : %d",fact);

}
