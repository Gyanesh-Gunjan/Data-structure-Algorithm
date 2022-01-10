#include "bits/stdc++.h"
using namespace std;

class path{
    private :
        vector<vector<pair<int, int>>> graph;
        int nodes;
        bool isValidConnections(int src, int dest);
    public:
        path(){this->nodes = 0;}

        vector<int> dijkstra(int source);
        void create(vector<vector<int>>& connections, int nodes);
        void show();

};

int main(){
    vector<pair<int, int>> connections = {
        {1,2}, {1,4}, {4,3}, {2,3}, {3,10}, {3,9}, {2,5}, {2,8}, {2,7}, {8,5}, {8,7}, {7,5}, {5,6}
    };
    vector<vector<int>> g1 = {
        {1,4,10}, {4,1,10}, {1,2,50}, {2,3,10}, {1,3,45},
        {2,4,15}, {4,5,15}, {5,2,20}, {6,5,3}, {5,3,35},{3,5,30}
    };
    int nodes = 7;
    path p;
    p.create(g1,7);

    vector<int> cost = p.dijkstra(1);
    cout<<"Cost from node 1 : ";
    for(int i=1;i<nodes;i++) {
        if(cost[i] == INT_MAX)  cout<<"{not possible path to "<<i<<"}\t";
        else cout<<"{to node "<<i<<": "<<cost[i]<<"}\t";
    }
    return 0;
}

/*
    Implementation of Dijkstra algorithm 
    Time complexity : O(nlogn)
    space complexity : O(n)
*/
vector<int> path::dijkstra(int source){
    vector<int> cost(this->nodes, INT_MAX);
    vector<bool> visited(this->nodes, false);

    priority_queue<pair<int, int>> trackNode;    // this will keep track of node value and it's cost
    trackNode.push({0, source});
    cost[source] = 0;       // cost of souce node = 0

    while(!trackNode.empty()){
        int srcNodeCost = -trackNode.top().first;
        int src = trackNode.top().second;
        trackNode.pop();

        if(visited[src]) continue;
        visited[src] = true;
    /*
        reduce the cost if possible 
    */
        for(auto edges : graph[src]){
            int dest = edges.first;
            int destCost = edges.second;
        /*
            relaxation which means if current node cost is greater 
            than source node cost + destination cost
            then reduce their cost
        */
            cost[dest] = min(cost[dest], destCost+srcNodeCost);
            trackNode.push({-cost[dest], dest});
        }
    }
    return cost;
}

/*
    this function will create adjacency List representation of graph
    connection : node1 -> {node2, weight}
*/
void path::create(vector<vector<int>>& connections, int nodes){
    this->nodes = nodes;
    this->graph.resize(nodes);
    for(auto edge : connections){
        if(isValidConnections(edge[0], edge[1]))
            graph[edge[0]].push_back({edge[1], edge[2]});
        else{
            graph.clear();
            cout<<"Invalid connections at "<<edge[0]<<" -> "<<edge[1]<<"\n";
        }
    }
}


/*
    this function will validate if connection is valid or not
*/
bool path::isValidConnections(int src, int dest){
    bool isValidSrc = (src >= 0 && src < this->nodes);
    bool isValidDest = (dest >= 0 && dest < this->nodes);

    return isValidSrc && isValidDest;
}

void path::show(){
    for(int i=0;i<nodes;i++){
        for(auto &edge : graph[i])
            cout<<"{"<<edge.first<<", "<<edge.second<<"}\t";
        cout<<"\n";
    }
}