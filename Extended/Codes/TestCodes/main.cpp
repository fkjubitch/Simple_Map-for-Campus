#include<iostream>
#include<fstream>
#include<sstream>
#include<cstring>
#include<unistd.h>
#include"map.hpp"

int main(){
    ifstream graphInput("../Tests/campus_map.txt",ios::in);
    ifstream queryIn("../Tests/query.txt",ios::in);
    ofstream resultOut("../Tests/result.txt",ios::out);
    int n;

    /* The first line contains the node number */
    [&](){
        char buffer[0xffff]={0};
        graphInput.getline(buffer,0xffff);
        stringstream ss(buffer);
        string temp;
        ss>>temp>>temp;
        n=stoi(temp);
    }();
    vector<string> addrName(n+1),addrInfo(n+1); // Use the node number n to initialize addr vectors

    /* The next two lines are useless */
    [&](){char buffer[0xffff]={0};graphInput.getline(buffer,0xffff);graphInput.getline(buffer,0xffff);}();

    /* Read the first stage —— Address Infomation */
    while(1){
        stringstream ss;
        char buffer[0xffff]={0};
        graphInput.getline(buffer,0xffff);
        ss<<buffer;
        string No,adName,adInfo;
        ss>>No>>adName>>adInfo;
        if(adInfo.length()==0) break; // If read the empty line then break this stage
        int no(stoi(No));
        addrName.at(no)=adName;
        addrInfo.at(no)=adInfo;
    }
    
    /* Construct Object to get & cal details */
    ExtendMap solution(addrName,addrInfo);

    /* The next two lines are useless */
    [&](){char buffer[0xffff]={0};graphInput.getline(buffer,0xffff);graphInput.getline(buffer,0xffff);}();

    /* Read the second stage —— Edges & Values */
    while(graphInput.peek()!=-1){ // If read the eof then break this stage
        stringstream ss;
        char buffer[0xffff]={0};
        graphInput.getline(buffer,0xffff);
        ss<<buffer;
        string uStr,vStr,valStr;
        ss>>uStr>>vStr>>valStr;
        if(valStr.length()==0) break; // If read the empty line then break this stage
        int u(stoi(uStr)),v(stoi(vStr)),val(stoi(valStr));
        solution.addEdge(u,v,val);
    }

    /* Start to find min route */ 
    for(int i=1;i<=n;i++){
        solution.findMinRoute(i);
    }

    /* Query Input: The first line is forsaken */
    [&](){char buffer[0xffff]={0};queryIn.getline(buffer,0xffff);}();

    /* Queries */
    try{
        while(queryIn.peek()!=-1){
            stringstream ss;
            char buffer[0xffff]={0};
            queryIn.getline(buffer,0xffff);
            ss<<buffer;
            string selection; ss>>selection; if(selection.length()==0) continue;
            int sel=stoi(selection);
            switch(sel){
                case 1:{
                    string addr; ss>>addr;
                    resultOut<<addr<<" : "<<solution.dotQuiry(addr).info<<endl<<endl;
                    break;
                }
                case 2:{
                    string uStr,vStr; ss>>uStr>>vStr;
                    auto p = solution.routeQuiry(uStr,vStr);
                    resultOut<<uStr<<" To "<<vStr<<" : "<<"路线 ";
                    for(int i=0;i<p.second.size();i++){
                        resultOut<<p.second.at(i);
                        if(i!=p.second.size()-1){resultOut<<" → ";}
                    }
                    resultOut<<" "<<p.first<<"米"<<endl<<endl;
                    break;
                }
                case 3:{
                    // find junctions
                    solution.findJunctions();
                    resultOut<<"关键节点 : ";
                    vector<Node> temp(solution.junctionsQuery());
                    if(temp.empty()) resultOut<<"无";
                    else{
                        for(size_t i=0;i<temp.size();i++){
                            resultOut<<temp[i].name;
                            if(i<temp.size()-1){resultOut<<",";}
                        }
                    }
                    resultOut<<endl<<endl;
                    break;
                }
                case 4:{
                    // find all paths from u to v;
                    string uStr,vStr; ss>>uStr>>vStr;
                    solution.findAllPaths(uStr,vStr);
                    pair<vector<int>,vector<vector<Node>>> temp(solution.allPathsQuery());
                    resultOut<<"从 "<<uStr<<" 到 "<<vStr<<" 的所有路径 : "<<endl;
                    vector<int>& vecVal(temp.first); int i=0;
                    for(vector<Node>& vec:temp.second){
                        for(int i=0;i<vec.size()-1;i++){
                            resultOut<<vec[i].name<<" → ";
                        }
                        resultOut<<vec[vec.size()-1].name<<" "<<vecVal.at(i)<<"米"<<endl;
                        resultOut.flush();
                        i++;
                    }
                    resultOut<<endl;
                    break;
                }
            }
        }
    }
    catch(out_of_range e){
        cerr<<"No such place in data"<<endl;
    }

    return 0;
}