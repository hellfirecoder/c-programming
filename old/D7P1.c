#include<stdio.h>
int words(char src[]){
    int i=0, words=0;
    while(src[i]!='\0'){
        if(src[i==' '])
            words++;
        i++;
    }
    return words;
}
int main(){
    char str[500];
    printf("Enter a string.");
    scanf("%[^\n]s", str);
    printf("Words: %d", words(str));
    return 0;
}