#include <iostream>
#include <time.h>
#include <stack>
#include <cmath>

using namespace std;
#define MAX_N 100000
long long arr[MAX_N + 5];
// 向左 和 向右
long long l[MAX_N + 5], r[MAX_N + 5];

int main () {
    // N
    int n;

    // 初始化 栈
    stack<int> s;

    // 读入 N
    cin >> n;

    // 左终点 右终点
    arr[0] = arr[n + 1] = -1;
    // 位置插入 下标+1
    for (int i = 1; i <= n; i++) cin >> arr[i];

    // 将 0 号压入栈(左边的最近最小值)
    s.push(0);
    
    // 扫描每一个节点
    // 左切
    for (int i = 1; i <= n; i++) {
        while (arr[s.top()] >= arr[i]) s.pop();
        l[i] = i - s.top();
        s.push(i);
    }

    // 将栈清空
    while (!s.empty()) s.pop();

    // 将右侧终点放到栈底
    s.push(n+1);

    for (int i = n; i >= 1; i--) {
        while (arr[s.top()] >= arr[i]) s.pop();
        r[i] = s.top() - i;
        s.push(i);
    }

    long long ans = 0;
    for (int i = 1; i <= n; i++) {
        ans = max(ans, arr[i] * (r[i] + l[i] - 1));
    }
    cout << ans << endl;
    return 0;
    /*
        时间复杂度 O(n)
    */
}



