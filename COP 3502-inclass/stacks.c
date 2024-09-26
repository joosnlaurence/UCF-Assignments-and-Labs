#include <stdio.h>
#include <stdlib.h>
// Stack operations
// push, pop, isempty, isfull, peek

// Array implementation of stack
typedef struct stack{
    int maxSize, top;
    char* stack;
}stack;

stack* create_stack(int maxSize){
    stack* s = (stack*)malloc(sizeof(stack));
    s->maxSize = maxSize;
    s->top = -1;
    s->stack = (char*)malloc(sizeof(char)*maxSize);

    return s;
}

int isempty(stack* s){
    return s->top == -1;
}
int isfull(stack* s){
    return s->top >= s->maxSize-1;
}

int push(stack* s, char ch){
    if(!isfull(s)){
        s->stack[++s->top] = ch;
        return 1;
    }
    else{
        printf("\nStack is full\n");
        return 0;
    }
}
char pop(stack* s){
    if(isempty(s)){
        printf("\nStack is empty\n");
        return 0;
    }
    return s->stack[s->top--];        
}
char peek(const stack* s){
    return s->stack[s->top];
}

void display_stack(const stack* s){
    printf("Stack: ");
    for(int i = 0; i < s->top+1; i++){
        printf("%c ", s->stack[i]);
    }
    puts("");
}

void free_mem(stack* st){
    free(st->stack);
    free(st);
}


int main(){
    printf("Enter the max size of the stack you want to create: ");
    int maxSize;
    scanf("%d", &maxSize);
    printf("Creating a stack with max size of %d...\n\n", maxSize);
    stack* st = create_stack(maxSize);

    while(1){
        int ch;
        printf("0. exit 1. push 2. pop 3. isfull? 4. isempty? 5. peek 6. display: ");
        scanf(" %d", &ch);
        switch(ch){
            case 0:
                printf("Exiting...\n");
                return 0;
                break;
            case 1: 
                char ele;
                printf("Enter character to push: ");
                scanf(" %c", &ele);
                push(st, ele);
                display_stack(st);
                break;
            case 2:
                char c = pop(st);
                if(c)
                    printf("Popping %c...\n", c);
                display_stack(st);
                break;
            case 3:
                printf(isfull(st) ? "True\n" : "False\n");
                break;
            case 4:
                printf(isempty(st) ? "True\n" : "False\n");
                break;
            case 5:
                printf("Top char on stack is %c\n", peek(st));
                break;
            case 6:
                display_stack(st);
                break;
            default:
                printf("Invalid option...\n");
                break;                
        }
    }

    free_mem(st);
    return 0;
}