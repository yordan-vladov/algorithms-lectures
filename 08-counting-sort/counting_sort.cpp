#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void countingSort(vector<int>& arr) {
    if (arr.empty()) return;

    int maxVal = *max_element(arr.begin(), arr.end());

    // count[v] = колко пъти се среща стойността v
    vector<int> count(maxVal + 1, 0);
    for (int x : arr) count[x]++;

    // префиксни суми - count[v] става "последна позиция на v в изхода"
    for (int i = 1; i <= maxVal; i++) {
        count[i] += count[i - 1];
    }

    // строим изходния масив, обхождайки arr отзад напред за стабилност
    vector<int> output(arr.size());
    for (int i = (int)arr.size() - 1; i >= 0; i--) {
        output[--count[arr[i]]] = arr[i];
    }

    arr = output;
}

int main() {
    vector<int> arr = {4, 2, 2, 8, 3, 3, 1};

    countingSort(arr);

    for (int x : arr) cout << x << " ";
    cout << "\n";
    return 0;
}
