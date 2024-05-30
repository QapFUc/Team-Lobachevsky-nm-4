#ifndef WIDGET_H
#define WIDGET_H

#include <QBoxLayout>
#include <QGuiApplication>
#include <QLabel>
#include <QLayout>
#include <QLineEdit>
#include <QMenuBar>
#include <QScreen>
#include <QTabWidget>
#include <QTableWidget>
#include <QWidget>
#include <Qt>
#include <QtCharts>
#include <QtDataVisualization>
#include <QtWidgets>

#include "core/netProcess.hpp"
#include "core/task.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"
#include <math.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <signal.h>
#include <iostream>

class Widget : public QWidget {
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();
    void InitTabTask();
    void InitTableTest();
    void UpdateTableTest();
    void InitTableMain();
    void UpdateTableMain();
    void CreateInfoTest();
    void CreateInfoMain();
    void CreateGraphsTest();
    void InitGraphsMain();
    void UpdateGraphsMain();
    void CreateTable2();
    void CreateGraphs();
    void StartSimplexIter();
    void StartCGM();
    void StartSOR();
    void InitDirTask();
    void UpdateDirTask();
    void UpdateInfoTest();
    void UpdateInfoMain();
private slots:

    void SendDatabtnClick();

private:
    NetPattern* Networkpattern;
    Net* Network;
    DirichletTask* DirTask;
    Config config;

    QTabWidget* tabWidget;
    // TaskTab
    QWidget* tabTask;

    QVBoxLayout* MainHLayout;

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
    //TabTableTest
    QWidget* tabTableTest;

    QVBoxLayout* TestInfoLayout;
    QVBoxLayout* MainInfoLayout;

    QTableWidget* TableTest_1;  // real solve
    QTableWidget* TableTest_2;  // iter solve
    QTableWidget* TableTest_3;  // real-iter solve
    // Table Main
    QWidget* tabTableMain;

    QVBoxLayout* MainTableLayout;

    QTableWidget* TableMain_1; // real solve
    QTableWidget* TableMain_2;
    QTableWidget* TableMain_3; 


    QWidget* tab3;
    QWidget* tab4;

    QLineEdit* TestLineEditInfo_1;
    QLineEdit* TestLineEditInfo_2;
    QLineEdit* TestLineEditInfo_3;
    QLineEdit* TestLineEditInfo_4;
    QLineEdit* TestLineEditInfo_5;
    QLineEdit* TestLineEditInfo_6;
    QLineEdit* TestLineEditInfo_7;
    QLineEdit* TestLineEditInfo_8;
    QLineEdit* TestLineEditInfo_9;
    QLineEdit* TestLineEditInfo_10;
    QLineEdit* TestLineEditInfo_11;
    QLineEdit* TestLineEditInfo_12;
    QLineEdit* TestLineEditInfo_13;

    //MainGraphs
    QWidget* tab6;

    Q3DSurface* Maingraph3D;
    QSurfaceDataProxy* MaindataProxy;
    QSurface3DSeries* Mainseries;



    QWidget* tab7;

    QLineEdit* MainLineEditInfo_1;
    QLineEdit* MainLineEditInfo_2;
    QLineEdit* MainLineEditInfo_3;
    QLineEdit* MainLineEditInfo_4;
    QLineEdit* MainLineEditInfo_5;
    QLineEdit* MainLineEditInfo_6;
    QLineEdit* MainLineEditInfo_7;
    QLineEdit* MainLineEditInfo_8;
    QLineEdit* MainLineEditInfo_9;
    QLineEdit* MainLineEditInfo_11;
    QLineEdit* MainLineEditInfo_12;
    QLineEdit* MainLineEditInfo_13;
    QLineEdit* MainLineEditInfo_14;
    QLineEdit* MainLineEditInfo_15;
    QLineEdit* MainLineEditInfo_16;
    QLineEdit* MainLineEditInfo_17;
    QLineEdit* MainLineEditInfo_18;
    QLineEdit* MainLineEditInfo_19;
    QLineEdit* MainLineEditInfo_20;
    QLineEdit* MainLineEditInfo_21;
    QLineEdit* MainLineEditInfo_22;
};
#endif  // WIDGET_H
