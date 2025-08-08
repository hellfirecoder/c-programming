#include<stdio.h>
#include<stdlib.h>

// It's good practice to use uppercase for constants.
#define SIZE 5

// The structure now represents a Deque.
typedef struct {
    int f;
    int r;
    int a[SIZE];
} deque;

// Checks if the deque is full.
int isFull(deque *q) {
    if ((q->r + 1) % SIZE == q->f)
        return 1;
    return 0;
}

// Checks if the deque is empty.
int isEmpty(deque *q) {
    if (q->f == -1)
        return 1;
    return 0;
}

// Adds an element to the REAR of the deque.
void enqueueRear(deque *q, int ele) {
    if (isFull(q)) {
        printf("Deque Overflow: The deque is full.\n");
        return;
    }
    if (isEmpty(q)) { // If it's the first element
        q->f = 0;
    }
    q->r = (q->r + 1) % SIZE; // Increment rear circularly
    q->a[q->r] = ele;
    printf("Enqueued %d to rear.\n", ele);
}

// NEW: Adds an element to the FRONT of the deque.
void enqueueFront(deque *q, int ele) {
    if (isFull(q)) {
        printf("Deque Overflow: The deque is full.\n");
        return;
    }
    if (isEmpty(q)) { // If it's the first element
        q->f = 0;
        q->r = 0;
    } else {
        // Decrement front circularly
        q->f = (q->f - 1 + SIZE) % SIZE;
    }
    q->a[q->f] = ele;
    printf("Enqueued %d to front.\n", ele);
}

// Removes an element from the FRONT of the deque.
int dequeueFront(deque *q) {
    int dequeued_element;
    if (isEmpty(q)) {
        printf("Deque Underflow: The deque is empty.\n");
        return -1;
    }
    dequeued_element = q->a[q->f];
    if (q->f == q->r) { // If it was the last element
        q->f = -1;
        q->r = -1;
    } else {
        q->f = (q->f + 1) % SIZE; // Increment front circularly
    }
    return dequeued_element;
}

// NEW: Removes an element from the REAR of the deque.
int dequeueRear(deque *q) {
    int dequeued_element;
    if (isEmpty(q)) {
        printf("Deque Underflow: The deque is empty.\n");
        return -1;
    }
    dequeued_element = q->a[q->r];
    if (q->f == q->r) { // If it was the last element
        q->f = -1;
        q->r = -1;
    } else {
        // Decrement rear circularly
        q->r = (q->r - 1 + SIZE) % SIZE;
    }
    return dequeued_element;
}

// Displays the deque's elements from front to rear.
void display(deque *q) {
    if (isEmpty(q)) {
        printf("Deque is empty.\n");
        return;
    }
    printf("Deque (front to rear): [ ");
    int i = q->f;
    while (1) {
        printf("%d ", q->a[i]);
        if (i == q->r) break;
        i = (i + 1) % SIZE;
    }
    printf("]\n");
}

int main() {
    int choice, element;
    deque q;
    q.r = -1;
    q.f = -1;

    while(1) {
        printf("\n--- Deque Menu ---\n");
        printf("1. Enqueue Rear\n2. Dequeue Front\n3. Enqueue Front\n4. Dequeue Rear\n");
        printf("5. IsEmpty\n6. IsFull\n7. Display\n8. Exit\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                printf("Enter element: ");
                scanf("%d", &element);
                enqueueRear(&q, element);
                break;
            case 2:
                element = dequeueFront(&q);
                if (element != -1) printf("Dequeued from front: %d\n", element);
                break;
            case 3:
                printf("Enter element: ");
                scanf("%d", &element);
                enqueueFront(&q, element);
                break;
            case 4:
                element = dequeueRear(&q);
                if (element != -1) printf("Dequeued from rear: %d\n", element);
                break;
            case 5:
                if(isEmpty(&q)) printf("Result: Deque IS empty.\n");
                else printf("Result: Deque is NOT empty.\n");
                break;
            case 6:
                if(isFull(&q)) printf("Result: Deque IS full.\n");
                else printf("Result: Deque is NOT full.\n");
                break;
            case 7:
                display(&q);
                break;
            case 8:
                printf("Exiting.\n");
                exit(0);
            default:
                printf("Invalid choice.\n");
        }
    }
    return 0;
}
