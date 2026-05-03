/*
 * [Topic] stack, queue, priority_queue
 * LIFO/FIFO 자료구조와 힙 기반 우선순위 큐.
 *
 * stack         : LIFO, push/pop/top
 * queue         : FIFO, push/pop/front
 * priority_queue: 힙, 기본 최대 힙 (top = 최댓값)
 *
 * Practice:
 *   - stack으로 괄호 균형 검사 함수 구현
 *   - priority_queue로 최소 힙 만들기 (greater<int> 사용)
 */
#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

// 괄호 균형 검사 (stack 활용)
bool isBalanced(const string& s) {
    stack<char> st;
    for (char c : s) {
        if (c == '(' || c == '[' || c == '{') st.push(c);
        else if (c == ')' || c == ']' || c == '}') {
            if (st.empty()) return false;
            char top = st.top(); st.pop();
            if ((c == ')' && top != '(') ||
                (c == ']' && top != '[') ||
                (c == '}' && top != '{')) return false;
        }
    }
    return st.empty();
}

int main() {
    // stack
    stack<int> st;
    for (int i = 1; i <= 5; i++) st.push(i);
    cout << "stack top: " << st.top() << "\n";
    while (!st.empty()) { cout << st.top() << " "; st.pop(); }
    cout << "\n\n";

    // queue
    queue<string> q;
    q.push("first"); q.push("second"); q.push("third");
    while (!q.empty()) { cout << q.front() << " "; q.pop(); }
    cout << "\n\n";

    // priority_queue (최대 힙)
    priority_queue<int> pq;
    for (int x : {3, 1, 4, 1, 5, 9, 2, 6}) pq.push(x);
    cout << "priority_queue (max): ";
    while (!pq.empty()) { cout << pq.top() << " "; pq.pop(); }
    cout << "\n";

    // 최소 힙
    priority_queue<int, vector<int>, greater<int>> min_pq;
    for (int x : {3, 1, 4, 1, 5, 9, 2, 6}) min_pq.push(x);
    cout << "priority_queue (min): ";
    while (!min_pq.empty()) { cout << min_pq.top() << " "; min_pq.pop(); }
    cout << "\n\n";

    // 괄호 검사
    cout << isBalanced("({[]})") << "\n";   // 1
    cout << isBalanced("({[})") << "\n";    // 0
    cout << isBalanced("((())") << "\n";    // 0

    return 0;
}
