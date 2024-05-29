#ifndef WIDGET_H
#define WIDGET_H

#include <QGuiApplication>
#include <QLabel>
#include <QLayout>
#include <QMenuBar>
#include <QScreen>
#include <QTabWidget>
#include <QTableWidget>
#include <QWidget>
#include <QLineEdit>
#include <QBoxLayout>
#include <Qt>

#include <qcombobox.h>
#include <qpushbutton.h>
#include <signal.h>
#include "dataTypes/config.hpp"
#include "core/netProcess.hpp"
#include "dataTypes/common.hpp"
#include "core/netProcess.hpp"
#include "core/task.hpp"

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    void InitTabTask();
    void CreateTableTest(int x, int y);
    void CreateTableMain(int x, int y);
    void CreateInfoTest();
    void CreateInfoMain();
    void CreateGraphsTest();
    void CreateGraphsMain();
    void CreateTable2();
    void CreateGraphs();
    static void StartSimplexIter(DirichletTask& dt);
    static void StartCGM(DirichletTask& dt);
    void InitDirTask();
    static void UpdateDirTask(Config& cfg, DirichletTask& dt, NetPattern& np, Net& net);
    static void UpdateAllData(Config& cfg, DirichletTask& dt, NetPattern& np, Net& net);
private slots:

    void SendDatabtnClick();

private:
    NetPattern* Networkpattern;
    Net* Network;
    DirichletTask* DirTask;
    QTabWidget* tabWidget;

    QWidget* tabTask;

    QVBoxLayout* MainHLayout;
    QVBoxLayout* TestTableLayout;
    QVBoxLayout* MainTableLayout;
    QVBoxLayout *TestInfoLayout;
    QVBoxLayout *MainInfoLayout;

    QLineEdit* InputN;
    QLineEdit* InputM;
    QLineEdit* InputEps;
    QLineEdit* InputMaxStep;
    QLineEdit* InputOmega;
    QLineEdit* InputStartXArea;
    QLineEdit* InputEndXArea;
    QLineEdit* InputStartYArea;
    QLineEdit* InputEndYArea;
    QComboBox* InputTask;
    QComboBox* InputStartx;
    QPushButton* SendDatabtn;

    Config config;


    QWidget* tab2;
    QWidget* tab3;
    QWidget* tab4;
    QWidget* tab5;
    QWidget* tab6;
    QWidget* tab7;
};
#endif  // WIDGET_H
