#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>
#include <map>
#include <unordered_map>
#include <set>
#include <stack>
#include <queue>
#include <utility>
using namespace std;

// ---------------------------------------------------------------
// 1. Типове и променливи
// ---------------------------------------------------------------
void types_demo() {
    cout << "--- Типове ---" << endl;

    int a = 7;
    long long big = 10000000000LL;   // не се събира в int
    double pi = 3.14;
    bool ok = true;
    char c = 'A';                    // единичен символ - единични кавички
    string s = "hello";              // текст - двойни кавички
    const int MAX_N = 100;           // константа - не може да се променя
    auto x = 2.5;                    // компилаторът сам извежда типа (double)

    cout << a << " " << big << " " << pi << " " << ok << " "
         << c << " " << s << " " << MAX_N << " " << x << endl;

    // Целочислено деление - като // в Python, но за положителни числа
    cout << "7 / 2   = " << 7 / 2 << endl;          // 3
    cout << "7 / 2.0 = " << 7 / 2.0 << endl;        // 3.5
    cout << "7 % 3   = " << 7 % 3 << endl;          // 1
    cout << "-7 / 2  = " << -7 / 2 << endl;         // -3 (към нулата!), в Python: -4

    // char е всъщност число
    cout << "'A' + 1 = " << 'A' + 1 << ", (char)('A' + 1) = "
         << (char)('A' + 1) << endl;
    cout << "'7' - '0' = " << '7' - '0' << endl;    // цифрата като число

    cout << "INT_MAX = " << INT_MAX << ", INT_MIN = " << INT_MIN << endl;
}

// ---------------------------------------------------------------
// 2. Условия и цикли
// ---------------------------------------------------------------
void control_flow_demo() {
    cout << "\n--- Условия и цикли ---" << endl;

    int n = 15;
    if (n % 15 == 0) {
        cout << "FizzBuzz" << endl;
    } else if (n % 3 == 0) {         // в Python: elif
        cout << "Fizz" << endl;
    } else {
        cout << n << endl;
    }

    // Тернарен оператор:  условие ? ако_да : ако_не
    cout << (n > 10 ? "голямо" : "малко") << endl;

    // for: инициализация; условие; стъпка
    for (int i = 0; i < 5; i++) cout << i << " ";     // range(5)
    cout << endl;
    for (int i = 10; i > 0; i -= 3) cout << i << " "; // range(10, 0, -3)
    cout << endl;

    // while и do-while (изпълнява тялото поне веднъж)
    int k = 3;
    while (k > 0) { cout << k << " "; k--; }
    cout << endl;
    do { cout << "поне веднъж" << endl; } while (false);

    // range-based for - като "for x in v" в Python
    vector<int> v = {4, 8, 15, 16};
    for (int x : v) cout << x << " ";
    cout << endl;

    // switch - break е задължителен, иначе "пада" в следващия случай
    int day = 2;
    switch (day) {
        case 1: cout << "Понеделник" << endl; break;
        case 2: cout << "Вторник" << endl; break;
        default: cout << "Друг ден" << endl;
    }
}

// ---------------------------------------------------------------
// 3. Функции и предаване на параметри
// ---------------------------------------------------------------
int add(int a, int b) {              // тип на резултата и на всеки параметър
    return a + b;
}

int power(int base, int exp = 2) {   // стойност по подразбиране
    int result = 1;
    for (int i = 0; i < exp; i++) result *= base;
    return result;
}

void by_value(int x) {                   // работи с КОПИЕ
    x = 100;
    cout << "вътре в by_value: x = " << x << endl;
}
void by_ref(int& x) { x = 100; }         // & - работи с ОРИГИНАЛА

int sum_all(const vector<int>& v) {      // const& - без копиране и без промяна
    int total = 0;
    for (int x : v) total += x;
    return total;
}

int factorial(int n) {                   // рекурсията е същата като в Python
    if (n <= 1) return 1;
    return n * factorial(n - 1);
}

