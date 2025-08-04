#include <stdio.h>
int main()
{
    int arr[10][10],i,j,r,c;
    
    printf("enter the rows \n ");
    scanf("%d",&r);
    printf("enter the columns both have to be same\n ");
    scanf("%d",&c);
    for(i=0;i<r;i++)
    {
        for(j=0;j<c;j++)
      {
        scanf("%d",&arr[i][j]);
      }
    }

    int isUpperTriangular = 1;
    int isLowerTriangular = 1;

    for ( i = 0; i < r; i++) {
        for ( j = 0; j < r; j++) {
            if (i > j && arr[i][j] != 0) 
            {
                isUpperTriangular = 0;
            }
            if (i < j && arr[i][j] != 0) 
            {
                isLowerTriangular = 0;
            }
        }
    }

    if (isUpperTriangular) {
        printf("The matrix is upper triangular.\n");
    } else if (isLowerTriangular) {
        printf("The matrix is lower triangular.\n");
    } else {
        printf("The matrix is neither upper triangular nor lower triangular.\n");
    }
}