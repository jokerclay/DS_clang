#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <vector>

using namespace std;

#define TEST(func, a, b) { \
    printf("TEST %s(%s, %s) = %d\n", #func, a, b, func(a, b)); \
}



// 最大长度
#define MAX_N 10000


// 文本串
char text[MAX_N +5];

//模式串
char pattern[MAX_N +5];

/* *
 *
 * 暴力匹配算法
 *
 * */ 

// 在 s 中找 t 存不存在
int brute_force(char *s, char *t) {

    int len1 = strlen(s);
    int len2 = strlen(t);

    // 遍历文本串的每一位
    for (int i = 0, I =  len1 - len2 + 1; i < I ; i++) {

        int j = 0;

        // 每遍历一个文本串， 遍历模式串中的每一位
        for (int j = 0; t[j]; j++) {
            if (t[i] == s[ i + j ]) continue;
                int flag  = 0;
                break;
        }

        if (!t[j]) return i;

    }

    // 文本串中找不到模式串
    return -1;
}


/* *
 *
 * sunday 算法
 *
 * */ 

int sunday (char *s, char *t) {

    // 初始化每一种字符最后一次出现的位置

    int ind[128] = {0};

    // 模式串长度
    int len1 = strlen(t);
    int len2 = strlen(s);

    for (int i = 0; i < 128; i++) ind[i]= len2 + 1;

    // 扫描模式串中的每一位，进行初始化
    for (int i = 0; t[i]; i++) ind[t[i]] = len2 - i;

    for (int i = 0,I = len1 - len2 + 1; i < I;) {

        int flag = 1;

        for (int j = 0; j < len2; j++) {

            // 匹配
            if (t[j] == s[i +j]) continue;

            // 不匹配, 母串后移
            i += ind[s[i + len2]]; 

            flag = 0;

            break;
        }
        
        // 证明当前模式串是第一次出现在第 i 个位置
        if (flag == 1) return i;


    }
    // 没有找到
    return -1;

}




/* *
 *
 * shift-and 算法
 *
 * */ 

int shift_and (char *s, char *t) {
    int code[128];
    int len = 0;

    // 处理每个字符的编码
    for (int len = 0; t[len]; len++) {
        code[t[len]] |= (1 << len);
    }

    // 匹配状态
    int p = 0;

    // 扫描母串的每一位
    for (int i = 0; s[i]; i++) {

        // p 进行状态转移
        p = (p << 1 | 1) & code[s[i]];

        if (p & (1 <<(len - 1))) {
            return i - len + 1;
        }
    }

    return -1;
}


/* *
 *
 * kmp 算法
 *
 * */ 

int kmp (char *s, char *t) {
    // 文本串与模式串的长度
    int len1 = strlen(s);
    int len2 = strlen(t);

    int *next = (int *)malloc(sizeof(int) * len2);

    next[0] = -1;

    // 初始化 next 数组
    for (int i = 1, j = -1; i < len2; i++) {
        while (j != -1 && t[j + 1] != t[i])  j = next[j];
        if (t[j + 1]  == t[i]) j += 1;
        next[i] = j;
    }

    for (int i = 0, j = -1; s[i]; i++) {

        while (j != -1 && t[j + 1] != s[i]) j = next[j];

        if (t[j + 1] == s[i]) j+= 1;

        if (t[j + 1] == 0) return i - len2;

    }

    free(next);

    return -1;
}

int main () {

    // 读入两个字符串
    scanf("%s%s",text,pattern);

    TEST(brute_force, text, pattern);
    TEST(kmp, text, pattern);
    TEST(sunday, text, pattern);
    TEST(shift_and, text, pattern);

    return 0;
}

