#include "bits/stdc++.h"
using namespace std;

/*
    A single trie node definition
    links : all child nodes of current node
    isWord : this is for end of word
*/
class trieNode{
    private:
        map<char, trieNode*> links;
    public:
        bool isWord;
        trieNode(){this->isWord = false;}
    
    bool containsKey(char ch);
    void putsKey(char ch);
    void markAsWord();
    trieNode* getNode(char ch);
    map<char, trieNode*> getAllNode();

};

/*
    Trie Data structure definition 
*/
class Trie{
    private:
        trieNode* root;

        trieNode* searchPrefix(string prefix);

    public:
        Trie(){this->root = new trieNode();}

        void insert(string word);
        bool search(string word);
};

int main(){
    Trie t;
    vector<string> arr ={ "a","apple", "bear","apps","wekc", "coding", "ex"};
    for(auto &s : arr) t.insert(s);

    if(t.search("apple"))   cout<<"found\n";
    return 0;
}

/*
    search a word in trie DS
    Time complexity : O(m)  where m is the length of the word
*/
bool Trie::search(string word){
    trieNode* node = searchPrefix(word);
    return node && node->isWord;
}
/*
    searchPrefix : 
    Time complexity : O(m)  where m is length of the prefix word 
*/
trieNode* Trie::searchPrefix(string prefix){
    int len = prefix.length();

/*  when prefix is empty then simply return */
    if(len == 0)    return nullptr;

    trieNode* currentNode = root;
    /*
        Iterate over all characters of prefix word
    */
    for(int i=0;i<len;i++){
        if(currentNode->containsKey(prefix[i]))
            currentNode = currentNode->getNode(prefix[i]);
        else return nullptr;    
    }

    return currentNode;
}


/*
    Inserting a word in trie DS
    Time complexity : O(m)  where m is the length of word
*/
void Trie::insert(string word){
    int len = word.length();

    /*  when word is empty then simply return it */
    if(len == 0)    return;

    trieNode* rootNode = root;
    /*
        Iterating over each charater of the word 
    */
    for(int i=0;i<len;i++){
        /*  
            when charater is not present then create new node 
        */
        if(!rootNode->containsKey(word[i]))   
            rootNode->putsKey(word[i]);

        rootNode = rootNode->getNode(word[i]);
    }
    /*
        marking as a end of word 
    */
    rootNode->markAsWord();
}

/*
    return true if current node having child with value ch
*/
bool trieNode::containsKey(char ch){
    return links.find(ch) != end(links);
}


/* 
    creating for new node with value ch 
*/
void trieNode::putsKey(char ch){
        links[ch] = new trieNode();
}


/*  
    mark as end of the word 
*/
void trieNode::markAsWord(){
    this->isWord = true;
}

/*
    return a single node which matches character ch
*/
trieNode* trieNode::getNode(char ch){
    return links[ch];
}

/*  
    return all the child nodes of current node 
*/
map<char, trieNode*> trieNode::getAllNode(){
    return links;
}