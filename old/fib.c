#include<stdio.h>
int main()
{
    int n , i,third;
    printf("enter the number of terms the fibonacci sequence is to be printed");
    scanf("%d",&n);
    int first=0;
    int second=1;
    if(n==1)
    {
        printf("%d \n",first);
    }

    else if (n==2)
    {
         printf("%d \n",first);
         printf("%d \n",second);
    }
    else
    {
         printf("%d \n",first);
         printf("%d \n",second);
    for(i=3;i<=n;i++)
    {
    
    third=first+second;
    first=second;
    second=third;
    printf("%d \n",third);
    } 
    }
    return 0;
}