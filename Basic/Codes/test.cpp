/* A simple test of min-heap-optimized Dijkstra algorithm */

#include<iostream>
#include<vector>
#include<climits>
#include<queue>
#include<fstream>
#include<sstream>

using namespace std;

struct Pair{
    int next;
    int val;
    Pair(int next,int val):next(next),val(val){}
};

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

int n,m;
vector<vector<Pair>> edges(1001);
vector<long long> minVal(1001);
vector<bool> flag(1001);
vector<bool> isConnect(1001);

void updateMinVal(int curr , priority_queue<indexValPair,vector<indexValPair>,cmpindexValPairGreater>& pq){
    auto& currVec = edges.at(curr);
    for(auto it=currVec.begin();it!=currVec.end();it++){
        if(flag.at(it->next)==0){
            long long temp = it->val+minVal.at(curr);
            isConnect.at(it->next)=isConnect.at(curr);
            if(temp<minVal.at(it->next)){
                minVal.at(it->next)=temp;
            }
            pq.push(indexValPair(it->next,minVal.at(it->next)));
        }
    }
}

void findMinRoute(int start,ofstream& output){
    priority_queue<indexValPair,vector<indexValPair>,cmpindexValPairGreater> pq;
    for(int i=1;i<=n;i++){
        isConnect.at(i)=0;
        flag.at(i)=0;
    }
    isConnect.at(start)=1;
    for(int i=0;i<=n;i++){
        minVal.at(i)=LLONG_MAX;
    }
    minVal.at(start)=0;
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
        if(isConnect.at(i)==isConnect.at(start)) output<<minVal.at(i)<<" ";
        else output<<-1<<" ";
    }
    output<<endl;
    output.flush();
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