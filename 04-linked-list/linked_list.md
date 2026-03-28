# Linked List

---

## Какво ще научим днес?

- Ограниченията на ArrayList
- Какво е Linked List
- Видове Linked List
- Примерна имплементация на C++
- Основни операции и тяхната сложност
- Сравнение с ArrayList
- `list` класът и неговите основни операции

---

## Проблемът с ArrayList

- ArrayList е бърз за достъп по индекс — O(1)
- Но вмъкването и изтриването в средата са **O(n)**

```
Изтриване на позиция 1:
[10, 20, 30, 40, 50]
      ↑
      Трябва да преместим 30, 40, 50 наляво

[10, 30, 40, 50, __]
```

- Какво ако вмъкваме/изтриваме **много често**?

---

## Какво е Linked List?

- **Linked List** (свързан списък) е структура от данни, при която:
  - Всеки елемент се съхранява в отделен обект — **възел (node)**
  - Всеки възел пази **стойност** и **указател към следващия възел**
  - Елементите **не са наредени последователно** в паметта

```
[10] → [20] → [30] → [40] → NULL
```

---

## Структура на възел

```cpp
struct Node {
    int data;
    Node* next;
};
```

![linked list](https://media.geeksforgeeks.org/wp-content/uploads/20250619155958124670/Linked-list.webp)

- `head` — указател към първия възел
- Последният възел има `next = NULL`

---

## Видове Linked List

**Singly Linked List** (единично свързан):
```
[10] → [20] → [30] → NULL
```

**Doubly Linked List** (двойно свързан):
```
NULL ← [10] ⇄ [20] ⇄ [30] → NULL
```

**Circular Linked List** (кръгов):
```
[10] → [20] → [30] → (обратно към [10])
```

---

## Примерна имплементация — Node и клас

```cpp
#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;

    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }
```

---

## Добавяне в началото — push_front

```cpp
    void push_front(int value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        size++;
    }
```

```
Преди: [20] → [30] → NULL    head → [20]

Добавяме 10:
1. Създаваме нов възел [10]
2. new_node->next = head (сочи към [20])
3. head = new_node

След: [10] → [20] → [30] → NULL
```

---

## Добавяне в края — push_back

```cpp
    void push_back(int value) {
        Node* new_node = new Node(value);

        if (head == nullptr) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr) {
                current = current->next;
            }
            current->next = new_node;
        }

        size++;
    }
```

---

## Вмъкване на позиция i

```cpp
    void insert(int index, int value) {
        if (index == 0) {
            push_front(value);
            return;
        }

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* new_node = new Node(value);
        new_node->next = current->next;
        current->next = new_node;
        size++;
    }
```

---

## Вмъкване — визуализация

```
Вмъкни 99 на позиция 2:
[10] → [20] → [30] → [40] → NULL

1. Стигаме до възел на позиция 1 (current = [20])
2. new_node->next = current->next  (99 → [30])
3. current->next = new_node        ([20] → 99)

[10] → [20] → [99] → [30] → [40] → NULL
```

- Не преместваме елементи — само пренасочваме указатели!

---

## Изтриване на позиция i

```cpp
    void remove(int index) {
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        Node* current = head;
        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        Node* to_delete = current->next;
        current->next = to_delete->next;
        delete to_delete;
        size--;
    }
```

---

## Изтриване — визуализация

```
Изтрий позиция 2 ([30]):
[10] → [20] → [30] → [40] → NULL
                ↑
           to_delete

1. current = [20]
2. to_delete = current->next = [30]
3. current->next = to_delete->next = [40]
4. delete to_delete

[10] → [20] → [40] → NULL
```

---

## Принтиране и размер

```cpp
    void print() {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " → ";
            current = current->next;
        }
        cout << " → NULL" << endl;
    }

    int get_size() { return size; }

private:
    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};
```

---

## Пример за употреба

```cpp
int main() {
    LinkedList list;

    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);
    list.print();  // 5 → 10 → 20 → 30 → NULL

    list.insert(2, 99);
    list.print();  // 5 → 10 → 99 → 20 → 30 → NULL

    list.remove(2);
    list.print();  // 5 → 10 → 20 → 30 → NULL
}
```

---

## Сложност на операциите

| Операция                | Сложност | Бележка                                  |
| ----------------------- | -------- | ---------------------------------------- |
| Достъп по индекс        | O(n)     | Трябва да обходим от началото            |
| Добавяне в началото     | O(1)     | Само пренасочване на указател            |
| Добавяне в края         | O(n)     | Трябва да намерим края (или O(1) с tail) |
| Вмъкване на позиция i   | O(n)     | Намиране на позицията                    |
| Изтриване на позиция i  | O(n)     | Намиране на позицията                    |
| Изтриване от началото   | O(1)     | Само пренасочване на head                |
| Търсене                 | O(n)     | Линейно обхождане                        |

---

## Оптимизация с `tail` указател

- Ако пазим и указател `tail` към последния елемент:
  - Добавянето в края става **O(1)**

```cpp
class LinkedList {
    Node* head;
    Node* tail;  // ← допълнителен указател
    int size;
    ...
};
```

```
head → [10] → [20] → [30] → NULL ← tail
```

---

## `std::list` — стандартната имплементация

- C++ предоставя `std::list` — двойно свързан списък
- Включва се с `#include <list>`

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l;

    l.push_back(20);
    l.push_back(30);
    l.push_front(10);

    for (int x : l) {
        cout << x << " ";  // 10 20 30
    }
}
```

---

## Основни операции на `std::list`

```cpp
list<int> l = {10, 20, 30};

