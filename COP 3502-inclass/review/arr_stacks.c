#include <stdio.h>
#include <string.h>
#define MAX_SIZE 100
#define EMPTY -127

typedef struct stack{
    char stack[MAX_SIZE];
    int top;
}stack;

void initStack(stack* st){
    st->top = -1;
}

int isFull(stack* st){
    return st->top >= MAX_SIZE-1;
}
int isEmpty(stack* st){
    return st->top <= -1;
}

void push(stack* st, char ch){
    if(isFull(st)){
        printf("Stack overflow\n");
        return ;
    }
    st->stack[++st->top] = ch;
}
char pop(stack* st){
    if(isEmpty(st))
        return EMPTY;
    return st->stack[st->top--];
}
void display(stack* st){
    printf("Printing the stack: ");
    for(int i = 0; i<=st->top; i++){
        printf("%c ", st->stack[i]);
    }
    printf("\n\n");
}
int isPalindrome(stack* st, char* word){
    int i;
    for(i = 0; i<strlen(word)/2; i++){
        push(st, word[i]);
    }
    if(strlen(word) % 2 == 1)
        i++;
    for(i = i; i<strlen(word); i++){
        if(pop(st) != word[i])
            return 0;
    }
    return 1;
}

int main(){
    stack st;
    st.top = -1;
    char word[100];
    printf("Enter a word: ");
    scanf("%s", word);
    if(isPalindrome(&st, word))
        printf("It's a palindrome\n");
    else
        printf("Not a palindrome\n");


    // while(1){
    //     int ch;
    //     char n;
    //     printf("0-exit. 1-push. 2-pop. 3-display : ");
    //     scanf("%d", &ch);
    //     switch(ch){
    //         case 0:
    //             return 0;
    //         case 1:
    //             printf("Choose a char to push: ");
    //             scanf(" %c", &n);
    //             push(st, n);
    //             display(st);
    //             break;
    //         case 2:
    //             char ele = pop(st);
    //             if(ele == EMPTY)
    //                 printf("Stack is empty...\n");
    //             else
    //                 printf("Popping %c...", ele);
    //             display(st);
    //             break;
    //         case 3:
    //             display(st);
    //             break;
    //         default:
    //             printf("Invalid option\n\n");
    //             break;
    //     }
    // }
    return 0;
}