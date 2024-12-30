#ifndef MAP_H
#define MAP_H

#include<vector>
#include<map>
#include<utility>
#include<assert.h>
#include<queue>
#include<string>

using namespace std;

/*************************************************************************************/
/*
    Usage information:
    1. Create a Map heritage object
    2. add edges
    3. dots qureies
    4. Dijkstra operation / Junctions operation / All Paths operation
    5. route queries / junctions queries / All Paths queries
*/
/*************************************************************************************/


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
    Node dotQuiry(int index);
    pair<int,vector<string>> routeQuiry(int from,int to);
    vector<Node> junctionsQuery();
    pair<vector<int>,vector<vector<Node>>> allPathsQuery();
    int nameIndexQuery(string name);
    int routeIndexQuery(string from,string to);

protected:
    // private struct
    struct Pair{
        int next; // next node index
        int val; // route val between two nodes
        Pair(int next,int val):next(next),val(val){}
    };
    // private vars
    int n; // addr numbers, node numbers
    int m; // edge number counter, eventually equals to edge numbers
    vector<Node> nodes; // index 0 is forsaken
    map<string,int> nameToIndex;
    vector<vector<Pair>> edges;
    vector<vector<int>> edgesNo; // The number of each edge, exclude 0
    /* Dijstra */
    vector<vector<int>> minRouteVal;
    vector<vector<vector<int>>> minRoutePassDots; // Dots passing by in the min route
    /* Junctions */
    vector<int> junctions; // Junction Dots indexes
    /* AllPaths */
    vector<int> allPathsVal; // Register-like var to store all paths value between two dots
    vector<vector<int>> allPaths; // Register-like var to store all paths between two dots
};

class Dijkstra:virtual public Map{
public:
    Dijkstra(const vector<string>&,const vector<string>&);
    void findMinRoute(int start);

private:
    // private structs
    struct indexValPair{
        int index;
        int val;
        indexValPair(int index,int val):index(index),val(val){}
        indexValPair():indexValPair(0,0){}
    };
    struct cmpindexValPairGreater{
        bool operator()(indexValPair& left,indexValPair& right){
            return left.val>=right.val;
        }
    };
    // private vars
    vector<int> minVal;
    vector<vector<int>> minDots;
    vector<bool> flag;

    // private functions
    void updateMinVal(int, priority_queue<indexValPair,vector<indexValPair>,cmpindexValPairGreater>&);
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

class AllPaths:virtual public Map{
public:
    AllPaths(const vector<string>&,const vector<string>&);
    void findAllPaths(int, int);

private:
    // private vars
    int val;
    vector<bool> visited;
    vector<int> stackVec;
    // private functions
    void dfs(int,int);
};

class ExtendMap:public Dijkstra,public JunctionNodes,public AllPaths{
public:
    ExtendMap(const vector<string>&,const vector<string>&);
};

#endif // MAP_H
