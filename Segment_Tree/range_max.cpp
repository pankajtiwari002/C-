#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int tree[4 * N];

void buildSegementTree(int arr[], int i, int j, int node)
{
    if (i == j)
    {
        tree[node] = arr[i];
        return;
    }
    int mid = (i + j) / 2;
    buildSegementTree(arr, i, mid, 2 * node + 1);
    buildSegementTree(arr, mid + 1, j, 2 * node + 2);

    tree[node] = max(tree[2 * node + 1], tree[2 * node + 2]);
}

int query(int st, int en, int i, int j, int node)
{
    if (st > j || en < i)
        return INT_MIN;
    if (i >= st && j <= en)
        return tree[node];
    int mid = (i + j) / 2;
    int left = query(st, en, i, mid, 2 * node + 1);
    int right = query(st, en, mid + 1, j, 2 * node + 2);
    return max(left, right);
}

int update(int ind, int val, int i, int j, int node)
{
    if (i == j && i == ind)
    {
        return tree[node] = val;
    }
    int mid = (i + j) / 2;
    if (ind <= mid)
    {
        update(ind, val, i, mid, 2 * node + 1);
        return tree[node] = max(tree[node], tree[2 * node + 1]);
    }
    update(ind, val, mid + 1, j, 2 * node + 2);
    return tree[node] = max(tree[node], tree[2 * node + 2]);
}

int main()
{
    // your code goes here
    int n;
    cin >> n;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    buildSegementTree(arr, 0, n - 1, 0);
    // 	for(int i=0;i<2*n;i++){
    // 	    cout<<tree[i]<<' ';
    // 	}
    // 	cout<<endl;
    while (1)
    {
        bool flag = false;
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            int st, en;
            cin >> st >> en;
            cout << query(st, en, 0, n - 1, 0) << endl;
            break;
        case 2:
            int ind, val;
            cin >> ind >> val;
            update(ind, val, 0, n - 1, 0);
            break;
        default:
            flag = 1;
            break;
        }
        if (flag)
            break;
    }
}
