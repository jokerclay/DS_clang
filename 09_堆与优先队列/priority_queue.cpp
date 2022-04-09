/*
 * 优先队列
 */ 

#define MX_OP 10


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define swap(a, b) { \
    __typeof(a) __temp = a; \
    a = b, b = __temp;  \
}

typedef struct priority_queue {

    int *data;                      //  一片连续存储区域
    int cnt,size;                   //  cnt 当前的优先队列中存储了多少个元素
                                    //  size 优先队列的大小
} priority_queue;

/*
 * init 操作
 */ 

// 初始化一个最多能存储 n 个元素的优先队列
priority_queue *init(int n) { 

    priority_queue *q  = (priority_queue *)malloc(sizeof(priority_queue));

    // 数组下从 1 开始比较方便,想存储 n 个元素就要 开辟 n + 1 个空间
    q->data  = (int *)malloc(sizeof(int) *(n + 1));

    q->cnt = 0;

    q->size = n;

    return q;
}

/*
 * clear 操作
 */ 

void clear(priority_queue *q) {
    if (q == NULL) return ;
    free(q -> data);
    free(q);
    return ;
}


/*
 * 对外操作 
 */ 

int empty(priority_queue *q) {
    return q->cnt == 0;
}

int top(priority_queue *q) {
    return q->data[1];
}

int push(priority_queue *q, int val)  {
    // 判断队列是否满了
    if (q -> cnt == q -> size) return 0;
    q->cnt += 1;

    // 1. 把元素放到整个队列的末尾
    q->data[q->cnt]  = val;

    int ind = q->cnt;
    
    // 2. 向前调整
    // 当前节点有父节点，当前元素大于父元素
    while (ind >> 1 && q->data[ind] > q->data[ind >> 1]) {

        //  与父节点交换
         swap(q->data[ind], q->data[ind >> 1 ]);

         // index 指向父节点
         ind >>= 1;
    }
    
    return 1;
}

int pop(priority_queue *q)  {
    if (empty(q)) return 0;

    // 将最后一个元素放到前面
    q->data[1] = q->data[q->cnt--];

    // 用 index 指向待调整的元素
    int ind = 1;
    while ((ind << 1) <= q->cnt) {
        int temp = ind ,l  = ind << 1, r = ind << 1 | 1;
        if (q->data[l] > q->data[temp]) temp = l;
        if (r <= q->cnt && q->data[r] > q->data[temp]) temp  = r;
        if (temp ==  ind) break;

        swap(q->data[ind], q->data[temp]);

        ind  = temp; 
    }

    return 1;

}


int main() {
    srand(time(0));

    priority_queue *q  = init(MX_OP);


    printf("\n插入队列的数是随机的:\n");


    for (int i = 0; i < MX_OP; i++) {
        int val =  rand() % 100;
        push(q, val);
        printf("Inserting\t%d\tto the queuen...\n", val);
    }
    printf("Done!\n");

    printf("\n每次弹出队列的数是全局的最大值(全局优先级最高的值):\n");

    for (int i = 0; i < MX_OP; i++) {
        printf("%d ", top(q));
        pop(q);
    }

    return 0;
}

