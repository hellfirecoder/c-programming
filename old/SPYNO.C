#include<stdio.h>
int spy(int n)
{
    int s=0,p=1,d;
    while(n>0)
    {
        d=n%10;
        s=s+d;
        p=p*d;
        n=n/10;
    }
    if (s == p)
    return 1;
else
    return 0;

}
int main()
{
    int n;
    printf("enter the number which is to be checked \n");
    scanf("%d",&n);
    if(spy(n))
    printf("spy no");
    else 
        printf("not spy no");
}