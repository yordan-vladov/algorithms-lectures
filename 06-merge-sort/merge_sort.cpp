#include <iostream>
#include <vector>
using namespace std;

void merge(vector<int>& arr, int low, int mid, int high) {

    // временни масиви за лявата и дясната половина
    vector<int> left(arr.begin() + low, arr.begin() + mid + 1);
    vector<int> right(arr.begin() + mid + 1, arr.begin() + high + 1);

    int i = 0, j = 0, k = low;

    // сливаме двете сортирани половини обратно в arr
    while (i < (int)left.size() && j < (int)right.size()) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        } else {
            arr[k++] = right[j++];
        }
    }

    // прехвърляме остатъка (ако има) от която и да е половина
    while (i < (int)left.size()) arr[k++] = left[i++];
    while (j < (int)right.size()) arr[k++] = right[j++];
}

void mergeSort(vector<int>& arr, int low, int high) {
    if (low >= high) return;

    int mid = low + (high - low) / 2;

    mergeSort(arr, low, mid);       // сортирай лявата половина
    mergeSort(arr, mid + 1, high);  // сортирай дясната половина
    merge(arr, low, mid, high);     // слей ги
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    mergeSort(arr, 0, (int)arr.size() - 1);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}
