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






















