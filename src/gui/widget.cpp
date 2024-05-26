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
#include <QtDataVisualization>


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
    tab5 = new QWidget();
    tab6 = new QWidget();
    tab7 = new QWidget();


    tabWidget->addTab(tabTask, tr("Ввод задачи и параметров"));
    tabWidget->addTab(tab2, tr("Таблицы тестовой задачи"));
    tabWidget->addTab(tab3, tr("График тестовой задачи"));
    tabWidget->addTab(tab4, tr("Справка тестовой задачи"));
    tabWidget->addTab(tab5, tr("Таблицы основной задачи"));
    tabWidget->addTab(tab6, tr("График основной задачи"));
    tabWidget->addTab(tab7, tr("Справка основной задачи"));

    // QLabel* label2 = new QLabel("Контент Вкладки 2", tab2);
    // QLabel* label3 = new QLabel("Контент Вкладки 3", tab3);

    // tab2->setLayout(new QVBoxLayout());  //WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // tab2->layout()->addWidget(label2);

    // tab3->setLayout(new QVBoxLayout());  //WARNING!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    // tab3->layout()->addWidget(label3);

    InitTabTask();

    CreateTableTest(5, 10);

    CreateTableMain(10, 10);

    CreateInfoTest();

    CreateInfoMain();

    CreateGraphsTest();

    CreateGraphsMain();
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

    QObject::connect(SendDatabtn, &QPushButton::clicked, this, &Widget::SendDatabtnClick);
}

void Widget::SendDatabtnClick() {
    config = Config((InputN->text()).toDouble(),
                    (InputM->text()).toDouble(),
                    (InputEps->text()).toDouble(),
                    (InputMaxStep->text()).toDouble(),
                    InputTask->currentIndex(),
                    InputOmega->text().toDouble());
    if (config.CountCutX<=0 || config.CountCutY<= 0) {
        QMessageBox::critical(this, "Critical Error", "Start point must be > 0");
        return;
    }
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
    default:
        //StartTest(config);
        break;
    }
}

void Widget::CreateTableTest(int x, int y) {

    TestTableLayout = new QVBoxLayout();

    tab2->setLayout(TestTableLayout);

    QVBoxLayout* TestLayout_1 = new QVBoxLayout();

    QLabel* TestLabel_1 = new QLabel("Точное решение u*(x, y) в узлах сетки", tab2);

    TestLayout_1->addWidget(TestLabel_1);

    QTableWidget* TableTest_1 = new QTableWidget(x, y);

    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            TableTest_1->setItem(row, col, item);
        }
    }

    TableTest_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < y; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("x_" + QString::number(col + 1));
        TableTest_1->setHorizontalHeaderItem(col, headerItem);
    }

    TableTest_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < x; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("y_" + QString::number(row + 1));
        TableTest_1->setHorizontalHeaderItem(row, headerItem);
    }

    TestLayout_1->addWidget(TableTest_1);

    TestTableLayout->addLayout(TestLayout_1);

    // 2 table 

    QVBoxLayout* TestLayout_2 = new QVBoxLayout();

    QLabel* TestLabel_2 = new QLabel("Численное решение V(N)(x, y) в узлах сетки", tab2);

    TestLayout_2->addWidget(TestLabel_2);

    QTableWidget* TableTest_2 = new QTableWidget(x, y);

    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            TableTest_2->setItem(row, col, item);
        }
    }

    TableTest_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < y; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("x_" + QString::number(col + 1));
        TableTest_2->setHorizontalHeaderItem(col, headerItem);
    }

    TableTest_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < x; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("y_" + QString::number(row + 1));
        TableTest_2->setHorizontalHeaderItem(row, headerItem);
    }

    TestLayout_2->addWidget(TableTest_2);

    TestTableLayout->addLayout(TestLayout_2);

    // table 3 

    QVBoxLayout* TestLayout_3 = new QVBoxLayout();

    QLabel* TestLabel_3 = new QLabel("Разность точного и численного решения в узлах сетки", tab2);

    TestLayout_3->addWidget(TestLabel_3);

    QTableWidget* TableTest_3 = new QTableWidget(x, y);

    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            TableTest_3->setItem(row, col, item);
        }
    }

    TableTest_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < y; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("x_" + QString::number(col + 1));
        TableTest_3->setHorizontalHeaderItem(col, headerItem);
    }

    TableTest_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < x; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("y_" + QString::number(row + 1));
        TableTest_3->setHorizontalHeaderItem(row, headerItem);
    }

    TestLayout_3->addWidget(TableTest_3);

    TestTableLayout->addLayout(TestLayout_3);
}

