# Домашна работа: Стек и Опашка

Имплементирайте класовете `Stack` и `Queue` **без** `std::stack`, `std::queue` или `std::vector`. Използвайте свързан списък или масив.

---

## Скелет

Копирайте кода по-долу в нов файл `solution.cpp` и попълнете всички `// TODO`.

```cpp
#include <iostream>
#include <string>
using namespace std;

// ── Stack (свързан списък) ──────────────────────────────────
class Stack {
private:
    struct Node {
        int value;
        Node* next;
    };
    Node* head;
    int   count;

public:
    Stack() : head(nullptr), count(0) {}
    ~Stack() { while (!empty()) pop(); }

    void push(int x) { /* TODO */ }
    void pop()       { /* TODO */ }
    int  top()  const { /* TODO */ return -1; }
    bool empty() const { /* TODO */ return true; }
    int  size()  const { /* TODO */ return 0; }
};

// ── Queue (кръгов буфер) ────────────────────────────────────
class Queue {
private:
    int* data;
    int  head, tail, capacity, count;

public:
    Queue(int cap = 16) : head(0), tail(0), capacity(cap), count(0) {
        data = new int[capacity];
    }
    ~Queue() { delete[] data; }

    void enqueue(int x) { /* TODO */ }
    int  dequeue()      { /* TODO */ return -1; }
    int  front() const  { /* TODO */ return -1; }
    bool empty() const  { /* TODO */ return true; }
    int  size()  const  { /* TODO */ return 0; }
};
```

---

## Задача 1 — Проверка на скоби

Напишете функция `is_valid_brackets(s)`, която приема низ от символите `()[]{}` и връща `true` ако скобите са правилно наредени.

**Примери:**

| Вход       | Изход |
| ---------- | ----- |
| `"(()[])"`  | `true`  |
| `"([)]"`    | `false` |
| `"{[]}"`    | `true`  |
| `"("`       | `false` |

**Изисквания:** използвайте вашия клас `Stack`.

```cpp
bool is_valid_brackets(const string& s) {
    // TODO
    return false;
}
```

---

## Задача 2 — Обръщане на опашка

Напишете функция `reverse_queue(q)`, която обръща реда на елементите в подадената опашка **на място**, използвайки само вашия клас `Stack`.

**Пример:**

```
Преди:  front → 1  2  3  4  5 ← back
След:   front → 5  4  3  2  1 ← back
```

```cpp
void reverse_queue(Queue& q) {
    // TODO
}
```

---

## Задача 3 (Бонус) — MinStack

Имплементирайте клас `MinStack`, който поддържа всички операции на обикновен стек плюс метод `getMin()`, който връща **минималния елемент в O(1)**.

**Пример:**

```
push(3) → push(1) → push(2)
getMin() → 1
pop()          // премахва 2
getMin() → 1
pop()          // премахва 1
getMin() → 3
```

> **Подсказка:** пазете втори стек, в който да съхранявате текущия минимум.

```cpp
class MinStack {
public:
    // TODO: добавете необходимите полета

    void push(int x) { /* TODO */ }
    void pop()       { /* TODO */ }
    int  top()    const { /* TODO */ return -1; }
    int  getMin() const { /* TODO */ return -1; }
    bool empty()  const { /* TODO */ return true; }
};
```

---

## Тестове

Добавете следния `main()` и проверете дали изходът съвпада с очаквания:

```cpp
int main() {
    // Stack
    Stack s;
    s.push(10); s.push(20); s.push(30);
    cout << s.top() << " " << s.size() << endl;  // 30 3
    s.pop();
    cout << s.top() << " " << s.size() << endl;  // 20 2

    // Queue
    Queue q(10);
    q.enqueue(1); q.enqueue(2); q.enqueue(3);
    cout << q.front() << " " << q.size() << endl; // 1 3
    q.dequeue();
    cout << q.front() << " " << q.size() << endl; // 2 2

    // Задача 1
    cout << is_valid_brackets("(()[])") << endl;  // 1
    cout << is_valid_brackets("([)]")   << endl;  // 0

    // Задача 2
    Queue q2(10);
    for (int x : {1,2,3,4,5}) q2.enqueue(x);
    reverse_queue(q2);
    while (!q2.empty()) { cout << q2.front() << " "; q2.dequeue(); }
    cout << endl;  // 5 4 3 2 1

    // Задача 3
    MinStack ms;
    ms.push(3); ms.push(1); ms.push(2);
    cout << ms.getMin() << endl;  // 1
    ms.pop(); cout << ms.getMin() << endl;  // 1
    ms.pop(); cout << ms.getMin() << endl;  // 3
}
```
