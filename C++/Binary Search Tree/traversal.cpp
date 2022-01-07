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

        /*  traversal using recursion   */
        void InorderUsingRecursion(node* rootNode, vector<int>& path);
        void PreorderUsingRecursion(node* rootNode, vector<int>& path);
        void PostorderUsingRecursion(node* rootNode, vector<int>& path);

        /*  traversal using iteration    */
        void InorderUsingIteration(node* rootNode, vector<int>& path);
        void PreorderUsingIteration(node* rootNode, vector<int>& path);
        void PostorderUsingIteration(node* rootNode, vector<int>& path);
        
    public:
        binarySearchTree(){ root = NULL;}

        void Insert(int value);
        vector<int> Inorder(bool usingRecursion = true);
        vector<int> Preorder(bool usingRecursion = true);
        vector<int> Postorder(bool usingRecursion = true);

        void test(vector<int>& a, vector<int>& b, string msg);
        
};

/*  main function   */
int main(){
    binarySearchTree bt;
    vector<int> arr = {25, 15, 50, 10, 22, 35, 70, 4, 12, 18, 24, 31, 44, 66, 90};
    vector<int> inorderExp =   {4, 10, 12, 15, 18, 22, 24, 25, 31, 35, 44, 50, 66, 70, 90};
    vector<int> preorderExp =  {25, 15, 10, 4, 12, 22, 18, 24, 50, 35, 31, 44, 70, 66, 90};
    vector<int> postorderExp = {4, 12, 10, 18, 24, 22, 15, 31, 44, 35, 66, 90, 70, 50, 25};
    vector<int> ans;

    for(auto &it : arr) bt.Insert(it);

    ans = bt.Inorder();
    bt.test(inorderExp, ans,"Inorder (Recursion)");

    ans = bt.Inorder(false);
    bt.test(inorderExp, ans, "Inorder (Iteration)");

    ans = bt.Preorder();
    bt.test(preorderExp, ans, "Preorder (Recursion)");

    ans = bt.Preorder(false);
    bt.test(preorderExp, ans, "Preorder (Iteration)");

    ans = bt.Postorder();
    bt.test(postorderExp, ans, "Postorder (Recursion)");

    ans = bt.Postorder(false);
    bt.test(postorderExp, ans, "Postorder (Iteration)");
    return 0;
}

/*
    Postorder traversal, default value for usingRecursion is true
    Time complexity : O(n)
    Space complexity : O(n)
*/
vector<int> binarySearchTree::Postorder(bool usingRecursion){
    vector<int> postorderPath;

    if(usingRecursion)  
        PostorderUsingRecursion(root, postorderPath);
    else PostorderUsingIteration(root, postorderPath);

    return postorderPath;
}

/*
    Postorder traversal using recursion
    Time complexity : O(n)
    Space Complexity : O(n)
    Traversal : left, right, root
*/
void binarySearchTree::PostorderUsingRecursion(node* rootNode, vector<int>& path){
    if(!rootNode)   return;     // when rootnode is null then return

    PostorderUsingRecursion(rootNode->left_child, path);
    PostorderUsingRecursion(rootNode->right_child, path);

    path.push_back(rootNode->value);
}

/*
    Postorder traversal using iteration
    Time complexity : O(n)
    Space complexity : O(n)
    Traversal : left, right, root
*/
void binarySearchTree::PostorderUsingIteration(node* rootNode, vector<int>& path){

    if(!rootNode)   return;

    stack<node*> trackNode;
 
    while(rootNode  || !trackNode.empty()){

    /*  if root node is not null then move to it's left child */
        if(rootNode){
            trackNode.push(rootNode);
            rootNode = rootNode->left_child;
        }
        else{

        /*  If root node is null then check whether it has right child or node */
            node* topRightChild = trackNode.top()->right_child;

        /*  if it has right child then point rootNode to its right child */
            if(topRightChild)   rootNode = topRightChild;
            else{

                /* current top node is leaf node */
                node* topNode = trackNode.top();
                path.push_back(topNode->value);
                trackNode.pop();

            /*  store right child of the top node */
                topRightChild = trackNode.top()->right_child;

            /*  this will print all right node to it's parent node */
                while(topRightChild == topNode){
                    
                    topNode = trackNode.top();
                    path.push_back(topNode->value);
                    trackNode.pop();

                    if(!trackNode.empty())
                        topRightChild = trackNode.top()->right_child;
                }
            }
        }
    }

}


