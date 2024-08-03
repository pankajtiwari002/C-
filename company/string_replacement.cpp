#include <bits/stdc++.h>
using namespace std;

string getSmallestString(string word,string substr){
    int n = word.size(),m = substr.size();
    if(substr.size()>word.size()) return "-1";
    bool globalFlag = true;
    for(int i=n-m;i>=0;i--){
        bool flag = true;
        for(int j=0;j<m;j++) {
            if(word[i+j]!='?' && word[i+j]!=substr[j]){
                flag = false;
                break;
            }
        }
        if(flag){
            globalFlag = false;
            for(int j=0;j<m;j++) {
                word[i+j] = substr[j];
            }
            break;
        }
    }
    if(globalFlag) return "-1";
    for(int i=0;i<n;i++){
        if(word[i]=='?') word[i]='a';
    }
    return word;
}

int main() {
    string word,substr;
    cin>>word>>substr;
    cout<<getSmallestString(word,substr);
}
