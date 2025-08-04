#include<stdio.h>
#include<math.h>
/*1. Write a menu-driven program to –
i. Calculate the factorial of a given number
ii. Check whether the number is prime or not (Use square root approach)
iii. Check whether the number is a palindrome or not.
iv. Check whether the number is Armstrong number or not.
Use different functions for each of the above tasks and call the functions from main().*/
int fact(int n)
{
    int f=1;
    for(int i=1;i<=n;i++)
        f=f*i;
    return f;
}
int primecheck( int n)
{
    if(n<=1)
        return 0;
    for(int i=2;i<=sqrt(n);i++)
        if(n%i==0)
            return 0;
    return 1;
}
int palindrome(int n)
{
    int sum=0, o=n;
    while(n!=0)
    {   int d=n%10;
        sum=(sum*10)+d;
        n=n/10;
    }
    if(sum==o)
        return 1;
    return 0;

}
int armstrong(int n)
{   int i=n,temp,sum;
    int z=i;
    int c=0;
    while (z!= 0) {
        
        z =z/ 10;
        c++;
    }
    z=i;
    sum=0;
    int original=z;
    while (z != 0) {
        temp = z % 10;
        sum=sum + round(pow(temp,c));
         z =z/10;
    
    }
   
    if (original == sum)
        return 1;
    else
        return 0;
}


int main()
{
    int n,choice;
    printf("enter the number which is to be checked");
    scanf("%d",&n);
    printf("enter the choice");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
            
             printf("%d",fact(n));
             break;
        case 2:
            if(primecheck(n))
                printf("prime number");
            else 
                printf("not prime number");
            break;
        case 3:
        if(palindrome(n))
        printf("palindrome number");
        else 
            printf("not palindrome number");
        break;   
        case 4:
            if(armstrong(n))
            printf("armstrong number");
            else 
                printf("not armstrong  number");
            break;  
    }
    return 1;

}
