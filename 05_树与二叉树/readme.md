# 树

**现实中的树根节点在下面，数据结构中的树根节点在上面**

* 树由两种元素组成
    * 节点: 节点当成**集合**, 根节点-> **全集**， 子节点 -> 全集中的**子集**, 所有子集的并集应该是全集
    * 边  : 边当成**关系**


# 树的定义
**选取某一边，可以看成链表**
**可以根据原有的链表，修改指针域的数量**

```cpp
// 链表
typedef struct Node {
    int data;
    struct Node *next;
} Node, *Tree
```

```cpp
// 三叉树
typedef struct Node {
    int data;
    struct Node *next[3];
} Node, *Tree
```

**树形结构是链表的一个扩展** <br>
**链表可以看成是树形结构的一个特例** <br>
**两者的差别仅仅在指针域上**  <br>


##  树的几个基本概念

1. 从上向下数: **树的深度**。从下向上数：**树的高度**
2. **节点的深度和高度**(不一定相等),<br>
   将某一个节点所在的子树拿出来，节点的高度 从 这个子树的底部向上，高度，从子树的根节点向下数，即为深度

3. **节点的度**: 某一个节点有几个子节点就是几度
4. **节点数量=边数+1**


## 二叉树
* 每个节点的度最多为 2
* 度 为 0 的节点 比度为 2 的节点多一个
* 任何 其他的树都可以转换成 二叉树
    * 如何 n 叉 数 转换成  二叉树? <br>
    **左孩子，右兄弟表示法**
## 二叉树的遍历
**前序遍历** :  **根 左 右** <br>
**中序遍历** :  **左 根 右** <br>
**后序遍历** :  **左 右 根** <br>

## 完全二叉树
**complete binnary tree** <br>
只有右半部分缺失
1. 编号为 i 的子节点(连续编号):  <br>
**左孩子编号： 2 * 1** <br>
**右孩子编号： 2 * 1 + 1** <br>

2. 可以用连续空间存储 (数组)

3. **完全二叉树基于计算(记住计算的规则的)，不基于记录(算法优化，记录式优化成计算式)**

    
## 二叉树 --  广义表
空树 --> ()  <br>
树中只有一个节点 A --> A 或者 A()  <br>
树中只有两个节点 A有一个子节点B --> A(B,) 或者 A(B)  <br>
树中只有三个节点 A有一个子节点B 一个子节点C  --> A(B,C) <br>




### 二叉树的具体实现
```C++

#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define MAX_OPTION 10

/*
 * 二叉树的结构定义
 *
 */

// 封装节点
typedef struct Node {

    int value;                          // 数据域
    struct Node *lchild, *rchild;       // 两个指针域,左孩子，右孩子

} Node;

// 封装树
typedef struct Tree {

    Node *root;     // 根节点
    int n;          // 二叉树中一共有多少个节点

} Tree;


/*
 * 二叉树节点的初始化 (NOTE: 节点是节点， 树是树)
 *
 */

Node *getNewNode(int value) {

    Node *p = (Node *)malloc(sizeof(Node));
    p->value = value;
    p->lchild = p->rchild = NULL;

    return p;
}

/*
 * 二叉树形结构的初始化 (NOTE: 节点是节点， 树是树)
 * 
 */

Tree *getNewTree() {
    Tree *tree =  (Tree *)malloc(sizeof(Tree));     // 开辟树的内存空间
    tree->n = 0;                                    // 树的节点数为 0
    tree->root = NULL;                              // 树的节地址初始化为 NULL

    return tree;
}

/*
 * 二叉树形结构和节点的销毁
 *
 */

// 清除节点
void clearNode(Node *node) {

    if (node == NULL) return;       // 节点本来就是空的，直接返回
    clearNode(node->lchild);        // 递归清除左子树
    clearNode(node->rchild);        // 递归清除右子树
    free(node);                     // 清除传入的节点
    return ;                        // 返回空

}

// 清除树
void clearTree(Tree *tree) {
    clearNode(tree->root);          // 清除树的根节点
    free(tree);                     // 清除树
    return ;
}


/*
 * 二叉树形转成广义表输出
 *
 */

// 打印节点
void outputNode(Node *root) {

    // 空树返回空
    if (root == NULL) return;
    // 打印根节点的值
    printf("%d ",root->value);

    // 左子树和右子树都为 NULL，不用输出子树信息
    if (root->lchild == NULL && root->rchild == NULL) return;

    printf("[");
    // 递归的打印左子树
    outputNode(root->lchild);
    printf(",");
    // 递归的打印右子树
    outputNode(root->rchild);
    printf("]");
}

// 打印树
void outputTree(Tree *tree) {
    printf("tree (%d) = ", tree->n);
    outputNode(tree->root);
    printf("\n");
    return ;
}

/*
 * insert 操作
 *
 */

// 排序二叉树 -> 平衡二叉排序树  
// 排序二叉树: 如果插入的值比根节点小，向左子树中插入，否则向右子树中插入

Node *insertNode(Node *root, int value, int *ret) {

    if (root == NULL) {
        *ret = 1;
        return getNewNode(value);
    }

    if (root->value == value) return root;

    if (root->value > value) root->lchild = insertNode(root->lchild, value, ret);
    else root->rchild = insertNode(root->rchild, value, ret);
    return root;
}

void insert(Tree *tree, int value) {
    int flag = 0;
    tree->root = insertNode(tree->root, value, &flag);
    tree->n += flag;
    return ;
}

/*
 * 前序遍历
 *
 */

void preorderNode(Node *node) {
    if (node == NULL) return;
    printf("%d ", node->value);
    preorderNode(node->lchild);
    preorderNode(node->rchild);
    return ;
}

void preorder(Tree *tree) {
     printf("preorder   : ");
     preorderNode(tree->root);
     printf("\n");
     return ;
 }
 
 
/*
 * 中序遍历
 *
 */

void inorderNode(Node *node) {
    if (node == NULL) return;
    inorderNode(node->lchild);
    printf("%d ", node->value);
    inorderNode(node->rchild);
    return ;
}

void inorder(Tree *tree) {
     printf("inorder    : ");
     inorderNode(tree->root);
     printf("\n");
     return ;
 }


/*
 * 后序遍历
 *
 */

void postorderNode(Node *node) {
    if (node == NULL) return;
    postorderNode(node->lchild);
    postorderNode(node->rchild);
    printf("%d ", node->value);
    return ;
}

void postorder(Tree *tree) {
     printf("post order : ");
     postorderNode(tree->root);
     printf("\n");
     return ;
 }



/*
 * 主函数
 *
 */
int main () {
    // 获取根据时间不同的随机数种子
    srand(time(0));

    // 建立一颗二叉树
    Tree *tree = getNewTree();

    // 向二叉树中随机插入 10 个值，每插入一个就打印一次
    for (int i = 0; i < MAX_OPTION; i++) {
        int value = rand() % 100;
        insert(tree, value);
        outputTree(tree);
    }
    printf("\n");

    // 前序遍历
    preorder(tree);

    // 中序遍历
    inorder(tree);

    // 后序遍历
    postorder(tree);

    // 清空树
    clearTree(tree);

    return 0;
}




```




