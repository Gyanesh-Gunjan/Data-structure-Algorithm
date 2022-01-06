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
        void InorderUsingRecusion(node* root, vector<int>& path);

    public:
        binarySearchTree(){ root = NULL;}

        void Insert(int value);
        void Inorder();
        
};

int main(){
    binarySearchTree bt;
    vector<int> arr = {25, 15, 50, 10, 22, 35, 70, 4, 12, 18, 24, 31, 44, 66, 90};
    for(auto &it : arr) bt.Insert(it);
    bt.Inorder();
    return 0;
}


/*
    Inorder traversal 
    Time Complexity : O(n)
    Space Complexity : O(n)
*/
void binarySearchTree::Inorder(){
    vector<int> path;
    InorderUsingRecusion(root, path);
    for(auto &val : path) cout<<val<<" ";
    cout<<"\n";
}

/*
    Inorder traversal using recursion
*/
void binarySearchTree::InorderUsingRecusion(node* root, vector<int>& path){
    if(root == NULL) return;
    InorderUsingRecusion(root->left_child, path);
    path.push_back(root->value);
    InorderUsingRecusion(root->right_child, path);
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