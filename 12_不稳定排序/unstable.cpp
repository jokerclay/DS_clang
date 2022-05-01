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
