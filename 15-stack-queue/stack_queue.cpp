#include <iostream>
#include <vector>
using namespace std;

class Stack {
private:
    vector<int> data;

public:
    void push(int x) {
        data.push_back(x);
    }

    void pop() {
        if (!empty()) data.pop_back();
    }

    int top() const {
        return data.back();
    }

    bool empty() const {
        return data.empty();
    }

    int size() const {
        return data.size();
    }
};

class Queue {
private:
    int* data;
    int head;
    int tail;
    int capacity;
    int count;

public:
    Queue(int cap = 16)
        : head(0), tail(0), capacity(cap), count(0) {
        data = new int[capacity];
    }

    ~Queue() { delete[] data; }

    void enqueue(int x) {
        data[tail] = x;
        tail = (tail + 1) % capacity;
        count++;
    }

    int dequeue() {
        int val = data[head];
        head = (head + 1) % capacity;
        count--;
        return val;
    }

    int front() const { return data[head]; }
    int back()  const { return data[(tail - 1 + capacity) % capacity]; }
    bool empty() const { return count == 0; }
    int  size()  const { return count; }
};

int main() {
    // --- Демо на Stack ---
    cout << "=== Stack (LIFO) ===" << endl;

    Stack s;
    s.push(1);
    s.push(2);
    s.push(3);

    cout << "Елементи при pop (обратен ред): ";
    while (!s.empty()) {
        cout << s.top() << " ";  // 3 2 1
        s.pop();
    }
    cout << endl;

    // Приложение: обръщане на поредица
    cout << "\n--- Обръщане на поредица с Stack ---" << endl;
    int arr[] = {10, 20, 30, 40, 50};
    for (int x : arr) s.push(x);
    cout << "Оригинал: 10 20 30 40 50" << endl;
    cout << "Обърнато: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    // Приложение: проверка на скоби
    cout << "\n--- Проверка на скоби ---" << endl;
    auto check_brackets = [](const string& expr) {
        Stack st;
        for (char c : expr) {
            if (c == '(' || c == '[' || c == '{')
                st.push(c);
            else if (c == ')' || c == ']' || c == '}') {
                if (st.empty()) return false;
                char top = st.top(); st.pop();
                if ((c == ')' && top != '(') ||
                    (c == ']' && top != '[') ||
                    (c == '}' && top != '{'))
                    return false;
            }
        }
        return st.empty();
    };

    cout << "\"(()[])\" валидно: " << check_brackets("(()[])") << endl;  // 1
    cout << "\"([)]\"  валидно: " << check_brackets("([)]")   << endl;  // 0

    // --- Демо на Queue ---
    cout << "\n=== Queue (FIFO) ===" << endl;

    Queue q(10);
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);

    cout << "Елементи при dequeue (същи ред): ";
    while (!q.empty()) {
        cout << q.front() << " ";  // 1 2 3
        q.dequeue();
    }
    cout << endl;

    // Демо на кръгов буфер
    cout << "\n--- Кръгов буфер демо ---" << endl;
    Queue cbuf(5);
    cbuf.enqueue(10);
    cbuf.enqueue(20);
    cbuf.enqueue(30);
    cout << "front=" << cbuf.front() << ", back=" << cbuf.back()
         << ", size=" << cbuf.size() << endl;
    cbuf.dequeue();
    cbuf.enqueue(40);
    cout << "След dequeue + enqueue(40): front=" << cbuf.front()
         << ", back=" << cbuf.back() << endl;

    return 0;
}
