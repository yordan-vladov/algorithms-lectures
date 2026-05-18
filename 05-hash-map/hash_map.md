# HashMap

---

## Какво ще научим днес?

- Проблемът с търсенето в масиви
- Какво е хеш функция
- Какво е HashMap
- Колизии и методи за разрешаването им
- Примерна имплементация на C++
- Основни операции и тяхната сложност
- `unordered_map` класът и неговите основни операции

---

## Ограниченията на традиционните масиви

- Масивите ни дават **O(1)** достъп — но само чрез **цели неотрицателни числа**

```
arr[0] = 10   ✓
arr[3] = 42   ✓
arr["alice"]  ✗  // не е валиден индекс
arr[-1]       ✗  // не е валиден индекс
```

- Какво ако искаме да индексираме по **произволен ключ**?
  - Низ: `"alice"`, `"product_id"`
  - Дата: `"2024-01-15"`
  - Дори отрицателно число: `-5`

---

## Асоциативен масив

- **Асоциативен масив** = структура, която свързва произволни **ключове** със **стойности**
- Работи като речник: думата (ключ) → значение (стойност)

```
"alice"  →  25      // string ключ
"bob"    →  30
"carol"  →  27
```

- Основни операции:
  - `insert(key, value)` — добавя двойка
  - `get(key)` → стойността по ключ
  - `remove(key)` — изтрива двойката

- Целта: всички операции в **O(1)** средно

---

## Идеята зад HashMap

- Използваме масив за пазене да стойностите
- Използваме **ключ (key)** за директен достъп до стойност
- **Хеш функция** превръща ключа в индекс на масив


![hash_map](https://media.geeksforgeeks.org/wp-content/uploads/20251025124952963087/hashmap.webp)


```
// за двойка ("alice", "bob")
key = "alice"
hash("alice") = 3

масив: [ _ , _ , _ , "bob", _ , _ ]
                      ↑
                 индекс 3
```

- Достъпът е директен - **O(1)** средно!

---

## Какво е хеш функция?

- **Хеш функция** `h(key)` → индекс
  - Приема произволен ключ
  - Връща цяло число (индекс в масива)
  - Един и същи ключ **винаги** дава един и същи резултат

```cpp
int hash(int key, int capacity) {
    return key % capacity;
}
```

```
hash(10, 7) = 3
hash(17, 7) = 3  ← колизия!
hash(24, 7) = 3  ← колизия!
```

---

## Какво е HashMap?

- **HashMap** е структура от данни тип **ключ → стойност**
  - Съхранява двойки `(key, value)`
  - Хеш функцията определя **къде** се пази двойката
  - Позволява O(1) средно за търсене, вмъкване, изтриване

```
insert("alice", 25)
insert("bob",   30)
insert("carol", 27)

get("bob") → 30
```

---

## Структура на HashMap

```cpp
struct Entry {
    string key;
    int    value;
    bool   occupied;

    Entry() : occupied(false) {}
};

class HashMap {
private:
    vector<Entry> table;
    int capacity;
    int size;
    ...
};
```

- Масив от `Entry` - всяка клетка е или заета, или свободна

---

## Колизии

- **Колизия** - два различни ключа дават един и същ индекс

```
hash("alice", 5) = 2
hash("eve",   5) = 2  ← колизия с "alice"!

масив: [ _ , _ , "alice"/"eve"?? , _ , _ ]
```

- Колизиите са **неизбежни** при достатъчно ключове
- Трябват ни стратегии за разрешаване

---

## Разрешаване на колизии - Chaining

- Всяка клетка пази **свързан списък** от двойки

```
индекс 2: → ("alice", 25) → ("eve", 22) → NULL
индекс 4: → ("bob", 30) → NULL
```

```cpp
vector<list<pair<string, int>>> table;
```

- Лесно за имплементация
- При много колизии - O(n) в най-лошия случай

---

## Разрешаване на колизии - Open Addressing

- При колизия търсим **следващата свободна клетка**

**Linear Probing:**
```
hash("eve", 5) = 2, но 2 е заето
→ пробваме 3 → свободно!

[ _ , _ , "alice" , "eve" , _ ]
```

```cpp
int probe(int hash, int i, int capacity) {
    return (hash + i) % capacity;
}
```

---

## Примерна имплементация - структура

```cpp
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class HashMap {
private:
    struct Entry {
        string key;
        int value;
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

## Вмъкване - insert

```cpp
    void insert(const string& key, int value) {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (!table[pos].occupied || table[pos].deleted) {
                table[pos].key      = key;
                table[pos].value    = value;
                table[pos].occupied = true;
                table[pos].deleted  = false;
                size++;
                return;
            }

            if (table[pos].key == key) {  // актуализиране
                table[pos].value = value;
                return;
            }
        }
    }
