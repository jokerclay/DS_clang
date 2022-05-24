# 哈希表

* 哈希表是一种用于查找的数据结构
* 数组时 **数组下标** 到 **值** 之间的映射<br>
    (只要给出数组的下标， 就能在O(1) 的时间复杂度中找到值)

* 如果想找到一个**元素** 能否利用这种性质 ?
(存储的元素是任意类型的, 如果将任意类型的元素， 通过一个方法, 转化成一个整型，改整型对应数组下标)
* 这样就可以利用到数组的性质

```txt

1 --> 5
2 --> 6

```
* 这种通过映射的方法， 查找元素，时间复杂度可以降低到 O(1)

* 关键在于我们能否将任意的元素映射成数组下标

<br>

* 哈希表有一片连续的存储区, 这片连续的存储区就是所谓的 “数组”
* 当我们想将任意元素存储到数组中的时候， 我们要 经过 “哈希函数”

* **哈希函数** 的作用就是**将任意类型元素转换成数字 **
* **冲突处理方法** 

## CODE

```c++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

/*
 * 节点结构定义
 */ 
typedef struct node {
    // 指向字符串的指针
    char *str;

    // 指向下一个节点的下一个节点指针
    struct node *next;

} node;


/*
 * 哈希表结构定义
 */ 
typedef struct hash_table {

    // 存储若干链表头[地址的数组]，哈希表的数据区
    node **data;
    // 哈希表的 size 大小
    int size;

} hash_table;


/*
 * 节点的初始化
 */ 
node *init_node(char *str, node * head) {

    node *p = (node *)malloc(sizeof(node));

    // strdup 将 str 中的内容拷贝一份,并放到新的 str 存储空间地址 中
    p->str = strdup(str);

    p->next = head;

    return p;
}

/*
 * 哈希表的初始化
 */ 

// 参数 n 存储 n 个元素的哈希表
hash_table *init_hash_table(int n) {

    hash_table *h = (hash_table *)malloc(sizeof(hash_table));

    // 将 hash_table 的大小扩大一点
    h->size = n << 1;

    // 初始化哈希表的数据区
    h->data = (node **)calloc(sizeof(node *), h->size);

    return h;
}

/*
 * 节点的清除
 */ 
void clear_node(node *n) {

     if (n == NULL) return ;

     node *p = n, *q;

     // 如果当前节点不为空, 就一直销毁当前节点
     if (p) {
          
         // 记录当前节点的下一个位置
         q = p->next;

         free(p->str);
         free(p);

         // 让当前节点指向下一个节点的位置
         p = q;

     }
     return ;
}

/*
 * 哈希表的清除
 */ 
void clear_hash_table(hash_table *h) {

    if (h == NULL) return ;

    // 遍历哈希表中的每一个位置
    for (int i = 0; i < h->size; ++i) {

        clear_node(h->data[i]);
    }

    free(h);
    return  ;
}


/*
 * BKDRhash, 处理字符串的经典 哈希函数
 */ 
 int BKDRhash(char *str) {

     // 种子，哈希值
     int seed = 31, hash = 0;

     for (int i = 0; str[i]; i++) {
         hash = hash * seed + str[i];
     }

     // 保证返回的是正值
     return hash & 0x7fffffff;
 }


/*
 * 哈希表的插入
 */ 
int insert_hash_table(hash_table *h, char* str) {
    //  获取哈希值
    int hash = BKDRhash(str);

    // 将 哈希值转换成数组下标
    int ind = hash % h->size;

    // 插入  拉链法的头插法
    h->data[ind] = init_node(str, h->data[ind]);

    //
    // 开放定值法(再去找到一个空的位置)
    //

    // 试探次数
    // int times = 0;

    // 创造新的节点
    // node *node = init_node(str, NULL);

    // 如果位置被占用了, 进行坐标的重映射
    // 二次试探法
    // while (h->size(ind)) {
    //  times++;
    //  ind += times * times;
    //  ind %= h->size;
    //  }
    // h->data[ind] = node;

    return 1;
}


/*
 * 哈希表的查找
 */ 
int search(hash_table *h, char *str) {

    // 获取 hash code
    int hash = BKDRhash(str);

    int ind = hash % h->size;

    node *p = h->data[ind];

    while (p && strcmp(p->str, str)) p = p->next;

    // p 非空代表找到了
    return p != NULL;
}

int main(void) {

    int op;
    char str[100];
    hash_table *h = init_hash_table(100);

    while( scanf("%d%s", &op, str) != EOF) {
        switch (op) {
            // op == 0, 插入
            case 0: {
                        printf("insert %s to hash table\n",str);
                        insert_hash_table(h, str);
                    } break;

            // op == 1, 查找
            case 1: {
                        printf("searching %s result = %d\n",str, search(h, str));
                    } break;
        }

    }

    return 0;
}

```

## RES

```txt
./hash_table

0 clay
insert clay to hash table
0 hello
insert hello to hash table
0 zeroMeansInsert
insert zeroMeansInsert to hash table
0 oneMeansSearch
insert oneMeansSearch to hash table 
1 clay
searching clay result = 1
1 hell                              
searching hell result = 0           
1 one                               
searching one result = 0            
1 oneMeansSearch                    
searching oneMeansSearch result = 1 
^C
```




















