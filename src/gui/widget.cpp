#include "core/netProcess.hpp"
#include "core/task.hpp"
#include "dataTypes/common.hpp"
#include "dataTypes/config.hpp"
#include "widget.h"

#include <cmath>
#include <cstddef>
#include <cstdlib>
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
    tabTableTest = new QWidget();
    tab3 = new QWidget();
    tab4 = new QWidget();
    tabTableMain = new QWidget();
    tab6 = new QWidget();
    tab7 = new QWidget();

    tabWidget->addTab(tabTask, tr("Ввод задачи и параметров"));
    tabWidget->addTab(tabTableTest, tr("Таблицы тестовой задачи"));
    tabWidget->addTab(tab3, tr("График тестовой задачи"));
    tabWidget->addTab(tab4, tr("Справка тестовой задачи"));
    tabWidget->addTab(tabTableMain, tr("Таблицы основной задачи"));
    tabWidget->addTab(tab6, tr("График основной задачи"));
    tabWidget->addTab(tab7, tr("Справка основной задачи"));

    InitTabTask();

    InitTableTest();

    InitTableMain();

    CreateInfoTest();

    CreateInfoMain();

    InitGraphsMain();

    InitGraphsTest();
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
    InputTask->addItem("Тестовая Колганов");
    InputTask->addItem("Тестовая Усов");
    InputTask->addItem("Тестовая Сучков");
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
    exitconfig = new ExitConfig();
    exitconfigdoublestep = new ExitConfig();
    InitDirTask();
}

void Widget::InitDirTask() {
    Networkpattern = (new NetPattern());
    Network = new Net();
    NetworkpatternEmpty = (new NetPattern());
    NetworkEmpty = new Net();
    Networkpatterndoublestep = (new NetPattern());
    Networkdoublestep = new Net();
    fBound_main = [](const double& x, const double& y, const Config& config) -> double {
        if (x == config.StartXArea) {
            return ((y-2)*(y-3));
        }
        if (x == config.EndXArea) {
            return (y*(y-2)*(y-3));
        }
        if (y == config.StartYArea) {
            return ((x-1)*(x-2));
        }
        if (y == config.EndYArea) {
            return (x*(x-1)*(x-2));
        }
        return 1;
    };

    fRHS_main = [](const double& x, const double& y) -> double {
        return (-1*std::exp(-1*x*y*y));
    };

    fTrueSol_test = [](const double& x, const double& y) -> double {
        return std::sin(M_PI*x*y);
    };

    fBound_test = [&](const double& x, const double& y, const Config& config) -> double {
        if (x == config.StartXArea || x == config.EndXArea || y == config.StartYArea || y == config.EndYArea) {
            return fTrueSol_test(x, y);
        }
        return 1;
    };

    fRHS_test = [](const double& x, const double& y) -> double {
        return M_PI*M_PI * (x * x + y * y) * std::sin(M_PI * x * y);
    };

    DirTask = new DirichletTask(fBound_main, fRHS_main, *Network, config);
    DirTaskdoublestep = new DirichletTask(fBound_main,fRHS_main,*Networkdoublestep,configdoublestep);
}

