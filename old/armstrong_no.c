#include <stdio.h>
#include<math.h>
int main() 
{
  int n,m, sum = 0,temp,i;
    printf("Enter the range(lower limit and upper limit) \n");
    scanf("%d%d", &m,&n);
    for(i=m;i<=n;i++)
    {
    int z=i;
    int c=0;
    while (z != 0) {
        
        z =z/ 10;
        c++;
    }
    z=i;
    sum =0;
    int original=z;
    while (z != 0) {
        temp = z % 10;
        sum=sum + round(pow(temp,c));
         z =z/10;
    
    }
   
    if (original == sum)
        printf("%d is an armstrong no.\n", original);
    else
        printf("%d is not an armstrong no.\n", original);
    
    }
}