/*
    Preorder traversal , default vaule for usingRecursion is true
    Time Complexity : O(n)
    Space complexity : O(n)
*/
vector<int> binarySearchTree::Preorder(bool usingRecursion){
    vector<int> preorderPath;

    if(usingRecursion)  
        PreorderUsingRecursion(root, preorderPath);
    else PreorderUsingIteration(root, preorderPath);

    return preorderPath;
}

/*
    Preorder traversal using Recursion 
    Time Complexity : O(n)
    Space Complexity : O(n)
    Traversal : root, left , right
*/
void binarySearchTree::PreorderUsingRecursion(node* rootNode, vector<int>& path){
    if(!rootNode)   return;     // when rootNode is null then return

    path.push_back(rootNode->value);

    PreorderUsingRecursion(rootNode->left_child, path);
    PreorderUsingRecursion(rootNode->right_child, path);
}


/*
    Preorder using Iteration 
    Time complexity : O(n)
    Space complexity : O(n)
    Traversal : root, left, right 
*/
void binarySearchTree::PreorderUsingIteration(node* rootNode, vector<int>& path){
    if(!rootNode)   return;     // if root node is null then return

    stack<node*> trackNode;
    trackNode.push(rootNode);

    while(!trackNode.empty()){

        node* frontNode = trackNode.top();
        trackNode.pop();
        path.push_back(frontNode->value);

        bool leftChild = frontNode->left_child;
        bool rightChild = frontNode->right_child;

        if(rightChild)  trackNode.push(frontNode->right_child);
        if(leftChild) trackNode.push(frontNode->left_child);
    }
}

/*
    Inorder Traversal function, default value for usingRecusion is true
    Time Complexity : O(n)
    Space Complexity : O(n)
*/
vector<int>binarySearchTree::Inorder(bool usingRecursion){
    vector<int> inorderPath;

    if(usingRecursion) 
        InorderUsingRecursion(root, inorderPath);
    else InorderUsingIteration(root, inorderPath);

    return inorderPath;
}

/*
    Inorder using recursion 
    Time Complexity : O(n)
    space complexity : O(n)
    Traversal : left, root , right
*/
void binarySearchTree::InorderUsingRecursion(node* rootNode, vector<int>& path){

    if(!rootNode) return;       // when root is null then return

    InorderUsingRecursion(rootNode->left_child,  path);
    path.push_back(rootNode->value); 
    InorderUsingRecursion(rootNode->right_child, path);
}

/*
    Inorder using iteration (stack)
    Time complexity : O(n)
    Space complexity : O(n)
    Traversal : left, root, right
*/
void binarySearchTree::InorderUsingIteration(node* rootNode, vector<int>& path){

    stack<node*> trackNode;

    while(rootNode || !trackNode.empty()){

        /* traverse towards its leftmost child and store each node in the stack */
        while(rootNode){
            trackNode.push(rootNode);
            rootNode = rootNode->left_child;
        }

        node* topNode = trackNode.top();
        bool havingRightChild = topNode->right_child;
        trackNode.pop();

        path.push_back(topNode->value);

        if(havingRightChild) rootNode = topNode->right_child;
    }
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
    node* currentNode = root;
    while(currentNode){
        /*
            if current root value is greater than given val then 
            travel to its left subtree (i.e. left_child direction)
        */ 
        if(currentNode->value > val){
            if(currentNode->left_child == NULL) {
                currentNode->left_child = new node(val);
                break;
            }
            else currentNode = currentNode->left_child;
        }
        /*
            if current root value is greater than or equal to given val then
            travel to its right substree (i.e. right_chil direction)
        */
        else{
            if(currentNode->right_child == NULL){
                currentNode->right_child = new node(val);
                break;
            }
            else currentNode = currentNode->right_child;
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