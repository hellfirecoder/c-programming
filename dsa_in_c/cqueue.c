// 2. Write a menu driven program to implement a circular queue using array with the following operations-
// i. enqueueRear
// ii. dequeueFront
// v. isEmpty
// vi. isFull

#include<stdio.h>
#include<stdlib.h>

// It's good practice to use uppercase for constants.
#define SIZE 5

// The structure remains the same.
typedef struct {
    int f;
    int r;
    int a[SIZE];
} queue;

// Checks if the queue is full in a circular manner.
// The queue is full when the position after rear is the front.
int isFull(queue *q) {
    if ((q->r + 1) % SIZE == q->f)
        return 1; // 1 means true (it is full)
    return 0; // 0 means false
}

// Checks if the queue is empty.
// We consider the queue empty if front is -1.
int isEmpty(queue *q) {
    if (q->f == -1)
        return 1; // 1 means true (it is empty)
    return 0; // 0 means false
}

// Adds an element to the rear, wrapping around if necessary.
void enqueueRear(queue *q, int ele) {
    if (isFull(q)) {
        printf("Queue Overflow: The queue is full.\n");
        return;
    }
    // If this is the first element, set front to 0.
    if (isEmpty(q)) {
        q->f = 0;
    }
    // Increment rear circularly.
    q->r = (q->r + 1) % SIZE;
    q->a[q->r] = ele;
    printf("Enqueued %d successfully.\n", ele);
}

// Removes an element from the front, wrapping around if necessary.
int dequeueFront(queue *q) {
    int dequeued_element;
    if (isEmpty(q)) {
        printf("Queue Underflow: The queue is empty.\n");
        return -1; // Return a sentinel value to indicate an error.
    }
    
    dequeued_element = q->a[q->f];

    // If this was the last element in the queue, reset to empty state.
    if (q->f == q->r) {
        printf("Queue is now empty, resetting pointers.\n");
        q->f = -1;
        q->r = -1;
    } else {
        // Otherwise, just move the front pointer circularly.
        q->f = (q->f + 1) % SIZE;
    }
    
    return dequeued_element;
}

int main() {
    int choice, element, dequeued_val;
    queue q;
    // Initialize front and rear pointers to -1 to indicate an empty queue.
    q.r = -1;
    q.f = -1;

    while(1) { // This creates an infinite loop, broken by choice 5.
        // Shortened menu
        printf("\n1.Enqueue 2.Dequeue 3.IsEmpty 4.IsFull 5.Exit\nChoice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter element: ");
                scanf("%d", &element);
                enqueueRear(&q, element);
                break;
                
            case 2:
                dequeued_val = dequeueFront(&q);
                if (dequeued_val != -1) {
                    printf("Dequeued: %d\n", dequeued_val);
                }
                break;
                
            case 3:
                if(isEmpty(&q)) {
                    printf("Result: Queue IS empty.\n");
                } else {
                    printf("Result: Queue is NOT empty.\n");
                }
                break;
                
            case 4:
                if(isFull(&q)) {
                    printf("Result: Queue IS full.\n");
                } else {
                    printf("Result: Queue is NOT full.\n");
                }
                break;
            
            case 5:
                printf("Exiting.\n");
                exit(0);
                
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
