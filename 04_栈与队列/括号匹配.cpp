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


























