# Подготовка за контролно — ArrayList, Linked List, HashMap

---

## Структура на теста

- **Част I:** 10 затворени въпроса × 1 т. = 10 точки
- **Част II:** 5 отворени въпроса × 4 т. = 20 точки
- **Общо:** 30 точки

---

## 1. ArrayList

### Ключови понятия

| Термин | Значение |
|--------|---------|
| `size` | Брой елементи в момента |
| `capacity` | Размер на вътрешния масив (заделена памет) |
| `resize` | Удвояване на capacity, копиране на елементи — O(n), но рядко |
| `shrink` | Намаляване на capacity наполовина — при `size <= capacity/4` |
| Амортизирано O(1) | Средна цена на операция, въпреки че отделни може да са O(n) |

### Сложности

| Операция | Сложност | Защо |
|----------|----------|------|
| Достъп по индекс | **O(1)** | Директно изчисляване на адрес |
| Добавяне в края (`push_back`) | **O(1) амортизирано** | Рядко се налага resize |
| Премахване от края (`pop_back`) | **O(1) амортизирано** | Рядко се налага shrink |
| Вмъкване на позиция i | **O(n)** | Преместване на елементи надясно |
| Изтриване на позиция i | **O(n)** | Преместване на елементи наляво |
| Търсене | **O(n)** | Линейно преглеждане |
| resize / shrink | **O(n)** | Копиране на всички елементи |

### Защо се удвоява, а не се добавя фиксирано число?

При добавяне на +10 за n вмъквания общата работа е: `10 + 20 + 30 + ... = O(n²)` → линейна на добавяне.

При удвояване: `1 + 2 + 4 + ... + n = 2n - 1` → средно **O(1) на добавяне**.

### Thrashing — защо shrink при capacity/4, не capacity/2?

```
Ако shrink при size == capacity/2:
push_back → resize: capacity 4 → 8   (копираме)
pop_back  → shrink: capacity 8 → 4   (копираме)
push_back → resize: capacity 4 → 8   (копираме)  ← цикъл!
```

При `size <= capacity/4` след shrink имаме `size == capacity/4` и новото `capacity = capacity/2`, т.е. `size = capacity_new/2` — далеч от следващия resize или shrink. Гарантира O(1) амортизирано и за двете операции.

### Визуализация на resize

```
capacity=4, size=4: [10, 20, 30, 40]
push_back(50) → resize!
  1. Нов масив с capacity=8
  2. Копираме: [10, 20, 30, 40, _, _, _, _]
  3. Добавяме: [10, 20, 30, 40, 50, _, _, _]
```

### Визуализация на shrink

```
capacity=16, size=4: [10, 20, 30, 40, _, _, _, _, _, _, _, _, _, _, _, _]
pop_back() → size=3, 3 <= 16/4=4 → shrink!
  capacity=8: [10, 20, 30, _, _, _, _, _]
```

### `std::vector` — основни операции

```cpp
vector<int> v = {1, 2, 3};
v.push_back(4);              // [1, 2, 3, 4]
v.pop_back();                // [1, 2, 3]
v.insert(v.begin() + 1, 99); // [1, 99, 2, 3]
v.erase(v.begin() + 2);      // [1, 99, 3]
cout << v[0];                // 1
cout << v.size();            // 3
cout << v.capacity();        // текущ капацитет

// Инициализиране
vector<int> a;               // празен
vector<int> b(5);            // 5 елемента, стойност 0
vector<int> c(5, 42);        // 5 елемента, стойност 42
vector<int> d = {1, 2, 3};   // конкретни стойности
```

---

## 2. Linked List

### Видове

```
Singly:   [10] → [20] → [30] → NULL
Doubly:   NULL ← [10] ⇄ [20] ⇄ [30] → NULL
Circular: [10] → [20] → [30] → (обратно към [10])
```

### Сложности

| Операция | Singly LL | Бележка |
|----------|-----------|---------|
| Достъп по индекс | **O(n)** | Обхождане от head |
| Добавяне в началото | **O(1)** | Само пренасочване на head |
| Добавяне в края (без tail) | **O(n)** | Трябва да намерим края |
| Добавяне в края (с tail) | **O(1)** | Директно чрез tail |
| Изтриване от началото | **O(1)** | head = head->next |
| Вмъкване/изтриване на позиция i | **O(n)** | Намиране на позицията |
| Търсене | **O(n)** | Линейно обхождане |

