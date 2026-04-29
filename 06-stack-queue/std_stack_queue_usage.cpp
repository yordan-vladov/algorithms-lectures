#include <iostream>
#include <stack>
#include <queue>
#include <string>
using namespace std;

int main() {
    // === std::stack ===
    cout << "=== std::stack ===" << endl;

    stack<int> s;
    s.push(10);
    s.push(20);
    s.push(30);

    cout << "top=" << s.top() << ", size=" << s.size() << endl;  // 30, 3

    // pop не връща стойност - трябва top() преди pop()
    int val = s.top();
    s.pop();
    cout << "Извадено: " << val << ", ново top=" << s.top() << endl;

    cout << "\nИзваждане на всички елементи: ";
    while (!s.empty()) {
        cout << s.top() << " ";
        s.pop();
    }
    cout << endl;

    // Приложение: обръщане на низ
    cout << "\n--- Обръщане на низ ---" << endl;
    string word = "алгоритъм";
    stack<char> chars;
    for (char c : word) chars.push(c);
    string reversed;
    while (!chars.empty()) {
        reversed += chars.top();
        chars.pop();
    }
    cout << "Оригинал: " << word << endl;
    cout << "Обърнат:  " << reversed << endl;

    // === std::queue ===
    cout << "\n=== std::queue ===" << endl;

    queue<int> q;
    q.push(1);   // enqueue
    q.push(2);
    q.push(3);

    cout << "front=" << q.front() << ", back=" << q.back()
         << ", size=" << q.size() << endl;

    q.pop();     // dequeue
    cout << "След pop(), front=" << q.front() << endl;

    cout << "\nИзваждане на всички елементи: ";
    while (!q.empty()) {
        cout << q.front() << " ";
        q.pop();
    }
    cout << endl;

    // Приложение: обработка на задачи по ред
    cout << "\n--- Симулация на опашка от задачи ---" << endl;
    queue<string> tasks;
    tasks.push("Задача 1: компилиране");
    tasks.push("Задача 2: тестване");
    tasks.push("Задача 3: деплой");

    cout << "Обработка на задачи:" << endl;
    while (!tasks.empty()) {
        cout << "  Изпълняване: " << tasks.front() << endl;
        tasks.pop();
    }

    // Приложение: обръщане на опашка чрез стек
    cout << "\n--- Обръщане на опашка чрез стек ---" << endl;
    queue<int> orig;
    orig.push(1); orig.push(2); orig.push(3); orig.push(4); orig.push(5);

    stack<int> tmp;
    while (!orig.empty()) {
        tmp.push(orig.front());
        orig.pop();
    }
    while (!tmp.empty()) {
        orig.push(tmp.top());
        tmp.pop();
    }

    cout << "Обърната опашка: ";
    while (!orig.empty()) {
        cout << orig.front() << " ";
        orig.pop();
    }
    cout << endl;

    return 0;
}