void Widget::CreateTableMain(int x, int y) {
    MainTableLayout = new QVBoxLayout();

    tab5->setLayout(MainTableLayout);

    QVBoxLayout* MainLayout_1 = new QVBoxLayout();

    QLabel* MainLabel_1 = new QLabel("Численное решение V(N)(x, y)", tab2);

    MainLayout_1->addWidget(MainLabel_1);

    QTableWidget* TableMain_1 = new QTableWidget(x, y);

    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            TableMain_1->setItem(row, col, item);
        }
    }

    TableMain_1->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < y; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("x_" + QString::number(col + 1));
        TableMain_1->setHorizontalHeaderItem(col, headerItem);
    }

    TableMain_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < x; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("y_" + QString::number(row + 1));
        TableMain_1->setHorizontalHeaderItem(row, headerItem);
    }

    MainLayout_1->addWidget(TableMain_1);

    MainTableLayout->addLayout(MainLayout_1);

    // 2 table 

    QVBoxLayout* MainLayout_2 = new QVBoxLayout();

    QLabel* MainLabel_2 = new QLabel("Численное решение V(N)(x, y) в узлах сетки", tab2);

    MainLayout_2->addWidget(MainLabel_2);

    QTableWidget* TableMain_2 = new QTableWidget(x, y);

    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            TableMain_2->setItem(row, col, item);
        }
    }

    TableMain_2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < y; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("x_" + QString::number(col + 1));
        TableMain_2->setHorizontalHeaderItem(col, headerItem);
    }

    TableMain_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < x; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("y_" + QString::number(row + 1));
        TableMain_2->setHorizontalHeaderItem(row, headerItem);
    }

    MainLayout_2->addWidget(TableMain_2);

    MainTableLayout->addLayout(MainLayout_2);

    // table 3 

    QVBoxLayout* MainLayout_3 = new QVBoxLayout();

    QLabel* MainLabel_3 = new QLabel("Разность точного и численного решения в узлах сетки", tab2);

    MainLayout_3->addWidget(MainLabel_3);

    QTableWidget* TableMain_3 = new QTableWidget(x, y);

    for (int row = 0; row < x; ++row) {
        for (int col = 0; col < y; ++col) {
            QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(row * 7 + col + 1));
            TableMain_3->setItem(row, col, item);
        }
    }

    TableMain_3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int col = 0; col < y; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("x_" + QString::number(col + 1));
        TableMain_3->setHorizontalHeaderItem(col, headerItem);
    }

    TableMain_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    for (int row = 0; row < x; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText("y_" + QString::number(row + 1));
        TableMain_3->setHorizontalHeaderItem(row, headerItem);
    }

    MainLayout_3->addWidget(TableMain_3);

    MainTableLayout->addLayout(MainLayout_3);
}