### Визуализация на push_front

```
Преди: head → [20] → [30] → NULL

push_front(10):
  1. Създаваме нов възел [10]
  2. new_node->next = head  ([10] → [20])
  3. head = new_node

След: head → [10] → [20] → [30] → NULL
```

### Визуализация на изтриване на позиция i

```
Изтрий позиция 2 от [10] → [20] → [30] → [40] → NULL

  current = [20] (позиция 1)
  to_delete = current->next = [30]
  current->next = to_delete->next = [40]
  delete to_delete

След: [10] → [20] → [40] → NULL
```

### Защо достъпът по индекс е O(n)?

Елементите **не са наредени последователно в паметта** — всеки възел е на произволен адрес. За да стигнем до позиция i, трябва да обходим от head.

### Защо Linked List използва повече памет?

Всеки възел пази освен данните и указател(и): `next` (4–8 байта) при singly, `next` + `prev` при doubly.

### ArrayList срещу Linked List

| Критерий | ArrayList | Linked List |
|----------|-----------|-------------|
| Достъп по индекс | **O(1)** | O(n) |
| Добавяне в началото | O(n) | **O(1)** |
| Добавяне в края | O(1)* | O(1)** |
| Използване на памет | По-малко | По-голямо (указатели) |
| Кеш ефективност | **Добра** (последователна памет) | Лоша (пръснати по паметта) |

\* амортизирано  \*\* с tail указател

**Кога ArrayList:** четем по индекс, добавяме предимно в края, важна е кеш ефективността.

**Кога Linked List:** вмъкваме/изтриваме от началото/средата, имаме итератор към позицията вече.

### `std::list` — основни операции

```cpp
list<int> l = {10, 20, 30};
l.push_back(40);        // [10, 20, 30, 40]
l.push_front(5);        // [5, 10, 20, 30, 40]
l.pop_back();           // [5, 10, 20, 30]
l.pop_front();          // [10, 20, 30]

// Вмъкване по итератор (няма operator[])
auto it = l.begin();
advance(it, 1);         // it сочи към 20
l.insert(it, 99);       // [10, 99, 20, 30]
l.erase(it);            // изтрива 20: [10, 99, 30]

// Итерация
for (int x : l) cout << x << " ";
```

**ВАЖНО:** `std::list` **НЕ** поддържа `l[i]` — само итератори.

---

## 3. HashMap

### Ключови понятия

| Термин | Значение |
|--------|---------|
| Хеш функция | Превръща ключ в индекс; детерминирана (един ключ → един индекс) |
| Колизия | Два различни ключа дават един и същ индекс |
| Load factor | `size / capacity` — мерка за запълненост |
| Rehashing | Удвояване на capacity + прехвърляне на всички елементи |
| Lazy deletion | Маркиране на изтрити клетки с флаг `deleted` |

### Хеш функция

```cpp
int hash(int key, int capacity) {
    return key % capacity;  // за числа
}
// За низове: сумиране на символи с тегла
int h = 0;
for (char c : key) h = (h * 31 + c) % capacity;
```

**Детерминирана** = един и същи ключ → **винаги** един и същи индекс (не рандомна!).

### Разрешаване на колизии

**Chaining (верижно):**
- Всяка клетка пази свързан списък от двойки
- Лесна имплементация; O(n) при много колизии

```
индекс 2: → ("alice", 25) → ("eve", 22) → NULL
```

**Open Addressing / Linear Probing:**
- При колизия търсим следващата свободна клетка последователно
- `pos = (hash + i) % capacity` за i = 0, 1, 2, ...

```
hash("alice") = 2 → клетка 2 свободна → вмъкваме
hash("eve")   = 2 → клетка 2 заета → пробваме 3 → свободна → вмъкваме

[ _ , _ , "alice":25 , "eve":22 , _ , _ , _ ]
```

### Защо "мързеливо" изтриване?

При open addressing, ако изчистим клетка напълно, счупваме probing веригата:

```
Вмъкнали сме: "alice"(idx=2), "eve"(idx=2→3), "bob"(idx=2→3→4)
Изтриваме "eve" от клетка 3 напълно (празна)

get("bob"): hash=2 → клетка 2 заета (alice) → клетка 3 ПРАЗНА → спираме!
            "bob" не е намерен — ГРЕШНО!
```

С `deleted` флаг: клетка 3 е `deleted` → **продължаваме** probing → намираме "bob" в клетка 4.

