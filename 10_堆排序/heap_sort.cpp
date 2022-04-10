#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MX_OP 20

#define swap(a, b) { \
    __typeof(a) __temp = a; \
    a = b, b = __temp; \
}


// 向下调整封装成一个方法
void down_update(int *arr, int n, int ind) {
    while ((ind << 1) <= n) {

        int temp = ind, l = ind << 1, r = ind << 1 | 1;

        // 找全局最小值
        if (arr[l] > arr[temp]) temp = l;
        if (r <= n && arr[r] > arr[temp]) temp = r;
        if (temp == ind) break;
        swap(arr[temp], arr[ind]);
        ind = temp;
    }
    return ;

}


// 线性建堆法

void heap_sort(int *arr, int n) {
    // 使得数组下标从 1 开始
    arr -= 1;

    // 找到数组中最后一个有元素的位置
    for (int i = n >> 1; i >= 1 ; --i) {

        down_update(arr, n, i);

    }

    // n 次弹出
    for (int i = n; i > 1; --i) {
        swap(arr[1], arr[i]);

        down_update(arr, i-1, 1);
    }
}

// 输出数组
void output(int *arr, int n) {

    printf("arr[%d] = [", n);

    for (int i = 0; i < n; i++) {
        printf(" %d", arr[i]);
    }
    printf(" ]\n");
    return ;
}




int main() {

    srand(time(0));

    int *arr =(int *)malloc(sizeof(int) * MX_OP);

    for (int i = 0; i < MX_OP; i++) {
        arr[i] = rand() % 100;
    }

    output(arr, MX_OP);

    heap_sort(arr, MX_OP);

    output(arr, MX_OP);

    return 0;
}

