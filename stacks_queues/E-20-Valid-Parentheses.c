/* 
Leetcode E 20 Valid Parenthesis

Approach:
Use stack of size = length of string.
For every open bracket, push it on stack
For every close bracket, if stack is empty throw error, otherwise if top element is not matching the closed bracket throw error.

Output:
Test String 1: Valid
Test String 2: Valid
Test String 3: Invalid
Test String 4: Invalid
Test String 5: Valid

*/
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Structure to represent a stack
typedef struct {
    char *array;
    int top;
} Stack;

// Function to initialize a stack
Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->array = (char*)malloc(capacity * sizeof(char));
    stack->top = -1;
    return stack;
}

// Function to check if the stack is empty
bool isEmpty(Stack* stack) {
    return stack->top == -1;
}

// Function to push an element onto the stack
void push(Stack* stack, char element) {
    stack->array[++stack->top] = element;
}

// Function to pop an element from the stack
char pop(Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->array[stack->top--];
    }
    return '\0'; // Return null character for an empty stack
}

// Function to check if parentheses are valid
bool isValid(char* s) {
    int length = 0;
    while (s[length] != '\0') {
        length++;
    }

    Stack* stack = createStack(length);

    for (int i = 0; i < length; i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[') {
            push(stack, s[i]);
        } else {
            if (isEmpty(stack)) {
                free(stack->array);
                free(stack);
                return false; // No corresponding open bracket
            }

            char topElement = pop(stack);
            if ((s[i] == ')' && topElement != '(') ||
                (s[i] == '}' && topElement != '{') ||
                (s[i] == ']' && topElement != '[')) {
                free(stack->array);
                free(stack);
                return false; // Mismatched brackets
            }
        }
    }

    bool result = isEmpty(stack); // Stack should be empty if all brackets are matched
    free(stack->array);
    free(stack);
    return result;
}

int main() {
    // Test the isValid function
    char testString1[] = "()";
    char testString2[] = "()[]{}";
    char testString3[] = "(]";
    char testString4[] = "([)]";
    char testString5[] = "{[]}";

    printf("Test String 1: %s\n", isValid(testString1) ? "Valid" : "Invalid");
    printf("Test String 2: %s\n", isValid(testString2) ? "Valid" : "Invalid");
    printf("Test String 3: %s\n", isValid(testString3) ? "Valid" : "Invalid");
    printf("Test String 4: %s\n", isValid(testString4) ? "Valid" : "Invalid");
    printf("Test String 5: %s\n", isValid(testString5) ? "Valid" : "Invalid");

    return 0;
}

