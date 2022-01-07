#include "bits/stdc++.h"
using namespace std;

/*
    structure of a single node in BST
*/
class node{
    public:
        int value;
        node* left_child;
        node* right_child;

        node(){}    

        node(int value , node* left_child = NULL, node* right_child = NULL) {
            this->value = value;
            this->left_child = left_child;
            this->right_child = right_child;
        }
};

/*
    Binary search Tree definitions
*/
class binarySearchTree{
    private:
        node* root;
        int heightUsingRecursion(node* rootNode );
        int heightUsingIteration(node* rootNode);

    public:
        binarySearchTree(){ root = NULL;}

        void Insert(int value);
        int height(bool usingRecursion = true);
        
        
};

/* - - - main function - - - */
int main(){
    binarySearchTree bt;
    vector<int> arr = {25, 15, 50, 10, 22, 35, 70, 4, 12, 18, 24, 31, 44, 66, 90};
    for(auto &it : arr) bt.Insert(it);
    cout<<"\n\tHeight Using Iteration : "<<bt.height(false)<<endl;
    cout<<"\n\tHeight Using Recursion : "<<bt.height()<<endl;
    return 0;
}

/*
    Height of the BST
    Time complexity : O(n)
    Space complexity : O(n)
*/
int binarySearchTree::height(bool usingRecursion){

    if(usingRecursion)
        return heightUsingRecursion(root);
   
    return heightUsingIteration(root);
}


/*
    Height using Iteration 
    Time complexity : O(n)
    Space Complexity : O(n)
*/

int binarySearchTree::heightUsingIteration(node* rootNode){
    if(!rootNode) return 0;

    stack<pair<node*, int>> trackNode;
    int lvl = 1;
    int maxHeight = 0;

    trackNode.push({rootNode, lvl});

    while(!trackNode.empty()){

        pair<node*, int> topNode = trackNode.top();
        trackNode.pop();
    
        lvl = topNode.second;
        node* leftChild = topNode.first->left_child;
        node* rightChild = topNode.first->right_child;
        
    /*  if current lvl is greater than maxHeight then update maxHeight value    */
        if(maxHeight < lvl) maxHeight = lvl;

        if(leftChild) trackNode.push({leftChild, lvl+1});
        if(rightChild)  trackNode.push({rightChild, lvl+1});
    }

    return maxHeight;
}


/*
    Height using recursion 
    Time complexity : O(n)
    Space complexity : O(n)
*/
int binarySearchTree::heightUsingRecursion(node* rootNode){
    /* when root node is null then return */
    if(!rootNode)   return 0;

    int leftHeight = heightUsingRecursion(rootNode->left_child);
    int rightHeight = heightUsingRecursion(rootNode->right_child);

    return 1 + max(leftHeight , rightHeight);
}

/*
    BST insert function definition
    Time Complexity : O(h) where h is the height of the tree
*/
void binarySearchTree::Insert(int val){

    // if root is null then insert new node to the root
    if(root == NULL) { 
        root = new node(val);  
        return;
    }

    // travelling to correct position at which value will be inserted 
    node* run = root;
    while(run){
        /*
            if current root value is greater than given val then 
            travel to its left subtree (i.e. left_child direction)
        */ 
        if(run->value > val){
            if(run->left_child == NULL) {
                run->left_child = new node(val);
                break;
            }
            else run = run->left_child;
        }
        /*
            if current root value is greater than or equal to given val then
            travel to its right substree (i.e. right_chil direction)
        */
        else{
            if(run->right_child == NULL){
                run->right_child = new node(val);
                break;
            }
            else run = run->right_child;
        }
    }
}