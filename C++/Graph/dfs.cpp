#include "bits/stdc++.h"
using namespace std;

class graph{
    private:
        vector<vector<int>> gh;
        int nodes;

    /*  dfs util */
        void dfsUsingRecursion(int source, vector<int>& path, vector<bool>& visited);
        void dfsUsingIteration(int source, vector<int>& path, vector<bool>& visited);

    /*  validation and connections  */
        bool isValidConnection(pair<int, int>& connection);
        void directedConnection(vector<pair<int, int>>& edges);
        void unDirectedConnection(vector<pair<int, int>>& edges);

    public:
        graph(){this->nodes = 0;}

        vector<int> dfs(int source, bool usingRecursion = true);

        void create(vector<pair<int,int>>& edges, int nodes, bool biDirection = true);
};

int main(){
    vector<pair<int, int>> connections = {
        {1,2}, {1,4}, {4,3}, {2,3}, {3,10}, {3,9}, {2,5}, {2,8}, {2,7}, {8,5}, {8,7}, {7,5}, {5,6}
    };
    int nodes = 10;

    graph g;
    g.create(connections, nodes+1);
    vector<int> output = g.dfs(1);
    cout<<"DFS Using recursion : ";
    for(auto &value : output) cout<<value<<" ";
    cout<<"\nDFS Using Iteration : ";
    output = g.dfs(1, false);
    for(auto &value: output)    cout<<value<<" ";
    return 0;
}

/*
    dfs 
    Time complexity : O(n)
*/
vector<int> graph::dfs(int source, bool usingRecursion){
    vector<int> path;
    vector<bool>visited(nodes+1, false);

    if(usingRecursion)
        dfsUsingRecursion(source, path, visited);
    else dfsUsingIteration(source, path, visited);

    return path;
}

/*
    dfs using Iteration 
    Time Complexity : O(n)
*/
void graph::dfsUsingIteration(int source, vector<int>& path, vector<bool>& visited){

    stack<int> trackNode;
    trackNode.push(source);

    while(!trackNode.empty()){

        source  = trackNode.top();
        trackNode.pop();

    /*  when source node is visited then continue   */
        if(visited[source]) continue;

        path.push_back(source);
        visited[source] = true;     // make source node as visited

    /*  stores all nodes which are directly connected to source nodes   */
        for(auto &node : gh[source])
            trackNode.push(node);
    }
}

/*
    dfs using recursion
    Time Complexity : O(E)  where E = number edges
*/
void graph::dfsUsingRecursion(int source, vector<int>& path, vector<bool>& visited){

    /*  when node is already visited then return    */
        if(visited[source]) return;

        path.push_back(source);
        visited[source] = true;

    /*  make recursive call to all nodes which are connected to source node */
        for(auto &node : gh[source])
            dfsUsingRecursion(node, path, visited);
}

/*
    creating graph with the help of adjacency List 
    default value for biDirection connection  =  true
    Time complexity : O(E)  where E is the number of edges
*/
void graph::create(vector<pair<int,int>>& edges, int nodes, bool biDirection){

    if(nodes > 0){
        gh.resize(nodes);
        this->nodes = nodes;

        if(biDirection) directedConnection(edges);
        else unDirectedConnection(edges);
    }
    else cout<<"\n\tInvalid Size!\n";
}

/*
    isValidConnection : this is connection validation function
*/
bool graph::isValidConnection(pair<int,int>& connection){

    bool isValidSource = connection.first >= 0 && connection.first < nodes;
    bool isValidDest = connection.second >= 0 && connection.second < nodes;

    return isValidSource && isValidDest;
}

/*
    directedConnection : this function creates directed connections
*/
void graph::directedConnection(vector<pair<int,int>>& connections){

    for(auto &edge : connections){

        if(isValidConnection(edge))
            gh[edge.first].push_back(edge.second);
    /* 
        when connection is Invalid then it will clear all connections 
        and will throw error message
    */
        else{
            gh.clear();
            cout<<"\n\tInvalid connection! (check connection : {"<<edge.first<<", "<<edge.second<<"}\n";
        }
    }
}


/*
    unDirectedConnection : this function creates undirected connections
*/
void graph::unDirectedConnection(vector<pair<int,int>>& connections){

    for(auto &edge : connections){

        if(isValidConnection(edge)){
            gh[edge.first].push_back(edge.second);
            gh[edge.second].push_back(edge.first);
        }
    /* 
        when connection is Invalid then it will clear all connections 
        and will throw error message
    */
        else{
            gh.clear();
            cout<<"\n\tInvalid connection! (check connection : {"<<edge.first<<", "<<edge.second<<"}\n";
        }
    }
}