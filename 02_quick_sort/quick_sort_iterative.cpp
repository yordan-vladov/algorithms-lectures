#include <iostream>
#include <vector>
#include <stack>
#include <random>
using namespace std;

// RNG
static random_device rd;
static mt19937 gen(rd());

int hoarePartition(vector<int>& arr, int low, int high) {
    uniform_int_distribution<int> dist(low, high);
    int pivot = arr[dist(gen)];

    int i = low - 1;
    int j = high + 1;

    while (true) {
        do { i++; } while (arr[i] < pivot);
        do { j--; } while (arr[j] > pivot);

        if (i >= j)
            return j;

        swap(arr[i], arr[j]);
    }
}

void quickSortIterative(vector<int>& arr, int low, int high) {

    stack<pair<int,int>> st;
    st.push({low, high});

    while (!st.empty()) {

        auto [l, h] = st.top();
        st.pop();

        if (l < h) {
            int p = hoarePartition(arr, l, h);

            // Push subarrays onto stack
            st.push({l, p});
            st.push({p + 1, h});
        }
    }
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    quickSortIterative(arr, 0, (int)arr.size() - 1);

    for (int x : arr)
        cout << x << " ";

    return 0;
}