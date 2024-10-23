/* COP 3502C Lab 6
This program is written by: Jason Laureano */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h> // needed for isdigit
#include <math.h>


// The array will store the items in the stack, first in
// index 0, then 1, etc. top will represent the index
// to the top element in the stack. If the stack is
// empty top will be -1.undefined reference to `pow

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
int evalPostfix(char postfix[]);



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
        printf("The postfix is: %s\n", postfix);\
        // printf("The expression equals: %d\n", evalPostfix(postfix));

        free(postfix);
    }

    return 0;
}

int checkBalance(char exp[])
{
    int valid = 1;
    struct stack st;

    // Set up the stack and push a couple items, then pop one.
    initialize(&st);

    printf("\nChecking balance...\n");
    
    // loop over stack content to check for balance
    char ch;
    for(int i = 0; i<strlen(exp) && valid; i++){
        if(exp[i] == '[' || exp[i] == '{' || exp[i] == '('){
            if( push(&st, exp[i]) == 0 ){
                printf("Error: Stack overflow - Too many parentheses\n");
                return 0;
            }
        }
        else if(exp[i] == ']' || exp[i] == '}' || exp[i] == ')'){
            ch = pop(&st);
            // For '[' and '{', ch+2 should be ']' or '}'
            // For '(', ch+1 should be ')'
            if( (ch+1 !=  exp[i]) && (ch+2 != exp[i]) ){
                valid = 0;
                ch = exp[i];
            }
        }
    }

    if(valid == 0)
        printf("INVALID for %c!!!\n", ch);
    else if(pop(&st)!='I') //it means we still have a parenthesis in the stack
    {
        valid= 0;
        printf("INVALID. You have extra!!!\n");
    }
    else if(valid==1)
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
    for(int i = 0; i<strlen(infix); i++){
        if(isdigit(infix[i])){
            postfix[count++] = infix[i];
            while(isdigit(infix[i+1])){
                postfix[count++] = infix[i+1];
                i++;
            }
            postfix[count++] = ' ';
        }
        else if(isOperator(infix[i])){
            int infPriority = priority(infix[i]);
            while( !empty(&operators) && infPriority <= priority((char)peek(&operators)) ){
                postfix[count++] = pop(&operators);
                postfix[count++] = ' ';      
            }
            push(&operators, infix[i]);
        }
        else if(isParentheses(infix[i])){
            if( infix[i] != ')' && infix[i] != '}' && infix[i] != ']' ){
                push(&operators, infix[i]);
            }
            else{
                char ch;
                while( !isParentheses(ch = pop(&operators)) ){
                    postfix[count++] = ch;
                    postfix[count++] = ' ';      
                }
            }
        }
    }
    while( !empty(&operators) ){
        postfix[count++] = pop(&operators);;
        postfix[count++] = ' ';      
    }

    // return the postfix expression 
    return postfix;
}

struct intStack{
    int items[SIZE];
    int top;
};

int evalPostfix(char postfix[]){
    struct intStack st;
    st.top = -1;

    for(int i = 0; i<strlen(postfix); i++){
        if(isdigit(postfix[i])){
            int n = postfix[i]-'0';
            while(isdigit(postfix[i+1])){
                n = n*10 + postfix[i+1]-'0';
                i++;
            }
            st.items[++st.top] = n;
        }
        else if(isOperator(postfix[i])){
            int n = st.items[st.top];
            int prev;
            switch(postfix[i]){
                case '*':
                    st.items[--st.top] *= n;
                    break;
                case '+':
                    st.items[--st.top] += n;
                    break;
                case '-':
                    st.items[--st.top] -= n;
                    break;
                case '/': // integer division
                    st.items[--st.top] /= n;
                    break;
                case '^': 
                    prev = st.items[--st.top];
                    for(int i = 0; i<n; i++)
                        st.items[st.top] *= prev;
                    break;
                case '%':
                    st.items[--st.top] %= n;
                    break;
                default: 
                    break;
            }
        }
    }

    return strlen(postfix) != 0 ? st.items[st.top] : -1;
}

int priority(char ch)
{
    if(ch == '(' || ch == '[' || ch == '{') return 0;
    if(ch == '+' || ch == '-') return 1;
    if(ch == '*' || ch == '/' || ch == '%') return 2;
    if(ch == '^') return 3;
    else return -1;
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
