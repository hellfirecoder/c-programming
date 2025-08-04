#include<stdio.h>

int main()
{
    int arr1[20][20], arr2[20][20], r,c,i,j;
    printf("enter the total no  of rows and columns to be entered  \n");
    scanf("%d%d",&r,&c);
    if(r<=20 && c<=20){
    printf("enter the  elements  \n");
    for(i=0;i<r;i++)
         for(j=0;j<c;j++)
        scanf("%d",&arr1[i][j]);
    }
    else{
        printf("invalid choice");
        return 1;
    }
    printf("the entered array \n");
    for(i=0;i<r;i++)
    {   for(j=0;j<c;j++)
            printf("%d \t",arr1[i][j]); 
        printf("\n");
    } 
    for(i=0;i<r;i++)
    {   for(j=0;j<c;j++)
          arr2[j][i]=arr1[i][j];
    }
    printf("the new arr  \n");
    for(i=0;i<c;i++)
    {   for(j=0;j<r;j++)
            printf("%d \t",arr2[i][j]); 
        printf("\n");
    } 
    return 0;  
}