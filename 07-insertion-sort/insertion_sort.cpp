#include <iostream>
#include <vector>
using namespace std;

void insertionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 1; i < n; i++) {

        int key = arr[i];   // елементът, който вмъкваме
        int j = i - 1;

        // местим елементите, по-големи от key, с една позиция надясно
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }

        // вмъкваме key на освободеното място
        arr[j + 1] = key;
    }
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    insertionSort(arr);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}