void Widget::CreateInfoTest() {

    TestInfoLayout = new QVBoxLayout();
    QHBoxLayout *TestInfoLayout_1 = new QHBoxLayout();
    QHBoxLayout *TestInfoLayout_2 = new QHBoxLayout();
    QHBoxLayout *TestInfoLayout_3 = new QHBoxLayout();
    QHBoxLayout *TestInfoLayout_4 = new QHBoxLayout();
    QHBoxLayout *TestInfoLayout_5 = new QHBoxLayout();
    QHBoxLayout *TestInfoLayout_6 = new QHBoxLayout();
    QHBoxLayout *TestInfoLayout_7 = new QHBoxLayout();
    tab4->setLayout(TestInfoLayout);

    QLabel *TestLabelInfo_1 = new QLabel("Для решения тестовой задачи использованы сетка с числом разбиений по x n = ", tab4);
    QLineEdit *TestLineEditInfo_1= new QLineEdit();
    TestLineEditInfo_1->setMaximumWidth(250);
    TestInfoLayout_1->addWidget(TestLabelInfo_1, 0, Qt::AlignRight);
    TestInfoLayout_1->addWidget(TestLineEditInfo_1, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_2 = new QLabel(" и числом разбиений по y m = ", tab4);    
    QLineEdit *TestLineEditInfo_2 = new QLineEdit();
    TestLineEditInfo_2->setMaximumWidth(250);
    TestInfoLayout_1->addWidget(TestLabelInfo_2, 0, Qt::AlignRight);
    TestInfoLayout_1->addWidget(TestLineEditInfo_2, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_3 = new QLabel(" метод верхней релаксации с параметром w = ", tab4);    
    QLineEdit *TestLineEditInfo_3 = new QLineEdit();
    TestLineEditInfo_3->setMaximumWidth(250);
    TestInfoLayout_2->addWidget(TestLabelInfo_3, 0, Qt::AlignRight);
    TestInfoLayout_2->addWidget(TestLineEditInfo_3, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_4 = new QLabel(" применены критерии остановки по точности E_мет =  ", tab4);    
    QLineEdit *TestLineEditInfo_4 = new QLineEdit();
    TestLineEditInfo_4->setMaximumWidth(250);
    TestInfoLayout_2->addWidget(TestLabelInfo_4, 0, Qt::AlignRight);
    TestInfoLayout_2->addWidget(TestLineEditInfo_4, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_5 = new QLabel(" и по числу итераций N_max =  ", tab4);    
    QLineEdit *TestLineEditInfo_5 = new QLineEdit();
    TestLineEditInfo_5->setMaximumWidth(250);
    TestInfoLayout_2->addWidget(TestLabelInfo_5, 0, Qt::AlignRight);
    TestInfoLayout_2->addWidget(TestLineEditInfo_5, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_6 = new QLabel(" На решение схемы (СЛАУ) затрачено итераций N = ", tab4);    
    QLineEdit *TestLineEditInfo_6 = new QLineEdit();
    TestLineEditInfo_6->setMaximumWidth(250);
    TestInfoLayout_3->addWidget(TestLabelInfo_6, 0, Qt::AlignRight);
    TestInfoLayout_3->addWidget(TestLineEditInfo_6, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_7 = new QLabel(" и достигнута точность итерационного метода E(N) = ", tab4);    
    QLineEdit *TestLineEditInfo_7 = new QLineEdit();
    TestLineEditInfo_7->setMaximumWidth(250);
    TestInfoLayout_3->addWidget(TestLabelInfo_7, 0, Qt::AlignRight);
    TestInfoLayout_3->addWidget(TestLineEditInfo_7, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_8 = new QLabel("Схема (СЛАУ) решена с невязкой ||R(N)|| = ", tab4);    
    QLineEdit *TestLineEditInfo_8 = new QLineEdit();
    TestLineEditInfo_8->setMaximumWidth(250);
    TestInfoLayout_4->addWidget(TestLabelInfo_8, 0, Qt::AlignRight);
    TestInfoLayout_4->addWidget(TestLineEditInfo_8, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_9 = new QLabel(" для невязки СЛАУ использована норма = ", tab4);    
    QLineEdit *TestLineEditInfo_9 = new QLineEdit();
    TestLineEditInfo_9->setMaximumWidth(250);
    TestInfoLayout_4->addWidget(TestLabelInfo_9, 0, Qt::AlignRight);
    TestInfoLayout_4->addWidget(TestLineEditInfo_9, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_10 = new QLabel("Тестовая задача должна быть решена с погрешностью не более E = 0.5 * 10^(-6), задача решена с погрешностью = ", tab4);    
    QLineEdit *TestLineEditInfo_10 = new QLineEdit();
    TestLineEditInfo_10->setMaximumWidth(250);
    TestInfoLayout_5->addWidget(TestLabelInfo_10, 0, Qt::AlignRight);
    TestInfoLayout_5->addWidget(TestLineEditInfo_10, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_11 = new QLabel("Максимальное отклонение точного и численного решений наблюдается в узле x = ", tab4);    
    QLineEdit *TestLineEditInfo_11 = new QLineEdit();
    TestLineEditInfo_11->setMaximumWidth(250);
    TestInfoLayout_6->addWidget(TestLabelInfo_11, 0, Qt::AlignRight);
    TestInfoLayout_6->addWidget(TestLineEditInfo_11, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_12 = new QLabel(" y = ", tab4);    
    QLineEdit *TestLineEditInfo_12 = new QLineEdit();
    TestLineEditInfo_12->setMaximumWidth(250);
    TestInfoLayout_6->addWidget(TestLabelInfo_12, 0, Qt::AlignRight);
    TestInfoLayout_6->addWidget(TestLineEditInfo_12, 0, Qt::AlignLeft);

    QLabel *TestLabelInfo_13 = new QLabel("В качестве начального приближения использовано : ", tab4);    
    QLineEdit *TestLineEditInfo_13 = new QLineEdit();
    TestLineEditInfo_13->setMaximumWidth(250);
    TestInfoLayout_7->addWidget(TestLabelInfo_13, 0, Qt::AlignRight);
    TestInfoLayout_7->addWidget(TestLineEditInfo_13, 0, Qt::AlignLeft);

    TestInfoLayout->addLayout(TestInfoLayout_1);
    TestInfoLayout->addLayout(TestInfoLayout_2);
    TestInfoLayout->addLayout(TestInfoLayout_3);
    TestInfoLayout->addLayout(TestInfoLayout_4);
    TestInfoLayout->addLayout(TestInfoLayout_5);
    TestInfoLayout->addLayout(TestInfoLayout_6);
    TestInfoLayout->addLayout(TestInfoLayout_7);
}

void Widget::CreateInfoMain() {

    MainInfoLayout = new QVBoxLayout();
    QHBoxLayout *MainInfoLayout_1 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_2 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_3 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_4 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_5 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_6 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_7 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_8 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_9 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_10 = new QHBoxLayout();
    QHBoxLayout *MainInfoLayout_11 = new QHBoxLayout();
    tab7->setLayout(MainInfoLayout);

    QLabel *MainLabelInfo_1 = new QLabel("Для решения основной задачи использованы сетка с числом разбиений по x n = ", tab7);
    QLineEdit *MainLineEditInfo_1= new QLineEdit();
    MainLineEditInfo_1->setMaximumWidth(250);
    MainInfoLayout_1->addWidget(MainLabelInfo_1, 0, Qt::AlignRight);
    MainInfoLayout_1->addWidget(MainLineEditInfo_1, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_2 = new QLabel(" и числом разбиений по y m = ", tab7);    
    QLineEdit *MainLineEditInfo_2 = new QLineEdit();
    MainLineEditInfo_2->setMaximumWidth(250);
    MainInfoLayout_1->addWidget(MainLabelInfo_2, 0, Qt::AlignRight);
    MainInfoLayout_1->addWidget(MainLineEditInfo_2, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_3 = new QLabel(" метод верхней релаксации с параметром w = ", tab7);    
    QLineEdit *MainLineEditInfo_3 = new QLineEdit();
    MainLineEditInfo_3->setMaximumWidth(250);
    MainInfoLayout_2->addWidget(MainLabelInfo_3, 0, Qt::AlignRight);
    MainInfoLayout_2->addWidget(MainLineEditInfo_3, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_4 = new QLabel(" применены критерии остановки по точности E_мет =  ", tab7);    
    QLineEdit *MainLineEditInfo_4 = new QLineEdit();
    MainLineEditInfo_4->setMaximumWidth(250);
    MainInfoLayout_2->addWidget(MainLabelInfo_4, 0, Qt::AlignRight);
    MainInfoLayout_2->addWidget(MainLineEditInfo_4, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_5 = new QLabel(" и по числу итераций N_max =  ", tab7);    
    QLineEdit *MainLineEditInfo_5 = new QLineEdit();
    MainLineEditInfo_5->setMaximumWidth(250);
    MainInfoLayout_2->addWidget(MainLabelInfo_5, 0, Qt::AlignRight);
    MainInfoLayout_2->addWidget(MainLineEditInfo_5, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_6 = new QLabel(" На решение схемы (СЛАУ) затрачено итераций N = ", tab7);    
    QLineEdit *MainLineEditInfo_6 = new QLineEdit();
    MainLineEditInfo_6->setMaximumWidth(250);
    MainInfoLayout_3->addWidget(MainLabelInfo_6, 0, Qt::AlignRight);
    MainInfoLayout_3->addWidget(MainLineEditInfo_6, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_7 = new QLabel(" и достигнута точность итерационного метода E(N) = ", tab7);    
    QLineEdit *MainLineEditInfo_7 = new QLineEdit();
    MainLineEditInfo_7->setMaximumWidth(250);
    MainInfoLayout_3->addWidget(MainLabelInfo_7, 0, Qt::AlignRight);
    MainInfoLayout_3->addWidget(MainLineEditInfo_7, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_8 = new QLabel("Схема (СЛАУ) решена с невязкой ||R(N)|| = ", tab7);    
    QLineEdit *MainLineEditInfo_8 = new QLineEdit();
    MainLineEditInfo_8->setMaximumWidth(250);
    MainInfoLayout_4->addWidget(MainLabelInfo_8, 0, Qt::AlignRight);
    MainInfoLayout_4->addWidget(MainLineEditInfo_8, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_9 = new QLabel(" для невязки СЛАУ использована норма = ", tab7);    
    QLineEdit *MainLineEditInfo_9 = new QLineEdit();
    MainLineEditInfo_9->setMaximumWidth(250);
    MainInfoLayout_4->addWidget(MainLabelInfo_9, 0, Qt::AlignRight);
    MainInfoLayout_4->addWidget(MainLineEditInfo_9, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_11 = new QLabel("Для контроля точности решения использована сетка с половинным шагом, метод верхней релаксиции с параметром w_2 = ", tab7);    
    QLineEdit *MainLineEditInfo_11 = new QLineEdit();
    MainLineEditInfo_11->setMaximumWidth(250);
    MainInfoLayout_6->addWidget(MainLabelInfo_11, 0, Qt::AlignRight);
    MainInfoLayout_6->addWidget(MainLineEditInfo_11, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_12 = new QLabel(" применены критерии остановки до точности E_мет-2 = ", tab7);    
    QLineEdit *MainLineEditInfo_12 = new QLineEdit();
    MainLineEditInfo_12->setMaximumWidth(250);
    MainInfoLayout_6->addWidget(MainLabelInfo_12, 0, Qt::AlignRight);
    MainInfoLayout_6->addWidget(MainLineEditInfo_12, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_13 = new QLabel(" и по числу итераций N_max-2 = ", tab7);    
    QLineEdit *MainLineEditInfo_13 = new QLineEdit();
    MainLineEditInfo_13->setMaximumWidth(250);
    MainInfoLayout_6->addWidget(MainLabelInfo_13, 0, Qt::AlignRight);
    MainInfoLayout_6->addWidget(MainLineEditInfo_13, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_14 = new QLabel("На решение задачи (СЛАУ) затрачено итераций N2 = ", tab7);    
    QLineEdit *MainLineEditInfo_14 = new QLineEdit();
    MainLineEditInfo_14->setMaximumWidth(250);
    MainInfoLayout_7->addWidget(MainLabelInfo_14, 0, Qt::AlignRight);
    MainInfoLayout_7->addWidget(MainLineEditInfo_14, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_15 = new QLabel(" и достигнута точность итерационного метода E(N2) = ", tab7);    
    QLineEdit *MainLineEditInfo_15 = new QLineEdit();
    MainLineEditInfo_15->setMaximumWidth(250);
    MainInfoLayout_7->addWidget(MainLabelInfo_15, 0, Qt::AlignRight);
    MainInfoLayout_7->addWidget(MainLineEditInfo_15, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_16 = new QLabel("Схема (СЛАУ) на сетке с половинным шагом решена с невязкой ||R(N2)|| = ", tab7);    
    QLineEdit *MainLineEditInfo_16 = new QLineEdit();
    MainLineEditInfo_16->setMaximumWidth(250);
    MainInfoLayout_8->addWidget(MainLabelInfo_16, 0, Qt::AlignRight);
    MainInfoLayout_8->addWidget(MainLineEditInfo_16, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_17 = new QLabel(" использована норма = ", tab7);    
    QLineEdit *MainLineEditInfo_17 = new QLineEdit();
    MainLineEditInfo_17->setMaximumWidth(250);
    MainInfoLayout_8->addWidget(MainLabelInfo_17, 0, Qt::AlignRight);
    MainInfoLayout_8->addWidget(MainLineEditInfo_17, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_18 = new QLabel("Основная задача должна быть решена с точностью не хуже чем E = 0.5 * 10^(-6), основная задача решена с точностью = ", tab7);    
    QLineEdit *MainLineEditInfo_18 = new QLineEdit();
    MainLineEditInfo_18->setMaximumWidth(250);
    MainInfoLayout_9->addWidget(MainLabelInfo_18, 0, Qt::AlignRight);
    MainInfoLayout_9->addWidget(MainLineEditInfo_18, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_19 = new QLabel("максимальное отклонение численных решений на основной сетке и сетке с половинным шагом наблюдается в узле x = ", tab7);    
    QLineEdit *MainLineEditInfo_19 = new QLineEdit();
    MainLineEditInfo_19->setMaximumWidth(250);
    MainInfoLayout_10->addWidget(MainLabelInfo_19, 0, Qt::AlignRight);
    MainInfoLayout_10->addWidget(MainLineEditInfo_19, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_20 = new QLabel(" y = ", tab7);    
    QLineEdit *MainLineEditInfo_20 = new QLineEdit();
    MainLineEditInfo_20->setMaximumWidth(250);
    MainInfoLayout_10->addWidget(MainLabelInfo_20, 0, Qt::AlignRight);
    MainInfoLayout_10->addWidget(MainLineEditInfo_20, 0, Qt::AlignLeft);
    
    QLabel *MainLabelInfo_21 = new QLabel("В качестве начального приближения на основной сетке использовано : ", tab7);    
    QLineEdit *MainLineEditInfo_21 = new QLineEdit();
    MainLineEditInfo_21->setMaximumWidth(250);
    MainInfoLayout_11->addWidget(MainLabelInfo_21, 0, Qt::AlignRight);
    MainInfoLayout_11->addWidget(MainLineEditInfo_21, 0, Qt::AlignLeft);

    QLabel *MainLabelInfo_22 = new QLabel(" на сетке с половинным шагом использовано : ", tab7);    
    QLineEdit *MainLineEditInfo_22 = new QLineEdit();
    MainLineEditInfo_22->setMaximumWidth(250);
    MainInfoLayout_11->addWidget(MainLabelInfo_22, 0, Qt::AlignRight);
    MainInfoLayout_11->addWidget(MainLineEditInfo_22, 0, Qt::AlignLeft);

    MainInfoLayout->addLayout(MainInfoLayout_1);
    MainInfoLayout->addLayout(MainInfoLayout_2);
    MainInfoLayout->addLayout(MainInfoLayout_3);
    MainInfoLayout->addLayout(MainInfoLayout_4);
    MainInfoLayout->addLayout(MainInfoLayout_5);
    MainInfoLayout->addLayout(MainInfoLayout_6);
    MainInfoLayout->addLayout(MainInfoLayout_7);
    MainInfoLayout->addLayout(MainInfoLayout_8);
    MainInfoLayout->addLayout(MainInfoLayout_9);
    MainInfoLayout->addLayout(MainInfoLayout_10);
    MainInfoLayout->addLayout(MainInfoLayout_11);
}

void Widget::CreateGraphsTest() {
    Q3DSurface *Testgraph3D = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(Testgraph3D);
    tab3->setLayout(new QVBoxLayout());
    tab3->layout()->addWidget(container);

    // Создание графика
    QSurfaceDataProxy *TestdataProxy = new QSurfaceDataProxy();
    QSurface3DSeries *Testseries = new QSurface3DSeries(TestdataProxy);
    
    // Создание данных для графика
    QSurfaceDataArray *TestdataArray = new QSurfaceDataArray();
    QSurfaceDataRow *TestdataRow = new QSurfaceDataRow();
    *TestdataRow << QVector3D(0, 0, 1) << QVector3D(1, 0, 2) << QVector3D(2, 0, 3);
    TestdataArray->append(TestdataRow);
    TestdataProxy->resetArray(TestdataArray);

    // Установка графика на поверхности
    Testgraph3D->addSeries(Testseries);

    // Настройка визуализации графика
    Testgraph3D->axisX()->setTitle("X Axis");
    Testgraph3D->axisY()->setTitle("Y Axis");
    Testgraph3D->axisZ()->setTitle("Z Axis");

    // Включение вращения графика в пространстве
    Testgraph3D->activeTheme()->setType(Q3DTheme::ThemeQt);

    // Настройка камеры для вращения графика
    Testgraph3D->scene()->activeCamera()->setCameraPosition(15, 15, 15);

}

void Widget::CreateGraphsMain() {
    Q3DSurface *Maingraph3D = new Q3DSurface();
    QWidget *container = QWidget::createWindowContainer(Maingraph3D);
    tab6->setLayout(new QVBoxLayout());
    tab6->layout()->addWidget(container);

    // Создание графика
    QSurfaceDataProxy *MaindataProxy = new QSurfaceDataProxy();
    QSurface3DSeries *Mainseries = new QSurface3DSeries(MaindataProxy);
    
    // Создание данных для графика
    QSurfaceDataArray *MaindataArray = new QSurfaceDataArray();
    QSurfaceDataRow *MaindataRow = new QSurfaceDataRow();
    *MaindataRow << QVector3D(0, 0, 1) << QVector3D(1, 0, 2) << QVector3D(2, 0, 3);
    MaindataArray->append(MaindataRow);
    MaindataProxy->resetArray(MaindataArray);

    // Установка графика на поверхности
    Maingraph3D->addSeries(Mainseries);

    // Настройка визуализации графика
    Maingraph3D->axisX()->setTitle("X Axis");
    Maingraph3D->axisY()->setTitle("Y Axis");
    Maingraph3D->axisZ()->setTitle("Z Axis");

    // Включение вращения графика в пространстве
    Maingraph3D->activeTheme()->setType(Q3DTheme::ThemeQt);

    // Настройка камеры для вращения графика
    Maingraph3D->scene()->activeCamera()->setCameraPosition(15, 15, 15);
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
