# Множества (Sets)

---

## Какво ще научим днес?

- Какво е множество като абстрактен тип данни (ADT)
- Разлика между множество и другите структури, които вече знаем
- Начини на имплементация: масив, хеш, балансирано дърво
- Примерна имплементация на C++ (HashSet)
- `std::set`, `std::unordered_set`, `std::multiset`
- Операции над множества: обединение, сечение, разлика
- Кога да използваме кой тип множество

---

## Мотивация

- Често трябва да отговорим само на въпроса "**видял ли съм вече този елемент?**"
- HashMap решава това, но пази ключ **и** стойност - излишно, ако не ни трябва стойност
- ArrayList позволява дубликати - трябва ръчно да проверяваме преди всяко вмъкване

```
Проблем: намери всички уникални думи в текст
  ArrayList → преди всяко insert трябва да проверим за дубликат: O(n)
  Set       → insert автоматично гарантира уникалност: O(1) средно
```

---

## Какво е множество (Set)?

- **Множество** е колекция от **уникални** елементи, без определен ред (или сортирани, в зависимост от имплементацията)
- Отразява математическото понятие за множество: `{1, 3, 5}` = `{5, 1, 3}` = `{1, 1, 3, 5}`

```
insert(3)   → {3}
insert(1)   → {1, 3}
insert(3)   → {1, 3}     ← вече съществува, нищо не се променя
contains(1) → true
remove(3)   → {1}
```

- Основни операции: `insert`, `remove`, `contains`, `size`

---

## Set срещу другите структури

| Структура     | Уникалност       | Наредба          | Ключ→стойност |
| -------------- | ----------------- | ----------------- | -------------- |
| ArrayList      | Не (позволява дубликати) | Ред на вмъкване | Не |
| HashMap        | Уникални ключове  | Не (unordered_map) | **Да** |
| **Set**        | **Уникални елементи** | Зависи от имплементацията | Не |

- Set е "HashMap само с ключове" или "BST само с ключове" - пазим наличието, не стойност

---

## Начини на имплементация

| Имплементация       | `contains` | `insert` | `remove` | Наредба      |
| --------------------- | ---------- | -------- | -------- | ------------- |
| Несортиран масив      | O(n)       | O(n)\*    | O(n)     | Няма          |
| Балансирано дърво (BST) | O(log n)   | O(log n) | O(log n) | **Сортирана** |
| Хеш таблица            | O(1) средно | O(1) средно | O(1) средно | Няма          |

\* трябва да проверим за дубликат преди вмъкване → O(n)

- `std::set` използва балансирано дърво, `std::unordered_set` използва хеш таблица

---

## Идея за HashSet - структура

- Същият принцип като HashMap, но пазим само ключа, без стойност

```cpp
class HashSet {
private:
    struct Entry {
        string key;
        bool occupied;
        bool deleted;

        Entry() : occupied(false), deleted(false) {}
    };

    vector<Entry> table;
    int capacity;
    int size;

    int hash(const string& key) const {
        int h = 0;
        for (char c : key) h = (h * 31 + c) % capacity;
        return h;
    }
```

---

## HashSet - insert и contains

```cpp
public:
    void insert(const string& key) {
        int idx = hash(key);
        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;
            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key)
                return;  // вече съществува
            if (!table[pos].occupied || table[pos].deleted) {
                table[pos].key = key;
                table[pos].occupied = true;
                table[pos].deleted = false;
                size++;
                return;
            }
        }
    }

    bool contains(const string& key) const {
        int idx = hash(key);
        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;
            if (!table[pos].occupied && !table[pos].deleted) return false;
            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key) return true;
        }
        return false;
    }
```

- Идентично на HashMap, само без полето `value`

---

## `std::set` - сортирано множество (BST)

- `std::set` в `<set>` - имплементирано като червено-черно дърво (както `std::map`)
- Елементите се пазят **сортирани**, гарантирано O(log n)

```cpp
#include <iostream>
#include <set>
using namespace std;

int main() {
    set<int> s;

    s.insert(5);
    s.insert(1);
    s.insert(9);
    s.insert(1);   // дубликат - игнорира се

    for (int x : s)
        cout << x << " ";   // 1 5 9  (сортирано!)
}
```

---

## Основни методи на `std::set`

```cpp
set<int> s = {5, 1, 9, 3};

s.insert(7);              // вмъкване
s.erase(1);                // изтриване по стойност

if (s.count(5) > 0)        // проверка за съществуване (0 или 1)
    cout << "5 е в множеството";

auto it = s.find(9);       // итератор, s.end() ако липсва
if (it != s.end())
    cout << "намерено: " << *it;

cout << s.size();          // брой елементи
cout << *s.begin();        // най-малкия елемент
cout << *s.rbegin();       // най-големия елемент
```

---

## `std::unordered_set` - хеш множество

- Същия интерфейс като `set`, но **без** наредба и с **O(1) средно**

```cpp
#include <unordered_set>
using namespace std;

int main() {
    unordered_set<string> visited;

    visited.insert("A");
    visited.insert("B");
    visited.insert("A");   // дубликат - игнорира се

    cout << visited.count("A");   // 1
    cout << visited.size();       // 2

    for (auto& x : visited)
        cout << x << " ";  // ред не е гарантиран
}
```

