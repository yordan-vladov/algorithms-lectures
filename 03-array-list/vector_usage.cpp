#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() {
    // Инициализация
    vector<int> v = {10, 20, 30};
    cout << "Начален вектор: ";
    for (int x : v) cout << x << " ";
    cout << "\nsize=" << v.size() << ", capacity=" << v.capacity() << endl;

    // push_back - добавяне в края
    v.push_back(40);
    v.push_back(50);
    cout << "\nСлед push_back(40), push_back(50): ";
    for (int x : v) cout << x << " ";
    cout << "\nsize=" << v.size() << ", capacity=" << v.capacity() << endl;

    // pop_back - премахване от края
    v.pop_back();
    cout << "\nСлед pop_back(): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Достъп по индекс
    cout << "\nv[0]=" << v[0] << ", v.front()=" << v.front()
         << ", v.back()=" << v.back() << endl;

    // insert - вмъкване на позиция
    v.insert(v.begin() + 1, 99);
    cout << "\nСлед insert(1, 99): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // erase - изтриване на позиция
    v.erase(v.begin() + 1);
    cout << "\nСлед erase(1): ";
    for (int x : v) cout << x << " ";
    cout << endl;

    // Различни начини за инициализация
    cout << "\n--- Различни начини за инициализация ---" << endl;
    vector<int> a;             // Празен вектор
    vector<int> b(5);          // 5 нули
    vector<int> c(5, 42);      // 5 пъти 42
    vector<int> d = {1, 2, 3}; // С конкретни стойности
    vector<int> e(d);          // Копие на d

    cout << "b (5 нули): ";
    for (int x : b) cout << x << " ";
    cout << endl;
    cout << "c (5 пъти 42): ";
    for (int x : c) cout << x << " ";
    cout << endl;

    // Сортиране
    vector<int> nums = {50, 10, 40, 20, 30};
    cout << "\nПреди sort: ";
    for (int x : nums) cout << x << " ";
    sort(nums.begin(), nums.end());
    cout << "\nСлед sort:  ";
    for (int x : nums) cout << x << " ";
    cout << endl;

    // empty и clear
    cout << "\nv.empty() = " << v.empty() << endl;
    v.clear();
    cout << "След clear(), v.empty() = " << v.empty() << endl;

    return 0;
}
