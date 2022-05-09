#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#define MX_OP 10;
#define P(func) { \
    printf("%s = %d\n", #func, func); \
}

/*
 * 一般的二分查找
 *(有序的队列)
 * 123456789 
 */
int binary_search_1(int *num, int n, int x) {

    int head = 0, tail = n - 1, mid; 

    while (head <= tail) {

        mid = (head + tail) >> 1;
        if(num[mid]  == x) return mid;
        if(num[mid]  > x)  tail = mid - 1;
        else head = mid + 1;
    }
    return -1;
}

/*
 *
 * 特殊的二分查找
 * (前面都是 1，后面都是 0， 找最后一个 1)
 * 111111100000000
 *
 */

int binary_search_2(int *num, int n) {
    // 含有虚拟节点
    int head = -1, tail = n -1, mid;
    // 当头尾指针没有重合的时候
    while (head < tail) {
        mid = (head + tail + 1) >> 1;
        if (num[mid] == 1) head = mid;
        else tail = mid - 1;
    }
     return head;
}


/*
 *
 * 特殊的二分查找
 * (前面都是 0，后面都是 1， 找到第一个 1)
 * 000000001111111
 *
 */

int binary_search_3(int *num, int n) {

    // 含有虚拟节点
    int head = 0, tail = n, mid;

    // 当头尾指针没有重合的时候
    while (head < tail) {
        mid = (head + tail) >> 1;
        if (num[mid] == 1) tail = mid;
        else head = mid + 1;
    }
     return head == n ? -1 : head;
}

int main() {

    int arr1[10] = {1,3,5,7,11,13,17,19,23,29};
    int arr2[10] = {1,1,1,0,0,0,0,0,0,0};
    int arr3[10] = {0,0,0,0,0,0,1,1,1,1};

    P(binary_search_1(arr1,10, 11));
    P(binary_search_2(arr2,10));
    P(binary_search_3(arr3,10));

    return 0;
}

