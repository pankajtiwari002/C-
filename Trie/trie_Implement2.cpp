#include <bits/stdc++.h>
using namespace std;

struct TrieNode{
    TrieNode* links[26];
    int count_prefix,count_end;

    TrieNode(){
        count_prefix=0;
        count_end=0;
    }

    bool containsKey(char ch){
        return links[ch-'a']!=NULL;
    }

    TrieNode* get(char ch){
        return links[ch-'a'];
    }

    void put(char ch,TrieNode* node){
        links[ch-'a'] = node;
    }

    int countEnd(){
        return count_end;
    }

    void increaseEnd(){
        count_end++;
    }

    void decreaseEnd(){
        count_end--;
    }

    int countPrefix(){
        return count_prefix;
    }

    void increasePrefix(){
        count_prefix++;
    }

    void decreasePrefix(){
        count_prefix--;
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
            curr->increasePrefix();
        }
        curr->increaseEnd();
    }

    int countWordEqualTo(string &s){
        TrieNode* curr = root;
        for(auto ch: s){
            if(!curr->containsKey(ch)){
                return 0;
            }
            curr = curr->get(ch);
        }
        return curr->countEnd();
    }

    int countWordStartsWith(string &s){
        TrieNode* curr = root;
        for(auto ch: s){
            if(!curr->containsKey(ch)){
                return 0;
            }
            curr = curr->get(ch);
        }
        return curr->countPrefix();
    }

    void erase(string &s){
        if(countWordEqualTo(s)>0){
            TrieNode* curr = root;
            for(auto ch: s){
                curr = curr->get(ch);
                curr->decreasePrefix();
            }
            curr->decreaseEnd();
        }
    }
};

int main(){

}