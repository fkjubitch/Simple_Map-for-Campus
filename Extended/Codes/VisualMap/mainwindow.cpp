#include "mainwindow.h"
#include "./ui_mainwindow.h"

string QStr2Str(const QString qStr)
{
    QByteArray data = qStr.toUtf8();
    return string(data);
}

MainWindow::MainWindow(string f,ExtendMap& extmap,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , extMap(extmap)
    , dataFileName(f)
    , choice(0)
{
    ui->setupUi(this);
    radioButtons = new QButtonGroup();
    radioButtons->setExclusive(true);
    radioButtons->addButton(ui->radioButton_1,1);
    radioButtons->addButton(ui->radioButton_2,2);
    radioButtons->addButton(ui->radioButton_3,3);
    radioButtons->addButton(ui->radioButton_4,4);
    radioButtons->addButton(ui->radioButton_5,5);
    radioButtons->addButton(ui->radioButton_6,6);
    radioButtons->addButton(ui->radioButton_7,7);
    radioButtons->addButton(ui->radioButton_8,8);
    radioButtons->addButton(ui->radioButton_9,9);
    radioButtons->addButton(ui->radioButton_10,10);
    radioButtons->addButton(ui->radioButton_11,11);
    radioButtons->addButton(ui->radioButton_12,12);
    radioButtons->addButton(ui->radioButton_13,13);
    radioButtons->addButton(ui->radioButton_14,14);
    radioButtons->addButton(ui->radioButton_15,15);
    radioButtons->addButton(ui->radioButton_16,16);
    radioButtons->addButton(ui->radioButton_17,17);
    radioButtons->addButton(ui->radioButton_18,18);
    radioButtons->addButton(ui->radioButton_19,19);
    radioButtons->addButton(ui->radioButton_20,20);
    radioButtons->addButton(ui->radioButton_21,21);

    routes.push_back(ui->label_0);
    routes.push_back(ui->label_1);
    routes.push_back(ui->label_2);
    routes.push_back(ui->label_3);
    routes.push_back(ui->label_4);
    routes.push_back(ui->label_5);
    routes.push_back(ui->label_6);
    routes.push_back(ui->label_7);
    routes.push_back(ui->label_8);
    routes.push_back(ui->label_9);
    routes.push_back(ui->label_10);
    routes.push_back(ui->label_11);
    routes.push_back(ui->label_12);
    routes.push_back(ui->label_13);
    routes.push_back(ui->label_14);
    routes.push_back(ui->label_15);
    routes.push_back(ui->label_16);
    routes.push_back(ui->label_17);
    routes.push_back(ui->label_18);
    routes.push_back(ui->label_19);
    routes.push_back(ui->label_20);
    routes.push_back(ui->label_21);
    routes.push_back(ui->label_22);
    routes.push_back(ui->label_23);
    routes.push_back(ui->label_24);
    routes.push_back(ui->label_25);
    routes.push_back(ui->label_26);
    routes.push_back(ui->label_27);
    routes.push_back(ui->label_28);
    routes.push_back(ui->label_29);
    routes.push_back(ui->label_30);
    routes.push_back(ui->label_31);
    routes.push_back(ui->label_32);
    routes.push_back(ui->label_33);
    routes.push_back(ui->label_34);
    routes.push_back(ui->label_35);
    routes.push_back(ui->label_36);
    routes.push_back(ui->label_37);

    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    ui->textEdit->setVisible(false);
    ui->pushButton->setVisible(false);
    setWindowIcon(QIcon(":/icon.png"));
}

MainWindow::~MainWindow()
{
    delete radioButtons;
    delete ui;
}

template<typename T>
void eraseTargetInQueue(queue<T>& q,const T& target){
    queue<T> assist;
    while(!q.empty()){
        if(q.front()!=target){
            assist.push(q.front());
        }
        q.pop();
    }
    q=assist;
}

template<typename T>
void clearQueue(queue<T>& q){
    while(!q.empty()){
        q.pop();
    }
}

// addr 1
void MainWindow::on_radioButton_1_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0){
        string temp(extMap.dotQuiry(1).name); temp+=" :\n"; temp+=(extMap.dotQuiry(1).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(1);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(1).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(1);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(1).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,1));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,1);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 2
void MainWindow::on_radioButton_2_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0){
        string temp(extMap.dotQuiry(2).name); temp+=" :\n"; temp+=(extMap.dotQuiry(2).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(2);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(2).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(2);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(2).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,2));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,2);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 3
