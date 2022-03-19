#include <stdio.h>
#include <stdlib.h>
#include <time.h>

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

    if (root->value > value) root->rchild = insertNode(root->rchild, value, ret);
    else root->lchild = insertNode(root->lchild, value, ret);
    return root;
}

void insert(Tree *tree, int value) {
    int flag = 0;
    tree->root = insertNode(tree->root, value, &flag);
    tree->n += flag;
    return ;
}

// 前序遍历


// void preorder(Tree *tree) {
// 
//     printf("preorder : ");
//     preorder (tree->root);
//     printf("\n");
// }
// 
// 
// void preorderNode(Node *node) {
//     if (node == NULL) return;
//     preorder();
// }
// 
// 
// 
// 中序遍历


// 后序遍历



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
    for (int i = 0; i < 10; i++) {
        int value = rand() % 100;
        insert(tree, value);
        outputTree(tree);
    }

// 前序遍历
//     preorder(tree);

// 中序遍历
//     inorder(tree);

// 后序遍历
//     postorder(tree);

// 清空树
    clearTree(tree);

    return 0;
}

