#include <stdio.h>
int main() {
  int n, reversed = 0, remainder, original;
    printf("Enter an integer: \n");
    scanf("%d", &n);
    original = n;
    int c=0, sum =0;
    
    while (n != 0) {
        remainder = n % 10;
        sum=sum+remainder;
        reversed = reversed * 10 + remainder;
        n /= 10;
        c++;
    }
    printf("the number of digits in the number = %d \n",c);
    printf("the sum of digits in the number = %d \n",sum);
    
    if (original == reversed)
        printf("%d is a palindrome.", original);
    else
        printf("%d is not a palindrome.", original);


    return 0;
}