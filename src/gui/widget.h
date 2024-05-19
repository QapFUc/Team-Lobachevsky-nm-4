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
    void CreateTable2();
    void CreateGraphs();
private slots:

    void onClick();

private:
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
    QComboBox* InputTask;
    QPushButton* SendDatabtn;


    QWidget* tab2;
    QWidget* tab3;
    QWidget* tab4;
    QWidget* tab5;
    QWidget* tab6;
    QWidget* tab7;
};
#endif  // WIDGET_H
