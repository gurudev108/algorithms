/*
Leetcode Medium 150 Evaluate Reverse Polish Notation

Verified output for below example

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

    return peek(&stack);
}

int main()
{

  char* tokens[] = {"10","6","9","3","+","-11","*","/","*","17","+","5","+"};
  int size = sizeof(tokens)/sizeof(tokens[0]);
  int result = evalRPN(tokens,size);
  printf("Result = %d", result);
  return 0;

}
