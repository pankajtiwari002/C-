#include <bits/stdc++.h>
using namespace std;

struct TrieNode{
    TrieNode* links[26];
    bool flag;

    bool containsKey(char ch){
        return links[ch-'a']!=NULL;
    }

    TrieNode* get(char ch){
        return links[ch-'a'];
    }

    void put(char ch,TrieNode* node){
        links[ch-'a'] = node;
    }

    bool isEnd(){
        return flag;
    }

    void setEnd(){
        flag = true;
    }
};

class Trie{
    TrieNode* root;
    public:
    Trie(){
        root = new TrieNode();
    }

    void insert(string &s){
        TrieNode* curr = root;
        for(auto ch: s){
            if(!curr->containsKey(ch)){
                curr->put(ch,new TrieNode());
            }
            curr = curr->get(ch);
        }
        curr->setEnd();
    }

    bool search(string &s){
        TrieNode* curr = root;
        for(auto ch: s){
            if(!curr->containsKey(ch)){
                return false;
            }
            curr = curr->get(ch);
        }
        return curr->isEnd();
    }

    bool startsWith(string &s){
        TrieNode* curr = root;
        for(auto ch: s){
            if(!curr->containsKey(ch)){
                return false;
            }
            curr = curr->get(ch);
        }
        return true;
    }
};

int main(){

}