void Widget::UpdateDirTask() {
    config.CountCutX += 1;
    config.CountCutY += 1;
    configdoublestep.CountCutX +=1;
    configdoublestep.CountCutY +=1;
    Networkpattern->setMainSpace(config.CountCutX / config.CountCutY);
    *Network = Networkpattern->generateNet(config.CountCutY,
                                           config.StartXArea,
                                           config.StartYArea,
                                           (config.EndXArea - config.StartXArea) / (config.CountCutX - 1),
                                           (config.EndYArea - config.StartYArea) / (config.CountCutY - 1));
    NetworkpatternEmpty->setMainSpace(config.CountCutX / config.CountCutY);
    NetworkpatternEmpty->addEmptySpace(0.75, 0, 0.75, 0);
    *NetworkEmpty = NetworkpatternEmpty->generateNet(config.CountCutY,
                                           config.StartXArea,
                                           config.StartYArea,
                                           (config.EndXArea - config.StartXArea) / (config.CountCutX - 1),
                                           (config.EndYArea - config.StartYArea) / (config.CountCutY - 1));
    Networkpatterndoublestep->setMainSpace((configdoublestep.CountCutX)/(configdoublestep.CountCutY));
    *Networkdoublestep = Networkpattern->generateNet(configdoublestep.CountCutY,
                                           configdoublestep.StartXArea,
                                           configdoublestep.StartYArea,
                                           (configdoublestep.EndXArea - configdoublestep.StartXArea) / (configdoublestep.CountCutX  - 1),
                                           (configdoublestep.EndYArea - configdoublestep.StartYArea) / (configdoublestep.CountCutY  - 1));
    DirTask->SetConfig(config);
    DirTask->SetNet(*Network); 
    DirTaskdoublestep->SetConfig(configdoublestep);
    DirTaskdoublestep->SetNet(*Networkdoublestep);
    for (size_t j = 0; j < NetworkEmpty->nodes[0].size(); ++j) {
        for (size_t i = 0; i < NetworkEmpty->nodes.size(); ++i) {
            if (NetworkEmpty->nodes[i][j] == NodeType::BOUND) {
                std::cout << 'o';
            } else if (NetworkEmpty->nodes[i][j] == NodeType::INNER) {
                std::cout << 'x';
            } else {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}

void Widget::UpdateInfoTest() {

    TestLineEditInfo_1->setText(QString::number(config.CountCutX-1));
    TestLineEditInfo_2->setText(QString::number(config.CountCutY-1));

    TestLineEditInfo_3->setText(QString::number(exitconfig->Parametr)); // параметр w для МВР
    TestLineEditInfo_4->setText(QString::number(config.tolerance)); // погрешность метода 

    TestLineEditInfo_5->setText(QString::number(config.Max_N));
    TestLineEditInfo_6->setText(QString::number(exitconfig->N)); // число затрасенных итераций для решения СЛАУ

    TestLineEditInfo_7->setText(QString::number(exitconfig->Methodtolerance)); // точность итерационного метода 
    TestLineEditInfo_8->setText(QString::number(exitconfig->tolerance)); // невязка слау

    TestLineEditInfo_9->setText(QString("2 норма")); // норма невязки слау
    TestLineEditInfo_10->setText(QString::number(MaxDistance)); // макс разность между точным и численным решением

    TestLineEditInfo_11->setText(QString::number(xMaxDistance)); // узел в котором макс отклонение - х
    TestLineEditInfo_12->setText(QString::number(yMaxDistance)); // узел в макс отклонение - у
    TestLineEditInfo_13->setText(QString("нулевое")); // начальное пиближение
}

void Widget::UpdateInfoMain() {

    MainLineEditInfo_1->setText(QString::number(config.CountCutX-1));
    MainLineEditInfo_2->setText(QString::number(config.CountCutY-1));
    MainLineEditInfo_3->setText(QString::number(exitconfig->Parametr)); // параметр метода 
    MainLineEditInfo_4->setText(QString::number(config.tolerance)); // критерии остановки по точности 
    MainLineEditInfo_5->setText(QString::number(config.Max_N)); // критерии остановки по числу итераций
    MainLineEditInfo_6->setText(QString::number(exitconfig->N)); // затраченное N на решение СЛАУ
    MainLineEditInfo_7->setText(QString::number(exitconfig->Methodtolerance)); // достигнутая точность итерац метода 
    MainLineEditInfo_8->setText(QString::number(exitconfig->tolerance)); // невязка решения СЛАУ
    MainLineEditInfo_9->setText(QString("2 норма")); // норма для невязки 
    MainLineEditInfo_11->setText(QString::number(exitconfigdoublestep->Parametr)); // параметр МВР с половинным шагом
    MainLineEditInfo_12->setText(QString::number(config.tolerance)); // крит остановки по точности на половинном шаге
    MainLineEditInfo_13->setText(QString::number(configdoublestep.Max_N)); // остановка по числу итераций на половинном шаге 
    MainLineEditInfo_14->setText(QString::number(exitconfigdoublestep->N)); // затраченное число итераций для решения СЛАУ на полов шаге
    MainLineEditInfo_15->setText(QString::number(exitconfigdoublestep->Methodtolerance)); // достигнутая точность на половинном шаге 
    MainLineEditInfo_16->setText(QString::number(exitconfigdoublestep->tolerance)); // невязка СЛАУ на половинном шаге
    MainLineEditInfo_17->setText("2 норма"); // использованная норма
    MainLineEditInfo_18->setText(QString::number(MaxDistancemain)); // точность решения СЛАУ
    MainLineEditInfo_19->setText(QString::number(xMaxDistancemain)); // макс отклонение в узле - х 
    MainLineEditInfo_20->setText(QString::number(yMaxDistancemain)); // макс отклонение в узле - у
    MainLineEditInfo_21->setText(QString("нулевое")); // начальное приближение 
    MainLineEditInfo_22->setText(QString("нулевое")); // нач приближение для полов шага

}

void Widget::StartSimplexIter() {
    DirTask->SetNet(*Network);
    DirTask->SetBoundary(fBound_main);
    DirTask->SetRHS(fRHS_main);
    DirTask->GenerateLinearSystem();
    DirTask->SetMethod(nm::Method::SimpleIter);
    DirTask->eval();

    DirTaskdoublestep->SetNet(*Networkdoublestep);
    DirTaskdoublestep->SetBoundary(fBound_main);
    DirTaskdoublestep->SetRHS(fRHS_main);
    DirTaskdoublestep->GenerateLinearSystem();
    DirTaskdoublestep->SetMethod(nm::Method::SimpleIter);
    DirTaskdoublestep->eval();

    *exitconfig=DirTask->GetMethod()->GetExitConfig();
    *exitconfigdoublestep=DirTaskdoublestep->GetMethod()->GetExitConfig();
}

void Widget::StartCGM() {
    DirTask->SetNet(*Network);
    DirTask->SetBoundary(fBound_main);
    DirTask->SetRHS(fRHS_main);
    DirTask->GenerateLinearSystem();
    DirTask->SetMethod(nm::Method::CGM);
    DirTask->eval();

    DirTaskdoublestep->SetNet(*Networkdoublestep);
    DirTaskdoublestep->SetBoundary(fBound_main);
    DirTaskdoublestep->SetRHS(fRHS_main);
    DirTaskdoublestep->GenerateLinearSystem();
    DirTaskdoublestep->SetMethod(nm::Method::CGM);
    DirTaskdoublestep->eval();

    *exitconfig=DirTask->GetMethod()->GetExitConfig();
    *exitconfigdoublestep=DirTaskdoublestep->GetMethod()->GetExitConfig();
}

void Widget::StartCGMEmptyArea() {
    DirTask->SetNet(*NetworkEmpty);
    DirTask->SetBoundary(fBound_main);
    DirTask->SetRHS(fRHS_main);
    DirTask->GenerateLinearSystem();
    DirTask->SetMethod(nm::Method::CGM);
    DirTask->eval();
    *exitconfig=DirTask->GetMethod()->GetExitConfig();
    *exitconfigdoublestep=DirTaskdoublestep->GetMethod()->GetExitConfig();
}

void Widget::StartSOR() {
    DirTask->SetNet(*Network);
    DirTask->SetBoundary(fBound_main);
    DirTask->SetRHS(fRHS_main);
    DirTask->GenerateLinearSystem();
    DirTask->SetMethod(nm::Method::SOR);
    DirTask->eval();

    DirTaskdoublestep->SetNet(*Networkdoublestep);
    DirTaskdoublestep->SetBoundary(fBound_main);
    DirTaskdoublestep->SetRHS(fRHS_main);
    DirTaskdoublestep->GenerateLinearSystem();
    DirTaskdoublestep->SetMethod(nm::Method::SOR);
    DirTaskdoublestep->eval();

    *exitconfig=DirTask->GetMethod()->GetExitConfig();
    *exitconfigdoublestep=DirTaskdoublestep->GetMethod()->GetExitConfig();
}

void Widget::StartTestCGM() {
    DirTask->SetNet(*Network);
    DirTask->SetBoundary(fBound_test);
    DirTask->SetRHS(fRHS_test);
    DirTask->GenerateLinearSystem();
    DirTask->SetMethod(nm::Method::CGM);
    DirTask->eval();
    *exitconfig=DirTask->GetMethod()->GetExitConfig();
}

void Widget::StartTestSOR() {
    DirTask->SetNet(*Network);
    DirTask->SetBoundary(fBound_test);
    DirTask->SetRHS(fRHS_test);
    DirTask->GenerateLinearSystem();
    DirTask->SetMethod(nm::Method::SOR);
    DirTask->eval();
    *exitconfig=DirTask->GetMethod()->GetExitConfig();
}

void Widget::StartTestSimpleIter() {
    DirTask->SetNet(*Network);
    DirTask->SetBoundary(fBound_test);
    DirTask->SetRHS(fRHS_test);
    DirTask->GenerateLinearSystem();
    DirTask->SetMethod(nm::Method::SimpleIter);
    DirTask->eval();
    *exitconfig=DirTask->GetMethod()->GetExitConfig();
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
    configdoublestep = Config((InputStartXArea->text()).toDouble(),
                    (InputEndXArea->text()).toDouble(),
                    (InputStartYArea->text()).toDouble(),
                    (InputEndYArea->text()).toDouble(),
                    (InputN->text()).toDouble()*2,
                    (InputM->text()).toDouble()*2,
                    (InputMaxStep->text()).toDouble()*6,
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
        break;
    case 1:
        StartTestSOR();
        UpdateTableTest();
        UpdateGraphsTest();
        UpdateInfoTest();
        break;
    case 2:
        StartTestSimpleIter();
        UpdateTableTest();
        UpdateGraphsTest();
        UpdateInfoTest();
        break;
    case 3:
        StartTestCGM();
        UpdateTableTest();
        UpdateGraphsTest();
        UpdateInfoTest();
        break;
    case 4:
        StartSOR();
        UpdateTableMain();
        UpdateGraphsMain();
        UpdateInfoMain();
        break;
    case 5:
        StartSimplexIter();
        UpdateTableMain();
        UpdateGraphsMain();
        UpdateInfoMain();
        break;
    case 6:
        StartCGM();
        UpdateTableMain();
        UpdateGraphsMain();
        UpdateInfoMain();
        break;
    case 7:
        StartCGMEmptyArea();
        UpdateTableMain();
        UpdateGraphsMain();
        break;
    default:
        //StartTest(config);
        break;
    }
}

void Widget::InitTableTest() {
    QVBoxLayout* TestTableLayout = new QVBoxLayout();

    tabTableTest->setLayout(TestTableLayout);

    QVBoxLayout* TestLayout_1 = new QVBoxLayout();

    QLabel* TestLabel_1 = new QLabel("Точное решение u*(x, y) в узлах сетки", tabTableTest);

    TestLayout_1->addWidget(TestLabel_1);

    TableTest_1 = new QTableWidget();

    TestLayout_1->addWidget(TableTest_1);

    TestTableLayout->addLayout(TestLayout_1);

    // 2 table

    QVBoxLayout* TestLayout_2 = new QVBoxLayout();

    QLabel* TestLabel_2 = new QLabel("Численное решение V(N)(x, y) в узлах сетки", tabTableTest);

    TestLayout_2->addWidget(TestLabel_2);

    TableTest_2 = new QTableWidget();

    TestLayout_2->addWidget(TableTest_2);

    TestTableLayout->addLayout(TestLayout_2);

    // table 3

    QVBoxLayout* TestLayout_3 = new QVBoxLayout();

    QLabel* TestLabel_3 = new QLabel("Разность точного и численного решения в узлах сетки", tabTableTest);

    TestLayout_3->addWidget(TestLabel_3);

    TableTest_3 = new QTableWidget();

    TestLayout_3->addWidget(TableTest_3);

    TestTableLayout->addLayout(TestLayout_3);
}

void Widget::UpdateTableTest() {
    std::cout << "update test table" << std::endl;
    // Real solve
    TableTest_1->setColumnCount(config.CountCutX);
    TableTest_1->setRowCount(config.CountCutY);
    double stepx = Network->step_x;
    double stepy = Network->step_y;
    for (int row = 0; row < config.CountCutY; ++row) {
        for (int col = 0; col < config.CountCutX; ++col) {
            if (Network->nodes[col][row] != NodeType::OUT) {
                double x = col * stepx;
                double y = row * stepy;

                QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(fTrueSol_test(config.StartXArea + x, config.StartYArea + y)));
                TableTest_1->setItem(row, col, item);
            }
        }
    }

    for (int col = 0; col < config.CountCutX; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(col * stepx+config.StartXArea));
        TableTest_1->setHorizontalHeaderItem(col, headerItem);
    }
    TableTest_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < config.CountCutY; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(row * stepy+config.StartYArea));
        TableTest_1->setVerticalHeaderItem(row, headerItem);
    }

    // Numeric solve
    TableTest_2->setColumnCount(config.CountCutX);
    TableTest_2->setRowCount(config.CountCutY);
    size_t biasY = 0;
    for (size_t row = 0; row < config.CountCutY; ++row) {
        size_t BordersInRow = 0;
        size_t biasX = 0;
        for (size_t l = 0; l < config.CountCutX; ++l) {
            if (Network->nodes[l][row] == NodeType::BOUND)
                BordersInRow += 1;
        }
        for (size_t col = 0; col < config.CountCutX; ++col) {
            if (Network->nodes[col][row] != NodeType::OUT) {
                double x = col * stepx+config.StartXArea;
                double y = row * stepy+config.StartYArea;
                double val = 0.l;

                if (Network->nodes[col][row] == NodeType::BOUND) {
                    val = DirTask->Boundary(x, y);
                    biasX += 1;
                } else if (Network->nodes[col][row] == NodeType::INNER) {
                    val = DirTask->Solution()[(col - biasX) + (row - 1) * (Network->nodes.size() - BordersInRow)];
                }

                QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(val));
                TableTest_2->setItem(row, col, item);
            }
        }
    }
    for (int col = 0; col < config.CountCutX; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartXArea + col * stepx));
        TableTest_2->setHorizontalHeaderItem(col, headerItem);
    }
    TableTest_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < config.CountCutY; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartXArea + row * stepy));
        TableTest_2->setVerticalHeaderItem(row, headerItem);
    }

    // Numeric - Real solve
    TableTest_3->setColumnCount(config.CountCutX);
    TableTest_3->setRowCount(config.CountCutY);
    biasY = 0;
    MaxDistance = -1;
    for (size_t row = 0; row < config.CountCutY; ++row) {
        size_t BordersInRow = 0;
        size_t biasX = 0;
        for (size_t l = 0; l < config.CountCutX; ++l) {
            if (Network->nodes[l][row] == NodeType::BOUND)
                BordersInRow += 1;
        }
        for (size_t col = 0; col < config.CountCutX; ++col) {
            if (Network->nodes[col][row] != NodeType::OUT) {
                double x = col * stepx+config.StartXArea;
                double y = row * stepy+config.StartYArea;
                double val = 0.l;

                if (Network->nodes[col][row] == NodeType::BOUND) {
                    val = DirTask->Boundary(x, y);
                    biasX += 1;
                } else if (Network->nodes[col][row] == NodeType::INNER) {
                    val = DirTask->Solution()[(col - biasX) + (row - 1) * (Network->nodes.size() - BordersInRow)];
                    if (std::abs(val - fTrueSol_test(x, y))>MaxDistance ) {
                    MaxDistance = std::abs(val - fTrueSol_test(x, y));
                    xMaxDistance = x;
                    yMaxDistance = y;
                    }
                }
                QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(std::abs(val - fTrueSol_test(x, y))));
                TableTest_3->setItem(row, col, item);
            }
        }
    }
    for (int col = 0; col < config.CountCutX; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(col * stepx+config.StartXArea));
        TableTest_3->setHorizontalHeaderItem(col, headerItem);
    }
    TableTest_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < config.CountCutY; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(row * stepy+config.StartYArea));
        TableTest_3->setVerticalHeaderItem(row, headerItem);
    }

    TableTest_1->resizeColumnsToContents();
    TableTest_1->resizeRowsToContents();
    TableTest_2->resizeColumnsToContents();
    TableTest_2->resizeRowsToContents();
    TableTest_3->resizeColumnsToContents();
    TableTest_3->resizeRowsToContents();
}

