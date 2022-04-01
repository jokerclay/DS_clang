#include <stdio.h>
#include <cstdlib>
#include <time.h>

using namespace std;

#define NORMAL 0                                // 正常的边
#define THREAD 1                                // 指向 前驱 / 后继 的边
#define MAX_OPTION 20                           // 随机插入的数字个数


/*
 * 定义节点的数据类型
 *
 */

 typedef struct Node{
     int key;                                   // 数据域
     int ltag, rtag;                            // 标记左子树指针和右子树指针
     struct Node *lchild, *rchild;              // 左子树，右子树

 } Node;

/*
 * 创建新节点
 *
 */

Node *getNewNode(int key) {
    Node *p   = (Node *)malloc(sizeof(Node));   // 开辟 Node 空间
    p->key    = key;                            // 传入的值赋给节点的值
    p->lchild = p->rchild = NULL;               // 左右子树设为NULL
    p->ltag   = p->ltag = NORMAL;               // 0 表示是正常的指针域
    return p;
}

/*
 * 排序二叉树的插入操作
 *
 */

Node *insert(Node *root, int key) {
     // 如果树为空，返回为传入值的节点作为根节点
     if (root == NULL) return getNewNode(key);

     // 如果传进来的值等于原有的值，什么也不做
     if (root->key == key) return root;

     // 如果传进来的值小于原有的值，把常进来的值放到左节点
     if (root->key < key) root->rchild = insert(root->rchild, key);
     
     // 否则向左子树中插入
     else root->lchild = insert(root->lchild, key);

     return root;
}

/*
 * 建立二叉树的线索化
 *
 */

void build_thread(Node *root) {
    if (root == NULL) return ;

    //静态的局部变量记录之前所 处理的子树的最后一个节点
    static Node *pre = NULL;
    // 先建立左子树的线索化
    build_thread(root->lchild);
    if (root->lchild == NULL) {
        root->lchild = pre;
        root->ltag = THREAD;
    }

    if (pre != NULL && pre->rchild == NULL) {
        pre->rchild  = root;
        pre->rtag = THREAD;
    }

    // 更新 pre 节点
    pre = root;
    build_thread(root->rchild);
    return ;
}


/*
 * 递归式的中序遍历
 *
 */

void inorder(Node *root) {
    // 如果树为空，返回
    if (root == NULL) return ;

    // 如果左边是正常的边,中序遍历左子树
    if (root->ltag == NORMAL) inorder(root->lchild);

    printf("%d ", root->key);

    // 如果右边是正常的边, 中序遍历右子树
    if (root->rtag == NORMAL) inorder(root->rchild);

    return;
}

/*
 * 销毁节点
 *
 */

void clearNode(Node *root) {
    // 如果是一颗空树，返回空
    if (root == NULL) return;
    // 如果是正常的边， 不是线索化，则递归的清除
    if (root->lchild == NORMAL) clearNode(root->lchild);
    if (root->rchild == NORMAL) clearNode(root->rchild);

    free(root);
    return;

}

Node *leftMost(Node *p) {
    while(p && p->ltag == NORMAL && p->lchild)  p = p->lchild;
    return p;
}

// 沿着线索化后的二叉树的线索输出二叉树
void output(Node *root) {
    Node *p = leftMost(root);
    while(p) {
        printf("%d ", p->key);
        if (p->rtag == THREAD) {
            p = p->rchild;
        } else {
            p = leftMost(p->rchild);
        }
    }
    printf("\n");
    return ;
}



/*
 * main 
 *
 */

int main() {
    Node *root = NULL;

    srand(time(0));

    for (int i = 0; i < MAX_OPTION; i++) {
        int val = rand() % 100;
        root = insert(root, val);
    }


    inorder(root);
    printf("\n");

    // 沿着线索化后的二叉树的线索输出二叉树
    output(root);

    clearNode(root);
    return 0;
}

