#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX_N 1000
#define swap(a, b) { \
    __typeof(a) temp = a; \
    a = b, b = temp; \
}

// *********************************************
// 节点结构
// *********************************************
typedef struct Node {

    // 字符域
    char ch;

    // 当前节点对应的概率值
    double p;

    // 指针域
    // struct Node *lchild, *rchild;
     struct Node *next[2];      // 开 2 个指针域，next[0], next[1]

} Node;


// *********************************************
// 相关字符以及字符的编码
// *********************************************

typedef struct Code {
    char ch;
    char *str;
} Code;



// *********************************************
// 树形结构， 节点结构包装成树形结构
// *********************************************

typedef struct HaffmanTree {
    // 指向 HaffmanTree 根节点的指针
    Node *root;

    // HaffmanTree 中有多少种字符
    int n;

    // 每种字符的编码
     Code *codes;

} HaffmanTree;

















// *********************************************
// 数据结构
// *********************************************

// 将数据封装成结构体
typedef struct Data {

    // 当前字符
    char ch;

    // 当前节点对应的概率值(频次)
    double p;

} Data;

Data arr[MAX_N + 5];


// *********************************************
// getNewNode 
// *********************************************
Node *getNewNode(Data *obj) {

    Node *p = (Node *)malloc(sizeof(Node));
    p->ch = (obj ? obj->ch : 0);
    p->p =  (obj ? obj->p : 0);
    p->next[0] = p->next[1] = NULL;

    return p;
}


// *********************************************
// getNewTree
// *********************************************
HaffmanTree *getNewTree(int n) {
    HaffmanTree *tree = (HaffmanTree *)malloc(sizeof(HaffmanTree));
    tree->codes = (Code *)malloc(sizeof(Code) * n);
    tree->root  = NULL;
    tree->n = n;
    return tree;
}

// *********************************************
// insert once 
// *********************************************
void insertOnce(Node **arr, int n) {
    for(int j = n;  j >= 1; j--) {
        if(arr[j]->p > arr[j -1]->p) swap(arr[j], arr[j - 1]);
        break;
    }
    return ;
}


// *********************************************
// extractCodes
// *********************************************
int extractCodes(Node *root, Code *arr, int k, int l, char *buff) {
    buff[l] = 0;
    if (root->next[0] == NULL && root->next[1] == NULL) {
        arr[k].ch = root->ch;
        arr[k].str = strdup(buff);

        return 1;
    }
    int delta  = 0;
    buff[l] = '0';
    delta += extractCodes(root->next[0], arr, k + delta, l + 1, buff);
        

    buff[l] = '1';
    delta += extractCodes(root->next[1], arr, k + delta, l + 1, buff);
    
    return delta;
}


// *********************************************
// 建立一棵 HaffmanTree 的方法
// *********************************************

// 返回的是哈夫曼树的地址， 传入的是 n 个字符的 Data
HaffmanTree *build(Data *arr, int n) {

    // 一个存储哈夫曼节点的地址,开出来 n 位
    Node **nodes = (Node **)malloc(sizeof(Node *) * n);

    // 把 n 个字符 变成 HaffmanTree 的节点
    for(int i = 0; i < n; i++) {
        nodes[i] = getNewNode(arr +i );
    }

    // 进行 n -  1 论的合并
    // 将 所有字符出现的频次进行排序(这里使用插入排序) 
    for(int i = 1; i < n; i++) {

        for(int j = i; i >= 1; j--) {
            insertOnce(nodes, i);
        }
    }

    for(int i = n -1; i >= 1; i--) {

        // 新生成的一个节点
        Node *p = getNewNode(NULL);

        p->next[0] = nodes[i];
        p->next[1] = nodes[i-1];

        // 合并得到一个新的节点
        p->p = p->next[0]->p + p->next[1]->p;

        nodes[i-1] = p;

        insertOnce(nodes, i -1);

    }

    // 建立一棵树
    char *buff  = (char *)malloc(sizeof(char) *n);
    HaffmanTree *tree = getNewTree(n);

    tree->root  = nodes[0];

    extractCodes(tree->root, tree->codes, 0, 0, buff);
    free(nodes);
    free(buff);

    return tree;
}


int main() {

    // 先读入若干个字符以及每一个字符可能出现的概率
    int n; 
    
    char str[10];

    scanf("%d",n);
    for(int i = 0; i < n; i++) {
        scanf("%s%lf",str, arr[i].p);
        arr[i].ch = str[0];
    }


    // 建立一颗 具有 n 个字符的 哈夫曼树， arr 表内容 (HaffmanTree)
    HaffmanTree *tree = build(arr, n);
    for (int i = 0; i < tree->n; i++) {
        printf("%c%s\n", tree->codes[i].ch,tree->codes[i].str);

    }

    return 0;

}


