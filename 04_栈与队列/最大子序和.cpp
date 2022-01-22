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












