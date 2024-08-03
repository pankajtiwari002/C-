
/*
Sereja has a bracket sequence s1, s2, ..., sn, or, in other words, a string s of length n, consisting of characters "(" and ")".

Sereja needs to answer m queries, each of them is described by two integers li, ri (1 ≤ li ≤ ri ≤ n). The answer to the i-th query is the length of the maximum correct bracket subsequence of sequence sli, sli + 1, ..., sri. Help Sereja answer all queries.

You can find the definitions for a subsequence and a correct bracket sequence in the notes.

Input
The first line contains a sequence of characters s1, s2, ..., sn (1 ≤ n ≤ 106) without any spaces. Each character is either a "(" or a ")". The second line contains integer m (1 ≤ m ≤ 105) — the number of queries. Each of the next m lines contains a pair of integers. The i-th line contains integers li, ri (1 ≤ li ≤ ri ≤ n) — the description of the i-th query.

Output
Print the answer to each question on a single line. Print the answers in the order they go in the input.

Sample Input:
())(())(())(
7
1 1
2 3
1 2
1 12
8 12
5 11
2 10

Sample Output
0
0
2
10
4
6
6

Link: https://codeforces.com/contest/380/problem/C
*/
#include <bits/stdc++.h>
using namespace std;

struct Node{
  int open,close,full;
  Node(){
      open = close = full = 0;
  }
  Node(char ch){
      open = close = full = 0;
      if(ch=='(') open=1;
      else close=1;
  }
  void calc(Node &a,Node &b){
      full = a.full + b.full + min(a.open,b.close);
      open = a.open + b.open - min(a.open,b.close);
      close = a.close + b.close - min(a.open,b.close); 
  }
};

class segmentTree
{
public:
    vector<Node> seg;
    segmentTree(int n)
    {
        seg.resize(4 * n + 2);
    }
    void build(int ind, int low, int high, string &str)
    {
        if (low == high)
        {
            seg[ind] = Node(str[low]);
            return;
        }
        int mid = (low + high) / 2;
        build(2 * ind + 1, low, mid, str);
        build(2 * ind + 2, mid + 1, high, str);
        seg[ind].calc(seg[2 * ind + 1],seg[2 * ind + 2]);
    }
    
    Node query(int ind, int low, int high, int l, int r)
    {
        // no overlap
        if (l > high || r < low)
            return Node();
        // complete overlap
        if (l >= low && r <= high)
            return seg[ind];
        // partial overlap
        int mid = (l + r) / 2;
        Node left = query(2 * ind + 1, low, high, l, mid);
        Node right = query(2 * ind + 2, low, high, mid + 1, r);
        Node ans = Node();
        ans.calc(left,right);
        return ans;
    }
    void print(){
        for(int i=0;i<seg.size();i++){
            cout<<seg[i].full<<' ';
        }
        cout<<endl;
    }
};

int main() {
	// your code goes here
	string s;
	cin>>s;
	int n,m;
	cin>>m;
	n = s.size();
	segmentTree tree(n);
	tree.build(0,0,n-1,s);
// 	tree.print();
	while(m--){
	    int l,r;
	    cin>>l>>r;
	    Node ans = tree.query(0,l-1,r-1,0,n-1);
	    cout<<2*ans.full<<endl;
	}
}