void functions_demo() {
    cout << "\n--- Функции ---" << endl;

    cout << "add(2, 3) = " << add(2, 3) << endl;
    cout << "power(3) = " << power(3) << ", power(2, 10) = " << power(2, 10) << endl;

    int n = 1;
    by_value(n);
    cout << "след by_value: n = " << n << endl;   // 1
    by_ref(n);
    cout << "след by_ref:   n = " << n << endl;   // 100

    vector<int> v = {1, 2, 3, 4};
    cout << "sum_all = " << sum_all(v) << endl;
    cout << "factorial(5) = " << factorial(5) << endl;
}

// ---------------------------------------------------------------
// 4. Масиви, vector, string
// ---------------------------------------------------------------
void containers_demo() {
    cout << "\n--- Масиви, vector, string ---" << endl;

    // Масив с фиксиран размер (не знае дължината си!)
    int arr[5] = {5, 1, 4, 2, 8};
    int n = 5;
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    // vector - като list в Python, но с един тип елементи
    vector<int> v = {5, 1, 4, 2, 8};
    v.push_back(3);                          // append
    v.pop_back();                            // pop()
    cout << "size = " << v.size() << ", v[0] = " << v[0]
         << ", front = " << v.front() << ", back = " << v.back() << endl;

    vector<int> zeros(5, 0);                 // [0] * 5
    vector<vector<int>> grid(3, vector<int>(4, 0));   // матрица 3x4 от нули
    grid[1][2] = 7;
    cout << "zeros.size() = " << zeros.size() << ", grid[1][2] = " << grid[1][2] << endl;

    // Сортиране и обръщане - за цял диапазон [begin, end)
    sort(v.begin(), v.end());
    cout << "sorted:   ";
    for (int x : v) cout << x << " ";
    cout << endl;
    reverse(v.begin(), v.end());
    cout << "reversed: ";
    for (int x : v) cout << x << " ";
    cout << endl;

    cout << "min = " << *min_element(v.begin(), v.end())
         << ", max = " << *max_element(v.begin(), v.end()) << endl;

    // string - може да се променя, за разлика от str в Python
    string s = "hello";
    s += " world";
    s[0] = 'H';
    cout << s << ", дължина " << s.size() << ", s[1] = " << s[1]
         << ", substr(0, 5) = " << s.substr(0, 5) << endl;
    cout << "s == \"Hello world\": " << (s == "Hello world") << endl;
}

// ---------------------------------------------------------------
// 5. Указатели и динамична памет
// ---------------------------------------------------------------
void pointers_demo() {
    cout << "\n--- Указатели ---" << endl;

    int x = 42;
    int* p = &x;                 // p съдържа АДРЕСА на x
    cout << "x = " << x << ", *p = " << *p << endl;   // *p - стойността на адреса
    *p = 7;                      // променяме x през указателя
    cout << "след *p = 7: x = " << x << endl;

    int* nothing = nullptr;      // "сочи към нищо" - като None
    cout << "nothing == nullptr: " << (nothing == nullptr) << endl;

    // new - заделя памет в heap; ние отговаряме за delete
    int* heap_value = new int(99);
    cout << "*heap_value = " << *heap_value << endl;
    delete heap_value;           // без delete - изтичане на памет (memory leak)

    int* dyn = new int[3]{1, 2, 3};    // динамичен масив
    cout << "dyn[2] = " << dyn[2] << endl;
    delete[] dyn;                      // за масиви - delete[]
}

// ---------------------------------------------------------------
// 6. struct, class, свързан списък
// ---------------------------------------------------------------
struct Point {                   // struct: всичко е public по подразбиране
    int x, y;
    Point(int x, int y) : x(x), y(y) {}          // конструктор с initializer list
    int manhattan() const { return abs(x) + abs(y); }   // const - не променя обекта
};

