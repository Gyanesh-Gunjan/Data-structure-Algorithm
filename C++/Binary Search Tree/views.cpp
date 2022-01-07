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

        void leftViewUtil(node* rootNode, vector<int>& view, int lvl);
        void rightViewUtil(node* rootNode, vector<int>& view, int lvl);
        void topViewUtil(node* rootNode, vector<int>& view);
        void bottomViewUtil(node* rootNode, vector<int>& view);
        

    public:
        binarySearchTree(){ root = NULL;}

        vector<int> leftView();
        vector<int> rightView();
        vector<int> topView();
        vector<int> bottomView();
       
        void Insert(int value);
        void test(vector<int>& actual, vector<int>& expected, string msg);
    
};

/* - - - main function - - - */
int main(){
    binarySearchTree bt;
    vector<int> arr = {25, 15, 50, 10, 22, 35, 70, 4, 12, 18, 24, 31, 44, 66, 90};
    vector<int> leftViewExp = {25, 15, 10, 4};
    vector<int> rightViewExp = {25, 50, 70,90};
    vector<int> topViewExp = {25, 15, 50, 10, 70, 4, 90};
    vector<int> bottomViewExp = {4, 10, 31, 35, 66, 70, 90};
    vector<int> actual;
    for(auto &it : arr) bt.Insert(it);
    actual = bt.leftView();
    bt.test(actual, leftViewExp, "Left View");

    actual = bt.rightView();
    bt.test(actual, rightViewExp, "Right View");

    actual = bt.topView();
    bt.test(actual, topViewExp, "Top View");

    actual = bt.bottomView();
    bt.test(actual, bottomViewExp, "Bottom View");
    return 0;
}
/*
    Bottom view 
    Time Complexity : O(n)
    Space Complexity : (n)
*/
vector<int> binarySearchTree::bottomView(){
    vector<int> view;
    bottomViewUtil(root, view);
    return view;
}

/*
    Bottom view using iteration
    Time complexity : O(n)
    Space complexity : O(n)
*/
void binarySearchTree::bottomViewUtil(node* rootNode, vector<int>& view){
/* when root node is null then return */
    if(!rootNode)   return;

    map<int, int> nodeTaken;
    queue<pair<node*, int>> trackNode;
    int verticalDistance = 0;       // assuming vertical distance at root = 0

    trackNode.push({rootNode, verticalDistance});

    while(!trackNode.empty()){
        pair<node*, int> frontNode = trackNode.front();
        trackNode.pop();
        verticalDistance = frontNode.second;

    /*  
        update curent vertical Distance to it's bottom most value  
        if vertical Distance x has mutiple node then taking it's right most node at that distance
    */
        nodeTaken[verticalDistance] = frontNode.first->value;
        
        node* leftChild = frontNode.first->left_child;
        node* rightChild = frontNode.first->right_child;

        if(leftChild)
            trackNode.push({leftChild, verticalDistance - 1});
        if(rightChild)
            trackNode.push({rightChild, verticalDistance + 1});
    }

    /* pushing bottom view value from left to right in view vector */
    for(auto &verticalDistance : nodeTaken)
        view.push_back(verticalDistance.second);
}

/*
    top view 
    Time complexity : O(n)
    Space Complexity : O(n)
*/
vector<int> binarySearchTree::topView(){
    vector<int> view;
    topViewUtil(root, view);
    return view;
}
/*
    top view util function using iteration
    Time complexity : O(n)
    Space Complexity : O(n)
*/
void binarySearchTree::topViewUtil(node* rootNode, vector<int>& view){

/*  when root node is null then return */
    if(!rootNode)   return;

    map<int, int> nodeTaken;
    queue<pair<node*, int>> trackNode;
    int verticalDistance = 0;       // considering root node vertical distance = 0

    trackNode.push({root, verticalDistance});

    while(!trackNode.empty()){

        pair<node*, int> frontNode = trackNode.front();
        trackNode.pop();
        verticalDistance = frontNode.second;

        bool isCurrentVDistNodeTaken = nodeTaken.find(verticalDistance) != end(nodeTaken);
    /*  
        If current vertical Distance node is not taken then 
        take node value , and mark it as taken
    */
        if(!isCurrentVDistNodeTaken){
            nodeTaken[frontNode.second] = 1;
            view.push_back(frontNode.first->value);
        }

        node* leftChild = frontNode.first->left_child ;
        node* rightChild = frontNode.first->right_child ;
        

        if(leftChild) 
            trackNode.push({leftChild, verticalDistance - 1});
        if(rightChild)  
            trackNode.push({rightChild, verticalDistance + 1});
    }
        
}

/*  
    right view 
    Time complexity : O(n)
    Space complexity : O(n)
*/
vector<int> binarySearchTree::rightView(){
    vector<int> view;
    rightViewUtil(root, view, 0);
    return view;
}

/*
    right view Util function 
    Time complexity : O(n)
    Space Complexity : O(n)
*/
void binarySearchTree::rightViewUtil(node* rootNode, vector<int>& view, int lvl){
    /*  when root node is null then return */
    if(!rootNode)   return;

/*  if views length is less than  or equal lvl 
    then push back root value to view  
*/
    if(lvl >= view.size()) view.push_back(rootNode->value);
    
    rightViewUtil(rootNode->right_child, view, lvl+1);
    rightViewUtil(rootNode->left_child, view, lvl+1);
    
}

/*
    left view 
    Time complexity : O(n)
    Space Complexity : O(n)
*/
vector<int> binarySearchTree::leftView(){
    vector<int> view;
    leftViewUtil(root, view, 0);
    return view;
}

/*
    leftView Util function 
    Time complexity : O(n)
    Space complexity : O(n)
*/
void binarySearchTree::leftViewUtil(node* rootNode, vector<int>& view , int lvl){
    /*  when root node is null then return */
    if(!rootNode)   return;

/*  if views length is less than  or equal lvl 
    then push back root value to view  
*/
    if(lvl >= view.size())
        view.push_back(rootNode->value);

    leftViewUtil(rootNode->left_child, view, lvl+1);
    leftViewUtil(rootNode->right_child, view, lvl+1);
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


/*  Testing the result of traversal */
void binarySearchTree::test(vector<int>& actual,  vector<int>& expected, string msg){
    int l1 = actual.size();     // actual output vector length 
    int l2 = expected.size();   // expected output vector length
    cout<<"\n\tRunning on #"<<msg;
    if(l1 != l2) cout<<": Test case failed!!\n";
    else{
        bool flag = true;
        for(int i=0;i<l1;i++){
            if(actual[i] != expected[i]){
                flag = false;
                break;
            }
        }
        if(flag)  cout<<": Test case passed!!\n";
        else cout<<": Test case failed!!\n";
    }
}