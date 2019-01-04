#include <iostream>
#include <vector>

using std::vector;

int partition3(vector<int>& A) {
    int total = 0;
    for (auto ele : A) {
        total += ele;
    }
    if (total % 3 != 0) {
        return 0;
    }
    total /= 3;
    int n = A.size();

    vector<vector<vector<int>>> dp(
        n + 1, vector<vector<int>>(total + 1, vector<int>(total + 1, 0)));
    // create 3d array, dp[a][b][c]
    // a:-> the index of each element in A
    // b:-> the sum of one set
    // c:-> the sum of the reset
    for (int k = 0; k < n + 1; ++k) {
        for (int i = 0; i < total + 1; ++i) {
            for (int j = 0; j < total + 1; ++j) {
                // std::cout << k << " " << i << " " << j << " |";
                if (k == 0) {
                    // dp[k][i][j] = 0;
                } else if (i == 0 && j == 0) {
                    // dp[k][i][j] = 0;
                } else if (i == 0) {
                    if (A[k - 1] > j) {
                        dp[k][i][j] = dp[k][i][j - 1];
                    } else {
                        // k element either used by j or not used by j
                        int t1 = dp[k][i][j - A[k - 1]] + A[k - 1];
                        int t2 = dp[k][i][j - 1];
                        dp[k][i][j] = std::max(t1, t2);
                    }
                } else if (j == 0) {
                    if (A[k - 1] > i) {
                        dp[k][i][j] = dp[k][i - 1][j];
                    } else {
                        // k element either used by j or not used by j
                        int t1 = dp[k][i - A[k - 1]][j] + A[k - 1];
                        int t2 = dp[k][i - 1][j];
                        dp[k][i][j] = std::max(t1, t2);
                    }
                } else {
                    // the new coming number can have three conditions:
                    // 1. not used
                    // 2. used by i
                    // 3. used by j
                    int t1 = dp[k - 1][i][j];
                    int t2 = 0;
                    int t3 = 0;
                    if (A[k - 1] <= i) {
                        t2 = dp[k][i - A[k - 1]][j] + A[k - 1];
                    } else {
                        t2 = dp[k][i - 1][j];
                    }
                    if (A[k - 1] <= j) {
                        t3 = dp[k][i][j - A[k - 1]] + A[k - 1];
                    } else {
                        t3 = dp[k][i][j - 1];
                    }
                    int v = t2;
                    if (t1 > t2) {
                        v = t1;
                    }
                    dp[k][i][j] = std::max(v, t3);
                }
                // std::cout << dp[k][i][j] << " \n";
            }
        }
    }

    if (dp[n][total][total] == total * 2) {
        return 1;
    }
    return 0;
}

int main() {
    int n;
    std::cin >> n;
    vector<int> A(n);
    for (size_t i = 0; i < A.size(); ++i) {
        std::cin >> A[i];
    }
    std::cout << partition3(A) << '\n';
}