### Load Factor и Rehashing

```
load factor = size / capacity

capacity=10, size=7 → LF = 0.7  ✓ приемливо
capacity=10, size=8 → LF = 0.8  → rehashing!
```

**Rehashing процес:**
1. Удвояваме capacity
2. Прехвърляме всички елементи с нови хеш стойности (старите индекси вече не важат)
3. Сложност: O(n), но се случва рядко → амортизирано O(1)

**Защо не "разваля" O(1)?** Същата логика като при ArrayList resize — геометрично нарастване означава, че средната цена на вмъкване е O(1).

### Сложности

| Операция | Средно | Най-лош случай |
|----------|--------|----------------|
| Вмъкване | **O(1)** | O(n) при много колизии |
| Търсене | **O(1)** | O(n) при много колизии |
| Изтриване | **O(1)** | O(n) при много колизии |
| Обхождане | O(capacity) | O(capacity) — минаваме целия масив |

### `std::unordered_map` — основни операции

```cpp
unordered_map<string, int> m;

// Вмъкване / актуализиране
m["alice"] = 25;           // създава ако не съществува!
m.insert({"bob", 30});     // само ако ключът НЕ съществува

// Достъп
cout << m["alice"];        // 25 (ОПАСНО: добавя ключа ако липсва!)
cout << m.at("alice");     // 25 (хвърля out_of_range ако липсва)

// Безопасен достъп
auto it = m.find("carol");
if (it != m.end()) cout << it->second;

// Проверка за съществуване
if (m.count("bob") > 0) cout << "exists";

// Изтриване
m.erase("alice");

// Итерация (редът НЕ е гарантиран!)
for (auto& [key, value] : m) {
    cout << key << ": " << value << endl;
}
```

### `m[key]` срещу `m.at(key)` срещу `m.find(key)` срещу `m.insert`

| Метод | Ако ключ НЕ съществува |
|-------|------------------------|
| `m[key]` | **Добавя** ключа с default стойност (0) |
| `m.at(key)` | **Хвърля** `std::out_of_range` |
| `m.find(key)` | Връща `m.end()` — безопасно |
| `m.insert({k,v})` | Вмъква; **не** презаписва ако вече съществува |

---

## 4. Примерни задачи с решения

### Задача 1 — Брой на думи

```cpp
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
using namespace std;

unordered_map<string, int> count_words(const vector<string>& words) {
    unordered_map<string, int> freq;
    for (const string& w : words) {
        freq[w]++;
    }
    return freq;
}

int main() {
    vector<string> words = {"apple", "banana", "apple", "cherry", "banana", "apple"};
    auto freq = count_words(words);
    for (auto& [w, cnt] : freq) {
        cout << w << ": " << cnt << endl;
    }
}
// Изход: apple: 3, banana: 2, cherry: 1 (в произволен ред)
```

### Задача 2 — Само уникални думи

```cpp
void print_unique(const vector<string>& words) {
    unordered_map<string, int> freq;
    for (const string& w : words) freq[w]++;
    for (auto& [w, cnt] : freq) {
        if (cnt == 1) cout << w << " ";
    }
}
// Вход: {"hello", "world", "hello", "foo"}
// Изход: world foo (в произволен ред)
```

### Задача 3 — Проверка за дубликати

```cpp
bool has_duplicate(const vector<int>& nums) {
    unordered_map<int, int> seen;
    for (int n : nums) {
        if (seen.count(n) > 0) return true;
        seen[n] = 1;
    }
    return false;
}
// has_duplicate({1, 2, 3, 2, 5}) → true
```

### Задача 4 — Безопасна проверка за ключ

```cpp
bool key_exists(const unordered_map<string, int>& m, const string& key) {
    return m.find(key) != m.end();
    // Алтернатива: return m.count(key) > 0;
}
// m[key] е опасно — добавя ключа с 0 ако не съществува!
```

### Задача 5 — contains за Linked List

```cpp
bool contains(int value) {
    Node* current = head;
    while (current != nullptr) {
        if (current->data == value) return true;
        current = current->next;
    }
    return false;
}
// Сложност: O(n) — линейно обхождане
```

### Задача 6 — push_front с std::list

```cpp
#include <iostream>
#include <list>
using namespace std;

int main() {
    list<int> l;
    for (int i = 1; i <= 5; i++) {
        l.push_front(i);
    }
    for (int x : l) cout << x << " ";
    // Изход: 5 4 3 2 1
}
```

