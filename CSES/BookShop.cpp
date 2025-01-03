#include <bits/stdc++.h>
using namespace std;

#define FAST_IO                       \
    ios_base::sync_with_stdio(false); \
    cin.tie(0);                       \
    cout.tie(0);
#define int long long

//---- Debugger ---- //

#define debarr(a, n)            \
    cout << #a << " : ";        \
    for (int i = 0; i < n; i++) \
        cerr << a[i] << " ";    \
    cerr << endl;
#define debmat(mat, row, col)         \
    cout << #mat << " :\n";           \
    for (int i = 0; i < row; i++)     \
    {                                 \
        for (int j = 0; j < col; j++) \
            cerr << mat[i][j] << " "; \
        cerr << endl;                 \
    }

//--------------- //

int helper(int price[], int pages[], vector<vector<int>>&dp, int idx, int k, int &size){
    if(idx == size){
        return 0;
    }
    if(dp[idx][k] != -1) return dp[idx][k];

    int pick = 0, notpick = 0;

    if(k >= price[idx]){
        pick = pages[idx] + helper(price, pages, dp, idx + 1, k - price[idx], size);
    }
    notpick = helper(price, pages, dp, idx + 1, k, size);

    return max(pick, notpick);
}

int32_t main()
{
    FAST_IO

    int n, k;
    cin >> n >> k;
    int price[n], pages[n];
    for (int i = 0; i < n; i++)
    {
        cin >> price[i];
    }
    for (int i = 0; i < n; i++)
    {
        cin >> pages[i];
    }

    // vector<vector<int>>dp(n + 1, vector<int>(k + 1, 0));
    // cout<< helper(price, pages, dp, 0, k, n);

    vector<int> curr(k + 1), prev(k + 1);

    for (int i = n - 1; i >= 0; i--)
    {
        for (int j = 0; j <= k; j++)
        {
            int pick = 0, notpick = 0;
            if (j >= price[i])
            {
                pick = pages[i] + prev[j - price[i]];
            }
            notpick = prev[j];
            curr[j] = max(pick, notpick);
        }
        prev = curr;
    }

    cout << prev[k];
}
