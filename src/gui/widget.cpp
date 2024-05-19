#include "widget.h"

#include <QtCharts>
#include <QtWidgets>
#include <qboxlayout.h>
#include <qcombobox.h>
#include <qlayoutitem.h>
#include <qnamespace.h>
#include <qpushbutton.h>
#include <qstyleoption.h>
#include <qtextedit.h>
#include <qwidget.h>

Widget::Widget(QWidget* parent) : QWidget(parent) {
    setWindowTitle("LobachevskyLab");

    // Загрузка стиля
    QFile file("/home/qapfuc/PetP/Team-Lobachevsky-nm-4/src/gui/Style.qss");
    file.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(file.readAll());
    setStyleSheet(styleSheet);

    // Получение размеров экрана
    QScreen* screen = QGuiApplication::primaryScreen();
    QRect screenGeometry = screen->geometry();
    int screenWidth = screenGeometry.width();
    int screenHeight = screenGeometry.height();

    // Установка размера главного окна в 60% от размеров экрана
    int mainWindowWidth = 0.5 * screenWidth;
    int mainWindowHeight = 0.5 * screenHeight;

    resize(mainWindowWidth, mainWindowHeight);

    int x = (screenWidth - this->width()) / 2;
    int y = (screenHeight - this->height()) / 2;
    move(x, y);

    QVBoxLayout* mainlayout = new QVBoxLayout(this);

    QMenuBar* menuBar = new QMenuBar(this);
    QMenu* fileMenuFile = menuBar->addMenu(tr("&File"));
    mainlayout->setMenuBar(menuBar);

    QTabWidget* tabWidget = new QTabWidget(this);
    mainlayout->addWidget(tabWidget);

    tabWidget->resize(mainWindowWidth * 0.9,
                      mainWindowHeight * 0.9);  // Размер вкладок аналогичен размеру окна

    tabTask = new QWidget();
    tab2 = new QWidget();
    tab3 = new QWidget();
    tab4 = new QWidget();

    tabWidget->addTab(tabTask, tr("Ввод задачи и параметров"));
    tabWidget->addTab(tab2, tr("Таблица 2"));
    tabWidget->addTab(tab3, tr("График"));
    tabWidget->addTab(tab4, tr("Справка"));

    QLabel* label2 = new QLabel("Контент Вкладки 2", tab2);
    QLabel* label3 = new QLabel("Контент Вкладки 3", tab3);

    tab2->setLayout(new QVBoxLayout());  //WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    tab2->layout()->addWidget(label2);

    tab3->setLayout(new QVBoxLayout());  //WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    tab3->layout()->addWidget(label3);

    InitTabTask();
}

Widget::~Widget() {}

