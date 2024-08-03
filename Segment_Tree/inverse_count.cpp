#include <bits/stdc++.h>
using namespace std;

class segmentTree
{
public:
    vector<int> seg;
    segmentTree(int n)
    {
        seg.resize(4 * n + 2);
    }
    void build(int ind, int low, int high, int arr[])
    {
        if (low == high)
        {
            seg[ind] = arr[low];
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
    int query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        if (l > high || r < low)
            return 0;
        // complete overlap
        if (l >= low && r <= high)
            return seg[ind];
        // partial overlap
        int mid = (l + r) / 2;
        int left = query(2 * ind + 1, low, high, l, mid);
        int right = query(2 * ind + 2, low, high, mid + 1, r);
        return left + right;
    }
    void update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] += val;
            return;
        }
        int mid = (low + high) / 2;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = seg[2 * ind + 1] + seg[2 * ind + 2];
    }
    void print()
    {
        for (auto ele : seg)
        {
            cout << ele << ' ';
        }
        cout << endl;
    }
};

void solve()
{
    int n;
    cin >> n;
    int a[n];
    int mx = -1;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    mx++;
    int freq[mx] = {0};
    for (int i = 0; i < n; i++)
        freq[a[i]]++;
    segmentTree tree(mx);
    tree.build(0, 0, mx - 1, freq);
    // tree.print();
    long long int ans = 0;
    for (int i = 0; i < n; i++)
    {
        tree.update(0, 0, mx - 1, a[i], -1);
        ans += tree.query(0, 0, a[i] - 1, 0, mx - 1);
    }
    cout << ans << endl;
}

int main()
{
    // your code goes here
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}
