#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// *********************************************
// 队列的结构定义
// *********************************************
typedef struct Queue {
    // 一段连续的存储区
    int *data;
    // head. tail
    int head, tail;
    // 整个队列的最大长度
    int length;

    // 当前队列所存储的元素的总数量
    int cnt;
} Queue;

// *********************************************
// 队列初始化
// *********************************************

Queue *init(int n) {
    Queue *q = (Queue *)malloc(sizeof(Queue));
    q->data = (int *)malloc(sizeof(int) *n);

//    q->head = q->tail = 0;
    q->head = q->tail = q->cnt = 0;

    q->length = n;
    return q;
}

// *********************************************
// 队列销毁
// *********************************************
void clear(Queue *q) {
    if (q == NULL) return ;
    free(q->data);
    free(q);
    return ;
}

// *********************************************
// 队列判空操作
// *********************************************
int empty(Queue *q) {
    // 判断头指针是否等于尾指针
//    return q->head == q->tail;
    // 队列中为 0
    return q->cnt == 0;
}

// *********************************************
// 查看队首元素
// *********************************************
int front (Queue *q) {
    return q->data[q->head];
}


// *********************************************
// 入队操作
// *********************************************
int push(Queue *q, int value) {
    // 判断指针是否为空
    if (q == NULL) return 0;

    // 判断队列是否满了
    if (q->cnt == q->length) return 0;

    // 入队操作
    q->data[q->tail++] = value;
    if (q->tail == q->length) q->tail -= q->length;
    q->cnt+= 1;
    return 1;
}

// *********************************************
// 出队操作
// *********************************************
int pop(Queue *q) {
    if (q == NULL) return 0;
    if (empty(q)) return 0;
    q->head++;
    if (q->head == q->length) q->head -= q->length;
    q->cnt -= 1;
    return 1;
}

// *********************************************
// 输出队列操作
// *********************************************
void output(Queue *q) {
    printf("queue = [");
    for (int i = q->head, j = 0; j < q->cnt; j++) {
        int index = (i + j) % q->length;
        printf(" %d ",q->data[index]);
    }
    printf("]\n");
}

int main() {
    srand(time(0));
    #define MAX_OP 20

    Queue *q = init(MAX_OP);
    for (int i = 0; i < MAX_OP; i++) {
        int value = rand() % 100, op = rand() % 2;
        switch(op) {
            case 0:{
                printf("push %d to  queue = %d \n",value,push(q,value));
            } break;
            case 1:{
                printf("pop %d from  queue = %d \n",front(q),pop(q));
            } break;

        }
        output(q);
    }
    printf("head: %d, tail: %d, count: %d\n",q->head,q->tail,q->cnt);
    for (int i = 0; i < MAX_OP; i++) {
        int value = rand() % 100;
        printf("push %d to  queue = %d \n",value,push(q,value));
    }

    output(q);
}


