/*
Alice has a string S with length N and Bob has a string C with length M. Bob gave Alice an array of integers A of size N representing the cost of deleting each letter in strings S. Find the minimum cost T to delete a number of characters(possibly zero) from S so that C doesn't appear as a sub sequence of S.

Notes: Ai is the cost to delete Si, where 1<=i<=N.

Input format first line: N denoting the no. of elements in A.
second line: M denoting the length of C.
third line: string S, denoting the Alice's string.
fourth line: string C, denoting the Bob's string.
fifth line: contains integers describing A[i].

Sample Input:

5
3
hallo
llo
1 2 3 4 5

output: 3

sample input:
8
8
muhammad
muhammad
1 2 3 4 5 6 7 8

sample output: 1

sample input:
15
4
hallohallohallo
allo
1 2 3 4 5 6 7 8 9 10 11 12 13 14 15

output: 21
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

int solve(string &s, string &c, int i, int j, int n, int m, vector<int> &a, vector<vector<int>> &dp)
{
    if (j >= m)
        return 1e8;
    if (i >= n)
        return 0;
    if (dp[i][j] != -1)
        return dp[i][j];
    int take = 1e8, notTake;
    if (s[i] == c[j])
    {
        take = solve(s, c, i + 1, j + 1, n, m, a, dp);
        notTake = a[i] + solve(s, c, i + 1, j, n, m, a, dp);
    }
    else
    {
        notTake = solve(s, c, i + 1, j, n, m, a, dp);
    }
    return dp[i][j] = min(take, notTake);
}

int minCostToRemoveSubsequence(int N, int M, string S, string C, vector<int> &A)
{
    vector<vector<int>> dp(N, vector<int>(M, -1));
    return solve(S, C, 0, 0, N, M, A, dp);
}

int main()
{
    int N, M;
    cin >> N >> M;
    string S, C;
    cin >> S >> C;
    vector<int> A(N);
    for (int i = 0; i < N; ++i)
    {
        cin >> A[i];
    }

    int result = minCostToRemoveSubsequence(N, M, S, C, A);
    cout << result << endl;

    return 0;
}
