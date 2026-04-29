#include <iostream>
#include <list>
using namespace std;

int main() {
    // Инициализация
    list<int> l = {10, 20, 30};
    cout << "Начален списък: ";
    for (int x : l) cout << x << " ";
    cout << endl;

    // push_back / push_front
    l.push_back(40);
    l.push_front(5);
    cout << "\nСлед push_back(40) и push_front(5): ";
    for (int x : l) cout << x << " ";
    cout << endl;

    // pop_back / pop_front
    l.pop_back();
    l.pop_front();
    cout << "\nСлед pop_back() и pop_front(): ";
    for (int x : l) cout << x << " ";
    cout << endl;

    // front / back
    cout << "\nfront=" << l.front() << ", back=" << l.back() << endl;

    // insert на позиция 1 (чрез итератор)
    auto it = l.begin();
    advance(it, 1);
    l.insert(it, 99);
    cout << "\nСлед insert(1, 99): ";
    for (int x : l) cout << x << " ";
    cout << endl;

    // erase на позиция 1
    it = l.begin();
    advance(it, 1);
    l.erase(it);
    cout << "\nСлед erase(1): ";
    for (int x : l) cout << x << " ";
    cout << endl;

    // Итерация с итератор
    cout << "\n--- Итерация с итератор ---" << endl;
    for (auto iter = l.begin(); iter != l.end(); ++iter)
        cout << *iter << " ";
    cout << endl;

    // size / empty / clear
    cout << "\nsize=" << l.size() << ", empty=" << l.empty() << endl;
    l.clear();
    cout << "След clear(), empty=" << l.empty() << endl;

    // std::list поддържа O(1) вмъкване при известен итератор
    cout << "\n--- Демо: O(1) вмъкване в средата ---" << endl;
    list<int> nums = {1, 2, 3, 4, 5};
    auto mid = nums.begin();
    advance(mid, 2);           // итератор сочи към 3
    nums.insert(mid, 99);      // вмъкване без преместване на елементи
    for (int x : nums) cout << x << " ";
    cout << endl;

    return 0;
}
