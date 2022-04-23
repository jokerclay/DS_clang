# 稳定排序

 - 稳定排序: `..... a[i] ......a[j]` `a[i] = a[j]`, 排序之后,`a[i]``a[j]`的相对位置不变

* 插入 n^2
* 冒泡 n^2
* 归并 n(log^n)

- 内部外部

### 插入排序(n^2)
**1.将数组分成[已排区域]和待排区域**
**2.将【已排区域】后面一个元素，向前插入到【待排区域】中**
**3.直到【待排区域】没有元素为止**

### 冒泡排序(n^2)
**1.将数组分成[已排区域]和待排区域**
**2.从头到尾扫描【待排区域】若前面的元素比后面元素大，则交换**
**3.每一轮都会将【待排区域】中最大的放到【已排区域】的开头**
**4.直到【待排区域】没有元素为止**

### 归并排序(n(log^n))
**分治**




# CODE
```C++
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MX_OP 20

#define swap(a,b) { \
    a^=b; b^=a; a^=b; \
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
 *
 * 插入排序
 *
 */ 

void insert_sort(int *num, int n) {
    for (int i = 1; i < n; ++i) {
        for (int j = i; j > 0 &&num[j] < num[j -1]; --j) {
            swap(num[j], num[j-1]);
        }
    }
    return ;
}

/*
 *
 * 冒泡排序
 *
 */ 
void bubble_sort(int *num, int n) {
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < n- i; j++){
            if (num[j] > num[j+1]) swap(num[j], num[j+1]);
        }
    }
    return ;
}


/*
 *
 * 归并排序
 *
 */ 
void merge_sort(int *num, int l, int r) {

    // 当元素很少时
    if (r -l <= 1) {
        if (r - l == 1 && num[l] > num[r]) {
            swap(num[l], num[r]);
        }
        return ;
    }

    int mid = (l + r) >> 1;

    merge_sort(num, l, mid);

    merge_sort(num, mid+1, r);

    int *temp = (int *)malloc(sizeof(int) * (r - l + 1));

    int p1 = l, p2 = mid + 1,  k = 0;


    while(p1 <= mid ||p2 <= r) {
        if (p2  > r ||(p1 <= mid && num[p1] <= num[p2])) {
            temp[k++] = num[p1++];
        } else {
            temp[k++] = num[p2++];
        }
    }


    memcpy(num + l, temp, sizeof(int) * (r - l + 1));

    free(temp);

    return ;

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
    TEST(arr, MX_OP, insert_sort, num, MX_OP);
    TEST(arr, MX_OP, bubble_sort, num, MX_OP);
    TEST(arr, MX_OP, merge_sort,num, 0, MX_OP - 1);

    return 0;
}

```



# RES

```txt
[ 8 58 37 14 84 27 84 21 72 41 31 9 12 18 78 23 6 56 40 31]

	insert_sort = [ 6 8 9 12 14 18 21 23 27 31 31 37 40 41 56 58 72 78 84 84]

[ 8 58 37 14 84 27 84 21 72 41 31 9 12 18 78 23 6 56 40 31]

	bubble_sort = [ 6 8 9 12 14 18 21 23 27 31 31 37 40 41 56 58 72 78 84 84]

[ 8 58 37 14 84 27 84 21 72 41 31 9 12 18 78 23 6 56 40 31]

	merge_sort = [ 6 8 9 12 14 18 21 23 27 31 31 37 40 41 56 58 72 78 84 84]

```
