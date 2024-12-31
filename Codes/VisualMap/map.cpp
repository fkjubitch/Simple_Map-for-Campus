#include"map.h"

/*************************************************************************************/
/* Implement Area */
/*************************************************************************************/
/*************************************************************************************/
/* Map */
/*************************************************************************************/
// construct function
Map::Map(const vector<string>& addrName,const vector<string>& addrInfo){
    // plz ensure addrName.size()==addrInfo.size()
    // index begin at 1,end at n
    assert(addrName.size() == addrInfo.size());
    m = 0;
    n = addrName.size() - 1;
    edges=vector<vector<Pair>>(n+1,vector<Pair>());
    edgesNo=vector<vector<int>>(n+1,vector<int>(n+1));
    nodes.push_back(Node());
    for(size_t i=1;i<=n;i++){
        nodes.push_back(Node(addrName[i],addrInfo[i]));
        nameToIndex[addrName[i]]=i;
    }
    minRouteVal=vector<vector<int>>(n+1,vector<int>(n+1));
    minRoutePassDots=vector<vector<vector<int>>>(n+1,vector<vector<int>>(n+1,vector<int>()));
}

// add an edge
void Map::addEdge(int u,int v,int val){
    edges.at(u).push_back(Pair(v,val));
    edges.at(v).push_back(Pair(u,val));
    edgesNo.at(u).at(v)=m+1;
    edgesNo.at(v).at(u)=m+1;
    m++;
}

// quiry at a dot
Node Map::dotQuiry(int index){
    return nodes.at(index);
}

// quiry between two dots with their min route
pair<int,vector<string>> Map::routeQuiry(int from,int to){
    vector<string> temp;
    for(int i:minRoutePassDots[from][to]){
        temp.push_back(nodes.at(i).name);
    }
    pair<int,vector<string>> ret(minRouteVal[from][to] , temp);
    return ret;
}

// query at junction nodes
vector<Node> Map::junctionsQuery(){
    vector<Node> ret;
    for(int i:junctions){
        ret.push_back(nodes.at(i));
    }
    return ret;
}

// query from start to end
pair<vector<int>,vector<vector<Node>>> Map::allPathsQuery(){
    vector<vector<Node>> ret;
    for(vector<int>& temp:allPaths){
        vector<Node> vec;
        for(int i:temp){
            vec.push_back(nodes.at(i));
        }
        ret.push_back(vec);
    }
    return {allPathsVal,ret};
}

// name To Index query
int Map::nameIndexQuery(string name){
    return nameToIndex.at(name);
}

// route Index query
int Map::routeIndexQuery(string from,string to){
    return edgesNo.at(nameToIndex.at(from)).at(nameToIndex.at(to));
}

/*************************************************************************************/
/* Dijkstra */
/*************************************************************************************/
// construct function
Dijkstra::Dijkstra(const vector<string>& addrName,const vector<string>& addrInfo):Map(addrName,addrInfo),minVal(vector<int>(n+1)),flag(vector<bool>(n+1)),minDots(vector<vector<int>>(n+1,vector<int>())){}

// Dijkstra algorithm main function
void Dijkstra::findMinRoute(int start){ // start should always begin at 1, 0 is forsaken
    priority_queue<indexValPair,vector<indexValPair>,cmpindexValPairGreater> pq; // min heap optimization
    // Initialize key vars everytime it calculate
    for(int i=1;i<=n;i++){
        flag.at(i)=0;
        minVal.at(i)=INT_MAX;
        minDots.at(i).clear();
    }
    minVal.at(start)=0;
    minDots.at(start).push_back(start);
    pq.push(indexValPair(start,0));
    for(int i=1;i<n;i++){
        indexValPair top;
        while(!pq.empty()){
            top=pq.top();
            pq.pop();
            if(flag.at(top.index)==0){
                flag.at(top.index)=1;
                break;
            }
        }
        updateMinVal(top.index,pq);
    }
    for(int i=1;i<=n;i++){
        minRouteVal[start][i]=minVal.at(i);
        minRoutePassDots[start][i]=minDots.at(i);
    }
}

// private function: update minVal after fixing each dot
void Dijkstra::updateMinVal(int curr , priority_queue<indexValPair,vector<indexValPair>,cmpindexValPairGreater>& pq){
    auto& currVec = edges.at(curr);
    for(auto it=currVec.begin();it!=currVec.end();it++){
        if(flag.at(it->next)==0){
            int temp = it->val+minVal.at(curr);
            if(temp<minVal.at(it->next)){
                minVal.at(it->next)=temp;
                minDots.at(it->next)=minDots.at(curr);
                minDots.at(it->next).push_back(it->next);
            }
            pq.push(indexValPair(it->next,minVal.at(it->next)));
        }
    }
}

/*************************************************************************************/
/* JunctionNodes */
/*************************************************************************************/
// construct function
JunctionNodes::JunctionNodes(const vector<string>& addrName,const vector<string>& addrInfo):Map(addrName,addrInfo),visited(vector<int>(n+1)),low(vector<int>(n+1)),treeEdges(vector<vector<int>>(n+1,vector<int>())),v(vector<bool>(n+1)){}

// Find Junction Nodes main function
void JunctionNodes::findJunctions(){
    junctions.clear();
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
    if(curr == 1) return; //root;
    for(int i:treeEdges.at(curr)){
        if(visited[curr]<=low.at(i)){
            junctions.push_back(curr);
            break;
        }
    }
}

/*************************************************************************************/
/* AllPaths */
/*************************************************************************************/
// construct function
AllPaths::AllPaths(const vector<string>& addrName,const vector<string>& addrInfo):Map(addrName,addrInfo),visited(vector<bool>(n+1)){
    visited.at(0)=1;
}

// find all paths from start to end
void AllPaths::findAllPaths(int start, int end){
    val=0;
    allPaths.clear();
    allPathsVal.clear();
    dfs(start,end);
}

// private function: dfs for findAllPaths
void AllPaths::dfs(int curr,int end){
    if(visited.at(curr)) return;
    visited.at(curr)=1;
    stackVec.push_back(curr);
    if(curr==end){
        allPaths.push_back(stackVec);
        allPathsVal.push_back(val);
    }
    else{
        for(const Pair& p:edges.at(curr)){
            val+=p.val;
            dfs(p.next,end);
            val-=p.val;
        }
    }
    stackVec.pop_back();
    visited.at(curr)=0;
}

/*************************************************************************************/
/* Special Area */
/*************************************************************************************/

/*************************************************************************************/
/* ExtendMap */
/*************************************************************************************/

// construct function
ExtendMap::ExtendMap(const vector<string>& addrName,const vector<string>& addrInfo):Map(addrName,addrInfo),Dijkstra(addrName,addrInfo),JunctionNodes(addrName,addrInfo),AllPaths(addrName,addrInfo){}
