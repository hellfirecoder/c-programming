#include<stdio.h>
#include<math.h>
int main()
{
int n,b,i=1;
printf("Enter a positive decimal number");
scanf("%d", &n);
printf("Enter the base");
scanf("%d", &b);
if(b==2)
{   int binaryNum[1000]; 
  
    // counter for binary array 
    int i = 0; 
    while (n > 0) { 
  
        // storing remainder in binary array 
        binaryNum[i] = n % 2; 
        n = n / 2; 
        i++; 
    } 
  
    // printing binary array in reverse order 
    for (int j = i - 1; j >= 0; j--) 
        printf("%d", binaryNum[j]);
}
else if(b==8)
{
    int  remainder;
    int octal[100]; // Array to store octal number
    int i = 0;
    while(n != 0) {
    remainder = n % 8;
    octal[i] = remainder;
    n /= 8;
    i++;
    }

// Display the octal number in reverse order
printf("Octal equivalent: ");
for (int j = i - 1; j >= 0; j--)
    printf("%d", octal[j]);
printf("\n");
}
else if(b==16)
{
    char hexadecimal[100];
    int index = 0;

    while (n != 0) {
        int remainder = n % 16;

        if (remainder < 10) {
            hexadecimal[index] = 48 + remainder; // 48 is the ASCII value for '0'
        } else {
            hexadecimal[index] = 55 + remainder; // 55 is the ASCII value for 'A'
        }

        n = n / 16;
        index++;
    }

    printf("Hexadecimal: ");
    for (int i = index - 1; i >= 0; i--) {
        printf("%c", hexadecimal[i]);
    }
    printf("\n");
}
else
    printf("invalid choice");
}