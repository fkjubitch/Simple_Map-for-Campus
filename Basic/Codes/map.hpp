#include<vector>
#include<map>
#include<utility>
#include<assert.h>
#include<queue>

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

    protected:
        // private struct
        struct Pair{
            int next; // next node index
            int val; // route val between two nodes
            Pair(int next,int val):next(next),val(val){}
        };
        // private vars
        int n; // addr numbers
        vector<Node> nodes; // index 0 is forsaken
        map<string,int> nameToIndex;
        vector<vector<Pair>> edges;
        vector<vector<int>> minRouteVal;
        vector<vector<vector<int>>> minRoutePassDots; // Dots passing by in the min route
};

class Dijkstra:public Map{
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
    assert(addrName.size()==addrInfo.size());
    n=addrName.size()-1;
    edges=vector<vector<Pair>>(n+1,vector<Pair>());
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
}

// quiry at a dot
Node Map::dotQuiry(string name){
    return nodes.at(nameToIndex.at(name));
}

// quiry between two dots with their min route
pair<int,vector<string>> Map::routeQuiry(string name1,string name2){
    vector<string> temp;
    for(int i:minRoutePassDots[nameToIndex[name1]][nameToIndex[name2]]){
        temp.push_back(nodes.at(i).name);
    }
    pair<int,vector<string>> ret(minRouteVal[nameToIndex[name1]][nameToIndex[name2]] , temp);
    return ret;
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