### Задача 7 — count_name

```cpp
int count_name(const vector<string>& names, const string& target) {
    unordered_map<string, int> freq;
    for (const string& n : names) freq[n]++;
    return freq.count(target) ? freq[target] : 0;
    // или по-просто: freq[target] (ако не съществува → 0)
}
// count_name({"Ana", "Bob", "Ana", "Carol", "Ana"}, "Ana") → 3
```

---

## 5. Типични затворени въпроси по теми

### ArrayList

- Достъп по индекс → **O(1)**
- Shrink при → **`size <= capacity/4`**
- Resize: капацитетът се **удвоява**, елементите се **копират**
- `vector<int> v(5)` → 5 елемента, стойност 0
- `capacity()` → размер на вътрешния масив (≥ `size()`)

### Linked List

- push_front, pop_front → **O(1)**
- Достъп по индекс → **O(n)** (елементите са пръснати в паметта)
- push_back без tail → **O(n)**, с tail → **O(1)**
- `std::list` НЕ поддържа `l[i]`
- `advance(it, 3)` → придвижва итератора напред с 3 позиции
- Doubly Linked List: всеки възел пази `next` **и** `prev`
- Circular: последният елемент сочи към **първия**

### HashMap

- Колизия → два различни ключа дават **един и същи индекс**
- Load factor = `size / capacity` → LF=0.7 при size=7, cap=10
- Rehashing: удвоява се capacity, **прехвърлят се с нови хеш стойности**
- Lazy deletion → клетка се маркира `deleted`, **не се почиства**
- `m.find(key)` → безопасно, връща `m.end()` ако липсва
- Обхождане на HashMap → O(**capacity**), не O(size)
- Ред на итерация при `unordered_map` → **не е гарантиран**
- `m.at(key)` → хвърля изключение ако ключът **не съществува**
- `m[key]` → **добавя** ключа с 0 ако не съществува

---

## 6. Честа сравнителна таблица (попълнена)

| Операция | ArrayList | Linked List | HashMap |
|----------|-----------|-------------|---------|
| Достъп по ключ/индекс | O(1) | O(n) | O(1) средно |
| Добавяне в началото | O(n) | O(1) | N/A |
| Добавяне в края | O(1) амортизирано | O(1) с tail | N/A |
| Търсене по стойност | O(n) | O(n) | O(1) средно по ключ |
| Допълнителна памет | Малко (capacity > size) | По-голяма (указатели) | По-голяма (хеш таблица) |
| Кеш ефективност | Добра | Лоша | Средна |

---

## 7. Проследяване на операции

### resize при ArrayList (начален capacity=2)

```
push_back(1): size=1, cap=2  [1, _]
push_back(2): size=2, cap=2  [1, 2]
push_back(3): size==cap → resize! cap=4  [1, 2, 3, _]
push_back(4): size=4, cap=4  [1, 2, 3, 4]
push_back(5): size==cap → resize! cap=8  [1, 2, 3, 4, 5, _, _, _]
```

### HashMap с linear probing (capacity=7)

```
insert("cat",1): hash=3 → клетка 3 свободна → вмъкваме
  [ _, _, _, cat:1, _, _, _ ]

insert("dog",2): hash=3 → клетка 3 заета → клетка 4 свободна → вмъкваме
  [ _, _, _, cat:1, dog:2, _, _ ]

insert("fox",3): hash=5 → клетка 5 свободна → вмъкваме
  [ _, _, _, cat:1, dog:2, fox:3, _ ]
```

### Lazy deletion при HashMap (capacity=5)

```
insert("a",10): hash=1 → [ _, a:10, _, _, _ ]
insert("b",20): hash=1 → клетка 1 заета → клетка 2: [ _, a:10, b:20, _, _ ]
insert("c",30): hash=1 → клетки 1,2 заети → клетка 3: [ _, a:10, b:20, c:30, _ ]

remove("b"): маркираме клетка 2 като DELETED
  [ _, a:10, DEL, c:30, _ ]

get("c"): hash=1 → клетка 1 (a, не съвпада) → клетка 2 (DELETED, продължаваме!)
         → клетка 3 (c, намерихме!) → връщаме 30  ✓

Без deleted флаг: клетка 2 щеше да изглежда празна → спираме → "c" не намерен ✗
```
