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
element pop(StackType *);
element peek(StackType *);
int eval(char[]); //계산식

int main(){
    int result;
    char *s = "23+4*92*+";
    printf("Postfix: %s\n",s);
    result = eval(s);
    printf("Result: %d\n",result);

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

element pop(StackType *s){
    if(is_empty(s)){
        printf("Underflow Error\n");
        exit(1);
    }
    else return s->stack[(s->top)--];
}

element peek(StackType *s){
    if(is_empty(s)){
        printf("Underflow Error\n");
        exit(1);
    }
    else return s->stack[s->top];
}

int eval(char exp[]){
    int op1, op2, value, i=0;
    int length = strlen(exp);
    char ch;
    StackType s;

    init_stack(&s);
    for(i=0;i<length;i++){
        ch = exp[i];
        if(ch!='+'&&ch!='-'&&ch!='*'&&ch!='/'){
            value = ch - '0';
            push(&s,value);
        }
        else{
            op2 = pop(&s);
            op1 = pop(&s);
            switch(ch){
                case '+': push(&s,op1+op2); break;
                case '-': push(&s,op1-op2); break;
                case '*': push(&s,op1*op2); break;
                case '/': push(&s,op1/op2); break;
            }
        }
    }
    return pop(&s);
}