#include<stdio.h>
void mystrcat(char src1[],char src2[],char dest[]){
    int i=0, j=0;
    while(src1[i]!='\0'){
        dest[i]=src1[i];
        i++;
    }
    while(src2[j]!='\0'){
        dest[i+j]=src2[j];
        j++;
    }
    dest[i+j]='\0';
}
int main(){
    char str1[500], str2[500], fstr[1000],c;
    printf("Enter string 1: \n");
    //while((c=getchar())!=EOF && c!='\n');
    scanf("%[^\n]s", str1);
    printf("Enter string 2: \n");
    //while((c=getchar())!=EOF && c!='\n');
    scanf(" %[^\n]s", str2);
    printf("str1: %s\n", str1);
    printf("str2: %s\n", str2);
    mystrcat(str1, str2, fstr);
    printf("final concatenated str: %s\n", fstr);
    return 0;
}