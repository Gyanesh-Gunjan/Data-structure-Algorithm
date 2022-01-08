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
        void showAllString(trieNode* rootNode , string word);

    public:
        Trie(){this->root = new trieNode();}

        void insert(string word);
        void show();
};

int main(){
    Trie t;
    vector<string> arr ={ "a","apple", "bear","apps","wekc", "coding", "ex"};
    for(auto &s : arr) t.insert(s);
    t.show();
    return 0;
}
/*
    show function definition 
    Time complexity : O(n) where n is the total length of the character 
*/
void::Trie::show(){
   
    showAllString(root, "");
    
}

/*
    show util function 
    Time complexity : O(n) where n is the total number of nodes in trie DS
*/
void Trie::showAllString(trieNode* rootNode, string word){
    /* when root node is word then print */
    if(rootNode->isWord) cout<<word<<endl;

    /* recursive call over all it's children links */
    for(auto &node : rootNode->getAllNode()){
        word +=node.first;
        showAllString(node.second, word);
        word.pop_back();
    }
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