#include <iostream>
#include <vector>
#include <random>
using namespace std;

// RNG (seeded once)
static random_device rd;
static mt19937 gen(rd());

int hoarePartition(vector<int>& arr, int low, int high) {
    // Pick a random pivot value from [low, high]
    uniform_int_distribution<int> dist(low, high);
    int pivot = arr[dist(gen)];

    int i = low - 1;
    int j = high + 1;

    while (true) {
        // Move i right until arr[i] >= pivot
        do { i++; } while (arr[i] < pivot);

        // Move j left until arr[j] <= pivot
        do { j--; } while (arr[j] > pivot);

        // Indices crossed: j is the split point
        if (i >= j) return j;

        swap(arr[i], arr[j]);
    }
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int p = hoarePartition(arr, low, high);

        // Note the ranges for Hoare:
        // [low..p] and [p+1..high]
        quickSort(arr, low, p);
        quickSort(arr, p + 1, high);
    }
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};
    quickSort(arr, 0, (int)arr.size() - 1);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}