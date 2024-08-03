#include<bits/stdc++.h>
using namespace std;
#define int long long int
const int N = 1e5+2;

struct Node{
    int sum;
    int pref;
    int suff;
    int ans;
    Node(int sum,int pref,int suff,int ans){
        this->ans = ans;
        this->pref = pref;
        this->sum  = sum;
        this->suff = suff;
    }
    Node(int x){
        sum = pref = suff = ans = x;
    }
};

Node tree[4*N];

const int N = 1e5;
int tree[4*N];

void buildSegementTree(int arr[],int i,int j,int node){
    if(i==j){
        tree[node] = Node(arr[i]);
        return;
    }
    int mid = (i+j)/2;
    int l = 2*node+1,r = 2*node+2;
    buildSegementTree(arr,i,mid,l);
    buildSegementTree(arr,mid+1,j,r);
    
    tree[node].sum = tree[l].sum + tree[r].sum;
    tree[node].pref = max(tree[l].pref,tree[l].sum+tree[r].pref);
    tree[node].suff =  max(tree[r].suff,tree[r].sum+tree[l].suff);
    tree[node].ans = max(tree[l].pref,max(tree[r].suff,tree[l].suff + tree[r].pref));
}

// int query(int st,int en,int i,int j,int node){
//     if(st>j || en<i) return INT_MIN;
//     if(i>=st && j<=en) return tree[node];
//     int mid = (i+j)/2;
//     int left = query(st,en,i,mid,2*node+1);
//     int right = query(st,en,mid+1,j,2*node+2);
//     return max(left,right);
// }

void update(int ind,int val,int i,int j,int node){
    if(i==j && i==ind){
        tree[node] = Node(val);
        return;
    }
    int mid = (i+j)/2;
    int l = 2*node+1,r = 2*node+2;
    if(ind<=mid){
        update(ind,val,i,mid,2*node+1);
    }
    else update(ind,val,mid+1,j,2*node+2);
    tree[node].sum = tree[l].sum + tree[r].sum;
    tree[node].pref = max(tree[l].pref,tree[l].sum+tree[r].pref);
    tree[node].suff =  max(tree[r].suff,tree[r].sum+tree[l].suff);
    tree[node].ans = max(tree[l].pref,max(tree[r].suff,tree[l].suff + tree[r].pref));
}


signed main(){
    int n,m;
    cin>>n>>m;
    int arr[n];
    for(int i=0;i<n;i++) cin>>arr[i];
    while(m--){
        int ind,val;
        cin>>ind>>val;
        cout<<tree[0].ans<<endl;
        update(ind,val,0,n-1,0);
    }
    cout<<tree[0].ans<<endl;
}