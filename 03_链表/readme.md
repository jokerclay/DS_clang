# 链表
## 什么是内存内部，什么是程序内部 ？
**程序内部:**
在程序中定义 `a` `b` `c` `*p`, 程序中定义的变量，是程序内部的东西
**内存内部:**
链表结构 在内存中开辟若干个节点，这些节点有 相关的指向关系



```
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// 数据结构 = 数据定义 + 数据操作

// 链表的结构定义

// *********************************************
// 链表的节点结构
// *********************************************
typedef struct ListNode {
    int data;                   // 数据域
    struct ListNode *next;      // 指向下一个节点的指针域
} ListNode;
    
// *********************************************
// 链表的结构
// *********************************************
typedef struct ListList {
//    ListNode *head;          // 指向 ListNode 的指针,代表链表的头节点
    ListNode head;             // 虚拟头节点
    int length;                // 链表的总长度
}ListList  ;

// *********************************************
// 链表的初始化
// *********************************************

// 1. 初始化节点
ListNode *init_listnode(int value) {
    ListNode *p = (ListNode *)malloc(sizeof(ListNode));     // 传出链表节点的地址
    p->data = value;
    p->next = NULL;
    return p;
}
// 2. 初始化链表总结构
ListList *init_linklist() {
    ListList *l = (ListList *)malloc(sizeof(ListList));
    l->head.next = NULL;     // 虚拟头结点的下一位指向空,虚拟头节点的下一位才是第 0 位
    l->length = 0;
    return l;
}

// *********************************************
// 链表的销毁
// *********************************************

// 1. 销毁节点
void clear_listnode(ListNode *node) {
    if (node == NULL) return;
    free(node);
    // 如果 节点的数据域也 malloc 出来了
    // 先销毁数据域，再销毁节点
    return ;

}

// 2. 销毁整个链表
void clear_linklist (ListList *l) {
    if (l == NULL) return ;
    // 不为空的话,顺着链表销毁每一个节点
    ListNode *p = l->head.next, *q;
    while (p) {
        q = p-> next;
        clear_listnode(p);
        p = q;
    }
    free(l);
    return ;
}


// *********************************************
// 链表的插入操作
// *********************************************
int insert (ListList *l, int index,int value ) {    // 插入哪个链表哪个位置插入什么值
    // 1. 合法性判断
    // 无链表 
    if (l == NULL) return 0;
    // 插入位置不合法
    if (index < 0 || index > l->length) return 0;
    // 2. 插入
    ListNode *p = &(l->head), *node = init_listnode(value);
    while (index--) {
        p = p->next;
    }
    node->next = p->next;
    p->next = node;
    l->length += 1;
    return 1;

}


// *********************************************
// 链表删除操作
// *********************************************
int erase(ListList *l, int index) {
    if (l == NULL) return 0;
    if (index < 0 || index >= l->length) return 0;
    ListNode *p = &(l->head), *q;
    while (index--) {
        p = p->next;
    }
    q = p->next->next;
    clear_listnode(p->next);
    p->next = q;
    l->length -= 1;
    return 1;
}


// *********************************************
// 链表输出操作
// *********************************************
void output(ListList *l) {
    printf("LinkList(%d) : ",l->length);
    for (ListNode *p = l->head.next; p; p = p->next) {
        printf("%d -> ",p->data);
    }
    printf("NULL\n");
    return ;
}



#define MAX_OP 30

int main() {
    srand(time(0));
    ListList *l = init_linklist();
    for (int i = 0; i < MAX_OP; i++) {
        int op = rand() % 3;
        int index = rand() % (l->length + 1);
        int value = rand() % 100;
        switch (op){
            case 0:
            case 1: {
                printf("insert %d at %d to ListList = %d\n",
                        value,index,insert(l,index,value));
            } break;
            case 2: {
                printf("erase item at %d from ListList = %d\n",
                        index,erase(l,index));
            } break;
        };

        output(l);
        printf("\n");
    
    }

    clear_linklist(l);
    return 0;
}

```

