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

```
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

6 3 2 5 4 1 7 4 2
6 3 2
  3 2 5
    2 5 4
      5 4 1




