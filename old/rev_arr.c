#include<stdio.h>

int main()
{
    int arr1[20], arr2[20], n,i,j;
    printf("enter the total no  of elements to be entered  \n");
    scanf("%d",&n);
    if(n<=20){
    printf("enter the  elements  \n");
    for(i=0;i<n;i++)
        scanf("%d",&arr1[i]);
    }
    else{
        printf("invalid choice");
        return 1;
    }
    for(i=0;i<n;i++)
    {
          arr2[n-i-1]=arr1[i];;
    }
    printf("the new arr  \n");
    for(i=0;i<n;i++)
        printf("%d \t",arr2[i]);  
    return 0;  
}