```

---

## Вмъкване - визуализация

```
capacity = 7, insert("alice", 25), insert("eve", 22)

hash("alice") = 2
hash("eve")   = 2  ← колизия!

Стъпки за "eve":
  pos 2 → заето ("alice") → продължаваме
  pos 3 → свободно → вмъкваме "eve"

[ _ , _ , "alice":25 , "eve":22 , _ , _ , _ ]
```

---

## Търсене - get

```cpp
    bool get(const string& key, int& result) const {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (!table[pos].occupied && !table[pos].deleted)
                return false;  // празна клетка → не съществува

            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key) {
                result = table[pos].value;
                return true;
            }
        }
        return false;
    }
```

---

## Изтриване - remove

```cpp
    bool remove(const string& key) {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (!table[pos].occupied && !table[pos].deleted)
                return false;

            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key) {
                table[pos].deleted  = true;  // "мързеливо" изтриване
                table[pos].occupied = false;
                size--;
                return true;
            }
        }
        return false;
    }
};
```

- Маркираме като изтрито, не почистваме - иначе ще счупим probing веригата

---

## Пример за употреба

```cpp
int main() {
    HashMap map(10);

    map.insert("alice", 25);
    map.insert("bob",   30);
    map.insert("carol", 27);

    int age;
    if (map.get("bob", age))
        cout << "bob: " << age << endl;  // bob: 30

    map.insert("bob", 31);               // актуализиране
    map.get("bob", age);
    cout << "bob: " << age << endl;      // bob: 31

    map.remove("alice");
    cout << map.get("alice", age);       // 0 (не е намерен)
}
```

---

## Сложност на операциите

| Операция    | Средно | Най-лош случай | Бележка                         |
| ----------- | ------ | -------------- | ------------------------------- |
| Вмъкване    | O(1)   | O(n)           | При много колизии               |
| Търсене     | O(1)   | O(n)           | При много колизии               |
| Изтриване   | O(1)   | O(n)           | При много колизии               |
| Обхождане   | O(n)   | O(n)           | Минаваме през целия масив       |

- **O(1) средно** се гарантира при нисък **load factor**

---

## Load Factor

- **Load factor** = `size / capacity`
- Мерка за запълненост на таблицата

```
capacity = 10, size = 7
load factor = 0.7  ← приемливо

capacity = 10, size = 9
load factor = 0.9  ← твърде много колизии!
```

- При load factor > 0.7–0.75 → **rehashing**: удвояваме капацитета и прехвърляме всички елементи

---

## Rehashing

```cpp
void rehash() {
    int new_capacity = capacity * 2;
    vector<Entry> old_table = table;

    table.assign(new_capacity, Entry());
    capacity = new_capacity;
    size = 0;

    for (auto& e : old_table) {
        if (e.occupied && !e.deleted) {
            insert(e.key, e.value);
        }
    }
}
```

- Rehashing е **O(n)** но се случва рядко → амортизирано O(1)

---


## Оптимизация: автоматичен rehashing при insert

```cpp
    void insert(const string& key, int value) {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (!table[pos].occupied || table[pos].deleted) {
                table[pos].key      = key;
                table[pos].value    = value;
                table[pos].occupied = true;
                table[pos].deleted  = false;
                size++;
                if ((double)size / capacity > 0.75)
                    rehash();
                return;
            }

            if (table[pos].key == key) {
                table[pos].value = value;
                return;
            }
        }
    }
```

- Проверяваме load factor след всяко вмъкване
- При надхвърляне на прага → автоматично rehashing

---

## `std::unordered_map` - стандартната имплементация

- C++ предоставя `std::unordered_map` - HashMap с chaining
- Включва се с `#include <unordered_map>`

```cpp
#include <iostream>
#include <unordered_map>
using namespace std;

int main() {
    unordered_map<string, int> ages;

    ages["alice"] = 25;
    ages["bob"]   = 30;
    ages["carol"] = 27;

    cout << ages["bob"] << endl;  // 30
}
```

