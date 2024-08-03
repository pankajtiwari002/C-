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
    int n, m;
    cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    FenwickTree tree(n);
    tree.build(a);
    while (m--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r;
            cin >> l >> r;
            cout << tree.sum(r + 1) - tree.sum(l) << endl;
        }
        else
        {
            int ind, val;
            cin >> ind >> val;
            tree.update(ind + 1, val - a[ind]);
        }
    }
}
