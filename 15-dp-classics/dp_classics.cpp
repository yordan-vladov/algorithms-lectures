#include <iostream>
#include <vector>
#include <climits>
#include <string>
using namespace std;

int coinChange(vector<int>& coins, int amount) {
    vector<int> dp(amount + 1, INT_MAX);
    dp[0] = 0;

    for (int s = 1; s <= amount; s++) {
        for (int c : coins) {
            if (c <= s && dp[s - c] != INT_MAX)
                dp[s] = min(dp[s], dp[s - c] + 1);
        }
    }

    return dp[amount] == INT_MAX ? -1 : dp[amount];
}

int lengthOfLIS(vector<int>& nums) {
    int n = nums.size();
    vector<int> dp(n, 1);

    int best = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < i; j++) {
            if (nums[j] < nums[i])
                dp[i] = max(dp[i], dp[j] + 1);
        }
        best = max(best, dp[i]);
    }

    return best;
}

int editDistance(string word1, string word2) {
    int n = word1.size(), m = word2.size();
    vector<vector<int>> dp(n + 1, vector<int>(m + 1, 0));

    for (int i = 0; i <= n; i++) dp[i][0] = i;
    for (int j = 0; j <= m; j++) dp[0][j] = j;

    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (word1[i - 1] == word2[j - 1])
                dp[i][j] = dp[i - 1][j - 1];
            else
                dp[i][j] = 1 + min({dp[i - 1][j], dp[i][j - 1], dp[i - 1][j - 1]});
        }
    }

    return dp[n][m];
}

int main() {
    vector<int> coins = {1, 3, 4};
    cout << "Coin Change(6): " << coinChange(coins, 6) << endl;
    // Изход: 2

    vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};
    cout << "LIS дължина: " << lengthOfLIS(nums) << endl;
    // Изход: 4

    cout << "Edit Distance(horse, ros): " << editDistance("horse", "ros") << endl;
    // Изход: 3

    return 0;
}