void Widget::InitTableMain() {
    MainTableLayout = new QVBoxLayout();

    tabTableMain->setLayout(MainTableLayout);
    QVBoxLayout* MainLayout_1 = new QVBoxLayout();
    QLabel* MainLabel_1 = new QLabel("Численное решение v(N)(x, y) в узлах сетки c двойным шагом", tabTableTest);
    MainLayout_1->addWidget(MainLabel_1);
    TableMain_1 = new QTableWidget();
    MainLayout_1->addWidget(TableMain_1);
    MainTableLayout->addLayout(MainLayout_1);

    // 2 table

    QVBoxLayout* MainLayout_2 = new QVBoxLayout();

    QLabel* MainLabel_2 = new QLabel("Численное решение v(N)(x, y) в узлах сетки c одинарным шагом", tabTableTest);

    MainLayout_2->addWidget(MainLabel_2);

    TableMain_2 = new QTableWidget();

    MainLayout_2->addWidget(TableMain_2);

    MainTableLayout->addLayout(MainLayout_2);

    // table 3

    QVBoxLayout* MainLayout_3 = new QVBoxLayout();

    QLabel* MainLabel_3 = new QLabel("Разность численного и численного с двйоным шагом в узлах сетки", tabTableTest);

    MainLayout_3->addWidget(MainLabel_3);

    TableMain_3 = new QTableWidget();
    MainLayout_3->addWidget(TableMain_3);

    MainTableLayout->addLayout(MainLayout_3);
}

