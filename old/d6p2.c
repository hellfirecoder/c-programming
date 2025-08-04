#include<stdio.h>
int DecimalToOctal(int n)
{
    static int sem=1,octal=0;
    if(n!=0)
    {
      octal=octal+(n%8)*sem;
      sem=sem*10;
      DecimalToOctal(n/8);
    }
   return octal;
}
int main()
{
    int n;
    printf("Enter the Decimal Value:");
    scanf("%d",&n);
    printf("Octal Value of Decimal number is: %d",DecimalToOctal(n));
}