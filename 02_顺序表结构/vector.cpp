#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// *********************************************
// 将 struct Vector 这个数据类型重新命名为 Vector
// *********************************************

// 顺序表的结构定义
typedef struct Vector {
    // 1. 一块连续的存储区
    int *data;

    // 2. size, length
    int size, length;
} Vector;

// *********************************************
// 结构的初始化, 初始化一个存储 n 个元素的顺序表
// *********************************************
Vector *init(int n) {
    //申请一段顺序表的空间
    Vector *vec = (Vector *)malloc(sizeof(Vector));
    vec->data = (int *)malloc(sizeof(int) * n);
    vec->size = n; 
    vec->length = 0;
    return vec;
}

// *********************************************
// 扩容操作
// *********************************************
/*  这样写有bug
int expand(Vector *vec) {
    vec->size *= 2;
    // realloc 失败返回 NULL 会覆盖原来 vec->data 的地址, 造成内存泄漏
    vec->data = (int *)realloc(vec->data,sizeof(int) * vec->size);
    return 1;
}
*/

int expand(Vector *vec) {
    int new_size = vec->size * 2;
    int *p = (int *)realloc(vec->data,sizeof(int) * vec->size);
    // 扩容失败
    if (p == NULL) return 0;
    // 否则
    vec->size = new_size;
    vec->data = p;
    return 1;
}

// *********************************************
// 顺序表的插入操作
// *********************************************
int  insert(Vector *vec, int index, int value) {
    // 1. 合法性判断
    if (vec == NULL ) return 0;      // 不能向空的顺序表中插入
    // 顺序表满了, 进行扩容
    if (vec->length == vec->size) {
        // 如果 扩容操作失败了， return 0
        if (!expand(vec)) return 0;
        printf("expand Vector size to %d success \n", vec->size);
    }     

    if (index < 0 || index > vec->length) return 0; // 插入的位置不在顺序表中

    // 2. 插入位置 index 后面的元素向后移动一位
    // 错误写法,会覆盖后面的元素
    // for(int i = index; i < vec->length; i++) {
    //      vec->data[i + 1 ] = vec->data[i]
    // }

    // 应该倒着遍历 
     for(int i = vec->length -1; i > index; i--) {
          vec->data[i] = vec->data[i-1];
     }

     // 3. 将 value 放到 index 位置
     vec->data[index] = value;
     
     // 4. 顺序表长度 + 1
     vec->length += 1;

     // 5. 插入成功 返回 1
     return 1;
}

// *********************************************
// 顺序表的删除操作
// *********************************************

int erase(Vector *vec, int index) {
    // 1. 判断那种情况不允许删除
    if (vec == NULL) return 0;      // 传入的是空指针
    if (vec->length == 0) return 0;    // 顺序表中没有元素
    if (index < 0 || index >= vec->length);  // 删除的位置越界
    // 2. 循环向前移动一位
    for (int i = index + 1; i < vec->length; i++) {
        vec->data[i -1] = vec->data[i];
    }
    // 3. 改变数据域的值,证明少了一个元素
    vec->length -= 1;

    // 4. return 1 代表删除成功
    return 1;
}

// *********************************************
// 输出顺序表
// *********************************************
void output(Vector *vec) {
    printf("Vector(%d) = [",vec->length);
    for (int i = 0; i < vec->length; i++) {
         if (i != 0) printf(", ");
         printf("%d",vec->data[i]);
    }

    printf("]\n");
    return ;
}

// *********************************************
// 顺序表的销毁操作
// *********************************************
void clear(Vector *vec) {
    // 如果传入的是 空地址，直接返回
    if (vec == NULL) return;
    
    // 否则,先销毁 数据区
    free(vec->data);
    
    // 再销毁vec本身
    free(vec);
    return ;
}


// *********************************************
// main
// *********************************************
int main() {
    #define MAX_OP 20
    srand(time(0));

    // 操作类型，操作位置，操作值
    int op,index,value;

    Vector *vec = init(1);
    for (int i = 0; i < MAX_OP; i++) {
        op = rand() % 4;        //随机产生的数字 模2 得到的结果是 0/1
        index = rand() % (vec->length + 3);
        value = rand() % 100;
        switch (op) {
            // 插入操作
            case 2: 
            case 3: 
            case 0: {
                printf("insert %d at %d to vector \n",value,index);
                insert(vec,index,value);
            } break;
            // 删除操作
            case 1:{
                printf("erase item at %d from vector \n",index);
                erase(vec,index);
            } break;
        }
        output(vec);
    }
    return 0;
}