void MainWindow::on_radioButton_3_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0){
        string temp(extMap.dotQuiry(3).name); temp+=" :\n"; temp+=(extMap.dotQuiry(3).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(3);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(3).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(3);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(3).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,3));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,3);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 4
void MainWindow::on_radioButton_4_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0){
        string temp(extMap.dotQuiry(4).name); temp+=" :\n"; temp+=(extMap.dotQuiry(4).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(4);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(4).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(4);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(4).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,4));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,4);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 5
void MainWindow::on_radioButton_5_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0){
        string temp(extMap.dotQuiry(5).name); temp+=" :\n"; temp+=(extMap.dotQuiry(5).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(5);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(5).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(5);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(5).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,5));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,5);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 6
void MainWindow::on_radioButton_6_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(6).name); temp+=" :\n"; temp+=(extMap.dotQuiry(6).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(6);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(6).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(6);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(6).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,6));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,6);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 7
void MainWindow::on_radioButton_7_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(7).name); temp+=" :\n"; temp+=(extMap.dotQuiry(7).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(7);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(7).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(7);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(7).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,7));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,7);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 8
void MainWindow::on_radioButton_8_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(8).name); temp+=" :\n"; temp+=(extMap.dotQuiry(8).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(8);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(8).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(8);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(8).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,8));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,8);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 9
void MainWindow::on_radioButton_9_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(9).name); temp+=" :\n"; temp+=(extMap.dotQuiry(9).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(9);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(9).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(9);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(9).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,9));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,9);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 10
void MainWindow::on_radioButton_10_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(10).name); temp+=" :\n"; temp+=(extMap.dotQuiry(10).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(10);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(10).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(10);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(10).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,10));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,10);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 11
void MainWindow::on_radioButton_11_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(11).name); temp+=" :\n"; temp+=(extMap.dotQuiry(11).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(11);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(11).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(11);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(11).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,11));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,11);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 12
void MainWindow::on_radioButton_12_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(12).name); temp+=" :\n"; temp+=(extMap.dotQuiry(12).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(12);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(12).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(12);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(12).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,12));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,12);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 13
void MainWindow::on_radioButton_13_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(13).name); temp+=" :\n"; temp+=(extMap.dotQuiry(13).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(13);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(13).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(13);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(13).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,13));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,13);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 14
void MainWindow::on_radioButton_14_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(14).name); temp+=" :\n"; temp+=(extMap.dotQuiry(14).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(14);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(14).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(14);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(14).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,14));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,14);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 15
void MainWindow::on_radioButton_15_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(15).name); temp+=" :\n"; temp+=(extMap.dotQuiry(15).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(15);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(15).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(15);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(15).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,15));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,15);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 16
void MainWindow::on_radioButton_16_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(16).name); temp+=" :\n"; temp+=(extMap.dotQuiry(16).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(16);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(16).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(16);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(16).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,16));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,16);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 17
void MainWindow::on_radioButton_17_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(17).name); temp+=" :\n"; temp+=(extMap.dotQuiry(17).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(17);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(17).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(17);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(17).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,17));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,17);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 18
void MainWindow::on_radioButton_18_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(18).name); temp+=" :\n"; temp+=(extMap.dotQuiry(18).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(18);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(18).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(18);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(18).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,18));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,18);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 19
void MainWindow::on_radioButton_19_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(19).name); temp+=" :\n"; temp+=(extMap.dotQuiry(19).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(19);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(19).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(19);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(19).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,19));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,19);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 20
void MainWindow::on_radioButton_20_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(20).name); temp+=" :\n"; temp+=(extMap.dotQuiry(20).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(20);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(20).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(20);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(20).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,20));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,20);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}

