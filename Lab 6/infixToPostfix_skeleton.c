//In this code we will use stack to check the balance of parentheses.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // needed for isdigit


// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.

#define SIZE 100
#define EMPTY -1

struct stack{

    char items[SIZE];
    int top;
};

void initialize(struct stack* stackPtr);
int full(struct stack* stackPtr);
int push(struct stack* stackPtr, char value);
int empty(struct stack* stackPtr);
char pop(struct stack* stackPtr);
int peek(struct stack* stackPtr);
void print_stack(struct stack* stackPtr);

int checkBalance(char exp[]);

int priority(char ch);
int isOperator(char ch);
char *infixToPostfix(char infix[]);
int isParentheses(char ch1);



int main(void) {
    int ch;
    char exp[SIZE], c;

    int valid;

     printf("\nEnter Expression: ");
     scanf("%[^\n]s",exp);

     printf("Your input expression: %s\n", exp);

     valid = checkBalance(exp);

     if(valid)
     {
         char * postfix = infixToPostfix(exp);
         printf("The postfix is: %s\n", postfix);

         free(postfix);
     }





    return 0;
}

int checkBalance(char exp[])
{
    int valid = 1;
    struct stack mine;

    // Set up the stack and push a couple items, then pop one.
    initialize(&mine);

    printf("\nChecking balance...\n");
    
    // loop over stack content to check for balance

    if(pop(&mine)!='I') //it means we still have a parenthesis in the stack
    {
        valid= 0;
        printf("INVALID. You have extra!!!\n");
    }
    if(valid==1)
       printf("VALID\n");

    return valid;
}


void print_stack(struct stack* stackPtr) {
     for(int i=0; i<=stackPtr->top; i++)
        printf("%c-->", stackPtr->items[i]);

     printf("\n");
}


void initialize(struct stack* stackPtr) {
     stackPtr->top = -1;
}

// If the push occurs, 1 is returned. If the
// stack is full and the push can't be done, 0 is
// returned.
int push(struct stack* stackPtr, char value) {

    // Check if the stack is full.
    if (full(stackPtr))
        return 0;

    // Add value to the top of the stack and adjust the value of the top.
    stackPtr->items[stackPtr->top+1] = value;
    (stackPtr->top)++;
    return 1;
}

// Returns true iff the stack pointed to by stackPtr is full.
int full(struct stack* stackPtr) {
    return (stackPtr->top == SIZE - 1);
}

// Returns true iff the stack pointed to by stackPtr is empty.
int empty(struct stack* stackPtr) {
    return (stackPtr->top == -1);
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is popped and returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
char pop(struct stack* stackPtr) {

    char retval;

    // Check the case that the stack is empty.
    if (empty(stackPtr))
        return 'I';

    // Retrieve the item from the top of the stack, adjust the top and return
    // the item.
    retval = stackPtr->items[stackPtr->top];
    (stackPtr->top)--;
    return retval;
}

// Pre-condition: The stack pointed to by stackPtr is NOT empty.
// Post-condition: The value on the top of the stack is returned.
// Note: If the stack pointed to by stackPtr is empty, -1 is returned.
int peek(struct stack* stackPtr) {

    // Take care of the empty case.
    if (empty(stackPtr))
        return EMPTY;

    // Return the desired item.
    return stackPtr->items[stackPtr->top];
}


char *infixToPostfix(char infix[])
{
    struct stack operators;
    initialize(&operators);

    int count = 0; //keep track of postfix index

    //allocating memory for postfix //as we will add space in the postfix, we are allocating double the size of infix
    char *postfix = (char*)malloc((strlen(infix)+1) * 2 * sizeof(char)); 

    //iterating through the infix and evaluating each char
    

    // return the postfix expression 
    return postfix;
}

int priority(char ch)
{
    if(ch == '(' || ch == '[' || ch == '{') return 0;
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch == '/' || ch == '%') return 2;
    if(ch == '^') return 3;

}

int isOperator(char ch)
{
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%')
        return 1;
    return 0;
}

//parentheses check
int isParentheses(char ch1)
{
    if(ch1 == '{' || ch1 == '}' || ch1 == '(' || ch1 == ')' ||ch1 == '[' || ch1 == ']') return 1;
    return 0;
}
