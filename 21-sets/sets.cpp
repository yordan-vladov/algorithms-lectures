#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
using namespace std;

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
    int count;

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
        count = 0;

        for (auto& e : old_table)
            if (e.occupied && !e.deleted)
                insert(e.key);
    }

public:
    HashSet(int initial_capacity = 8)
        : capacity(initial_capacity), count(0) {
        table.assign(capacity, Entry());
    }

    void insert(const string& key) {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key)
                return;  // вече съществува

            if (!table[pos].occupied || table[pos].deleted) {
                table[pos].key      = key;
                table[pos].occupied = true;
                table[pos].deleted  = false;
                count++;
                if ((double)count / capacity > 0.75)
                    rehash();
                return;
            }
        }
    }

    bool contains(const string& key) const {
        int idx = hash(key);

        for (int i = 0; i < capacity; i++) {
            int pos = (idx + i) % capacity;

            if (!table[pos].occupied && !table[pos].deleted)
                return false;

            if (table[pos].occupied && !table[pos].deleted
                    && table[pos].key == key)
                return true;
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
                count--;
                return true;
            }
        }
        return false;
    }

    HashSet set_union(const HashSet& other) const {
        HashSet result(*this);
        for (auto& e : other.table)
            if (e.occupied && !e.deleted)
                result.insert(e.key);
        return result;
    }

    int size() const { return count; }

    vector<string> keys() const {
        vector<string> result;
        for (auto& e : table)
            if (e.occupied && !e.deleted)
                result.push_back(e.key);
        return result;
    }
};

vector<int> find_duplicates(const vector<int>& arr) {
    unordered_set<int> seen;
    unordered_set<int> duplicates;
    for (int x : arr) {
        if (seen.count(x))
            duplicates.insert(x);
        else
            seen.insert(x);
    }
    return vector<int>(duplicates.begin(), duplicates.end());
}

int main() {
    cout << "--- insert / contains ---" << endl;
    HashSet set1;
    set1.insert("alice");
    set1.insert("bob");
    set1.insert("carol");
    set1.insert("alice");  // дубликат - игнорира се

    cout << "size = " << set1.size() << endl;  // 3
    cout << "contains(bob) = " << set1.contains("bob") << endl;    // 1
    cout << "contains(dave) = " << set1.contains("dave") << endl;  // 0

    cout << "\n--- remove ---" << endl;
    set1.remove("alice");
    cout << "contains(alice) след remove = " << set1.contains("alice") << endl;  // 0
    cout << "size = " << set1.size() << endl;  // 2

    cout << "\n--- set_union ---" << endl;
    HashSet set2;
    set2.insert("carol");
    set2.insert("dave");

    HashSet unioned = set1.set_union(set2);
    cout << "union size = " << unioned.size() << endl;  // 3 (bob, carol, dave)
    for (auto& k : unioned.keys()) cout << k << " ";
    cout << endl;

    cout << "\n--- find_duplicates ---" << endl;
    vector<int> nums = {4, 1, 4, 2, 1, 3, 4};
    for (int x : find_duplicates(nums)) cout << x << " ";
    cout << endl;

    return 0;
}
