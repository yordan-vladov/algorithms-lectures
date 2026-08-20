#include <iostream>
#include <vector>
using namespace std;

void selectionSort(vector<int>& arr) {
    int n = arr.size();

    for (int i = 0; i < n - 1; i++) {

        // намираме индекса на най-малкия елемент в неподредената част
        int minIndex = i;

        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        // разменяме го с първия елемент на неподредената част
        if (minIndex != i) {
            swap(arr[i], arr[minIndex]);
        }
    }
}

int main() {
    vector<int> arr = {10, 7, 8, 9, 1, 5};

    selectionSort(arr);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}
