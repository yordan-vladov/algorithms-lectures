#include <iostream>
#include <unordered_map>
#include <map>
#include <string>
using namespace std;

int main() {
    // Инициализация
    unordered_map<string, int> ages;

    // Вмъкване
    ages["alice"] = 25;
    ages["bob"]   = 30;
    ages["carol"] = 27;
    ages.insert({"dave", 22});

    cout << "--- Достъп по ключ ---" << endl;
    cout << "alice: " << ages["alice"] << endl;       // 25
    cout << "bob:   " << ages.at("bob") << endl;      // 30 (хвърля изключение ако липсва)

    // Актуализиране
    ages["bob"] = 31;
    cout << "bob след актуализиране: " << ages["bob"] << endl;  // 31

    // Проверка за съществуване - безопасен начин
    cout << "\n--- find (безопасен достъп) ---" << endl;
    auto it = ages.find("carol");
    if (it != ages.end())
        cout << "carol: " << it->second << endl;

    // ОПАСНО: ages["eve"] добавя eve:0 ако не съществува!
    auto it2 = ages.find("eve");
    if (it2 == ages.end())
        cout << "eve не е намерена" << endl;

    // count - проверка за съществуване
    cout << "\n--- count ---" << endl;
    cout << "count(\"alice\") = " << ages.count("alice") << endl;  // 1
    cout << "count(\"eve\")   = " << ages.count("eve")   << endl;  // 0

    // erase - изтриване
    ages.erase("alice");
    cout << "\nСлед erase(\"alice\"), count = "
         << ages.count("alice") << endl;  // 0

    // Итерация (редът не е гарантиран)
    cout << "\n--- Итерация (без гарантиран ред) ---" << endl;
    for (auto& [key, value] : ages)
        cout << key << ": " << value << endl;

    // size / empty
    cout << "\nsize=" << ages.size() << ", empty=" << ages.empty() << endl;

    // Брой срещания на думи (честотна таблица)
    cout << "\n--- Брой срещания на думи ---" << endl;
    string words[] = {"ябълка", "банан", "ябълка", "череша", "банан", "ябълка"};
    unordered_map<string, int> freq;
    for (const string& w : words)
        freq[w]++;
    for (auto& [word, count] : freq)
        cout << word << ": " << count << endl;

    // std::map - сортирани ключове, O(log n)
    cout << "\n--- std::map (сортирани ключове) ---" << endl;
    map<string, int> sorted_ages = {{"carol", 27}, {"alice", 25}, {"bob", 30}};
    for (auto& [key, value] : sorted_ages)
        cout << key << ": " << value << endl;  // изходът е сортиран по ключ

    return 0;
}
