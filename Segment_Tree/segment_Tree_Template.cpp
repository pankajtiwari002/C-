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
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    int query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        if (l > high || r < low)
            return INT_MAX;
        // complete overlap
        if (l >= low && r <= high)
            return seg[ind];
        // partial overlap
        int mid = (l + r) / 2;
        int left = query(2 * ind + 1, low, high, l, mid);
        int right = query(2 * ind + 2, low, high, mid + 1, r);
        return min(left, right);
    }
    int update(int ind, int low, int high, int i, int val)
    {
        if (low == high)
        {
            seg[ind] = val;
            return;
        }
        int mid = (low + high) / 2;
        if (i <= mid)
            update(2 * ind + 1, low, mid, i, val);
        else
            update(2 * ind + 2, mid + 1, high, i, val);
        seg[ind] = min(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
};