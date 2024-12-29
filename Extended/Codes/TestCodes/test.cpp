/* A simple test of min-heap-optimized Dijkstra algorithm */

#include<iostream>
#include<vector>
#include<climits>
#include<queue>
#include<fstream>
#include<sstream>

using namespace std;

/*************************************************************************************/
/* Define Area */
/*************************************************************************************/
struct Node{
    string name;
    string info;
    Node(string name,string info):name(name),info(info){}
    Node():Node("",""){}
};

class Map{
    public:
        Map(const vector<string>& addrName,const vector<string>& addrInfo);
        void addEdge(int u,int v,int val);
        Node dotQuiry(string name);
        pair<int,vector<string>> routeQuiry(string name1,string name2);
        vector<Node> junctionsQuery();

    protected:
        // private struct
        struct Pair{
            int next; // next node index
            int val; // route val between two nodes
            Pair(int next,int val):next(next),val(val){}
        };
        // private vars
        int n; // addr numbers, node numbers
        vector<Node> nodes; // index 0 is forsaken
        map<string,int> nameToIndex;
        vector<vector<Pair>> edges;
        vector<vector<int>> minRouteVal;
        vector<vector<vector<int>>> minRoutePassDots; // Dots passing by in the min route
        vector<int> junctions; // Junction Dots indexes
};

class JunctionNodes:virtual public Map{
    public:
        JunctionNodes(const vector<string>&,const vector<string>&);
        void findJunctions();

    private:
        // private vars
        int count;
        vector<int> visited;
        vector<int> low;
        vector<vector<int>> treeEdges; // dfs Tree , direction graph
        vector<bool> v; // visited or not (for dfsLO)

        //private functions
        bool dfsFO(int curr); // first order dfs
        void dfsLO(int curr); // last order dfs
};

/*************************************************************************************/
/* JunctionNodes */
/*************************************************************************************/
// construct function
JunctionNodes::JunctionNodes(const vector<string>& addrName,const vector<string>& addrInfo):Map(addrName,addrInfo),visited(vector<int>(n+1)),low(vector<int>(n+1)),treeEdges(vector<vector<int>>(n+1,vector<int>())),v(vector<bool>(n+1)){}

// Find Junction Nodes main function
void JunctionNodes::findJunctions(){
    count=0;
    for(int i=1;i<=n;i++){
        visited.at(i)=0;
        low.at(i)=INT_MAX;
        treeEdges.at(i).clear();
        v.at(i)=0;
    }
    dfsFO(1); // if edges has no nodes then throw out_of_range
    if(treeEdges.at(1).size()>1){
        junctions.push_back(1);
    }
    dfsLO(1);
}

// private function : first order dfs, construct dfs tree and vector::visited
bool JunctionNodes::dfsFO(int curr){
    if(visited.at(curr)) return false;
    visited.at(curr) = ++count;
    for(const Pair& nextPair:edges.at(curr)){
        if(dfsFO(nextPair.next)){
            treeEdges.at(curr).push_back(nextPair.next);
        }
    }
    return true;
}

// private function : last order dfs
void JunctionNodes::dfsLO(int curr){
    /*
        hypothesis:
        for root:
            if treeEdges.at(root).size() > 1 , then root is a junction
        for leaf node curr:
            none of them are junctions
        for non-leaf & non-root node curr:
            status transition function —— low[curr]=min(low[w],visited[k]),
            k-curr are in edges , visited[k] < visited[curr] , curr->w are in treeEdges
            if visited[curr] <= low[w] , then curr is a junction
    */
    // dfs last order
    if(v.at(curr)) return;
    v.at(curr)=1;
    for(const Pair& nextPair:edges.at(curr)){
        dfsLO(nextPair.next);
    }
    for(int i:treeEdges.at(curr)){
        low.at(curr)=min(low.at(curr),low.at(i));
    }
    for(Pair& p:edges.at(curr)){
        if(visited[p.next]<visited[curr]){
            low.at(curr)=min(low.at(curr),visited[p.next]);
        }
    }
    if(treeEdges.at(curr).empty()) return; // leaf
    if(curr = 1) return; //root;
    for(int i:treeEdges.at(curr)){
        if(visited[curr]<=low.at(i)){
            junctions.push_back(curr);
            break;
        }
    }
}

int main(){
    ifstream input("./input.txt",ios::in);
    ofstream output("./output.txt",ios::out);
    char buffer;
    string inputString;
    while(input.peek()!=-1){
        input.get(buffer);
        inputString+=buffer;
    }
    stringstream ss(inputString);
    ss>>n>>m;
    for(int i=0;i<m;i++){
        int u,v,w; ss>>u>>v>>w;
        edges.at(u).push_back(Pair(v,w));
    }
    for(int i=1;i<=n;i++){
        findMinRoute(i,output);
    }
    return 0;
}