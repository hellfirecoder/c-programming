//Write a menu driven program to find the max, min, average and standard deviation of the elements
//of an integer array.
#include<stdio.h>
#include <math.h>
int main()
{
    int arr[100],i,n,choice,max,min;
    float sum = 0;
    printf("enter the array length");
    scanf("%d",&n);
    printf("enter the array elements");
    for(i=0;i<n;i++)
    {
        scanf("%d",&arr[i]);
    }
    printf("enter the choice");
    scanf("%d",&choice);
    switch(choice)
    {
    case 1:
        max=arr[0];
        
        for(i=0;i<n;i++)
        {
             if(max<arr[i])
                 max=arr[i];
        }    
        printf("max element %d \n",max);
        break;
    case 2:
        min=arr[0];
        for(i=0;i<n;i++)
        {
             if(min>arr[i])
                min=arr[i];
        }
        printf("min element %d \n",min);
        break;
    case 3:
    
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }
    float mean = sum / n;
    float values = 0;
    for (int i = 0; i < n; i++) {
        values += pow(arr[i] - mean, 2);
    }
    float variance = values / n;
    float standardDeviation = sqrt(variance);
    printf("%.2f\n", standardDeviation);
    break;
    default:
        printf("invalid choice");
    }
}   
