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
    s->stack = (char*)malloc(sizeof(char));

    return s;
}

int isempty(stack* s){
    return s->top == -1;
}
int isfull(stack* s){
    return s->top == s->maxSize;
}

void push(stack* s, char ch){
    if(!isfull(s)){
        s->stack[++s->top] = ch;
    }
    else
        printf("\nStack is full\n");
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
    for(int i = 0; i < s->top+1; i++){
        printf("%c ", s->stack[i]);
    }
    puts("");
}


int main(){
    int max_size = 5;
    stack* my_stack = create_stack(max_size);

    for(int i = 0; i<max_size; i++){
        push(my_stack, 'a' + i);
    }
    display_stack(my_stack);
    printf("Popping: %c\n", pop(my_stack));
    printf("Popping: %c\n", pop(my_stack));
    printf("Popping: %c\n", pop(my_stack));
    display_stack(my_stack);
    return 0;
}