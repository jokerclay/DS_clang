# 二分查找与三分查找
###二分查找要解决的问题

* 在有序的数组中，查找元素X 是否存在

```txt
min 是 头指针
max 是 尾指针
分别指向待排序列的头和尾

(核心观点了，不断地缩小待查找的区间, 每次缩小一半？)

如何缩小呢 ？
(利用数组有序的特性)

声明一个 mid 指针
mid = (min +max) / 2 

调整:
    如果 arr[mid] < x, min = mid + 1; ==> x 在数组的后半段
    如果 arr[mid] > x, max = mid - 1; ==> x 在数组的前半段

    【使得待查找数组减少一半】

    如果 arr[mid] == x, 找到结果

```

#### 思维转换
* 数组时展开的函数, 二分查找是在有序的下标，查找一个值
* 对于函数来说, 下标是 自变量x ， 值 是因变量 y, f(x) = y

**将有序数组与函数对应,二分查找是在做单调函数的值的求解问题**

##### 二分查找的实际应用的模型
1. 连续的数组前面一串 `1` ， 后面一串 `0`, **要找最后一位  `1`**
    * 如何做 ？
    * 如果 `mid[x] == 1`, **要找最后一位  `1`**,  `min = mid + 1`
    * 如果 `mid[x] == 0`, **要找最后一位  `1`**,  `max = mid - 1`
    * 如果 `min = max` 找到结果

* 如果序列中全是 `0` 没有  `1`, 的话，返回 `-1` 比较合适

* 加入虚拟 `min` 节点
    * `min` 虚拟节点
    * `max` 尾指针
    * `mid = (min + max + 1 )/2 `


2. 连续的数组前面一串 `0` ， 后面一串 `1`, **要找第一位  `1`**

    * 如果 `mid[x] != 1`, **要找第一位  `1`**,  `min = mid + 1`
    * 如果 `mid[x] == 1`, **要找第一位  `1`**,  `max = mid`
    * 如果 `min = max` 找到结果

* 如果序列中全是 `0` 没有  `1`, 的话，在最后一位加上虚拟位

###三分查找要解决的问题
#### 求解 凹凸函数的极值问题




# CODE
```txt

[L, R] 是查找的范围
m1 是 [L, R] 的  1/3 处
m1 是 [L, R] 的  2/3 处

```
*  如果 `f[m1] <  f[m2]`, L  = m1
*  如果 `f[m2] <  f[m1]`, L  = m2
*  如果 `[m1 -m2]` < exp, 未找到结果

* 三文查找每一轮缩小 1/3, 
**二分查找和三分查找缩小的是问题的查找规模**






```c++
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

```

# RES
```txt
binary_search_1(arr1,10, 11) = 4
binary_search_2(arr2,10) = 2
binary_search_3(arr3,10) = 6
```
