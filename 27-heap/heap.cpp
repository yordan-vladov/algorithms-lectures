#include <iostream>
#include <vector>
using namespace std;

class MinHeap {
private:
    vector<int> data;

    void sift_up(int i) {
        while (i > 0) {
            int parent = (i - 1) / 2;
            if (data[parent] <= data[i]) break;
            swap(data[i], data[parent]);
            i = parent;
        }
    }

    void sift_down(int i) {
        int n = data.size();
        while (true) {
            int left = 2 * i + 1, right = 2 * i + 2, smallest = i;
            if (left  < n && data[left]  < data[smallest]) smallest = left;
            if (right < n && data[right] < data[smallest]) smallest = right;
            if (smallest == i) break;
            swap(data[i], data[smallest]);
            i = smallest;
        }
    }

public:
    void push(int value) {
        data.push_back(value);
        sift_up(data.size() - 1);
    }

    int pop() {
        int min_val = data[0];
        data[0] = data.back();
        data.pop_back();
        if (!data.empty()) sift_down(0);
        return min_val;
    }

    int top() const { return data[0]; }
    bool empty() const { return data.empty(); }
    int size() const { return data.size(); }

    void build_heap(const vector<int>& arr) {
        data = arr;
        int n = data.size();
        for (int i = n / 2 - 1; i >= 0; i--)
            sift_down(i);
    }
};

vector<int> heap_sort(vector<int> arr) {
    MinHeap heap;
    heap.build_heap(arr);

    vector<int> sorted;
    while (!heap.empty())
        sorted.push_back(heap.pop());
    return sorted;
}

int find_kth_largest(const vector<int>& arr, int k) {
    MinHeap heap;  // pазмер k min-heap - пази k-те най-големи видени досега
    for (int x : arr) {
        heap.push(x);
        if (heap.size() > k)
            heap.pop();
    }
    return heap.top();
}

int main() {
    cout << "--- push / pop ---" << endl;
    MinHeap heap;
    heap.push(5);
    heap.push(1);
    heap.push(9);
    heap.push(3);
    heap.push(7);

    while (!heap.empty()) {
        cout << heap.top() << " ";
        heap.pop();
    }
    cout << endl;

    cout << "\n--- build_heap + heap_sort ---" << endl;
    vector<int> arr = {4, 1, 9, 6, 3, 8, 2};
    vector<int> sorted = heap_sort(arr);
    for (int x : sorted) cout << x << " ";
    cout << endl;

    cout << "\n--- find_kth_largest ---" << endl;
    cout << "3-тия най-голям в [4,1,9,6,3,8,2] = "
         << find_kth_largest(arr, 3) << endl;  // 6

    return 0;
}
