#include <iostream>
#include <vector>

using namespace std;

const int MOD = 998244353;

int add(int a, int b) {
    return (a + b) % MOD;
}

int mul(int a, int b) {
    return ((long long)a * b) % MOD;
}

int power(int a, int b) {
    int res = 1;
    while (b > 0) {
        if (b & 1) {
            res = mul(res, a);
        }
        a = mul(a, a);
        b >>= 1;
    }
    return res;
}

int inv(int a) {
    return power(a, MOD - 2);
}

int main() {
    int t;
    cin >> t;
    
    while (t--) {
        int n, m, k;
        cin >> n >> m >> k;
        
        vector<int> a(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }
        
        int p = n / k;
        
        vector<int> s(p);
        for (int i = 0; i < p; i++) {
            s[i] = 0;
            for (int j = i * k; j < (i + 1) * k; j++) {
                s[i] += a[j];
            }
        }
        
        vector<vector<int>> dp(p + 1, vector<int>(m + 1));
        dp[0][0] = 1;
        for (int i = 0; i < p; i++) {
            for (int j = 0; j <= m; j++) {
                for (int x = 0; x <= k && x <= j; x++) {
                    dp[i + 1][j] = add(dp[i + 1][j], mul(dp[i][j - x], inv(k - x + 1)));
                }
            }
        }
        
        int ans = 1;
        for (int i = 0; i < p; i++) {
            ans = mul(ans, dp[i + 1][m]);
        }
        
        cout << ans << endl;
    }
    
    return 0;
}
