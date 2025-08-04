#include<stdio.h>
int main()
{ int a[100],c[100],c2[100];
  printf("enter the no of elements to be entered");
  int n,i,pos,num,p;
  scanf("%d",&n);
  printf("enter the  elements ");
  for(i=0;i<n;i++)
    scanf("%d",&a[i]);
  printf("enter the position  to be inserted");
  scanf("%d",&pos);
  printf("enter the num  to be inserted");
  scanf("%d",&num);
  pos=pos-1;
  n=n+1;
  for(i=0;i<pos;i++)
    c[i]=a[i];
  c[pos]=num;
  for(i=pos+1;i<n;i++)
    c[i]=a[i-1];
    for(i=0;i<n;i++)
     printf("%d  ",c[i]); 
    
    //now for deletion
    printf("enter the position  to be deleted");
    scanf("%d",&p);
    p=p-1;
    for(i=0;i<p;i++)
    c2[i]=a[i];
  for(i=p;i<n;i++)
    c2[i]=a[i+1];
    for(i=0;i<n-2;i++)
     printf("%d  ",c2[i]);
}