---

## Основни операции на `std::unordered_map`

```cpp
unordered_map<string, int> m;

m["alice"] = 25;                // вмъкване / актуализиране
m.insert({"bob", 30});         // алтернативен синтаксис

cout << m["alice"];            // достъп по ключ → 25
cout << m.at("alice");         // същото, но хвърля изключение ако липсва

m.erase("alice");              // изтриване

if (m.count("bob") > 0)        // проверка за съществуване
    cout << "bob exists";

cout << m.size();              // брой елементи
```

---

## Итерация

```cpp
unordered_map<string, int> ages = {
    {"alice", 25}, {"bob", 30}, {"carol", 27}
};

// Итерация по всички двойки
for (auto& [key, value] : ages) {
    cout << key << ": " << value << endl;
}

// С итератор
for (auto it = ages.begin(); it != ages.end(); ++it) {
    cout << it->first << ": " << it->second << endl;
}
```

- Редът на итерация **не е гарантиран** - използвайте `map` ако е нужен сортиран ред

---

## Полезни методи на `std::unordered_map`

| Метод               | Описание                                        |
| ------------------- | ----------------------------------------------- |
| `m[key] = val`      | Вмъква или актуализира стойността               |
| `m.at(key)`         | Достъп с проверка (хвърля `out_of_range`)       |
| `m.insert({k, v})`  | Вмъква двойка (само ако ключът не съществува)   |
| `m.erase(key)`      | Изтрива по ключ                                 |
| `m.count(key)`      | 1 ако съществува, 0 ако не                      |
| `m.find(key)`       | Итератор към елемента или `m.end()`             |
| `m.size()`          | Брой елементи                                   |
| `m.empty()`         | Проверка дали е празен                          |
| `m.clear()`         | Изтрива всички елементи                         |

---

## `find` - безопасен достъп

```cpp
unordered_map<string, int> ages = {{"alice", 25}};

// ОПАСНО: m["carol"] добавя carol:0 ако не съществува!
cout << ages["carol"];  // 0 и добавя {carol: 0}

// БЕЗОПАСНО: проверяваме преди достъп
auto it = ages.find("carol");
if (it != ages.end()) {
    cout << it->second;
} else {
    cout << "carol не е намерена";
}
```

---

## HashMap срещу сортиран `map`

| Операция        | `unordered_map` | `map`        |
| --------------- | --------------- | ------------ |
| Вмъкване        | **O(1)** ср.    | O(log n)     |
| Търсене         | **O(1)** ср.    | O(log n)     |
| Изтриване       | **O(1)** ср.    | O(log n)     |
| Наредени ключове| Не              | **Да**       |
| Памет           | По-голяма       | По-малка     |

- Използвайте `unordered_map` за бързодействие
- Използвайте `map` ако се нуждаете от сортиран ред на ключовете

---

## Кога да използваме HashMap?

**HashMap / `unordered_map`** - когато:
- Търсим по **ключ** (не по позиция)
- Нуждаем се от O(1) за вмъкване, търсене, изтриване
- Броим срещания (честоти, хистограми)
- Кешираме резултати (memoization)

**Примери:**
- Речник: дума → превод
- Телефонен указател: име → номер
- Брой думи в текст

---

## Въпроси

1. Защо хеш функцията трябва да е **детерминирана**?
2. Каква е разликата между **chaining** и **open addressing**?
3. Защо използваме "мързеливо" изтриване при open addressing?
4. Кога е O(n) вмъкването в HashMap?
5. Защо `m["key"]` може да е опасно?

---

## Домашна работа

- Разширете примерната `HashMap` имплементация с:
    1. Метод `contains(key)` - проверка за съществуване
    2. Метод `keys()` - връща вектор с всички ключове
- **Бонус:** Имплементирайте HashMap с chaining (свързани списъци)

---

## Обобщение

- HashMap съхранява **двойки ключ-стойност** с O(1) достъп
- **Хеш функцията** превръща ключа в индекс на масив
- **Колизиите** се разрешават чрез chaining или open addressing
- **Load factor** определя кога да правим rehashing
- `std::unordered_map` е готовата имплементация в C++
- Изборът между `unordered_map` и `map` зависи от нуждата от наредени ключове
