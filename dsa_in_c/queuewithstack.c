#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// --- Stack Implementation ---

// A structure to represent a node in the stack
struct StackNode {
    int data;
    struct StackNode* next;
};

// A structure to represent a stack.
// The stack is implemented as a linked list.
struct Stack {
    struct StackNode* top;
};

// Function to create a new stack node
struct StackNode* newStackNode(int data) {
    struct StackNode* stackNode = (struct StackNode*)malloc(sizeof(struct StackNode));
    if (!stackNode) {
        printf("Heap Overflow\n");
        exit(1);
    }
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

// Function to create a stack
struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    if (!stack) {
        printf("Heap Overflow\n");
        exit(1);
    }
    stack->top = NULL;
    return stack;
}

// Function to check if the stack is empty
int isStackEmpty(struct Stack* stack) {
    return stack->top == NULL;
}

// Function to push an item to the stack
void push(struct Stack* stack, int item) {
    struct StackNode* stackNode = newStackNode(item);
    stackNode->next = stack->top;
    stack->top = stackNode;
}

// Function to pop an item from the stack
int pop(struct Stack* stack) {
    if (isStackEmpty(stack)) {
        // In a real application, you might handle this error differently
        return INT_MIN;
    }
    struct StackNode* temp = stack->top;
    stack->top = stack->top->next;
    int popped = temp->data;
    free(temp);
    return popped;
}


// --- Queue Implementation using two Stacks ---

// A structure to represent a queue
struct Queue {
    struct Stack* input_stack;
    struct Stack* output_stack;
};

// Function to create a queue
struct Queue* createQueue() {
    struct Queue* q = (struct Queue*)malloc(sizeof(struct Queue));
    if (!q) {
        printf("Heap Overflow\n");
        exit(1);
    }
    q->input_stack = createStack();
    q->output_stack = createStack();
    return q;
}

// A helper function to transfer elements from input_stack to output_stack
void transfer_if_needed(struct Queue* q) {
    // If output_stack is empty, transfer all items from input_stack
    if (isStackEmpty(q->output_stack)) {
        while (!isStackEmpty(q->input_stack)) {
            push(q->output_stack, pop(q->input_stack));
        }
    }
}

// Function to check if the queue is empty
int isQueueEmpty(struct Queue* q) {
    return isStackEmpty(q->input_stack) && isStackEmpty(q->output_stack);
}

// Function to add an item to the queue (enqueue)
void enqueue(struct Queue* q, int item) {
    // Simply push the item onto the input stack.
    push(q->input_stack, item);
    printf("Enqueued: %d\n", item);
}

// Function to remove an item from the queue (dequeue)
int dequeue(struct Queue* q) {
    // Ensure the output stack has the oldest elements at its top.
    transfer_if_needed(q);

    if (isQueueEmpty(q)) {
        printf("Dequeue failed: Queue is empty.\n");
        return INT_MIN; // Return a sentinel value for error
    }

    // Pop from the output stack, which has elements in FIFO order.
    int item = pop(q->output_stack);
    printf("Dequeued: %d\n", item);
    return item;
}

// Function to get the front item of the queue without removing it (peek)
int peek(struct Queue* q) {
    // Ensure the output stack has the oldest elements at its top.
    transfer_if_needed(q);

    if (isQueueEmpty(q)) {
        printf("Peek failed: Queue is empty.\n");
        return INT_MIN; // Return a sentinel value for error
    }

    // The top of the output stack is the front of the queue.
    int front_item = q->output_stack->top->data;
    printf("Peek: %d\n", front_item);
    return front_item;
}

// Function to free the memory used by the queue
void freeQueue(struct Queue* q) {
    // Free any remaining nodes in both stacks
    while (!isStackEmpty(q->input_stack)) {
        pop(q->input_stack);
    }
    while (!isStackEmpty(q->output_stack)) {
        pop(q->output_stack);
    }
    free(q->input_stack);
    free(q->output_stack);
    free(q);
}

// --- Driver Code to Demonstrate Usage ---
int main() {
    struct Queue* q = createQueue();
    int choice, value;

    while (1) {
        printf("\n--- Queue using Stacks Menu ---\n");
        printf("1. Enqueue\n");
        printf("2. Dequeue\n");
        printf("3. Peek (Front)\n");
        printf("4. Check if Empty\n");
        printf("5. Exit\n");
        printf("-------------------------------\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            // Clear the input buffer in case of non-integer input
            while (getchar() != '\n');
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                printf("Enter the value to enqueue: ");
                if (scanf("%d", &value) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid input. Please enter a number.\n");
                } else {
                    enqueue(q, value);
                }
                break;
            case 2:
                dequeue(q);
                break;
            case 3:
                peek(q);
                break;
            case 4:
                if (isQueueEmpty(q)) {
                    printf("Result: Queue is empty.\n");
                } else {
                    printf("Result: Queue is not empty.\n");
                }
                break;
            case 5:
                printf("Exiting program. Cleaning up memory...\n");
                freeQueue(q);
                return 0;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}

