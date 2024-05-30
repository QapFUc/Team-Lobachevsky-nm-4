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
    void UpdateGraphsTest() {};
    void InitGraphsMain();
    void UpdateGraphsMain();
    void CreateTable2();
    void CreateGraphs();
    void StartSimplexIter();
    void StartCGM();
    void StartSOR();
    void StartTestCGM();
    void StartTestSOR();
    void StartTestSimpleIter();
    void InitDirTask();
    void UpdateDirTask();
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

    //MainGraphs
    QWidget* tab6;

    Q3DSurface* Maingraph3D;
    QSurfaceDataProxy* MaindataProxy;
    QSurface3DSeries* Mainseries;



    QWidget* tab7;

    std::function<double(double, double)> fRHS_test;
    std::function<double(double, double, Config)> fBound_test;
    std::function<double(double, double)> fRHS_main;
    std::function<double(double, double, Config)> fBound_main;
    std::function<double(double, double)> fTrueSol_test;

};
#endif  // WIDGET_H
