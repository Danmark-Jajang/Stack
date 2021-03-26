#include <stdio.h>
#include <stdlib.h>

#define MAX_STACK_SIZE 100

typedef char element;
typedef struct _StackType{
    element stack[MAX_STACK_SIZE];
    int top;
}StackType;

void init_stack(StackType *);
int is_full(StackType *);
int is_empty(StackType *);
void push(StackType *, char);
char pop(StackType *);
char peek(StackType *);
void infix_to_postfix(char exp[]);
int perc(char ch);

int main(){
    char *s = "(2+3)*4+9*2";
    printf("infix: %s\n",s);
    printf("postfix: ");
    infix_to_postfix(s);
    printf("\n");

    return 0;
}

void init_stack(StackType *s){
    s->top  = -1;
}

int is_full(StackType *s){
    return s->top==MAX_STACK_SIZE-1;
}

int is_empty(StackType *s){
    return s->top == -1;
}

void push(StackType *s, char ch){
    if(is_full(s)){
        printf("Overflow Errer\n");
        exit(1);
    }
    else s->stack[++(s->top)] = ch;
}

char pop(StackType *s){
    if(is_empty(s)){
        printf("Underflow Error\n");
        exit(1);
    }
    else return s->stack[(s->top)--];
}

char peek(StackType *s){
    if(is_empty(s)){
        printf("Underflow Error\n");
        exit(1);
    }
    else return s->stack[s->top];
}

void infix_to_postfix(char exp[]){
    int i=0;
    char ch, top_op;
    int length = strlen(exp);
    StackType s;

    init_stack(&s);
    for(i=0;i<length;i++){
        ch = exp[i];
        switch(ch){
            case '+':
            case '-':
            case '*':
            case '/':
                while((!is_empty(&s))&&(perc(ch)<=perc(peek(&s)))){ //스택이 비어있지 않으면서 스택안의 연산자의 우선순위가 더 높거나 같다면
                    printf("%c",pop(&s)); //스택 안에 있는 우선순위가 더 높거나 먼저나온 연산자를 먼저 출력
                }
                push(&s,ch);
                break;
            case '(':
                push(&s,ch);
                break;
            case ')':
                top_op = pop(&s);
                while(top_op!='('){
                    printf("%c",top_op);
                    top_op = pop(&s);
                }
                break;
            default: //피연산자
                printf("%c",ch);
                break;
        }

    }
    while(!is_empty(&s)){
        printf("%c",pop(&s));
    }
}

int perc(char ch){
    switch(ch){
        case '(':
        case ')':
            return 0;
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
    }
    return -1;
}