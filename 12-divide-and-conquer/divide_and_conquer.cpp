#include <iostream>
#include <vector>
#include <climits>
using namespace std;

// Fast power - O(log n) чрез "разделяй и владей"
double fastPower(double x, int n) {
    if (n == 0) return 1;

    double half = fastPower(x, n / 2);

    if (n % 2 == 0)
        return half * half;
    else
        return x * half * half;
}

// Maximum subarray sum - O(n log n) чрез "разделяй и владей"
int maxCrossingSum(vector<int>& arr, int low, int mid, int high) {
    int leftSum = INT_MIN, sum = 0;
    for (int i = mid; i >= low; i--) {
        sum += arr[i];
        leftSum = max(leftSum, sum);
    }

    int rightSum = INT_MIN;
    sum = 0;
    for (int i = mid + 1; i <= high; i++) {
        sum += arr[i];
        rightSum = max(rightSum, sum);
    }

    return leftSum + rightSum;
}

int maxSubArraySum(vector<int>& arr, int low, int high) {
    if (low == high) return arr[low];

    int mid = (low + high) / 2;

    int leftMax  = maxSubArraySum(arr, low, mid);
    int rightMax = maxSubArraySum(arr, mid + 1, high);
    int crossMax = maxCrossingSum(arr, low, mid, high);

    return max({leftMax, rightMax, crossMax});
}

int main() {
    cout << "2^10 = " << fastPower(2, 10) << endl;

    vector<int> arr = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    cout << "Max subarray sum = " << maxSubArraySum(arr, 0, arr.size() - 1) << endl;
    // Изход: 6  (подмасивът [4, -1, 2, 1])

    return 0;
}
