/*
1 -> head
0 -> tails
give an array of n elements containing 0 and 1
given m queries
1. count no of head and tail in range l to r
2. flip the coin from range l to r
*/

#include <bits/stdc++.h>
using namespace std;

struct Node
{
    int head, tail;
    Node(int x)
    {
        head = tail = 0;
        if (x == 1)
            head = 1;
        else
            tail = 1;
    }
    Node()
    {
        head = tail = 0;
    }
    void swap()
    {
        head = head ^ tail;
        tail = head ^ tail;
        head = head ^ tail;
    }
    void calc(Node &left, Node &right)
    {
        head = left.head + right.head;
        tail = left.tail + right.tail;
    }
};

class segmentTree
{
public:
    vector<Node> seg;
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
            seg[ind] = Node(arr[low]);
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, arr);
        build(2 * ind + 2, mid + 1, high, arr);
        seg[ind] = Node();
        seg[ind].calc(seg[2 * ind + 1], seg[2 * ind + 2]);
    }

    Node query(int ind, int low, int high, int l, int r)
    {
        // previous update
        if (lazy[ind] == 1)
        {
            seg[ind].swap();
            if (l != r)
            {
                lazy[2 * ind + 1] = !lazy[2 * ind + 1];
                lazy[2 * ind + 2] = !lazy[2 * ind + 2];
            }
            lazy[ind] = 0;
        }
        // no overlap
        if (l > high || r < low)
            return Node();
        // complete overlap
        if (l >= low && r <= high)
        {
            return seg[ind];
        }
        // partial overlap
        int mid = (l + r) / 2;
        Node left = query(2 * ind + 1, low, high, l, mid);
        Node right = query(2 * ind + 2, low, high, mid + 1, r);
        Node ans = Node();
        ans.calc(left, right);
        return ans;
    }
    void update(int ind, int low, int high, int l, int r)
    {
        // previous update
        if (lazy[ind] == 1)
        {
            seg[ind].swap();
            if (l != r)
            {
                lazy[2 * ind + 1] = !lazy[2 * ind + 1];
                lazy[2 * ind + 2] = !lazy[2 * ind + 2];
            }
            lazy[ind] = 0;
        }

        if (l > high || r < low)
            return;
        // complete overlap
        if (l >= low && r <= high)
        {
            // update
            seg[ind].swap();
            if (l != r)
            {
                lazy[2 * ind + 1] = !lazy[2 * ind + 1];
                lazy[2 * ind + 2] = !lazy[2 * ind + 2];
            }
            return;
        }
        // partial overlap
        int mid = (l + r) / 2;
        update(2 * ind + 1, low, high, l, mid);
        update(2 * ind + 2, low, high, mid + 1, r);
        seg[ind].calc(seg[2 * ind + 1], seg[2 * ind + 2]);
    }
    void print()
    {
        for (auto ele : seg)
        {
            cout << ele.tail << ' ';
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
            int l, r;
            cin >> l >> r;
            Node ans = tree.query(0, l, r, 0, n - 1);
            cout << "head = " << ans.head << " tail = " << ans.tail << endl;
        }
        else
        {
            int l, r;
            cin >> l >> r;
            tree.update(0, l, r, 0, n - 1);
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
