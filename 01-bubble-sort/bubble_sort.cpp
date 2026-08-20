#include <iostream>
#include <vector>
using namespace std;

void bubbleSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        // flag - следи дали е имало размяна в този проход
        bool swapped = false;

        // последните i елемента вече са наредени
        for (int j = 0; j < n - 1 - i; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }

        // ако няма размяна - масивът вече е сортиран
        if (!swapped) break;
    }
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    bubbleSort(arr);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}
