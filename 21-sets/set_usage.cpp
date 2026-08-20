#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include <iterator>
#include <string>
using namespace std;

int main() {
    cout << "--- std::set (сортирано) ---" << endl;
    set<int> s = {5, 1, 9, 3, 1};  // дубликатът "1" се игнорира

    for (int x : s)
        cout << x << " ";  // 1 3 5 9  (сортирано)
    cout << endl;

    s.insert(7);
    s.erase(1);
    cout << "size = " << s.size() << endl;               // 4
    cout << "count(9) = " << s.count(9) << endl;          // 1
    cout << "min = " << *s.begin() << ", max = " << *s.rbegin() << endl;  // 3, 9

    cout << "\n--- std::unordered_set (без ред, O(1) средно) ---" << endl;
    unordered_set<string> visited;
    visited.insert("A");
    visited.insert("B");
    visited.insert("A");  // дубликат - игнорира се

    cout << "size = " << visited.size() << endl;          // 2
    cout << "count(A) = " << visited.count("A") << endl;   // 1

    cout << "\n--- std::multiset (позволява дубликати) ---" << endl;
    multiset<int> ms = {3, 1, 3, 2, 3};
    for (int x : ms)
        cout << x << " ";  // 1 2 3 3 3
    cout << endl;
    cout << "count(3) = " << ms.count(3) << endl;  // 3

    ms.erase(ms.find(3));  // трие само ЕДНО срещане
    cout << "след erase(find(3)), count(3) = " << ms.count(3) << endl;  // 2

    cout << "\n--- обединение, сечение, разлика ---" << endl;
    set<int> a = {1, 2, 3, 4};
    set<int> b = {3, 4, 5, 6};
    vector<int> result;

    set_union(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    cout << "union: ";
    for (int x : result) cout << x << " ";  // 1 2 3 4 5 6
    cout << endl;

    result.clear();
    set_intersection(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    cout << "intersection: ";
    for (int x : result) cout << x << " ";  // 3 4
    cout << endl;

    result.clear();
    set_difference(a.begin(), a.end(), b.begin(), b.end(), back_inserter(result));
    cout << "difference (a - b): ";
    for (int x : result) cout << x << " ";  // 1 2
    cout << endl;

    cout << "\n--- премахване на дубликати чрез set ---" << endl;
    vector<int> nums = {4, 1, 4, 2, 1, 3};
    set<int> unique_nums(nums.begin(), nums.end());
    cout << "уникални елементи: " << unique_nums.size() << endl;  // 4
    for (int x : unique_nums) cout << x << " ";  // 1 2 3 4
    cout << endl;

    return 0;
}
