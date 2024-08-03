#include <bits/stdc++.h>
using namespace std;

// Binary Index Tree(BIT)
class FenwickTree
{
    vector<int> bit;
    int n;

public:
    FenwickTree(int n)
    {
        bit.resize(n + 1, 0);
        this->n = n;
    }
    int sum(int i)
    {
        int ans = 0;
        for (; i >= 1; i -= (i & (-i)))
        {
            ans += bit[i];
        }
        return ans;
    }
    void update(int i, int x)
    {
        for (; i <= n; i += (i & (-i)))
        {
            bit[i] += x;
        }
    }
    void build(int arr[])
    {
        for (int i = 0; i < n; i++)
        {
            update(i + 1, arr[i]);
        }
    }
};

int main()
{
    // your code goes here
    int n;
    cin >> n;
    int a[n];
    int mx = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    FenwickTree tree(mx);
    mx = 0;
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        mx = max(mx, a[i]);
        ans += tree.sum(mx) - tree.sum(a[i]);
        tree.update(a[i], 1);
    }
    cout << ans << endl;
}
