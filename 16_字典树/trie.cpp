#include <stdio.h>
#include <stdlib.h>

#define BASE 26
#define BASE_LETTER 'a'

using namespace std;

typedef struct  Node {

    int flag;
    struct Node *next[BASE];

} Node;


// 申请新的节点
Node *getNewNode() {
    Node *p = (Node *)calloc(sizeof(Node), 1);
    return p;
}


// 销毁操作
void clear(Node *root) {
    if (root == NULL) return ;

    for (int i = 0; i <  BASE ; i++ ) {
        clear(root->next[i]);
    }
    free(root);

    return ;
}


inline int code(char ch) {
    return ch - BASE_LETTER;
}

// 插入操作
void insert (Node *root, char *str){

    Node *p = root;

    for (int i = 0; str[i]; i++) {

        if (p->next[code(str[i])] == NULL) p->next[code(str[i])] = getNewNode();

        p = p->next[code(str[i])];

    }
    p->flag = 1;

    return ;
}


void output(Node *root, int k, char *buff) {

    if (root == NULL)  return ;

    if (root->flag) printf("%s\n", buff);

    for (int i = 0; i < BASE; i++) {

        buff[k] =BASE_LETTER + i;

        buff[k+1] = '\0';

        output(root->next[i], k+1, buff);

    }
    return ;

}


// 查询操作
int query(Node *root, char *str) {

    Node *p = root;

    for (int i = 0; str[i]; i++) {

        p = p->next[code(str[i])];

        if (p == NULL ) return 0;

    }

    return p->flag;
}


int main() {

    char str[1000];

    int n;

    Node *root = getNewNode();

    scanf("%d", &n);

    for (int i = 0; i < n; i++) {

        scanf("%s", str);

        insert(root, str);
    }

    output(root, 0, str);
    while (~scanf("%s", str)) {

        printf("query %s, result = %s\n", str, query(root, str) ? "YES" : "NO");

    }

    return 0;
}

