#include <stdio.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// *********************************************
// 二叉树的结构定义
// *********************************************

// 封装节点
typedef struct Node {
    int value;                          // 数据域
    struct Node *lchild, *rchild;       // 左孩子，右孩子
} Node;


// 封装树
typedef struct Tree {

    Node *root;     // 根节点
    int n;          // 二叉树中一共有多少个节点

} Tree;


// *********************************************
// 二叉树节点的初始化
// *********************************************
Node *getNewNode(int value) {

    Node *p = (Node *)malloc(sizeof(Node));
    p->value = value;
    p->lchild = rchild = NULL;
    return p;
}


// *********************************************
// insert 操作
// *********************************************
// 排序二叉树 -> 平衡二叉排序树  
// 排序二叉树: 如果插入的值比根节点小，向左子树中插入，否则向右子树中插入

Node *insertNode(Node *node, int value) {
    if (root == NULL) getNewNode(value);
    if (root->value = value) return root;
    else root->rchild = insertNode(root->rchild, value);
    return root;
}

void insert(Tree *tree, int value) {
    tree->root = insertNode(tree->node, value);
    return ;
}

// *********************************************
// 二叉树形结构的初始化
// *********************************************
Tree getNewTree() {

    Tree *tree =  (Tree *)malloc(sizeof(Tree));     // 开辟树的内存空间
    tree->n = 0;                                    // 树的节点数为 0
    tree->root = NULL;                              // 树的节地址初始化为 NULL

    return tree;
}

// *********************************************
// 二叉树形结构和节点的销毁
// *********************************************

// 清除节点
void clearNode(Node *node) {

    if (node == NULL) return ;
    clearNode(node->lchild);
    clearNode(node->rchild);
    free(node);

}

// 清除树
void clearTree(Tree *tree) {
    clearNode(tree->root);
    free(tree);
    return ;
}

// *********************************************
// 二叉树形转成广义表输出
// *********************************************
void outputNode(Node *root) {
    if (root == NULL) return ;
    printf("%d",root->value);
    // 左子树和右子树都为 NULL
    if (root->lchild == NULL && root->rchild == NULL) return ;
    printf("(");
    outputNode(root->lchild);
    printf(",");
    outputNode(root->rchild);
    printf(")");
    printf("\n");
}


void output(Tree *tree) {
    printf("tree (%d) = ", tree->n);
    outputNode(tree->root);
    return ;
}


// *********************************************
// 主函数
// *********************************************

int main () {
    srand(time(0));
    Tree *tree = getNewTree();
    for (int i = 0; i < 0; i++) {
        int value = rand() % 100;
        insert(tree, value);
        output(tree);
    }

    return 0;
}