void Widget::InitTabTask() {
    QLabel* label1 = new QLabel("Введите число разбиений по X", tabTask);
    QLabel* label2 = new QLabel("Введите число разбиений по Y", tabTask);
    QLabel* label3 = new QLabel("Введите точность", tabTask);
    QLabel* label4 = new QLabel("Введите максимальное количество шагов", tabTask);
    QLabel* label5 = new QLabel("Введите параметр метода", tabTask);

    MainHLayout = new QVBoxLayout();

    tabTask->setLayout(MainHLayout);

    InputN = new QLineEdit();
    InputN->setMaximumWidth(200);
    InputM = new QLineEdit();
    InputM->setMaximumWidth(200);
    InputEps = new QLineEdit();
    InputEps->setMaximumWidth(200);
    InputMaxStep = new QLineEdit();
    InputMaxStep->setMaximumWidth(200);
    InputOmega = new QLineEdit();
    InputOmega->setMaximumWidth(200);
    InputTask = new QComboBox();
    SendDatabtn = new QPushButton();
    QHBoxLayout* HLayoutInputN = new QHBoxLayout();
    QHBoxLayout* HLayoutInputM = new QHBoxLayout();
    QHBoxLayout* HLayoutInputEps = new QHBoxLayout();
    QHBoxLayout* HLayoutInputMaxStep = new QHBoxLayout();
    QHBoxLayout* HLayoutInputOmega = new QHBoxLayout();
    QHBoxLayout* HLayoutInputConnect = new QHBoxLayout();

    HLayoutInputN->addWidget(label1, 0, Qt::AlignRight);
    HLayoutInputN->addWidget(InputN, 0, Qt::AlignLeft);
    HLayoutInputM->addWidget(label2, 0, Qt::AlignRight);
    HLayoutInputM->addWidget(InputM, 0, Qt::AlignLeft);
    HLayoutInputEps->addWidget(label3, 0, Qt::AlignRight);
    HLayoutInputEps->addWidget(InputEps, 0, Qt::AlignLeft);
    HLayoutInputMaxStep->addWidget(label4, 0, Qt::AlignRight);
    HLayoutInputMaxStep->addWidget(InputMaxStep, 0, Qt::AlignLeft);
    HLayoutInputOmega->addWidget(label5, 0, Qt::AlignRight);
    HLayoutInputOmega->addWidget(InputOmega, 0, Qt::AlignLeft);
    HLayoutInputConnect->addWidget(SendDatabtn, 0, Qt::AlignRight);
    HLayoutInputConnect->addWidget(InputTask, 0, Qt::AlignLeft);
    

    MainHLayout->addLayout(HLayoutInputN);
    MainHLayout->addLayout(HLayoutInputM);
    MainHLayout->addLayout(HLayoutInputEps);
    MainHLayout->addLayout(HLayoutInputMaxStep);
    MainHLayout->addLayout(HLayoutInputOmega);
    MainHLayout->addLayout(HLayoutInputConnect);

    QObject::connect(SendDatabtn, &QPushButton::clicked, this ,&Widget::onClick);
}

void Widget::onClick() {}

void Widget::CreateTable1() {
    QTableWidget* table_1 = new QTableWidget(5, 6);

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 6; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            table_1->setItem(row, col, item);
        }
    }

    table_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < 6; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        switch (col) {
        case 0:
            headerItem->setText("x(i-1)");
            break;
        case 1:
            headerItem->setText("x(i)");
            break;
        case 2:
            headerItem->setText("a(i)");
            break;
        case 3:
            headerItem->setText("b(i)");
            break;
        case 4:
            headerItem->setText("c(i)");
            break;
        case 5:
            headerItem->setText("d(i)");
            break;
        }
        table_1->setHorizontalHeaderItem(col, headerItem);
    }
}

void Widget::CreateTable2() {
    QTableWidget* table_2 = new QTableWidget(5, 7, tab2);

    for (int row = 0; row < 5; ++row) {
        for (int col = 0; col < 7; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            table_2->setItem(row, col, item);
        }
    }

    table_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < 7; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        if (col == 0) {
            headerItem->setText("x(j)");
        }
        if (col == 1) {
            headerItem->setText("F(x_j)");
        }
        if (col == 2) {
            headerItem->setText("S(x_j)");
        }
        if (col == 3) {
            headerItem->setText("F(x_j) - S(x_j)");
        }
        if (col == 4) {
            headerItem->setText("F'(x_j)");
        }
        if (col == 5) {
            headerItem->setText("S'(x_j)");
        }
        if (col == 6) {
            headerItem->setText("F'(x_j) - S'(x_j)");
        }
        table_2->setHorizontalHeaderItem(col, headerItem);
    }

    tab2->layout()->addWidget(table_2);
}

void Widget::CreateGraphs() {
    QWidget* tab4GraphWidget = new QWidget();

    QChartView* chartView = new QChartView(tab4GraphWidget);
    chartView->setRenderHint(QPainter::Antialiasing);

    QChart* chart = new QChart();

    QLineSeries* series = new QLineSeries();
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    chart->addSeries(series);

    chart->setTitle("Пример графика");

    chart->createDefaultAxes();

    chartView->setChart(chart);

    tab4GraphWidget->setLayout(new QVBoxLayout());  //WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    tab4GraphWidget->layout()->addWidget(chartView);

    tabWidget->addTab(tab4GraphWidget, tr("График"));
}