l.push_back(40);       // Добавяне в края:    [10, 20, 30, 40]
l.push_front(5);       // Добавяне в началото:[5, 10, 20, 30, 40]
l.pop_back();          // Премахване от края: [5, 10, 20, 30]
l.pop_front();         // Премахване от началото: [10, 20, 30]

auto it = l.begin();
advance(it, 1);
l.insert(it, 99);      // Вмъкване: [10, 99, 20, 30]
l.erase(it);           // Изтриване на it: [10, 99, 30]
```

---

## Полезни методи на `std::list`

| Метод              | Описание                               |
| ------------------ | -------------------------------------- |
| `push_back(x)`     | Добавя x в края                        |
| `push_front(x)`    | Добавя x в началото                    |
| `pop_back()`       | Премахва последния елемент             |
| `pop_front()`      | Премахва първия елемент                |
| `front()`          | Първи елемент                          |
| `back()`           | Последен елемент                       |
| `size()`           | Брой елементи                          |
| `empty()`          | Проверка дали е празен                 |
| `clear()`          | Изтрива всички елементи                |
| `insert(it, x)`    | Вмъква x преди итератор it             |
| `erase(it)`        | Изтрива елемент на итератор it         |

---

## Итерация с итератор

```cpp
list<int> l = {10, 20, 30, 40};

// С итератор
for (auto it = l.begin(); it != l.end(); ++it) {
    cout << *it << " ";
}

// С range-based for (препоръчително)
for (int x : l) {
    cout << x << " ";
}
```

- За разлика от `vector`, `list` **не поддържа** `l[i]`
- Достъпът е само чрез итератори или обхождане

---

## ArrayList срещу Linked List

| Операция                | ArrayList  | Linked List |
| ----------------------- | ---------- | ----------- |
| Достъп по индекс        | **O(1)**   | O(n)        |
| Добавяне в края         | **O(1)** * | O(1) **     |
| Добавяне в началото     | O(n)       | **O(1)**    |
| Вмъкване в средата      | O(n)       | O(n)        |
| Изтриване от средата    | O(n)       | O(n)        |
| Памет                   | По-малко   | По-голяма   |
| Кеш ефективност         | Добра      | Лоша        |

\* амортизирано && ** с tail указател

---

## Кога да използваме кое?

**ArrayList / `vector`** — когато:
- Четем/достъпваме елементи по индекс **често**
- Добавяме предимно в края
- Паметта е ограничена

**Linked List / `list`** — когато:
- Вмъкваме/изтриваме от **началото или средата** често
- Не ни трябва достъп по индекс
- Имаме итератор към позицията вече

---

## Въпроси

1. Защо достъпът по индекс при Linked List е O(n)?
2. Каква е разликата между Singly и Doubly Linked List?
3. Кога е изтриването O(1) при Linked List?
4. Защо Linked List използва повече памет от ArrayList?

---

## Домашна работа

- Разширете примерната `LinkedList` имплементация с:
    1. Метод `get(int index)` — достъп по индекс
    2. Метод `reverse()` — обръща реда на елементите
    3. Метод `contains(int value)` — търсене на стойност
- **Бонус:** Имплементирайте Doubly Linked List с `prev` указател

---

## Обобщение

- Linked List съхранява елементи в **възли с указатели**
- Вмъкването/изтриването от началото е **O(1)**
- Достъпът по индекс е **O(n)** — няма директно адресиране
- `std::list` е готовата двойно свързана имплементация в C++
- Изборът между ArrayList и Linked List зависи от операциите
