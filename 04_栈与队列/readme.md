# 栈与队列
# 队列
### 队列结构的定义

**性质** : 先入先被服务(先出去)
**在队首出队，在队尾入队**
**先入先出** **FIFO**

占用连续的空间
```
length = 9;
head = 0;
tail = 4;
data_type = xxx;
```

### 队列结构的操作
#### 出队
* 出队 --> 头指针向后移动一位
* 

```
length = 9;           -->             length = 9;
head = 0;             -->   +1        head = 1;
tail = 4;             -->             tail = 4;
data_type = xxx;      -->             data_type = xxx;
```
#### 入队
(尾部入队)

```
length = 9;           -->             length = 9;
head = 0;             -->             head = 1;
tail = 4;             -->   +1        tail = 5;
data_type = xxx;      -->             data_type = xxx;
```

#### 入队 - 假溢出
#### 循环队列



# 栈
### 结构定义 
**连续的存储区去存储数据**
栈是 从底向上，最底部叫栈底，最顶部叫栈顶，只有一个指针
无论是出栈还是入栈都是从栈顶开始的
**后入的元素会先出来** **LIFO** 

```
size = 5;           // 最多存储多少个元素
top = 3;            // 栈顶指针
data_type = xxx;
```

具体的场景：
* 羽毛球筒 相当于 栈 


#### 出栈
* 出栈 --> 栈顶指针向下移动一位

```
size = 5;           -->           length = 9;
top = 3;            -->   -1      top = 2;
data_type = xxx;    -->           data_type = xxx;

```


#### 入栈
* 入栈 --> 栈顶指针向上移动一位
```
size = 5;           -->           length = 9;
top = 3;            -->   +1      top = 4;
data_type = xxx;    -->           data_type = xxx;
```

```c
/*
 * Given a string containing just the character '(' ')' '{' '}' ['' ']' 
 * determine if the input string is vaild .
 * the brackets must close in the correct order "()" and " () {} []" are
 * all vaild but "(]" and "{[(]" are not.
 *
 * */

/*
 * 思考:
 *      问题简化成只有一种括号怎么做 ？
 *      1. ((()())())
 *      2. (()))()
 *      3. (()()
 *      a. 任意位置，右括号的数量 <= 左括号的数量
 *      b. 在最后位置，右括号的数量 == 左括号的数量
 *      c. 程序中只需要记录左括号和右括号的数量即可
 *
 * */
 
bool isValid(char *s) {
    int32_t lnum = 0, rnum = 0;
    int32_t len = strlen(s);
    for (int32_t i = 0; i < len; i++) {
        switch (s[i]) {
            case '(': ++lnum; break;
            case ')': ++rnum; break;
            default: return false;
        }
        if (lnum >= rnum) continue;
        return false;
    }
    return lnum == rnum;
}

/*
 * +1 可以等价为 进 -1 可以等价为 出
 * 一对 （） 可以等价一个完整的事件
 * (()) 可以看做事件与事件之间的完全包含关系
 * 先发生的事，最后被解决
 *
 * */

```

## 栈的本质 
**栈** **可以处理具有 完全包含 关系的问题**

## 栈和队列的应用
* 栈            -->     树的深度遍历，深度优先搜索
* 队列          -->     树的层序遍历，广度优先搜索
* 单调栈        -->     临近最大(小) 值
* 单调队列      -->     区间最大(小) 值

# 单调队列
## 单调队列可以解决什么问题 ？
## ---->维护区间最值

* 维护区间最大值

每三个之间最大值 :

```
6 3 2 5 4 1 7 4 2
6 3 2
  3 2 5
    2 5 4
      5 4 1
```
```c
/*

   输入一个 长度为 n 的 整数序列，从中找出一段不超过 M 的连续子序列，使得整个序列的和最大
   例如： 1， -3， 5， 1，-2， 3
   当 m = 4 时, S = 5 + 1 -2 + 3 = 7
   当 m = 2 或 3 时, S = 5 + 1 = 6

   输入：
        第一行两个数: n,m
        第二行有 n 个数， 要求在 n 个数找到最大子序和
   输出：
        一个数：数出他们的最大子序和

   样例输入： 6 4
              1， -3， 5， 1，-2， 3

   样例输出： 7 
  
 */

#include <iostream>
#include <cmath>
using namespace std;

#define MAX_N 30000
int q[MAX_N + 5], head, tail;
long long arr[MAX_N +5];

int main () {
    long long n, m, ans;
    for (int i = 0; i <= n; i++) cin >> arr[i], arr[i] += arr[i - 1];
    head = tail = 0;
    q[tail++] = 0;
    ans = arr[1];

    for (int i = 1; i <= n; i++) {
        ans = max(ans, arr[i] - arr[q[head]]);
        while (tail - head && arr[q[tail-1]] >= arr[i]) tail--;
        q[tail++] = i;
        if (q[head] == i - m) head++;
    }

    cout << ans << endl;
    return 0;
}


```


# 单调栈
## 单调栈可以解决什么问题 ？
## ---->维护区间最近大于或小于关系

```c
/*
找到左边第一个比它大的数

INF 6  4  3  5  2  7   1  9 
   INF 6  4  6  5 INF  7 INF
    单调递增维护最近大于
    单调递减维护最近小于
*/

/*
 最大矩形面积
 给定从左到右有多个矩形，矩形的宽度都为 1， 长度不完全相等，这些矩形相连，连成一排
 求在这些矩形包括的范围内能得到的最大面积的矩形，打印出该面积，所求矩形可横跨多个
 矩形， 但不能超出原有矩形所确定的范围


 输入：
      输入共一行，第一个数表示举行的个数 N, 接下来 N 个数表示矩形的大小 (1 <= N <= 100000>)
 输出：
      输出最大矩形的面积

 样例输入：


 样例输出：

*/










```