void Widget::UpdateTableMain() {
    std::cout << "start upd" << std::endl;
    double stepx = Network->step_x;
    double stepy = Network->step_y;
    double stpexdouble = Networkdoublestep->step_x;
    double stpeydouble = Networkdoublestep->step_y;

    // Numeric solve
    TableMain_1->setColumnCount(configdoublestep.CountCutX);
    TableMain_1->setRowCount(configdoublestep.CountCutY);
    for (size_t row = 0; row < configdoublestep.CountCutY; ++row) {
        size_t BordersInRow = 0;
        size_t biasX = 0;
        for (size_t l = 0; l < configdoublestep.CountCutX; ++l) {
            if (Networkdoublestep->nodes[l][row] == NodeType::BOUND)
                BordersInRow += 1;
        }
        for (size_t col = 0; col < configdoublestep.CountCutX; ++col) {
            if (Networkdoublestep->nodes[col][row] != NodeType::OUT) {
                double x = col * stpexdouble+configdoublestep.StartXArea;
                double y = row * stpeydouble+configdoublestep.StartYArea;
                double val = 0.l;

                if (Networkdoublestep->nodes[col][row] == NodeType::BOUND) {
                    val = DirTaskdoublestep->Boundary(x, y);
                    biasX += 1;
                } else if (Networkdoublestep->nodes[col][row] == NodeType::INNER) {
                    val = DirTaskdoublestep->Solution()[(col - biasX) + (row - 1) * (Networkdoublestep->nodes.size() - BordersInRow)];
                }

                QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(val));
                TableMain_1->setItem(row, col, item);
            }
        }
    }

    // Numeric solve
    TableMain_2->setColumnCount(config.CountCutX);
    TableMain_2->setRowCount(config.CountCutY);
    for (size_t row = 0; row < config.CountCutY; ++row) {
        size_t BordersInRow = 0;
        size_t biasX = 0;
        for (size_t l = 0; l < config.CountCutX; ++l) {
            if (Network->nodes[l][row] == NodeType::BOUND)
                BordersInRow += 1;
        }
        for (size_t col = 0; col < config.CountCutX; ++col) {
            if (Network->nodes[col][row] != NodeType::OUT) {
                double x = col * stepx+config.StartXArea;
                double y = row * stepy+config.StartYArea;
                double val = 0.l;

                if (Network->nodes[col][row] == NodeType::BOUND) {
                    val = DirTask->Boundary(x, y);
                    biasX += 1;
                } else if (Network->nodes[col][row] == NodeType::INNER) {
                    val = DirTask->Solution()[(col - biasX) + (row - 1) * (Network->nodes.size() - BordersInRow)];
                }

                QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(val));
                TableMain_2->setItem(row, col, item);
            }
        }
    }
    

    TableMain_3->setColumnCount(config.CountCutX);
    TableMain_3->setRowCount(config.CountCutY);
    MaxDistancemain=-1;
    for (size_t row = 0; row < config.CountCutY; ++row) {
        size_t BordersInRow = 0;
        size_t biasX = 0;
        for (size_t l = 0; l < config.CountCutX; ++l) {
            if (Network->nodes[l][row] == NodeType::BOUND)
                BordersInRow += 1;
        }
        for (size_t col = 0; col < config.CountCutX; ++col) {
            if (Network->nodes[col][row] != NodeType::OUT) {
                double x = col * stepx+config.StartXArea;
                double y = row * stepy+config.StartYArea;
                double val = 0.l;

                if (Network->nodes[col][row] == NodeType::BOUND) {
                    val = std::abs(DirTask->Boundary(x, y)- (TableMain_1->item(row*2,col*2)->text()).toDouble());
                    biasX += 1;
                } else if (Network->nodes[col][row] == NodeType::INNER) {
                    val = std::abs(DirTask->Solution()[(col - biasX) + (row - 1) * (Network->nodes.size() - BordersInRow)] - (TableMain_1->item(row*2, col*2)->text()).toDouble());
                }

                if (std::abs(val)>MaxDistancemain ) {
                    MaxDistancemain = val;
                    xMaxDistancemain = x;
                    yMaxDistancemain = y;
                    }

                QTableWidgetItem* item = new QTableWidgetItem(QString("%1").arg(val));
                TableMain_3->setItem(row, col, item);
            }
        }
    }

    for (int col = 0; col < configdoublestep.CountCutX; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartXArea + col * stpexdouble));
        TableMain_1->setHorizontalHeaderItem(col, headerItem);
    }
    TableMain_1->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < configdoublestep.CountCutY; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartYArea + row * stpeydouble));
        TableMain_1->setVerticalHeaderItem(row, headerItem);
    }

    for (int col = 0; col < config.CountCutX; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartXArea + col * stepx));
        TableMain_2->setHorizontalHeaderItem(col, headerItem);
    }
    TableMain_2->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < config.CountCutY; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartYArea + row * stepy));
        TableMain_2->setVerticalHeaderItem(row, headerItem);
    }

    for (int col = 0; col < config.CountCutX; ++col) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartXArea + col * stepx));
        TableMain_3->setHorizontalHeaderItem(col, headerItem);
    }
    TableMain_3->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    for (int row = 0; row < config.CountCutY; ++row) {
        QTableWidgetItem* headerItem = new QTableWidgetItem();
        headerItem->setText(QString::number(config.StartYArea + row * stepy));
        TableMain_3->setVerticalHeaderItem(row, headerItem);
    }

    TableMain_1->resizeColumnsToContents();
    TableMain_1->resizeRowsToContents();
    TableMain_2->resizeColumnsToContents();
    TableMain_2->resizeRowsToContents();
    TableMain_3->resizeColumnsToContents();
    TableMain_3->resizeRowsToContents();

}

