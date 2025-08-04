#include <stdio.h>
#include <math.h>
int conv2(int n) {
    if(n==0)
    return 0;
    return (n%2) + conv2(n/2)*10;
}
int conv8(int n) {
    if(n==0)
    return 0;
    return (n%8) + conv8(n/8)*10;
}
int conv10f2(int n) {
    int c = 0, d;
    int res = 0;
    while (n != 0) {
        d = n % 10;
        res = res + d * (int)pow(2, c);
        c++;
        n = n / 10;
    }
    return res;
}
int conv10f8(int n) {
    int c = 0, d;
    int res = 0;
    while (n != 0) {
        d = n % 10;
        res = res + d * (int)pow(8, c);
        c++;
        n = n / 10;
    }
    return res;
}

int main() {
    int n, b, tb;
    printf("Enter the number and its base (excluding hexadecimal base):\n");
    scanf("%d %d", &n, &b);
    printf("To which base do you want to convert (excluding hexadecimal base)?\n");
    scanf("%d", &tb);
    int nd = n;
    if(b==2 || b==8 ||b==10){
    if (b == 2) 
        nd = conv10f2(n);
    else if (b == 8) 
        nd = conv10f8(n);
    switch (tb) {
        case 2:
            printf("%d in base %d is %d\n", n, tb, conv2(nd));
            break;
        case 8:
            printf("%d in base %d is %d\n", n, tb, conv8(nd));
            break;
        case 10:
            printf("%d in base %d is %d\n", n, tb, nd);
            break;
        default:
            printf("Invalid choice!\n");
    }
 }
 else 
 printf("Invalid Base!Base must be either 2 or 8 or 10\n");
    return 0;
}