//import
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//define 
#define MAX_STACK_SIZE 100

typedef char element;
typedef struct _StackType{
	element stack[MAX_STACK_SIZE];
	int top;
}StackType;

//function define
int is_empty(StackType *);
int is_full(StackType *);
void init_stack(StackType *);
void push(StackType *s, char ch);
element pop(StackType *);
element peek(StackType *);
int check_match();

//Funtion
void main(){
    char *p = "a[{(i+1)}]";
    printf("%s: ",p);
    if(check_match(p)) printf("Correct Expression\n");
    else printf("Wrong Expression\n");

    return;
}

int is_empty(StackType *s){
	return s->top == -1;
}

int is_full(StackType *s){
	return s->top ==  MAX_STACK_SIZE-1;
}

void init_stack(StackType *s){
	s->top = -1;
}

void push(StackType *s, char ch){
	if(is_full(s)){
		printf("Overflow Error");
		return;
	}
	else s->stack[++(s->top)] = ch;
}

element pop(StackType *s){
	if(is_empty(s)){
		printf("Underflow Error");
		exit(1);
	}
	else return s->stack[(s->top)--];
}

element peek(StackType *s){
    if(is_empty(s)){
        printf("Underflow Error");
        exit(1);
    }
    else return s->stack[s->top];
}

int check_match(const char *in){  //Error = 0, Success = 1;
	StackType s;
	char ch, open_ch;
	int i, length = strlen(in);
	init_stack(&s);

    for(i=0;i<length;i++){
        ch = in[i];
        switch(ch){
            case '(':
            case '{':
            case '[':
                push(&s,ch);
                break;
            case ')':
            case '}':
            case ']':
                if(is_empty(&s)) return 0;
                else{
                    open_ch = pop(&s);
                    if(((ch=='(')&&(open_ch!=')'))||
                        ((ch=='{')&&(open_ch!='}'))||
                        ((ch=='[')&&(open_ch!=']'))){
                        return 0;
                    }
                    break;
                }
        }
    }
    if(!is_empty(&s)) return 0;
    return 1;
	
}