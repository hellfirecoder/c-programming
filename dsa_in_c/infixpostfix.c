#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_SIZE 100

// --- Stack for Characters (for Infix to Postfix) ---
struct CharStack {
    int top;
    char items[MAX_SIZE];
};

void initCharStack(struct CharStack* s) { s->top = -1; }

// Updated function with if-else
int isCharStackEmpty(struct CharStack* s) {
    if (s->top == -1) {
        return 1; // True, the stack is empty
    } else {
        return 0; // False, the stack is not empty
    }
}

void pushChar(struct CharStack* s, char value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Char Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

char popChar(struct CharStack* s) {
    if (isCharStackEmpty(s)) 
        return '\0';
    return s->items[(s->top)--];
}

char peekChar(struct CharStack* s) {
    if (isCharStackEmpty(s)) return '\0'; // Added a check to prevent reading from an empty stack
    return s->items[s->top];
}

// --- Stack for Doubles (for Postfix Evaluation) ---
struct DoubleStack {
    int top;
    double items[MAX_SIZE];
};

void initDoubleStack(struct DoubleStack* s) { s->top = -1; }

// Updated function with if-else
int isDoubleStackEmpty(struct DoubleStack* s) {
    if (s->top == -1) {
        return 1; // True, the stack is empty
    } else {
        return 0; // False, the stack is not empty
    }
}

void pushDouble(struct DoubleStack* s, double value) {
    if (s->top == MAX_SIZE - 1) {
        printf("Double Stack Overflow\n");
        exit(EXIT_FAILURE);
    }
    s->items[++(s->top)] = value;
}

double popDouble(struct DoubleStack* s) {
    if (isDoubleStackEmpty(s)) return 0.0;
    return s->items[(s->top)--];
}

// --- Core Functions ---

/**
 * @brief Returns the precedence of a mathematical operator.
 */
int prec(char c) {
    if (c == '^')
        return 3;
    else if (c == '/' || c == '*')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    else
        return -1;
}

/**
 * @brief Converts an infix expression string to a postfix expression string.
 */
void infixToPostfix(const char* infix, char* postfix) {
    struct CharStack stack;
    initCharStack(&stack);
    int j = 0;

    for (int i = 0; infix[i] != '\0'; i++) {
        char token = infix[i];

        // Check if token is a letter or a digit using ASCII values
        if ((token >= 'a' && token <= 'z') || (token >= 'A' && token <= 'Z') || (token >= '0' && token <= '9')) {
            postfix[j++] = token;
        }
        else if (token == '(') {
            pushChar(&stack, token);
        }
        else if (token == ')') {
            while (!isCharStackEmpty(&stack) && peekChar(&stack) != '(') {
                postfix[j++] = popChar(&stack);
            }
            popChar(&stack); // Pop the '('
        }
        else { // Operator
            while (!isCharStackEmpty(&stack) && peekChar(&stack) != '(' && prec(token) <= prec(peekChar(&stack))) {
                postfix[j++] = popChar(&stack);
            }
            pushChar(&stack, token);
        }
    }

    // Pop any remaining operators from the stack
    while (!isCharStackEmpty(&stack)) {
        postfix[j++] = popChar(&stack);
    }
    
    postfix[j] = '\0';
}

/**
 * @brief Evaluates a postfix expression string.
 */
double evaluatePostfix(const char* postfix) {
    struct DoubleStack stack;
    initDoubleStack(&stack);

    for (int i = 0; postfix[i] != '\0'; i++) {
        char token = postfix[i];

        // Check if token is a digit using ASCII values
        if (token >= '0' && token <= '9') {
            pushDouble(&stack, (double)(token - '0'));
        }
        else { // Operator
            double operand2 = popDouble(&stack);
            double operand1 = popDouble(&stack);

            switch (token) {
                case '+': pushDouble(&stack, operand1 + operand2); break;
                case '-': pushDouble(&stack, operand1 - operand2); break;
                case '*': pushDouble(&stack, operand1 * operand2); break;
                case '/':
                    // Division by zero check is still present as in your last provided code
                    if (operand2 == 0) {
                        fprintf(stderr, "Error: Division by zero.\n");
                        exit(EXIT_FAILURE);
                    }
                    pushDouble(&stack, operand1 / operand2);
                    break;
                case '^': pushDouble(&stack, pow(operand1, operand2)); break;
            }
        }
    }
    return popDouble(&stack);
}

// --- Driver Program ---
int main() {
    char infix[MAX_SIZE];
    char postfix[MAX_SIZE];

    // 1. Get infix expression from the user using scanf
    printf("Enter an infix expression (e.g., 3+5*2): ");
    scanf("%s", infix);

    printf("\nInfix Expression: %s\n", infix);

    // 2. Convert to postfix
    infixToPostfix(infix, postfix);
    printf("Postfix Expression: %s\n", postfix);

    // 3. Evaluate the postfix expression and print the result
    double result = evaluatePostfix(postfix);
    printf("Evaluation Result: %.2f\n", result);

    return 0;
}