struct Node {                    // възел на свързан списък
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class Counter {                  // class: всичко е private по подразбиране
private:
    int count;
public:
    Counter() : count(0) {}
    void increment() { count++; }
    int get() const { return count; }
    ~Counter() { cout << "[деструктор на Counter]" << endl; }   // вика се при унищожаване
};

void structs_demo() {
    cout << "\n--- struct и class ---" << endl;

    Point p(3, -4);
    cout << "p = (" << p.x << ", " << p.y << "), manhattan = " << p.manhattan() << endl;

    Point* pp = &p;
    cout << "през указател: pp->x = " << pp->x << " (същото като (*pp).x)" << endl;

    // Свързан списък 1 -> 2 -> 3
    Node* head = new Node(1);
    head->next = new Node(2);
    head->next->next = new Node(3);

    cout << "списък: ";
    for (Node* cur = head; cur != nullptr; cur = cur->next)
        cout << cur->data << " ";
    cout << endl;

    while (head != nullptr) {    // освобождаваме всеки възел
        Node* tmp = head;
        head = head->next;
        delete tmp;
    }

    Counter c;
    c.increment();
    c.increment();
    cout << "counter = " << c.get() << endl;
}   // тук c излиза от обхват и деструкторът се вика автоматично

// ---------------------------------------------------------------
// 7. STL контейнери
// ---------------------------------------------------------------
struct Item {
    string name;
    int weight;
};

void stl_demo() {
    cout << "\n--- STL ---" << endl;

    // pair
    pair<int, string> pr = {1, "one"};
    cout << pr.first << " " << pr.second << endl;

    // unordered_map / map - като dict
    unordered_map<string, int> ages;
    ages["Ana"] = 20;
    ages["Boris"] = 22;
    cout << "ages[\"Ana\"] = " << ages["Ana"]
         << ", съдържа Boris: " << (ages.count("Boris") > 0)
         << ", съдържа Vera: " << (ages.count("Vera") > 0) << endl;

    map<string, int> sorted_ages(ages.begin(), ages.end());   // подредена по ключ
    for (auto& [name, age] : sorted_ages)                     // структурирано свързване
        cout << name << ":" << age << " ";
    cout << endl;

    // set - уникални елементи
    set<int> st = {3, 1, 3, 2, 1};
    cout << "set: ";
    for (int x : st) cout << x << " ";
    cout << "(size " << st.size() << ")" << endl;

    // stack и queue
    stack<int> stk;
    stk.push(1); stk.push(2); stk.push(3);
    cout << "stack top = " << stk.top() << endl;
    stk.pop();                                   // pop() НЕ връща стойност

    queue<int> q;
    q.push(1); q.push(2); q.push(3);
    cout << "queue front = " << q.front() << ", back = " << q.back() << endl;
    q.pop();

    // priority_queue - по подразбиране max-heap
    priority_queue<int> maxh;
    maxh.push(5); maxh.push(1); maxh.push(9);
    cout << "max-heap top = " << maxh.top() << endl;

    priority_queue<int, vector<int>, greater<int>> minh;   // min-heap
    minh.push(5); minh.push(1); minh.push(9);
    cout << "min-heap top = " << minh.top() << endl;

    // Ламбда израз (компаратор) - като lambda в Python, но с тяло като функция
    vector<Item> items = {{"a", 5}, {"b", 2}, {"c", 9}};
    sort(items.begin(), items.end(),
         [](const Item& l, const Item& r) { return l.weight < r.weight; });
    cout << "по тегло: ";
    for (const Item& it : items) cout << it.name << "(" << it.weight << ") ";
    cout << endl;

    swap(items[0], items[2]);
    cout << "след swap първият е: " << items[0].name << endl;
    cout << "min(3, 8) = " << min(3, 8) << ", max(3, 8) = " << max(3, 8) << endl;
}

// ---------------------------------------------------------------
// 8. Вход от потребителя
// ---------------------------------------------------------------
void input_demo() {
    cout << "\n--- Вход ---" << endl;
    cout << "Въведете две числа: ";
    int a, b;
    if (cin >> a >> b)                       // като map(int, input().split())
        cout << a << " + " << b << " = " << a + b << endl;
    else
        cout << "(няма вход - пропускаме)" << endl;
}

int main() {
    types_demo();
    control_flow_demo();
    functions_demo();
    containers_demo();
    pointers_demo();
    structs_demo();
    stl_demo();
    input_demo();
    return 0;
}
