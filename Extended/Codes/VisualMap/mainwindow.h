#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLabel>
#include <QButtonGroup>
#include <QFile>
#include <QMainWindow>
#include "map.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

string QStr2Str(const QString qStr);

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(string f,ExtendMap& extmap,QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    // addr buttons
    void on_radioButton_1_toggled(bool checked);
    void on_radioButton_2_toggled(bool checked);
    void on_radioButton_3_toggled(bool checked);
    void on_radioButton_4_toggled(bool checked);
    void on_radioButton_5_toggled(bool checked);
    void on_radioButton_6_toggled(bool checked);
    void on_radioButton_7_toggled(bool checked);
    void on_radioButton_8_toggled(bool checked);
    void on_radioButton_9_toggled(bool checked);
    void on_radioButton_10_toggled(bool checked);
    void on_radioButton_11_toggled(bool checked);
    void on_radioButton_12_toggled(bool checked);
    void on_radioButton_13_toggled(bool checked);
    void on_radioButton_14_toggled(bool checked);
    void on_radioButton_15_toggled(bool checked);
    void on_radioButton_16_toggled(bool checked);
    void on_radioButton_17_toggled(bool checked);
    void on_radioButton_18_toggled(bool checked);
    void on_radioButton_19_toggled(bool checked);
    void on_radioButton_20_toggled(bool checked);
    void on_radioButton_21_toggled(bool checked);

    // selections
    void on_action_1_triggered();
    void on_action_2_triggered();
    void on_action_3_triggered();
    void on_action_4_triggered();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    ExtendMap& extMap;
    string dataFileName;
    int choice;
    QButtonGroup* radioButtons;
    vector<QLabel*> routes;
    queue<int> order; // for two dots' min route query
    pair<vector<int>,vector<vector<Node>>> allPaths;
    string registerStr4AllPaths;

};
#endif // MAINWINDOW_H