- Класическа употреба: пазене на **посетени** върхове при DFS/BFS в граф

---

## `std::multiset` - множество с дубликати

- Като `set`, но **позволява повтарящи се** стойности - остава сортиран

```cpp
#include <set>
using namespace std;

int main() {
    multiset<int> ms;
    ms.insert(3);
    ms.insert(1);
    ms.insert(3);   // дубликатите се пазят!

    for (int x : ms)
        cout << x << " ";   // 1 3 3

    cout << ms.count(3);    // 2 - брой срещания

    ms.erase(3);             // изтрива ВСИЧКИ срещания на 3!
    cout << ms.count(3);    // 0
}
```

> За изтриване само на **едно** срещане: `ms.erase(ms.find(3));`

---

## Set срещу Map

| Структура        | Пази               | Пример                       |
| ------------------ | ------------------- | ------------------------------ |
| `set`             | Само ключове         | Уникални стойности            |
| `map`             | Ключ → стойност       | Речник, броене                |
| `unordered_set`   | Само ключове (хеш)    | Бърза проверка за наличие     |
| `unordered_map`   | Ключ → стойност (хеш) | Бърз речник                   |

- Ако не ти трябва стойност, а само "видях ли това вече?" → `set`/`unordered_set`

---

## Операции над множества - обединение, сечение, разлика

- Математически операции: `∪` (обединение), `∩` (сечение), `\` (разлика)

```
A = {1, 2, 3, 4}
B = {3, 4, 5, 6}

A ∪ B (обединение) = {1, 2, 3, 4, 5, 6}
A ∩ B (сечение)    = {3, 4}
A \ B (разлика)     = {1, 2}
```

- C++ предоставя готови алгоритми в `<algorithm>` - работят върху **сортирани** диапазони

---

## Обединение, сечение, разлика в C++

```cpp
#include <algorithm>
#include <set>
#include <vector>
#include <iterator>
using namespace std;

set<int> a = {1, 2, 3, 4};
set<int> b = {3, 4, 5, 6};
vector<int> result;

set_union(a.begin(), a.end(), b.begin(), b.end(),
          back_inserter(result));
// result = {1, 2, 3, 4, 5, 6}

result.clear();
set_intersection(a.begin(), a.end(), b.begin(), b.end(),
                  back_inserter(result));
// result = {3, 4}

result.clear();
set_difference(a.begin(), a.end(), b.begin(), b.end(),
                back_inserter(result));
// result = {1, 2}
```

- Работят с `set`, защото елементите вече са **сортирани** (изискване на алгоритмите)

---

## Приложения на множества

- **Премахване на дубликати** - зареди елементите в set, извади ги обратно
- **Проверка за наличие** - "посетени" върхове в DFS/BFS, "видени" елементи
- **Математически операции** - обединение/сечение на потребителски групи, тагове
- **Броене на уникални елементи** - `set.size()` след зареждане

```cpp
vector<int> nums = {4, 1, 4, 2, 1, 3};
set<int> unique_nums(nums.begin(), nums.end());
cout << unique_nums.size();  // 4  (1, 2, 3, 4)
```

---

## Кога да използваме кой тип set?

| Нужда                              | Избор              |
| ------------------------------------ | -------------------- |
| Максимална скорост, не ти трябва ред | `unordered_set`     |
| Трябва ти сортиран ред               | `set`                |
| Range заявки (елементи между A и B)  | `set`                |
| Позволяваш дубликати, но сортирани   | `multiset`           |
| Трябва ти стойност по ключ, не само наличие | `map`/`unordered_map` |

---

## Въпроси

1. Каква е разликата между `set` и `unordered_set` по отношение на наредбата и сложността?
2. Защо `set_union`/`set_intersection` изискват **сортирани** диапазони?
3. Кога бихме избрали `multiset` пред `set`?
4. Каква е разликата между `set` и `map`?
5. Как HashSet имплементацията се различава от HashMap имплементацията?

---

## Домашна работа

- Разширете примерната `HashSet` имплементация с:
    1. Метод `remove(key)` - изтриване с "мързеливо" маркиране (както при HashMap)
    2. Метод `set_union(const HashSet& other)` - връща ново множество с обединението
- **Бонус:** Имплементирайте `find_duplicates(vector<int>& arr)`, която връща всички елементи, срещащи се повече от веднъж, използвайки `unordered_set`

---

## Обобщение

- **Set** е колекция от **уникални** елементи - `insert`, `remove`, `contains`
- Може да се имплементира с масив (бавно), балансирано дърво (сортирано, O(log n)) или хеш (O(1) средно)
- `std::set` е сортирано (BST), `std::unordered_set` е неподредено (хеш), `std::multiset` позволява дубликати
- `set_union`, `set_intersection`, `set_difference` работят върху сортирани диапазони от `<algorithm>`
- Set е добрият избор, когато не ти трябва стойност, а само проверка за наличие или уникалност
