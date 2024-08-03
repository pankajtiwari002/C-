// range sum with range update  

#include <bits/stdc++.h>
using namespace std;

class segmentTree
{
public:
    vector<int> seg;
    vector<int> lazy;
    segmentTree(int n)
    {
        seg.resize(4 * n + 2);
        lazy.resize(4 * n + 2, 0);
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
        // previous update
        seg[ind] += ((r - l + 1) * lazy[ind]);
        if (l != r)
        {
            lazy[2 * ind + 1] += lazy[ind];
            lazy[2 * ind + 2] += lazy[ind];
        }
        lazy[ind] = 0;
        // no overlap
        if (l > high || r < low)
            return 0;
        // complete overlap
        if (l >= low && r <= high)
        {
            return seg[ind];
        }
        // partial overlap
        int mid = (l + r) / 2;
        int left = query(2 * ind + 1, low, high, l, mid);
        int right = query(2 * ind + 2, low, high, mid + 1, r);
        return left + right;
    }
    void update(int ind, int low, int high, int l, int r, int val)
    {
        // previous update
        seg[ind] += ((r - l + 1) * lazy[ind]);
        if (l != r)
        {
            lazy[2 * ind + 1] += lazy[ind];
            lazy[2 * ind + 2] += lazy[ind];
        }
        lazy[ind] = 0;

        if (l > high || r < low)
            return;
        // complete overlap
        if (l >= low && r <= high)
        {
            // update
            seg[ind] += ((r - l + 1) * val);
            // lazy propogate
            if (l != r)
            {
                lazy[2 * ind + 1] += val;
                lazy[2 * ind + 2] += val;
            }
            return;
        }
        // partial overlap
        int mid = (l + r) / 2;
        update(2 * ind + 1, low, high, l, mid, val);
        update(2 * ind + 2, low, high, mid + 1, r, val);
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
    int n, m;
    cin >> n >> m;
    int a[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    segmentTree tree(n);
    tree.build(0, 0, n - 1, a);
    // tree.print();
    while (m--)
    {
        int type;
        cin >> type;
        if (type == 1)
        {
            int l, r, val;
            cin >> l >> r >> val;
            tree.update(0, l, r, 0, n - 1, val);
        }
        else
        {
            int l, r;
            cin >> l >> r;
            cout << tree.query(0, l, r, 0, n - 1) << endl;
        }
    }
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
