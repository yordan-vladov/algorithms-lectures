#include <iostream>
#include <vector>
using namespace std;

int binarySearch(const vector<int>& arr, int target) {
    int low = 0, high = arr.size() - 1;

    while (low <= high) {
        int mid = low + (high - low) / 2; // избягва overflow спрямо (low + high) / 2

        if (arr[mid] == target) return mid;
        else if (arr[mid] < target) low = mid + 1;
        else high = mid - 1;
    }

    return -1; // не е намерен
}

int binarySearchRecursive(const vector<int>& arr, int target, int low, int high) {
    if (low > high) return -1;

    int mid = low + (high - low) / 2;

    if (arr[mid] == target) return mid;
    else if (arr[mid] < target) return binarySearchRecursive(arr, target, mid + 1, high);
    else return binarySearchRecursive(arr, target, low, mid - 1);
}

int main() {
    vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    cout << binarySearch(arr, 11) << "\n"; // 5
    cout << binarySearch(arr, 4) << "\n";  // -1

    cout << binarySearchRecursive(arr, 11, 0, arr.size() - 1) << "\n"; // 5
    cout << binarySearchRecursive(arr, 4, 0, arr.size() - 1) << "\n";  // -1

    return 0;
}
