#include <iostream>
#include <vector>
using namespace std;

int knapsack(vector<int>& weight, vector<int>& value, int W) {
    int n = weight.size();
    vector<vector<int>> dp(n + 1, vector<int>(W + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            dp[i][w] = dp[i - 1][w];  // do not take item i-1

            if (weight[i - 1] <= w)
                dp[i][w] = max(dp[i][w], value[i - 1] + dp[i - 1][w - weight[i - 1]]);
        }
    }

    return dp[n][W];
}

int main() {
    vector<int> weight = {2, 3, 4, 5};
    vector<int> value  = {3, 4, 5, 6};
    int W = 5;

    cout << "Максимална стойност: " << knapsack(weight, value, W) << endl;
    // Изход: 7

    return 0;
}
