#include <stdio.h>
#include <stdlib.h>

// Define the structure for a node in the doubly linked list
struct Node {
    int data;
    struct Node* prev;
    struct Node* next;
};

// Use a typedef for convenience
typedef struct Node node;

// Global pointer to the first node of the list
node* head = NULL;

// --- Function Prototypes ---
int len();
void ins();
void del();
void show();
void find();
void rev();

// --- Main Function with Menu ---
int main() {
    int choice;
    printf(
               "1. Insert   2. Delete   3. Display\n"
               "4. Search   5. Reverse  6. Exit\n"
               
               "Enter your choice: ");
    while (1) {
        // Consolidate menu printing into a single printf call

        scanf("%d", &choice);

        switch (choice) {
            case 1:
                ins();
                break;
            case 2:
                del();
                break;
            case 3:
                show();
                break;
            case 4:
                find();
                break;
            case 5:
                rev();
                break;
            case 6:
                printf("Exiting program\n");
                exit(0);
            default:
                printf("Invalid choice! Please enter a number between 1 and 6.\n");
        }
    }
    return 0;
}

// --- Function to get the current number of nodes in the list ---
int len() {
    int count = 0;
    node* temp = head;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

// --- i) Function to insert an element at any position ---
void ins() {
    int data, pos, count;
    node* newNode, *temp;

    // Create the new node
    newNode = (node*)malloc(sizeof(node));
    if (newNode == NULL) {
        printf("Error: Memory allocation failed!\n");
        return;
    }

    printf("Enter the data to insert: ");
    scanf("%d", &data);
    newNode->data = data;
    newNode->next = NULL;
    newNode->prev = NULL;

    // Get position from user
    count = len();
    printf("Enter the position to insert (1 to %d): ", count + 1);
    scanf("%d", &pos);

    // Validate the position
    if (pos < 1 || pos > count + 1) {
        printf("Invalid position!\n");
        free(newNode); // Free the allocated memory if position is invalid
        return;
    }

    // Case 1: Insert at the beginning (pos == 1)
    if (pos == 1) {
        if (head == NULL) { // If the list is initially empty
            head = newNode;
        } else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    } else {
        // Case 2: Insert at the end or an intermediate position
        temp = head;
        // Traverse to the node *before* the desired insertion point
        for (int i = 1; i < pos - 1; i++) {
            temp = temp->next;
        }

        newNode->next = temp->next;
        newNode->prev = temp;

        if (temp->next != NULL) { // If not inserting at the very end
            temp->next->prev = newNode;
        }
        temp->next = newNode;
    }
    printf("Element %d inserted successfully at position %d.\n", data, pos);
}

// --- ii) Function to delete an element from any position ---
void del() {
    if (head == NULL) {
        printf("List is empty. Nothing to delete.\n");
        return;
    }

    int pos, count;
    node* temp;

    count = len();
    printf("Enter the position of the element to delete (1 to %d): ", count);
    scanf("%d", &pos);

    // Validate the position
    if (pos < 1 || pos > count) {
        printf("Invalid position!\n");
        return;
    }

    // Case 1: Delete from the beginning (pos == 1)
    if (pos == 1) {
        temp = head;
        head = head->next;
        if (head != NULL) { // If there is more than one node
            head->prev = NULL;
        }
        printf(" Deleted element: %d\n", temp->data);
        free(temp);
    } else {
        // Case 2: Delete from the end or an intermediate position
        temp = head;
        // Traverse to the node to be deleted
        for (int i = 1; i < pos; i++) {
            temp = temp->next;
        }

        // Adjust the links
        temp->prev->next = temp->next;
        if (temp->next != NULL) { // If not deleting the last node
            temp->next->prev = temp->prev;
        }
        printf("Deleted element: %d\n", temp->data);
        free(temp);
    }
}

// --- iii) Function to display the list ---
void show() {
    if (head == NULL) {
        printf("The list is empty.\n");
        return;
    }

    node* temp = head;
    printf("List elements (Forward): NULL <-> ");
    while (temp != NULL) {
        printf("%d <-> ", temp->data);
        temp = temp->next;
    }
    printf("NULL\n");
}

// --- iv) Function to search for an element ---
void find() {
    if (head == NULL) {
        printf("The list is empty. Cannot search.\n");
        return;
    }

    int key, pos = 1;
    int found = 0;
    node* temp = head;

    printf("Enter the element to search for: ");
    scanf("%d", &key);

    while (temp != NULL) {
        if (temp->data == key) {
            printf("Element %d found at position %d.\n", key, pos);
            found = 1;
            break; // Use break to find only the first occurrence
        }
        temp = temp->next;
        pos++;
    }

    if (!found) {
        printf("Element %d was not found in the list.\n", key);
    }
}

// --- v) Function to reverse the list ---
void rev() {
    if (head == NULL || head->next == NULL) {
        printf("List is empty or has only one node. No reversal needed.\n");
        return;
    }

    node* current = head;
    node* temp = NULL;

    // Traverse the list and swap the next and prev pointers for each node
    while (current != NULL) {
        temp = current->prev;        // Store original prev
        current->prev = current->next; // Make prev point to next
        current->next = temp;        // Make next point to original prev
        current = current->prev;     // Move to the next node (which is now in prev)
    }

    // After the loop, `temp` points to the new tail's prev pointer.
    // The new head is the `prev` of the old head.
    if (temp != NULL) {
        head = temp->prev;
    }

    printf("The list has been successfully reversed.\n");
}