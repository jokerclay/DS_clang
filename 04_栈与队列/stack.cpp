#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// *********************************************
// 栈的结构定义
// *********************************************
typedef struct stack {
    // 连续的存储区
    int *data;

    // 栈顶指针,栈的大小
    int top, size;
} stack;


// *********************************************
// 栈的初始化
// *********************************************
stack *init (int n) {
    stack *s = (stack *)malloc(sizeof(stack));
    s->data = (int *)malloc(sizeof(int) * n);
    s->size = n;
    s->top  = -1;
    return s;
}

// *********************************************
// 栈的清空操作
// *********************************************
void clear(stack *s) {
    // 如果栈地址为空
    if (s == NULL) return;
    // 否则先销毁数据区，再销毁栈本身的存储空间
    free(s->data);
    free(s);
    return ;
}


// *********************************************
// 栈的判空操作
// *********************************************
int empty(stack *s) {
    return s->top == -1;
}

// *********************************************
// 查看栈顶元素操作
// *********************************************

int top (stack *s) {
    if (empty(s)) return 0;
    return s->data[s->top];
}

// *********************************************
// 入栈操作
// *********************************************
int push (stack *s, int value) {
    if (s == NULL) return 0;
    if (s->top + 1 == s->size) return 0;
    s->top += 1;
    s->data[s->top] = value;
    return 1;
}

// *********************************************
// 出栈操作
// *********************************************
int pop (stack *s) {
    if (s == NULL) return 0;
    if (empty(s)) return 0;
    s->top -= 1;
    return 1;
}

// *********************************************
// 输出栈中的所有元素
// *********************************************

void output(stack *s) {
    printf("stack(%d) = [",s->top+1);
    for (int i = s->top; i >= 0; i--) {
        printf(" %d",s->data[i]);
    }
    printf("]\n");
    return ;
}


int main () {
    #define MAX_OP 20
    srand(time(0));
    stack *s = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++ ) {

        int op = rand() % 2, value = rand() % 100;

        switch (op) {
            case 0: {
                 printf("push %d to stack = %d\n",value, push(s,value));
                } break;
            case 1: {
                 printf("pop %d from stack = %d\n",top(s), pop(s));
                } break;
        }

        output(s);
        printf("\n");

    }

    return 0;
}

