#include <bits/stdc++.h>
using namespace std;

const int N = 1e5;
int tree[4*N];

void buildSegementTree(int arr[],int i,int j,int node){
    if(i==j){
        tree[node] = arr[i];
        return;
    }
    int mid = (i+j)/2;
    buildSegementTree(arr,i,mid,2*node+1);
    buildSegementTree(arr,mid+1,j,2*node+2);
    
    tree[node] = tree[2*node+1] + tree[2*node + 2];
}

int query(int st,int en,int i,int j,int node){
    if(st>j || en<i) return 0;
    if(i>=st && j<=en) return tree[node];
    int mid = (i+j)/2;
    int left = query(st,en,i,mid,2*node+1);
    int right = query(st,en,mid+1,j,2*node+2);
    return left + right;
}

int main() {
	// your code goes here
	int n;
	cin>>n;
	int arr[n];
	for(int i=0;i<n;i++) cin>>arr[i];
	buildSegementTree(arr,0,n-1,0);
// 	for(int i=0;i<2*n;i++){
// 	    cout<<tree[i]<<' ';
// 	}
// 	cout<<endl;
	int st,en;
	cin>>st>>en;
	cout<<query(st,en,0,n-1,0);
}
