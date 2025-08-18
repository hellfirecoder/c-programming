#include<stdio.h>
#include<stdlib.h>
#include<limits.h> // For INT_MIN....

typedef struct node {
    int data;
    struct node *next;
}node;

// Inserts a new node at the beginning of the list.
void insertBeg(int ele, node **head){
    // 1. Allocate memory for the new node
    node *temp = malloc(sizeof(node));
    if (temp == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    // 2. Set the data and link to the old head
    temp->data=ele;
    temp->next=(*head);

    // 3. Make the new node the new head
    (*head)=temp;
}

// Inserts a new node at the end of the list.
void insertEnd(int ele, node **head) {
    // 1. Allocate memory for the new node
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }

    // 2. Set the data and make its next pointer NULL, as it will be the last node
    newNode->data = ele;
    newNode->next = NULL;

    // 3. If the list is empty, the new node becomes the head
    if (*head == NULL) {
        *head = newNode;
        return;
    }

    // 4. Otherwise, traverse to the end of the list
    node *last = *head;
    while (last->next != NULL) {
        last = last->next;
    }

    // 5. Link the last node to the new node
    last->next = newNode;
}

// Inserts a new node at a specified position (1-based index).
void insertAnywhere(int ele, int pos, node **head) {
    // Position 1 is the beginning.
    if (pos < 1) {
        printf("Invalid position. Position must be 1 or greater.\n");
        return;
    }
    if (pos == 1) {
        insertBeg(ele, head);
        return;
    }

    // Traverse to the node just before the desired position.
    node *temp = *head;
    // We stop at pos-1. The loop runs pos-2 times.
    // e.g., for pos=3, i=1; i<2. Loop runs once. temp points to node 1.
    for (int i = 1; i < pos - 1 && temp != NULL; i++) {
        temp = temp->next;
    }

    // If the position is out of bounds (e.g., pos 5 in a 3-node list)
    if (temp == NULL) {
        printf("Position %d is out of bounds.\n", pos);
        return;
    }

    // Create the new node
    node *newNode = malloc(sizeof(node));
    if (newNode == NULL) {
        fprintf(stderr, "Error: Memory allocation failed.\n");
        return;
    }
    newNode->data = ele;

    // Link the new node into the list
    newNode->next = temp->next;
    temp->next = newNode;
}

// Deletes the first node and returns its data.
int deleteBeg(node **head) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return INT_MIN; // Return a value indicating error
    }
    node *temp = *head;
    int deletedData = temp->data;
    *head = (*head)->next; // Move head to the next node
    free(temp);            // Free the old head
    return deletedData;
}

// Deletes the last node and returns its data.
int deleteEnd(node **head) {
    if (*head == NULL) {
        printf("List is empty. Cannot delete.\n");
        return INT_MIN;
    }
    // If there is only one node
    if ((*head)->next == NULL) {
        return deleteBeg(head);
    }

    // Traverse to the second-to-last node
    node *second_last = *head;
    while (second_last->next->next != NULL) {
        second_last = second_last->next;
    }

    node *lastNode = second_last->next;
    int deletedData = lastNode->data;
    second_last->next = NULL; // Unlink the last node
    free(lastNode);           // Free it
    return deletedData;
}

// Deletes a node from a specified position (1-based index).
int deleteAnywhere(int pos, node **head) {
    if (pos < 1 || *head == NULL) {
        printf("Invalid position or empty list.\n");
        return INT_MIN;
    }
    if (pos == 1) {
        return deleteBeg(head);
    }
    node *prev = *head;
    for (int i = 1; i < pos - 1 && prev->next != NULL; i++) {
        prev = prev->next;
    }
    if (prev->next == NULL) {
        printf("Position %d is out of bounds.\n", pos);
        return INT_MIN;
    }
    node *nodeToDelete = prev->next;
    int deletedData = nodeToDelete->data;
    prev->next = nodeToDelete->next;
    free(nodeToDelete);
    return deletedData;
}

// Utility function to print the linked list
void printList(node *head) {
    node *current = head;
    printf("List: ");
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

int main() {
    node *head = NULL;
    int choice, element, position, deleted_val;
    printf("\n--- Menu: 1.InsBeg 2.InsEnd 3.InsPos | 4.DelBeg 5.DelEnd 6.DelPos | 7.Disp 0.Exit ---\n");
    while (1) {
        // A more compact menu
        
        printf("choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                insertBeg(element, &head);
                printList(head);
                break;
            case 2:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                insertEnd(element, &head);
                printList(head);
                break;
            case 3:
                printf("Enter element to insert: ");
                scanf("%d", &element);
                printf("Enter position : ");
                scanf("%d", &position);
                insertAnywhere(element, position, &head);
                printList(head);
                break;
            case 4:
                deleted_val = deleteBeg(&head);
                if (deleted_val != INT_MIN) printf("Deleted element: %d\n", deleted_val);
                printList(head);
                break;
            case 5:
                deleted_val = deleteEnd(&head);
                if (deleted_val != INT_MIN) printf("Deleted element: %d\n", deleted_val);
                printList(head);
                break;
            case 6:
                printf("Enter position to delete: ");
                scanf("%d", &position);
                deleted_val = deleteAnywhere(position, &head);
                if (deleted_val != INT_MIN) printf("Deleted element: %d\n", deleted_val);
                printList(head);
                break;
            case 7:
                printList(head);
                break;
            case 0:
                printf("Exiting program. Freeing all nodes...\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
    return 0; // This line is technically unreachable but good practice.
}
