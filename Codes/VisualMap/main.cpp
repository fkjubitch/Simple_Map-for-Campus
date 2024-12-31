#include "mainwindow.h"

#include <QDebug>
#include <sstream>
#include <QApplication>
#include <QTextStream>

int main(int argc, char *argv[])
{
    string fileName(":/new/img/campus_map.txt");
    QFile file(QString::fromStdString(fileName));
    int n;

    // read only
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {}
    else {
        qDebug() << "Cannot open source data.";
    }

    QTextStream f(&file);

    /* The first line contains the node number */
    [&](){
        QString buffer = f.readLine();
        stringstream ss(QStr2Str(buffer));
        string temp;
        ss>>temp>>temp;
        n=stoi(temp);
    }();
    vector<string> addrName(n+1),addrInfo(n+1); // Use the node number n to initialize addr vectors

    /* The next two lines are useless */
    [&](){f.readLine(); f.readLine();}();

    /* Read the first stage —— Address Infomation */
    while(1){
        QString buffer = f.readLine();
        stringstream ss(QStr2Str(buffer));
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
    [&](){f.readLine(); f.readLine();}();

    /* Read the second stage —— Edges & Values */
    while(!f.atEnd()){ // If read the eof then break this stage
        QString buffer = f.readLine();
        stringstream ss(QStr2Str(buffer));
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

    file.close();

    QApplication a(argc, argv);
    MainWindow w(fileName,solution);
    w.show();
    return a.exec();
}