// addr 21
void MainWindow::on_radioButton_21_toggled(bool checked)
{
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    if(choice==0)
    {
        string temp(extMap.dotQuiry(21).name); temp+=" :\n"; temp+=(extMap.dotQuiry(21).info);
        if(checked) ui->textBrowser->setText(QString::fromStdString(temp));
    }
    else if(choice!=1){
        if(checked){
            if(order.size()==0){
                order.push(21);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(21).name;
                temp+="\n";
                ui->textBrowser->setText(QString::fromStdString(temp));
            }
            else{
                if(order.size()==2){
                    order.pop();
                }
                int start = order.front();
                order.push(21);
                string temp("起点 : ");
                temp+=extMap.dotQuiry(start).name;
                temp+="\n终点 : ";
                temp+=extMap.dotQuiry(21).name;
                temp+="\n";
                if(choice==2){
                    pair<int,vector<string>> tempPair(extMap.routeQuiry(start,21));
                    for(int i=0;i<tempPair.second.size()-1;i++){
                        temp+=tempPair.second.at(i);
                        temp+=" → ";
                        routes.at(extMap.routeIndexQuery(tempPair.second.at(i),tempPair.second.at(i+1)))->setVisible(true);
                    }
                    temp+=tempPair.second.at(tempPair.second.size()-1);
                    temp+="\n路程 : ";
                    temp+=to_string(tempPair.first);
                    ui->textBrowser->setText(QString::fromStdString(temp));
                }
                else{
                    extMap.findAllPaths(start,21);
                    allPaths = extMap.allPathsQuery();
                    vector<int>& vecVal(allPaths.first);
                    temp+="共有 "; temp+=to_string(vecVal.size());
                    temp+=" 条路径 , 请在下方的输入框中填写要查询的路径编号并提交 (编号从1至"; temp+=to_string(vecVal.size()); temp+=")\n";
                    ui->textBrowser->setText(QString::fromStdString(temp));
                    registerStr4AllPaths = temp;
                }
            }
        }
    }
}


void MainWindow::on_action_1_triggered()
{
    ui->textEdit->setVisible(false);
    ui->pushButton->setVisible(false);
    clearQueue(order);
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    radioButtons->setExclusive(false);
    choice = 0;
    for(int i=1;i<=21;i++){
        radioButtons->button(i)->setChecked(false);
    }
    radioButtons->setExclusive(true);
}


void MainWindow::on_action_2_triggered()
{
    ui->textEdit->setVisible(false);
    ui->pushButton->setVisible(false);
    clearQueue(order);
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    radioButtons->setExclusive(false);
    choice = 1;
    for(int i=1;i<=21;i++){
        radioButtons->button(i)->setChecked(false);
    }
    string tempString("关键节点 : \n");
    extMap.findJunctions();
    vector<Node> tempVec(extMap.junctionsQuery());
    for(int i=0;i<tempVec.size()-1;i++){
        tempString+=tempVec.at(i).name;
        tempString+=" , ";
        radioButtons->button(extMap.nameIndexQuery(tempVec.at(i).name))->setChecked(true);
    }
    tempString+=tempVec.at(tempVec.size()-1).name;
    ui->textBrowser->setText(QString::fromStdString(tempString));
    radioButtons->button(extMap.nameIndexQuery(tempVec.at(tempVec.size()-1).name))->setChecked(true);
}


void MainWindow::on_action_3_triggered()
{
    ui->textEdit->setVisible(false);
    ui->pushButton->setVisible(false);
    clearQueue(order);
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    radioButtons->setExclusive(false);
    choice = 2;
    for(int i=1;i<=21;i++){
        radioButtons->button(i)->setChecked(false);
    }
    radioButtons->setExclusive(true);
    ui->textBrowser->setText("请选择要查询路径的起点和终点\n");
}


void MainWindow::on_action_4_triggered()
{
    ui->textEdit->setVisible(true);
    ui->pushButton->setVisible(true);
    clearQueue(order);
    for(int i=1;i<routes.size();i++){
        routes.at(i)->setVisible(false);
    }
    radioButtons->setExclusive(false);
    choice = 3;
    for(int i=1;i<=21;i++){
        radioButtons->button(i)->setChecked(false);
    }
    radioButtons->setExclusive(true);
    ui->textBrowser->setText("请选择要查询路径的起点和终点\n");
}


void MainWindow::on_pushButton_clicked()
{
    try{
        if(choice==3){
            string temp(registerStr4AllPaths);
            temp += "\n";
            string s = QStr2Str(ui->textEdit->toPlainText());
            int index = stoi(s);
            index--;
            vector<int>& vals(allPaths.first);
            vector<vector<Node>>& paths(allPaths.second);
            for(int i=0;i<paths.at(index).size()-1;i++){
                temp+=paths.at(index).at(i).name;
                temp+=" → ";
                routes.at(extMap.routeIndexQuery(paths.at(index).at(i).name,paths.at(index).at(i+1).name))->setVisible(true);
            }
            temp+=paths.at(index).at(paths.at(index).size()-1).name;
            temp+="\n路程 : ";
            temp+=to_string(vals.at(index));
            ui->textBrowser->setText(QString::fromStdString(temp));
        }
    }
    catch(out_of_range e){
        ui->textBrowser->setText("输入的数字越界了！或者还没有选两个点！");
    }
    catch(invalid_argument e){
        ui->textBrowser->setText("输入的内容无效！必须是范围内的数字！");
    }
}



