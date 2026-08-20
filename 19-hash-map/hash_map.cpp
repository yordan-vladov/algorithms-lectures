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
        for (char c : key)
            h = (h * 31 + c) % capacity;
        return h;
    }

    void rehash() {
        int new_capacity = capacity * 2;
        vector<Entry> old_table = table;

        table.assign(new_capacity, Entry());
        capacity = new_capacity;
        size = 0;

        for (auto& e : old_table) {
            if (e.occupied && !e.deleted)
                insert(e.key, e.value);
        }
    }

public:
    HashMap(int initial_capacity = 8)
        : capacity(initial_capacity), size(0) {
        table.assign(capacity, Entry());
    }

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

    bool get(const string& key, int& result) const {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (!table[pos].occupied && !table[pos].deleted)
                return false;

            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key) {
                result = table[pos].value;
                return true;
            }
        }
        return false;
    }

    bool remove(const string& key) {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (!table[pos].occupied && !table[pos].deleted)
                return false;

            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key) {
                table[pos].deleted  = true;
                table[pos].occupied = false;
                size--;
                return true;
            }
        }
        return false;
    }

    bool contains(const string& key) const {
        int result;
        return get(key, result);
    }

    vector<string> keys() const {
        vector<string> result;
        for (auto& e : table)
            if (e.occupied && !e.deleted)
                result.push_back(e.key);
        return result;
    }

    int get_size() const { return size; }

    double load_factor() const {
        return (double)size / capacity;
    }
};

int main() {
    HashMap map(10);

    cout << "--- insert ---" << endl;
    map.insert("alice", 25);
    map.insert("bob",   30);
    map.insert("carol", 27);
    map.insert("dave",  22);

    int age;
    cout << "\n--- get ---" << endl;
    if (map.get("bob", age))
        cout << "bob: " << age << endl;      // bob: 30
    if (map.get("carol", age))
        cout << "carol: " << age << endl;    // carol: 27

    cout << "\n--- Актуализиране (insert на съществуващ ключ) ---" << endl;
    map.insert("bob", 31);
    map.get("bob", age);
    cout << "bob след актуализиране: " << age << endl;  // 31

    cout << "\n--- contains ---" << endl;
    cout << "contains(\"alice\") = " << map.contains("alice") << endl;  // 1
    cout << "contains(\"eve\")   = " << map.contains("eve")   << endl;  // 0

    cout << "\n--- remove ---" << endl;
    map.remove("alice");
    cout << "contains(\"alice\") след remove = "
         << map.contains("alice") << endl;  // 0

    cout << "\n--- keys ---" << endl;
    for (const string& k : map.keys())
        cout << k << " ";
    cout << endl;

    cout << "\nsize=" << map.get_size()
         << ", load_factor=" << map.load_factor() << endl;

    return 0;
}
