#include <stdio.h>
#include <stdlib.h>

#define MAZE_SIZE 6
#define MAX_STACK_SIZE MAZE_SIZE*MAZE_SIZE
#define MICE 'e'
#define OUT 'x'
#define WALL '1'
#define ROAD '0'
#define PASSED '.'

typedef struct _element{
    int x;
    int y;
}element;
typedef struct _StackType{
    element stack[MAX_STACK_SIZE];
    int top;
}StackType;

void init_stack(StackType *);
int is_empty(StackType *);
int is_full(StackType *);
void push(StackType *, element);
element pop(StackType *);
element peek(StackType *);
void push_loc(StackType *,int ,int);
void print_maze(char maze[MAZE_SIZE][MAZE_SIZE]);

char maze[MAZE_SIZE][MAZE_SIZE] = {
    {'1','1','1','1','1','1'},  //0
    {'e','0','0','0','0','1'},  //1
    {'1','0','1','0','1','1'},  //2
    {'1','1','1','0','1','1'},  //3
    {'x','0','0','0','0','1'},  //4
    {'1','1','1','1','1','1'}   //5  y
    //0   1   2   3   4   5   x
};

element here = {0,1};
element entrance = {0,1};

int main(){
    int x,y;
    StackType s;
    init_stack(&s);
    here = entrance;
    while(maze[here.x][here.y]!=OUT){
        x = here.x;
        y = here.y;
        maze[x][y] = PASSED;
        print_maze(maze);
        push_loc(&s,x,y+1);
        push_loc(&s,x,y-1);
        push_loc(&s,x+1,y);
        push_loc(&s,x-1,y);
        if(is_empty(&s)){
            printf("Failure\n");
            return -1;
        }
        else{
            here = pop(&s); //갈 수 있는 곳으로 좌표이동
        }

    }
    printf("Success\n");
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

void push(StackType *s, element ch){
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

void push_loc(StackType *s,int x,int y){
    if(x<0 || y<0) return;
    if(maze[x][y]!= WALL && maze[x][y] != PASSED){
        element tmp;
        tmp.x = x;
        tmp.y = y;
        push(s,tmp);
    }
}

void print_maze(char maze[MAZE_SIZE][MAZE_SIZE]){
    int i,k;
    printf("\n");
    for(i=0;i<MAZE_SIZE;i++){
        for(k=0;k<MAZE_SIZE;k++){
            printf("%c ",maze[i][k]);
        }
        printf("\n");
    }
}