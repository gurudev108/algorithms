/*
Leetcode Medium 150 Evaluate Reverse Polish Notation
You are given an array of strings tokens that represents an arithmetic expression in a Reverse Polish Notation.

Evaluate the expression. Return an integer that represents the value of the expression.

Tip:
Reverse Polish = Postfix notation

Approach:
Stack


Verified output:
Result = 22

Input: tokens = ["10","6","9","3","+","-11","*","/","*","17","+","5","+"]
Output: 22
Explanation: ((10 * (6 / ((9 + 3) * -11))) + 17) + 5
= ((10 * (6 / (12 * -11))) + 17) + 5
= ((10 * (6 / -132)) + 17) + 5
= ((10 * 0) + 17) + 5
= (0 + 17) + 5
= 17 + 5
= 22

*/

#include "stdio.h"
#include "stdlib.h"
#include "string.h"

struct stack {
    int top;
    int array[10000];
};

int is_empty(struct stack* stack) { return stack->top == 0; }
//@TODO-IMP stack->top is 0 indexed so to get top element use top-1.
int peek(struct stack* stack) { return stack->array[stack->top - 1]; }

void push(struct stack* stack, int num) {
    stack->array[stack->top] = num;
    stack->top++;
}

int pop(struct stack* stack) { return stack->array[--stack->top]; }

int evalRPN(char** tokens, int tokensSize) {
    struct stack stack;
    stack.top = 0;

    for (int i = 0; i < tokensSize; i++) {
        //if number (not operand) push on stack
        if (strcmp(tokens[i], "+") != 0 && strcmp(tokens[i], "-") != 0 &&
            strcmp(tokens[i], "*") != 0 && strcmp(tokens[i], "/") != 0) {
            push(&stack, atoi(tokens[i]));
        } else {
            int number2 = pop(&stack);
            int number1 = pop(&stack);
            int result = 0;
            if (strcmp(tokens[i], "+") == 0) {
                result = number1 + number2;
            } else if (strcmp(tokens[i], "-") == 0) {
                result = number1 - number2;
            } else if (strcmp(tokens[i], "*") == 0) {
                result = number1 * number2;
            } else if (strcmp(tokens[i], "/") == 0) {
                result = number1 / number2;
            }
            push(&stack, result);
        }
    }
    printf("\n stack->top at the end = %d", stack.top);
    return peek(&stack);
}

int main()
{

  char* tokens[] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
  int size = sizeof(tokens)/sizeof(tokens[0]);
  int result = evalRPN(tokens,size);
  printf("\nResult = %d", result);
  return 0;

}
