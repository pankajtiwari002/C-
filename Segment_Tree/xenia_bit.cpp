/*
Link: https://codeforces.com/contest/339/problem/D
Adjacent element First or then xor then or so on until one element remains.

Let's consider an example. Suppose that sequence a = (1, 2, 3, 4). Then let's write down all the transformations (1, 2, 3, 4)  →  (1 or 2 = 3, 3 or 4 = 7)  →  (3 xor 7 = 4). The result is v = 4.

Input
The first line contains two integers n and m (1 ≤ n ≤ 17, 1 ≤ m ≤ 105). The next line contains 2n integers a1, a2, ..., a2n (0 ≤ ai < 230). Each of the next m lines contains queries. The i-th line contains integers pi, bi (1 ≤ pi ≤ 2n, 0 ≤ bi < 230) — the i-th query.
Each query a[pi-1] = bi;

Output
Print m integers — the i-th integer denotes value v for sequence a after the i-th query.

Input:
2 4
1 6 3 5
1 4
3 4
1 2
1 2

((1|6) ^ (3|5)) = 1
((4|6) ^ (3|5)) = 3

Output:
1
3
3
3
*/

#include <bits/stdc++.h>
using namespace std;

class segmentTree{
    public:
    vector<int> seg;
    segmentTree(int n){
        seg.resize(4*n+2);
    }
    bool build(int ind,int low,int high,int arr[]){
        if(low==high){
            seg[ind] = arr[low];
            return true;
        }
        int mid = (low+high)/2;
        bool flag = build(2*ind+1,low,mid,arr);
        build(2*ind+2,mid+1,high,arr);
        if(flag) seg[ind] = seg[2*ind+1] | seg[2*ind+2];
        else seg[ind] = seg[2*ind+1] ^ seg[2*ind+2];
        return !flag;
    }
    int query(){
        return seg[0];
    }
    int update(int ind,int low,int high,int i,int val){
        if(low==high){
            seg[ind] = val;
            return true;
        }
        int mid = (low+high)/2;
        bool flag;
        if(i<=mid) flag = update(2*ind + 1,low,mid,i,val);
        else flag = update(2*ind + 2,mid+1,high,i,val);
        if(flag) seg[ind] = seg[2*ind+1] | seg[2*ind+2];
        else seg[ind] = seg[2*ind+1] ^ seg[2*ind+2];
        return !flag;
    }
};

int main() {
    int n,m;
    cin>>n>>m;
    int size = 1<<n;
    int a[size];
    for(int i=0;i<size;i++) cin>>a[i];
    segmentTree tree(size);
    tree.build(0,0,size-1,a);
    while(m--){
        int ind,val;
        cin>>ind>>val;
        a[ind] = val;
        tree.update(0,0,size-1,ind-1,val);
        cout<<tree.query()<<endl;
    }

}
