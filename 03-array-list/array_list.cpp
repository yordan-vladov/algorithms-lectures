#include <iostream>
using namespace std;

class ArrayList {
private:
    int* data;
    int size;
    int capacity;

    void resize() {
        capacity *= 2;
        int* new_data = new int[capacity];
        for (int i = 0; i < size; i++)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
    }

    void shrink() {
        capacity /= 2;
        int* new_data = new int[capacity];
        for (int i = 0; i < size; i++)
            new_data[i] = data[i];
        delete[] data;
        data = new_data;
    }

public:
    ArrayList() : size(0), capacity(2) {
        data = new int[capacity];
    }

    ~ArrayList() {
        delete[] data;
    }

    void push_back(int value) {
        if (size == capacity)
            resize();
        data[size++] = value;
    }

    int pop_back() {
        int value = data[--size];
        if (size > 0 && size <= capacity / 4)
            shrink();
        return value;
    }

    void insert(int index, int value) {
        if (size == capacity)
            resize();
        for (int i = size; i > index; i--)
            data[i] = data[i - 1];
        data[index] = value;
        size++;
    }

    void remove(int index) {
        for (int i = index; i < size - 1; i++)
            data[i] = data[i + 1];
        size--;
        if (size > 0 && size <= capacity / 4)
            shrink();
    }

    int get(int index) const {
        return data[index];
    }

    int get_size() const {
        return size;
    }

    int get_capacity() const {
        return capacity;
    }

    void print() const {
        cout << "[";
        for (int i = 0; i < size; i++) {
            cout << data[i];
            if (i < size - 1) cout << ", ";
        }
        cout << "]" << endl;
    }
};

int main() {
    ArrayList list;

    cout << "--- push_back ---" << endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    list.print();  // [10, 20, 30, 40, 50]

    cout << "size=" << list.get_size()
         << ", capacity=" << list.get_capacity() << endl;

    cout << "\n--- get(2) ---" << endl;
    cout << "list.get(2) = " << list.get(2) << endl;  // 30

    cout << "\n--- insert(2, 99) ---" << endl;
    list.insert(2, 99);
    list.print();  // [10, 20, 99, 30, 40, 50]

    cout << "\n--- remove(2) ---" << endl;
    list.remove(2);
    list.print();  // [10, 20, 30, 40, 50]

    cout << "\n--- pop_back ---" << endl;
    cout << "Премахнато: " << list.pop_back() << endl;  // 50
    list.print();  // [10, 20, 30, 40]

    cout << "\n--- Многократни pop_back (shrink демо) ---" << endl;
    cout << "Преди: size=" << list.get_size()
         << ", capacity=" << list.get_capacity() << endl;
    list.pop_back();
    list.pop_back();
    list.pop_back();
    cout << "След: size=" << list.get_size()
         << ", capacity=" << list.get_capacity() << endl;
    list.print();

    return 0;
}
