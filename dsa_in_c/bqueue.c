// 1. Write a menu driven program to implement a basic queue using array with the following operations-
// i. enqueueRear
// ii. dequeueFront
// v. isEmpty
// vi. isFull

#include<stdio.h>
#include<stdlib.h>
#define SIZE 5

typedef struct queue
{
    int f;
    int r;
    int a[SIZE];
}queue;

int isEmpty(queue *q)
{
    if(q->f == q ->r)
        return 1;// size is empty
    return 0;
}
int isFull(queue *q)
{
    if(q->r == SIZE-1)
        return 1;//size full
    return 0;
}

int enqueuer(queue *q,int ele)
{
    if(isFull(q))
    {
        printf("the queue is full overflow error");
        return 0;
    }
    (q->r)++;
    q->a[q->r]=ele;
    return 1;
}

int dequeuef(queue *q)
{
    if(isEmpty(q))
    {
        printf("the queue is empty underflow error");
        return 0;
    }
    (q->f)++;
    int p=q->a[q->f];
    
    return p;

}

int main()
{
    int c,n=1;
    int e,z;
    queue q;
    q.r=q.f=-1;
    while(n!=0)
    {
    printf("enter your choice\n1)isEmpty\n2)isFull\n3)enqueuer\n4)dequeuef\n");
    scanf("%d",&c);
    printf("press cnrl+c to exit\n");


    switch(c)
    {
        case 1:
            printf("you have chosen isEmpty\n");
            if(isEmpty(&q)){
                printf("the queue is empty\n");
                q.f=q.r=-1;
            }
                
            else
                printf("the queue is not empty\n");
            break;
        case 2:
            printf("you have chosen isFull\n");
            if(isFull(&q))
                printf("the queue is Full\n");
            else
                printf("the queue is not Full\n");
            break;
        case  3:
            printf("you have chosen enqueue rear\n");
            printf("enter the value u want to add\n");
            scanf("%d",&e);
            enqueuer(&q,e);
            break;
        case  4:
            printf("you have chosen dequeue front\n");
            z=dequeuef(&q);
            printf("the value dequed=%d\n",z);
            break;    
        default:
            printf("invaid choice\n");


        

            
    }
}

}