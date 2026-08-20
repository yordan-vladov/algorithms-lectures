#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
    Node(int value) : data(value), next(nullptr) {}
};

class LinkedList {
private:
    Node* head;
    int size;

    void clear() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

public:
    LinkedList() : head(nullptr), size(0) {}

    ~LinkedList() {
        clear();
    }

    void push_front(int value) {
        Node* new_node = new Node(value);
        new_node->next = head;
        head = new_node;
        size++;
    }

    void push_back(int value) {
        Node* new_node = new Node(value);
        if (head == nullptr) {
            head = new_node;
        } else {
            Node* current = head;
            while (current->next != nullptr)
                current = current->next;
            current->next = new_node;
        }
        size++;
    }

    void insert(int index, int value) {
        if (index == 0) {
            push_front(value);
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1; i++)
            current = current->next;
        Node* new_node = new Node(value);
        new_node->next = current->next;
        current->next = new_node;
        size++;
    }

    void remove(int index) {
        if (index == 0) {
            Node* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }
        Node* current = head;
        for (int i = 0; i < index - 1; i++)
            current = current->next;
        Node* to_delete = current->next;
        current->next = to_delete->next;
        delete to_delete;
        size--;
    }

    int get(int index) const {
        Node* current = head;
        for (int i = 0; i < index; i++)
            current = current->next;
        return current->data;
    }

    bool contains(int value) const {
        Node* current = head;
        while (current != nullptr) {
            if (current->data == value) return true;
            current = current->next;
        }
        return false;
    }

    void reverse() {
        Node* prev = nullptr;
        Node* current = head;
        while (current != nullptr) {
            Node* next = current->next;
            current->next = prev;
            prev = current;
            current = next;
        }
        head = prev;
    }

    int get_size() const { return size; }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            cout << current->data;
            if (current->next != nullptr) cout << " -> ";
            current = current->next;
        }
        cout << " -> NULL" << endl;
    }
};

int main() {
    LinkedList list;

    cout << "--- push_back ---" << endl;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.print();  // 10 -> 20 -> 30 -> NULL

    cout << "\n--- push_front(5) ---" << endl;
    list.push_front(5);
    list.print();  // 5 -> 10 -> 20 -> 30 -> NULL

    cout << "\n--- insert(2, 99) ---" << endl;
    list.insert(2, 99);
    list.print();  // 5 -> 10 -> 99 -> 20 -> 30 -> NULL

    cout << "\n--- remove(2) ---" << endl;
    list.remove(2);
    list.print();  // 5 -> 10 -> 20 -> 30 -> NULL

    cout << "\n--- get(1) ---" << endl;
    cout << "list.get(1) = " << list.get(1) << endl;  // 10

    cout << "\n--- contains ---" << endl;
    cout << "contains(20) = " << list.contains(20) << endl;  // 1
    cout << "contains(99) = " << list.contains(99) << endl;  // 0

    cout << "\n--- reverse ---" << endl;
    list.reverse();
    list.print();  // 30 -> 20 -> 10 -> 5 -> NULL

    cout << "\nsize = " << list.get_size() << endl;

    return 0;
}
