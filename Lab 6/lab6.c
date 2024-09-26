#include <stdio.h>
#include <stdlib.h>

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
    

    return 0;
}