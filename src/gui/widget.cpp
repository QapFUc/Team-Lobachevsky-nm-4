#include "core/netProcess.hpp"
#include "core/task.hpp"
#include "dataTypes/common.hpp"
#include "widget.h"

#include <QtCharts>
#include <QtWidgets>
#include <qboxlayout.h>
#include <qcombobox.h>
#include <qlayoutitem.h>
#include <qlineedit.h>
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
    QLabel* label6 = new QLabel("Введите границы области x:", tabTask);
    QLabel* label7 = new QLabel(" y:", tabTask);

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
    InputStartXArea = new QLineEdit();
    InputStartXArea->setMaximumWidth(200);
    InputEndXArea = new QLineEdit();
    InputEndXArea->setMaximumWidth(200);
    InputStartYArea = new QLineEdit();
    InputStartYArea->setMaximumWidth(200);
    InputEndYArea = new QLineEdit();
    InputEndYArea->setMaximumWidth(200);
    InputTask = new QComboBox();
    InputTask->addItem("Выбрать задачу");
    InputTask->addItem("Тестовая");
    InputTask->addItem("Первая ступень Колганов");
    InputTask->addItem("Вторая ступень Усов");
    InputTask->addItem("Вторая ступень Сучков");
    InputTask->addItem("Третья ступень Руяткин");
    InputStartx = new QComboBox();
    InputStartx->addItem("Выбрать приближение");
    InputStartx->addItem("Нулевое");
    SendDatabtn = new QPushButton("&Старт");
    QHBoxLayout* HLayoutArea = new QHBoxLayout();
    QHBoxLayout* HLayoutInputN = new QHBoxLayout();
    QHBoxLayout* HLayoutInputM = new QHBoxLayout();
    QHBoxLayout* HLayoutInputEps = new QHBoxLayout();
    QHBoxLayout* HLayoutInputMaxStep = new QHBoxLayout();
    QHBoxLayout* HLayoutInputOmega = new QHBoxLayout();
    QHBoxLayout* HLayoutInputConnect = new QHBoxLayout();

    HLayoutArea->addWidget(label6, 0, Qt::AlignRight);
    HLayoutArea->addWidget(InputStartXArea, 0, Qt::AlignRight);
    HLayoutArea->addWidget(InputEndXArea, 0, Qt::AlignLeft);
    HLayoutArea->addWidget(label7, 0, Qt::AlignRight);
    HLayoutArea->addWidget(InputStartYArea, 0, Qt::AlignRight);
    HLayoutArea->addWidget(InputEndYArea, 0, Qt::AlignLeft);
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
    HLayoutInputConnect->addWidget(InputTask, 0, Qt::AlignRight);
    HLayoutInputConnect->addWidget(InputStartx, 0, Qt::AlignLeft);

    MainHLayout->addLayout(HLayoutArea);
    MainHLayout->addLayout(HLayoutInputN);
    MainHLayout->addLayout(HLayoutInputM);
    MainHLayout->addLayout(HLayoutInputEps);
    MainHLayout->addLayout(HLayoutInputMaxStep);
    MainHLayout->addLayout(HLayoutInputOmega);
    MainHLayout->addLayout(HLayoutInputConnect);

    QObject::connect(SendDatabtn, &QPushButton::clicked, this, &Widget::SendDatabtnClick);

    InitDirTask();
}

void Widget::InitDirTask() {
    Networkpattern = (new NetPattern());
    Network = new Net();
    auto fb = [](const double& x, const double& y) -> double {
        return (x + y);
    };
    auto fr = [](const double& x, const double& y) -> double {
        return 1 - x - y;
    };

    DirTask = new DirichletTask(fb, fr, *Network, config);
}

void Widget::UpdateDirTask() {
    Networkpattern->setMainSpace(config.CountCutX / config.CountCutY);
    *Network = Networkpattern->generateNet(config.CountCutY,
                                           config.StartXArea,
                                           config.StartYArea,
                                           (config.EndXArea - config.StartXArea) / config.CountCutX,
                                           (config.EndYArea - config.StartYArea) / config.CountCutY);

    DirTask->SetConfig(config);
    DirTask->SetNet(*Network);
    DirTask->GenerateLinearSystem();
}

void Widget::StartSimplexIter() {
    DirTask->SetMethod(nm::Method::SimpleIter);
    DirTask->eval();
}

void Widget::StartCGM() {
    DirTask->SetMethod(nm::Method::CGM);
    DirTask->eval();
}

void Widget::SendDatabtnClick() {
    config = Config((InputStartXArea->text()).toDouble(),
                    (InputEndXArea->text()).toDouble(),
                    (InputStartYArea->text()).toDouble(),
                    (InputEndYArea->text()).toDouble(),
                    (InputN->text()).toDouble(),
                    (InputM->text()).toDouble(),
                    (InputMaxStep->text()).toDouble(),
                    InputTask->currentIndex(),
                    InputOmega->text().toDouble(),
                    static_cast<nm::StartApr>(InputStartx->currentIndex() - 1),
                    (InputEps->text()).toDouble());
    if (config.CountCutX <= 0 || config.CountCutY <= 0) {
        QMessageBox::critical(this, "Critical Error", "Start point must be > 0");
        return;
    }
    UpdateDirTask();
    switch (InputTask->currentIndex()) {
    case 0:
        //StartTest(config);
        break;
    case 1:
        //StartMain(config);
        break;
    case 2:
        //StartOscil(config);
        break;
    case 3:
        StartSimplexIter();
        break;
    case 4:
        StartCGM();
        break;
    case 5:
        //StartOscil(config);
        break;
    default:
        //StartTest(config);
        break;
    }
}

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
