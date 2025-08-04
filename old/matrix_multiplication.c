#include<stdio.h>

int main()
{
    int arr1[20][20], arr2[20][20], r1,c1,i,j,result[20][20],r2,c2,k;
    printf("enter the total no  of rows and columns to be entered for first matrix \n");
    scanf("%d%d",&r1,&c1);
    if(r1<=20 && c1<=20){
    printf("enter the  elements  \n");
    for(i=0;i<r1;i++)
         for(j=0;j<c1;j++)
        scanf("%d",&arr1[i][j]);
    }
    else{
        printf("invalid choice");
        return 1;
    }
    printf("the entered array \n");
    for(i=0;i<r1;i++)
    {   for(j=0;j<c1;j++)
            printf("%d \t",arr1[i][j]); 
        printf("\n");
    } 
    printf("enter the total no  of rows and columns to be entered for second matix  \n");
    scanf("%d%d",&r2,&c2);
    if(r2<=20 && c2<=20){
    printf("enter the  elements  \n");
    for(i=0;i<r2;i++)
         for(j=0;j<c2;j++)
        scanf("%d",&arr2[i][j]);
    }
    else{
        printf("invalid choice");
        return 1;
    }
    printf("the entered array \n");
    for(i=0;i<r2;i++)
    {   for(j=0;j<c2;j++)
            printf("%d \t",arr2[i][j]); 
        printf("\n");
    } 
    // storing zero in the result matix elements
    for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
           result[i][j] = 0;
        }
     }
  
     // Multiplying first and second matrices and storing it in result
     for (int i = 0; i < r1; ++i) {
        for (int j = 0; j < c2; ++j) {
           for ( k = 0; k < c1; ++k) {
              result[i][j] += arr1[i][k] * arr2[k][j];
           }
        }
     }
     printf("\nOutput Matrix:\n");
   for (int i = 0; i < r1; ++i) {
      for (int j = 0; j < c2; ++j) {
         printf("%d  ", result[i][j]);
         if (j == c2 - 1)
            printf("\n");
      }
    }
}