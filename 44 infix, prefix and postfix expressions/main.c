#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX][MAX];
} Stack;

// Function to initialize stack
void initStack(Stack *s) {
    s->top = -1;
}

// Function to check if the stack is empty
int isEmpty(Stack *s) {
    return s->top == -1;
}

// Function to check if the stack is full
int isFull(Stack *s) {
    return s->top == MAX - 1;
}

// Function to push an element onto the stack
void push(Stack *s, char *value) {
    if (isFull(s)) {
        printf("Stack overflow\n");
        return;
    }
    strcpy(s->items[++s->top], value);
}

// Function to pop an element from the stack
char* pop(Stack *s) {
    if (isEmpty(s)) {
        printf("Stack underflow\n");
        return NULL;
    }
    return s->items[s->top--];
}

// Function to get the precedence of an operator
int precedence(char op) {
    switch (op) {
        case '+':
        case '-': return 1;
        case '*':
        case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}

// Function to check if a character is an operator
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^';
}

// Function to convert infix expression to postfix expression
void infixToPostfix(char *infix, char *postfix) {
    Stack stack;
    initStack(&stack);
    int i, j = 0;
    for (i = 0; infix[i] != '\0'; i++) {
        if (isdigit(infix[i]) || isalpha(infix[i])) {
            postfix[j++] = infix[i];
        } else if (infix[i] == '(') {
            push(&stack, &infix[i]);
        } else if (infix[i] == ')') {
            while (!isEmpty(&stack) && stack.items[stack.top][0] != '(') {
                postfix[j++] = pop(&stack)[0];
            }
            pop(&stack); // pop '('
        } else if (isOperator(infix[i])) {
            while (!isEmpty(&stack) && precedence(stack.items[stack.top][0]) >= precedence(infix[i])) {
                postfix[j++] = pop(&stack)[0];
            }
            push(&stack, &infix[i]);
        }
    }
    while (!isEmpty(&stack)) {
        postfix[j++] = pop(&stack)[0];
    }
    postfix[j] = '\0';
}

// Function to convert infix expression to prefix expression
void infixToPrefix(char *infix, char *prefix) {
    Stack stack;
    initStack(&stack);
    int i, j = 0;
    int len = strlen(infix);
    char *reversedInfix = (char *)malloc(len + 1);
    char *reversedPrefix = (char *)malloc(len + 1);

    // Reverse the infix expression
    for (i = 0; i < len; i++) {
        if (infix[len - i - 1] == '(') {
            reversedInfix[i] = ')';
        } else if (infix[len - i - 1] == ')') {
            reversedInfix[i] = '(';
        } else {
            reversedInfix[i] = infix[len - i - 1];
        }
    }
    reversedInfix[len] = '\0';

    infixToPostfix(reversedInfix, reversedPrefix);

    // Reverse the result to get prefix
    for (i = 0; i < len; i++) {
        prefix[i] = reversedPrefix[len - i - 1];
    }
    prefix[len] = '\0';

    free(reversedInfix);
    free(reversedPrefix);
}

// Function to convert postfix expression to infix expression
void postfixToInfix(char *postfix, char *infix) {
    Stack stack;
    initStack(&stack);
    char operand1[MAX], operand2[MAX], expr[MAX];
    int i;

    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i]) || isalpha(postfix[i])) {
            char operand[2] = {postfix[i], '\0'};
            push(&stack, operand);
        } else if (isOperator(postfix[i])) {
            strcpy(operand2, pop(&stack));
            strcpy(operand1, pop(&stack));
            snprintf(expr, MAX, "(%s%c%s)", operand1, postfix[i], operand2);
            push(&stack, expr);
        }
    }
    strcpy(infix, pop(&stack));
}

// Function to convert prefix expression to infix expression
void prefixToInfix(char *prefix, char *infix) {
    Stack stack;
    initStack(&stack);
    char operand1[MAX], operand2[MAX], expr[MAX];
    int i, len = strlen(prefix);

    for (i = len - 1; i >= 0; i--) {
        if (isdigit(prefix[i]) || isalpha(prefix[i])) {
            char operand[2] = {prefix[i], '\0'};
            push(&stack, operand);
        } else if (isOperator(prefix[i])) {
            strcpy(operand1, pop(&stack));
            strcpy(operand2, pop(&stack));
            snprintf(expr, MAX, "(%s%c%s)", operand1, prefix[i], operand2);
            push(&stack, expr);
        }
    }
    strcpy(infix, pop(&stack));
}

// Function to evaluate a postfix expression
int evaluatePostfix(char *postfix) {
    Stack stack;
    initStack(&stack);
    int i, op1, op2;
    for (i = 0; postfix[i] != '\0'; i++) {
        if (isdigit(postfix[i])) {
            push(&stack, &postfix[i]);
        } else if (isOperator(postfix[i])) {
            op2 = pop(&stack)[0] - '0';
            op1 = pop(&stack)[0] - '0';
            int result;
            switch (postfix[i]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
            }
            char resStr[2] = {result + '0', '\0'};
            push(&stack, resStr);
        }
    }
    return pop(&stack)[0] - '0';
}

// Function to evaluate a prefix expression
int evaluatePrefix(char *prefix) {
    Stack stack;
    initStack(&stack);
    int i, op1, op2;
    int len = strlen(prefix);
    for (i = len - 1; i >= 0; i--) {
        if (isdigit(prefix[i])) {
            push(&stack, &prefix[i]);
        } else if (isOperator(prefix[i])) {
            op1 = pop(&stack)[0] - '0';
            op2 = pop(&stack)[0] - '0';
            int result;
            switch (prefix[i]) {
                case '+': result = op1 + op2; break;
                case '-': result = op1 - op2; break;
                case '*': result = op1 * op2; break;
                case '/': result = op1 / op2; break;
            }
            char resStr[2] = {result + '0', '\0'};
            push(&stack, resStr);
        }
    }
    return pop(&stack)[0] - '0';
}

int main() {
    char infix[MAX], postfix[MAX], prefix[MAX], convertedInfix[MAX];

    printf("Enter infix expression: ");
    scanf("%s", infix);

    infixToPostfix(infix, postfix);
    infixToPrefix(infix, prefix);

    printf("Infix expression: %s\n", infix);
    printf("Postfix expression: %s\n", postfix);
    printf("Prefix expression: %s\n", prefix);

    printf("Evaluated Postfix expression result: %d\n", evaluatePostfix(postfix));
    printf("Evaluated Prefix expression result: %d\n", evaluatePrefix(prefix));

    postfixToInfix(postfix, convertedInfix);
    printf("Postfix to Infix: %s\n", convertedInfix);

    prefixToInfix(prefix, convertedInfix);
    printf("Prefix to Infix: %s\n", convertedInfix);

    return 0;
}
