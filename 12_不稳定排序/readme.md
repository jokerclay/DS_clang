# 不稳定排序

### 选择排序

**将数组分成【已排序区】和【待排序区】**<br>
**每一轮从【待排序区】中选择一个最小的元素放到【已排区域】的尾部**<br>
**直到【带排区域】中选择一个最小的元素放到【已排元素】**<br>

### 为什么选择排序是不稳定排序 ？

### 快速排序



















# CODE
```C
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#define MX_OP 20

#define swap(a, b) {\
    __typeof(a) _temp = a; a = b; b = _temp; \
}

#define TEST(arr, n, func, args...) { \
    int *num = (int *)malloc(sizeof(int) * n); \
    memcpy(num, arr, sizeof(int) * n); \
    output(num, n); \
    printf("\t%s = ", #func); \
    func(args); \
    output(num, n); \
    free(num); \
}


/*
 * 选择排序
 */ 

void select_sort(int *num, int n) {
    for (int i =0; i < n-1; i++) {
        int ind = i;
        for (int j = i + 1; j < n; j++) {

            if (num[ind] > num[j]) ind = j;
        }
        swap(num[i], num[ind]);
    }
    return ;
}


/*
 * 快速排序
 */ 

void quick_sort(int *num, int l, int r) {
    if (r <= l) return ;

    int x = l, y = r, z = num[l];

    while (x < y) {
    while(x < y && num[y] >=z) --y;
    if (x < y) num[x++] = num[y];

    while(x < y && num[y] >=z) ++x;
    if (x < y) num[y--] = num[x];
    }

    num[x] = z;

    quick_sort(num, l, x-1);
    quick_sort(num, x+1, r);
}


void random_int(int *arr, int n){
    while(n--) {
         arr[n] = rand() % 100;
    }
    return ;
}

void output(int *num, int n) {
    printf("[");
    for (int i = 0; i< n; i++) {
        printf(" %d", num[i]);
    }
    printf("]\n\n");
    
    return ;

}

int main() {

    srand(time(0));
    
    int arr[MX_OP];
    random_int(arr, MX_OP);

    // 测试排序的宏
    TEST(arr, MX_OP, select_sort, num, MX_OP);
    TEST(arr, MX_OP, quick_sort,num, 0, MX_OP - 1);

    return 0;
}
```




# RES
```txt
[ 9 11 95 53 80 95 83 78 18 62 92 77 3 57 87 61 4 99 5 76]

	select_sort = [ 3 4 5 9 11 18 53 57 61 62 76 77 78 80 83 87 92 95 95 99]

[ 9 11 95 53 80 95 83 78 18 62 92 77 3 57 87 61 4 99 5 76]

	quick_sort = [ 3 5 4 9 53 57 76 11 61 77 80 78 83 87 92 18 62 95 95 99]

```
