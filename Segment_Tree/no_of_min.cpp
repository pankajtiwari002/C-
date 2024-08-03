// https://codeforces.com/edu/course/2/lesson/4/1/practice/contest/273169/problem/C

#include <bits/stdc++.h>
using namespace std;

#define int long long int
const int N = 1e5+2;
pair<int,int> tree[4 * N];

void buildSegementTree(int arr[], int i, int j, int node)
{
    if (i == j)
    {
        tree[node].first = arr[i];
        tree[node].second = 1;
        return;
    }
    int mid = (i + j) / 2;
    int lind = 2*node+1,rind = 2*node+2;
    buildSegementTree(arr, i, mid, lind);
    buildSegementTree(arr, mid + 1, j, rind);

    if(tree[lind].first < tree[rind].first){
        tree[node].first = tree[lind].first;
        tree[node].second = tree[lind].second;
    }
    else if(tree[rind].first < tree[lind].first){
        tree[node].first = tree[rind].first;
        tree[node].second = tree[rind].second;
    }
    else{
        tree[node].first = tree[lind].first;
        tree[node].second = tree[lind].second + tree[rind].second;
    }
}

pair<int,int> query(int st, int en, int i, int j, int node)
{
    if (st > j || en < i){
        return {INT_MAX,-1};
    }
    if (i >= st && j <= en)
        return tree[node];
    int mid = (i + j) / 2;
    pair<int,int> left = query(st, en, i, mid, 2 * node + 1);
    pair<int,int> right = query(st, en, mid + 1, j, 2 * node + 2);
    pair<int,int> ans;
    if(left.first < right.first){
        ans = left;
    }
    else if(right.first < left.first){
        ans = right;
    }
    else{
        ans.first = left.first;
        ans.second = left.second + right.second;
    }
    return ans;
}

void update(int ind, int val, int i, int j, int node)
{
    if (i == j && i==ind)
    {
        tree[node].first = val;
        tree[node].second = 1;
        return;
    }
    int mid = (i + j) / 2;
    int lind = 2*node+1,rind = 2*node+2;
    if(ind<=mid){
        update(ind,val,i,mid,lind);
    }
    else{
        update(ind,val,mid+1,j,rind);
    }
    if(tree[lind].first < tree[rind].first){
        tree[node].first = tree[lind].first;
        tree[node].second = tree[lind].second;
    }
    else if(tree[rind].first < tree[lind].first){
        tree[node].first = tree[rind].first;
        tree[node].second = tree[rind].second;
    }
    else{
        tree[node].first = tree[lind].first;
        tree[node].second = tree[lind].second + tree[rind].second;
    }
}

signed main()
{
    // your code goes here
    int n,m;
    cin >> n >> m;
    int arr[n];
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    buildSegementTree(arr, 0, n - 1, 0);
    // 	for(int i=0;i<2*n;i++){
    // 	    cout<<tree[i]<<' ';
    // 	}
    // 	cout<<endl;
    while (m--)
    {
        int ch;
        cin >> ch;
        switch (ch)
        {
        case 1:
            int ind, val;
            cin >> ind >> val;
            update(ind, val, 0, n - 1, 0);
            break;
        case 2:
            int st, en;
            cin >> st >> en;
            pair<int,int> ans = query(st, en-1, 0, n - 1, 0);
            cout<<ans.first<<' '<<ans.second<<endl;
            break;
        }
    }
}
