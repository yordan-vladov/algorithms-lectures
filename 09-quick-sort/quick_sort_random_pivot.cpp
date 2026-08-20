#include <iostream>
#include <vector>
#include <random>
using namespace std;

// random number generator
random_device rd;
mt19937 gen(rd());

int partition(vector<int>& arr, int low, int high) {

    // choose a random pivot index
    uniform_int_distribution<> dist(low, high);
    int randomIndex = dist(gen);

    // move random pivot to the end
    swap(arr[randomIndex], arr[high]);

    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(vector<int>& arr, int low, int high) {

    if (low < high) {

        int pi = partition(arr, low, high);

        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int main() {

    vector<int> arr = {10, 7, 8, 9, 1, 5};
    int n = arr.size();

    quickSort(arr, 0, n - 1);

    for (int x : arr) {
        cout << x << " ";
    }

    return 0;
}