void Widget::CreateInfoTest() {
    TestInfoLayout = new QVBoxLayout();
    QHBoxLayout* TestInfoLayout_1 = new QHBoxLayout();
    QHBoxLayout* TestInfoLayout_2 = new QHBoxLayout();
    QHBoxLayout* TestInfoLayout_3 = new QHBoxLayout();
    QHBoxLayout* TestInfoLayout_4 = new QHBoxLayout();
    QHBoxLayout* TestInfoLayout_5 = new QHBoxLayout();
    QHBoxLayout* TestInfoLayout_6 = new QHBoxLayout();
    QHBoxLayout* TestInfoLayout_7 = new QHBoxLayout();
    tab4->setLayout(TestInfoLayout);

    QLabel* TestLabelInfo_1 = new QLabel("Для решения тестовой задачи использованы сетка с числом разбиений по x n = ", tab4);
    TestLineEditInfo_1 = new QLineEdit();
    TestLineEditInfo_1->setMaximumWidth(250);
    TestInfoLayout_1->addWidget(TestLabelInfo_1, 0, Qt::AlignRight);
    TestInfoLayout_1->addWidget(TestLineEditInfo_1, 0, Qt::AlignLeft);

    QSpacerItem* spacer_1 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_1->addItem(spacer_1);

    QLabel* TestLabelInfo_2 = new QLabel(" и числом разбиений по y m = ", tab4);
    TestLineEditInfo_2 = new QLineEdit();
    TestLineEditInfo_2->setMaximumWidth(250);
    TestInfoLayout_1->addWidget(TestLabelInfo_2, 0, Qt::AlignRight);
    TestInfoLayout_1->addWidget(TestLineEditInfo_2, 0, Qt::AlignLeft);

    QSpacerItem* spacer_2 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_1->addItem(spacer_2);

    QLabel* TestLabelInfo_3 = new QLabel(" параметр метода = ", tab4);
    TestLineEditInfo_3 = new QLineEdit();
    TestLineEditInfo_3->setMaximumWidth(250);
    TestInfoLayout_2->addWidget(TestLabelInfo_3, 0, Qt::AlignRight);
    TestInfoLayout_2->addWidget(TestLineEditInfo_3, 0, Qt::AlignLeft);

    QSpacerItem* spacer_3 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_2->addItem(spacer_3);

    QLabel* TestLabelInfo_4 = new QLabel(" применены критерии остановки по точности E_мет =  ", tab4);
    TestLineEditInfo_4 = new QLineEdit();
    TestLineEditInfo_4->setMaximumWidth(250);
    TestInfoLayout_2->addWidget(TestLabelInfo_4, 0, Qt::AlignRight);
    TestInfoLayout_2->addWidget(TestLineEditInfo_4, 0, Qt::AlignLeft);

    QSpacerItem* spacer_4 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_2->addItem(spacer_4);

    QLabel* TestLabelInfo_5 = new QLabel(" и по числу итераций N_max =  ", tab4);
    TestLineEditInfo_5 = new QLineEdit();
    TestLineEditInfo_5->setMaximumWidth(250);
    TestInfoLayout_2->addWidget(TestLabelInfo_5, 0, Qt::AlignRight);
    TestInfoLayout_2->addWidget(TestLineEditInfo_5, 0, Qt::AlignLeft);

    QSpacerItem* spacer_5 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_2->addItem(spacer_5);

    QLabel* TestLabelInfo_6 = new QLabel(" На решение схемы (СЛАУ) затрачено итераций N = ", tab4);
    TestLineEditInfo_6 = new QLineEdit();
    TestLineEditInfo_6->setMaximumWidth(250);
    TestInfoLayout_3->addWidget(TestLabelInfo_6, 0, Qt::AlignRight);
    TestInfoLayout_3->addWidget(TestLineEditInfo_6, 0, Qt::AlignLeft);

    QSpacerItem* spacer_6 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_3->addItem(spacer_6);

    QLabel* TestLabelInfo_7 = new QLabel(" и достигнута точность итерационного метода E(N) = ", tab4);
    TestLineEditInfo_7 = new QLineEdit();
    TestLineEditInfo_7->setMaximumWidth(250);
    TestInfoLayout_3->addWidget(TestLabelInfo_7, 0, Qt::AlignRight);
    TestInfoLayout_3->addWidget(TestLineEditInfo_7, 0, Qt::AlignLeft);

    QSpacerItem* spacer_7 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_3->addItem(spacer_7);

    QLabel* TestLabelInfo_8 = new QLabel("Схема (СЛАУ) решена с невязкой ||R(N)|| = ", tab4);
    TestLineEditInfo_8 = new QLineEdit();
    TestLineEditInfo_8->setMaximumWidth(250);
    TestInfoLayout_4->addWidget(TestLabelInfo_8, 0, Qt::AlignRight);
    TestInfoLayout_4->addWidget(TestLineEditInfo_8, 0, Qt::AlignLeft);

    QSpacerItem* spacer_8 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_4->addItem(spacer_8);

    QLabel* TestLabelInfo_9 = new QLabel(" для невязки СЛАУ использована норма = ", tab4);
    TestLineEditInfo_9 = new QLineEdit();
    TestLineEditInfo_9->setMaximumWidth(250);
    TestInfoLayout_4->addWidget(TestLabelInfo_9, 0, Qt::AlignRight);
    TestInfoLayout_4->addWidget(TestLineEditInfo_9, 0, Qt::AlignLeft);

    QSpacerItem* spacer_9 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_4->addItem(spacer_9);

    QLabel* TestLabelInfo_10 = new QLabel("Тестовая задача должна быть решена с погрешностью не более E = 0.5 * 10^(-6), задача решена с погрешностью = ", tab4);
    TestLineEditInfo_10 = new QLineEdit();
    TestLineEditInfo_10->setMaximumWidth(250);
    TestInfoLayout_5->addWidget(TestLabelInfo_10, 0, Qt::AlignRight);
    TestInfoLayout_5->addWidget(TestLineEditInfo_10, 0, Qt::AlignLeft);

    QSpacerItem* spacer_10 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_5->addItem(spacer_10);

    QLabel* TestLabelInfo_11 = new QLabel("Максимальное отклонение точного и численного решений наблюдается в узле x = ", tab4);
    TestLineEditInfo_11 = new QLineEdit();
    TestLineEditInfo_11->setMaximumWidth(250);
    TestInfoLayout_6->addWidget(TestLabelInfo_11, 0, Qt::AlignRight);
    TestInfoLayout_6->addWidget(TestLineEditInfo_11, 0, Qt::AlignLeft);

    QSpacerItem* spacer_11 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_6->addItem(spacer_11);

    QLabel* TestLabelInfo_12 = new QLabel(" y = ", tab4);
    TestLineEditInfo_12 = new QLineEdit();
    TestLineEditInfo_12->setMaximumWidth(250);
    TestInfoLayout_6->addWidget(TestLabelInfo_12, 0, Qt::AlignRight);
    TestInfoLayout_6->addWidget(TestLineEditInfo_12, 0, Qt::AlignLeft);

    QSpacerItem* spacer_12 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_6->addItem(spacer_12);

    QLabel* TestLabelInfo_13 = new QLabel("В качестве начального приближения использовано : ", tab4);
    TestLineEditInfo_13 = new QLineEdit();
    TestLineEditInfo_13->setMaximumWidth(250);
    TestInfoLayout_7->addWidget(TestLabelInfo_13, 0, Qt::AlignRight);
    TestInfoLayout_7->addWidget(TestLineEditInfo_13, 0, Qt::AlignLeft);

    QSpacerItem* spacer_13 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    TestInfoLayout_7->addItem(spacer_13);

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
    QHBoxLayout* MainInfoLayout_1 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_2 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_3 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_4 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_5 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_6 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_7 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_8 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_9 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_10 = new QHBoxLayout();
    QHBoxLayout* MainInfoLayout_11 = new QHBoxLayout();
    tab7->setLayout(MainInfoLayout);

    QLabel* MainLabelInfo_1 = new QLabel("Для решения основной задачи использованы сетка с числом разбиений по x n = ", tab7);
    MainLineEditInfo_1 = new QLineEdit();
    MainLineEditInfo_1->setMaximumWidth(250);
    MainInfoLayout_1->addWidget(MainLabelInfo_1, 0, Qt::AlignRight);
    MainInfoLayout_1->addWidget(MainLineEditInfo_1, 0, Qt::AlignLeft);

    QSpacerItem* spacer_1 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_1->addItem(spacer_1);

    QLabel* MainLabelInfo_2 = new QLabel(" и числом разбиений по y m = ", tab7);
    MainLineEditInfo_2 = new QLineEdit();
    MainLineEditInfo_2->setMaximumWidth(250);
    MainInfoLayout_1->addWidget(MainLabelInfo_2, 0, Qt::AlignRight);
    MainInfoLayout_1->addWidget(MainLineEditInfo_2, 0, Qt::AlignLeft);

    QSpacerItem* spacer_2 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_1->addItem(spacer_2);

    QLabel* MainLabelInfo_3 = new QLabel(" параметр метода = ", tab7);
    MainLineEditInfo_3 = new QLineEdit();
    MainLineEditInfo_3->setMaximumWidth(250);
    MainInfoLayout_2->addWidget(MainLabelInfo_3, 0, Qt::AlignRight);
    MainInfoLayout_2->addWidget(MainLineEditInfo_3, 0, Qt::AlignLeft);

    QSpacerItem* spacer_3 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_2->addItem(spacer_3);

    QLabel* MainLabelInfo_4 = new QLabel(" применены критерии остановки по точности E_мет =  ", tab7);
    MainLineEditInfo_4 = new QLineEdit();
    MainLineEditInfo_4->setMaximumWidth(250);
    MainInfoLayout_2->addWidget(MainLabelInfo_4, 0, Qt::AlignRight);
    MainInfoLayout_2->addWidget(MainLineEditInfo_4, 0, Qt::AlignLeft);

    QSpacerItem* spacer_4 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_2->addItem(spacer_4);

    QLabel* MainLabelInfo_5 = new QLabel(" и по числу итераций N_max =  ", tab7);
    MainLineEditInfo_5 = new QLineEdit();
    MainLineEditInfo_5->setMaximumWidth(250);
    MainInfoLayout_2->addWidget(MainLabelInfo_5, 0, Qt::AlignRight);
    MainInfoLayout_2->addWidget(MainLineEditInfo_5, 0, Qt::AlignLeft);

    QSpacerItem* spacer_5 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_2->addItem(spacer_5);

    QLabel* MainLabelInfo_6 = new QLabel(" На решение схемы (СЛАУ) затрачено итераций N = ", tab7);
    MainLineEditInfo_6 = new QLineEdit();
    MainLineEditInfo_6->setMaximumWidth(250);
    MainInfoLayout_3->addWidget(MainLabelInfo_6, 0, Qt::AlignRight);
    MainInfoLayout_3->addWidget(MainLineEditInfo_6, 0, Qt::AlignLeft);

    QSpacerItem* spacer_6 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_3->addItem(spacer_6);

    QLabel* MainLabelInfo_7 = new QLabel(" и достигнута точность итерационного метода E(N) = ", tab7);
    MainLineEditInfo_7 = new QLineEdit();
    MainLineEditInfo_7->setMaximumWidth(250);
    MainInfoLayout_3->addWidget(MainLabelInfo_7, 0, Qt::AlignRight);
    MainInfoLayout_3->addWidget(MainLineEditInfo_7, 0, Qt::AlignLeft);

    QSpacerItem* spacer_7 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_3->addItem(spacer_7);

    QLabel* MainLabelInfo_8 = new QLabel("Схема (СЛАУ) решена с невязкой ||R(N)|| = ", tab7);
    MainLineEditInfo_8 = new QLineEdit();
    MainLineEditInfo_8->setMaximumWidth(250);
    MainInfoLayout_4->addWidget(MainLabelInfo_8, 0, Qt::AlignRight);
    MainInfoLayout_4->addWidget(MainLineEditInfo_8, 0, Qt::AlignLeft);

    QSpacerItem* spacer_8 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_4->addItem(spacer_8);

    QLabel* MainLabelInfo_9 = new QLabel(" для невязки СЛАУ использована норма = ", tab7);
    MainLineEditInfo_9 = new QLineEdit();
    MainLineEditInfo_9->setMaximumWidth(250);
    MainInfoLayout_4->addWidget(MainLabelInfo_9, 0, Qt::AlignRight);
    MainInfoLayout_4->addWidget(MainLineEditInfo_9, 0, Qt::AlignLeft);

    QSpacerItem* spacer_9 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_4->addItem(spacer_9);

    QLabel* MainLabelInfo_11 =
        new QLabel("Для контроля точности решения исп. сетка с половинным шагом, парам. метода (2) = ", tab7);
    MainLineEditInfo_11 = new QLineEdit();
    MainLineEditInfo_11->setMaximumWidth(250);
    MainInfoLayout_6->addWidget(MainLabelInfo_11, 0, Qt::AlignRight);
    MainInfoLayout_6->addWidget(MainLineEditInfo_11, 0, Qt::AlignLeft);

    QSpacerItem* spacer_10 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_6->addItem(spacer_10);

    QLabel* MainLabelInfo_12 = new QLabel(" критерии остановки до точности E_мет-2 = ", tab7);
    MainLineEditInfo_12 = new QLineEdit();
    MainLineEditInfo_12->setMaximumWidth(250);
    MainInfoLayout_6->addWidget(MainLabelInfo_12, 0, Qt::AlignRight);
    MainInfoLayout_6->addWidget(MainLineEditInfo_12, 0, Qt::AlignLeft);

    QSpacerItem* spacer_11 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_6->addItem(spacer_11);

    QLabel* MainLabelInfo_13 = new QLabel(" и по числу итераций N_max-2 = ", tab7);
    MainLineEditInfo_13 = new QLineEdit();
    MainLineEditInfo_13->setMaximumWidth(250);
    MainInfoLayout_6->addWidget(MainLabelInfo_13, 0, Qt::AlignRight);
    MainInfoLayout_6->addWidget(MainLineEditInfo_13, 0, Qt::AlignLeft);

    QSpacerItem* spacer_12 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_6->addItem(spacer_12);

    QLabel* MainLabelInfo_14 = new QLabel("На решение задачи (СЛАУ) затрачено итераций N2 = ", tab7);
    MainLineEditInfo_14 = new QLineEdit();
    MainLineEditInfo_14->setMaximumWidth(250);
    MainInfoLayout_7->addWidget(MainLabelInfo_14, 0, Qt::AlignRight);
    MainInfoLayout_7->addWidget(MainLineEditInfo_14, 0, Qt::AlignLeft);

    QSpacerItem* spacer_13 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_7->addItem(spacer_13);

    QLabel* MainLabelInfo_15 = new QLabel(" и достигнута точность итерационного метода E(N2) = ", tab7);
    MainLineEditInfo_15 = new QLineEdit();
    MainLineEditInfo_15->setMaximumWidth(250);
    MainInfoLayout_7->addWidget(MainLabelInfo_15, 0, Qt::AlignRight);
    MainInfoLayout_7->addWidget(MainLineEditInfo_15, 0, Qt::AlignLeft);

    QSpacerItem* spacer_14 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_7->addItem(spacer_14);

    QLabel* MainLabelInfo_16 = new QLabel("Схема (СЛАУ) на сетке с половинным шагом решена с невязкой ||R(N2)|| = ", tab7);
    MainLineEditInfo_16 = new QLineEdit();
    MainLineEditInfo_16->setMaximumWidth(250);
    MainInfoLayout_8->addWidget(MainLabelInfo_16, 0, Qt::AlignRight);
    MainInfoLayout_8->addWidget(MainLineEditInfo_16, 0, Qt::AlignLeft);

    QSpacerItem* spacer_15 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_8->addItem(spacer_15);

    QLabel* MainLabelInfo_17 = new QLabel(" использована норма = ", tab7);
    MainLineEditInfo_17 = new QLineEdit();
    MainLineEditInfo_17->setMaximumWidth(250);
    MainInfoLayout_8->addWidget(MainLabelInfo_17, 0, Qt::AlignRight);
    MainInfoLayout_8->addWidget(MainLineEditInfo_17, 0, Qt::AlignLeft);

    QSpacerItem* spacer_16 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_8->addItem(spacer_16);

    QLabel* MainLabelInfo_18 =
        new QLabel("Основная задача должна быть решена с точностью не хуже чем E = 0.5 * 10^(-6), основная задача решена с точностью = ", tab7);
    MainLineEditInfo_18 = new QLineEdit();
    MainLineEditInfo_18->setMaximumWidth(250);
    MainInfoLayout_9->addWidget(MainLabelInfo_18, 0, Qt::AlignRight);
    MainInfoLayout_9->addWidget(MainLineEditInfo_18, 0, Qt::AlignLeft);

    QSpacerItem* spacer_17 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_9->addItem(spacer_17);

    QLabel* MainLabelInfo_19 =
        new QLabel("максимальное отклонение численных решений на основной сетке и сетке с половинным шагом наблюдается в узле x = ", tab7);
    MainLineEditInfo_19 = new QLineEdit();
    MainLineEditInfo_19->setMaximumWidth(250);
    MainInfoLayout_10->addWidget(MainLabelInfo_19, 0, Qt::AlignRight);
    MainInfoLayout_10->addWidget(MainLineEditInfo_19, 0, Qt::AlignLeft);

    QSpacerItem* spacer_18 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_10->addItem(spacer_18);

    QLabel* MainLabelInfo_20 = new QLabel(" y = ", tab7);
    MainLineEditInfo_20 = new QLineEdit();
    MainLineEditInfo_20->setMaximumWidth(250);
    MainInfoLayout_10->addWidget(MainLabelInfo_20, 0, Qt::AlignRight);
    MainInfoLayout_10->addWidget(MainLineEditInfo_20, 0, Qt::AlignLeft);

    QSpacerItem* spacer_19 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_10->addItem(spacer_19);

    QLabel* MainLabelInfo_21 = new QLabel("В качестве начального приближения на основной сетке использовано : ", tab7);
    MainLineEditInfo_21 = new QLineEdit();
    MainLineEditInfo_21->setMaximumWidth(250);
    MainInfoLayout_11->addWidget(MainLabelInfo_21, 0, Qt::AlignRight);
    MainInfoLayout_11->addWidget(MainLineEditInfo_21, 0, Qt::AlignLeft);

    QSpacerItem* spacer_20 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_11->addItem(spacer_20);

    QLabel* MainLabelInfo_22 = new QLabel(" на сетке с половинным шагом использовано : ", tab7);
    MainLineEditInfo_22 = new QLineEdit();
    MainLineEditInfo_22->setMaximumWidth(250);
    MainInfoLayout_11->addWidget(MainLabelInfo_22, 0, Qt::AlignRight);
    MainInfoLayout_11->addWidget(MainLineEditInfo_22, 0, Qt::AlignLeft);

    QSpacerItem* spacer_21 = new QSpacerItem(10, 0, QSizePolicy::Expanding, QSizePolicy::Minimum);
    MainInfoLayout_11->addItem(spacer_21);

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


void Widget::InitGraphsTest() {
    Testgraph3D = new Q3DSurface();
    QWidget* container = QWidget::createWindowContainer(Testgraph3D);
    tab3->setLayout(new QVBoxLayout());
    tab3->layout()->addWidget(container);

    // Создание графика
    TestdataProxy = new QSurfaceDataProxy();
    Testseries = new QSurface3DSeries(TestdataProxy);
    Testgraph3D->addSeries(Testseries);


    // Настройка визуализации графика
    Testgraph3D->axisX()->setTitle("X Axis");
    Testgraph3D->axisY()->setTitle("Y Axis");
    Testgraph3D->axisZ()->setTitle("Z Axis");

    QLinearGradient gradient;
    gradient.setColorAt(0.0, Qt::blue);   // Low z-values
    gradient.setColorAt(0.5, Qt::green);  // Mid z-values
    gradient.setColorAt(1.0, Qt::red);    // High z-values

    Testseries->setBaseGradient(gradient);
    Testseries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    // Включение вращения графика в пространстве
    Testgraph3D->activeTheme()->setType(Q3DTheme::ThemeQt);

    // Настройка камеры для вращения графика
    Testgraph3D->scene()->activeCamera()->setCameraPosition(15, 15, 15);
}

void Widget::InitGraphsMain() {
    Maingraph3D = new Q3DSurface();
    QWidget* container = QWidget::createWindowContainer(Maingraph3D);
    tab6->setLayout(new QVBoxLayout());
    tab6->layout()->addWidget(container);

    // Создание графика
    MaindataProxy = new QSurfaceDataProxy();
    Mainseries = new QSurface3DSeries(MaindataProxy);
    Maingraph3D->addSeries(Mainseries);

    // Настройка визуализации графика
    Maingraph3D->axisX()->setTitle("X Axis");
    Maingraph3D->axisY()->setTitle("Y Axis");
    Maingraph3D->axisZ()->setTitle("Z Axis");

    QLinearGradient gradient;
    gradient.setColorAt(0.0, Qt::blue);   // Low z-values
    gradient.setColorAt(0.5, Qt::green);  // Mid z-values
    gradient.setColorAt(1.0, Qt::red);    // High z-values

    Mainseries->setBaseGradient(gradient);
    Mainseries->setColorStyle(Q3DTheme::ColorStyleRangeGradient);

    // Включение вращения графика в пространстве
    Maingraph3D->activeTheme()->setType(Q3DTheme::ThemeQt);

    // Настройка камеры для вращения графика
    Maingraph3D->scene()->activeCamera()->setCameraPosition(15, 15, 15);
}

void Widget::UpdateGraphsTest() {
    QSurfaceDataArray* TestdataArray = new QSurfaceDataArray();
    TestdataArray->reserve(config.CountCutX);

    double stepx = (config.EndXArea - config.StartXArea) / config.CountCutX;
    double stepy = (config.EndYArea - config.StartYArea) / config.CountCutY;

    for (int row = 0; row < config.CountCutY; ++row) {
        size_t BordersInRow = 0;
        size_t biasX = 0;
        for (size_t l = 0; l < config.CountCutX; ++l) {
            if (Network->nodes[l][row] == NodeType::BOUND)
                BordersInRow += 1;
        }
        QSurfaceDataRow* TestdataRow = new QSurfaceDataRow(config.CountCutX);

        for (int col = 0; col < config.CountCutX; ++col) {
            double x = config.StartXArea + col * stepx;
            double y = config.StartYArea + row * stepy;
            double val = 0.l;

            if (Network->nodes[col][row] == NodeType::BOUND) {
                val = DirTask->Boundary(x, y);
                biasX += 1;
            } else if (Network->nodes[col][row] == NodeType::INNER) {
                val = DirTask->Solution()[(col - biasX) + (row - 1) * (Network->nodes.size() - BordersInRow)];
            }
            (*TestdataRow)[col] = QVector3D(x, val, y);
        }
        TestdataArray->append(TestdataRow);
    }

    TestdataProxy->resetArray(TestdataArray);
}

void Widget::UpdateGraphsMain() {
    QSurfaceDataArray* MaindataArray = new QSurfaceDataArray();
    MaindataArray->reserve(config.CountCutX);

    double stepx = (config.EndXArea - config.StartXArea) / config.CountCutX;
    double stepy = (config.EndYArea - config.StartYArea) / config.CountCutY;

    for (int row = 0; row < config.CountCutY; ++row) {
        size_t BordersInRow = 0;
        size_t biasX = 0;
        for (size_t l = 0; l < config.CountCutX; ++l) {
            if (Network->nodes[l][row] == NodeType::BOUND)
                BordersInRow += 1;
        }
        QSurfaceDataRow* MaindataRow = new QSurfaceDataRow(config.CountCutX);

        for (int col = 0; col < config.CountCutX; ++col) {
            double x = config.StartXArea + col * stepx;
            double y = config.StartYArea + row * stepy;
            double val = 0.l;

            if (Network->nodes[col][row] == NodeType::BOUND) {
                val = DirTask->Boundary(x, y);
                biasX += 1;
            } else if (Network->nodes[col][row] == NodeType::INNER) {
                val = DirTask->Solution()[(col - biasX) + (row - 1) * (Network->nodes.size() - BordersInRow)];
            }
            (*MaindataRow)[col] = QVector3D(x, val, y);
        }
        MaindataArray->append(MaindataRow);
    }

    MaindataProxy->resetArray(MaindataArray);
}

void Widget::CreateTable2() {
    QTableWidget* table_2 = new QTableWidget(5, 7, tabTableTest);

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

    tabTableTest->layout()->addWidget(table_2);
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
