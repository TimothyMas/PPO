/********************************************************************************
** Form generated from reading UI file 'mainppo.ui'
**
** Created by: Qt User Interface Compiler version 6.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINPPO_H
#define UI_MAINPPO_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainPPO
{
public:
    QAction *actionCalculateAverage;
    QAction *actionCalculateMaxMin;
    QAction *actionHealthOverview;

    QAction *actionVariance;
    QAction *actionStandardDeviation;

    QPushButton *runMLButton;

    QAction *actionExit;
    QAction *actionSet_Default_Directory;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *LoadData;
    QLabel *label_2;
    QPushButton *analyzeDataButton;
    QPushButton *generateDataButton;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_3;
    QPushButton *themeSwitchButton;
    QSpinBox *numPatientsSpinBox;
    QTextEdit *textEdit;
    QSpacerItem *horizontalSpacer;
    QLabel *label;
    QSpinBox *numMeasurementsSpinBox;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *saveToCSVButton;
    QMenuBar *menubar;
    QMenu *menuAnalysis;
    QMenu *menuExit;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainPPO)

    {
        if (MainPPO->objectName().isEmpty())
            MainPPO->setObjectName("MainPPO");

        MainPPO->resize(497, 837);
        MainPPO->setAutoFillBackground(false);

        actionCalculateAverage = new QAction(MainPPO);
        actionCalculateAverage->setObjectName("actionCalculateAverage");

        actionCalculateMaxMin = new QAction(MainPPO);
        actionCalculateMaxMin->setObjectName("actionCalculateMaxMin");

        actionHealthOverview = new QAction(MainPPO);
        actionHealthOverview->setObjectName("actionHealthOverview");


        actionStandardDeviation = new QAction(MainPPO);
        actionStandardDeviation->setObjectName("actionStandardDeviation");

        actionVariance = new QAction(MainPPO);
        actionVariance->setObjectName("actionVariance");


        actionExit = new QAction(MainPPO);
        actionExit->setObjectName("actionExit");

        actionSet_Default_Directory = new QAction(MainPPO);
        actionSet_Default_Directory->setObjectName("actionSet_Default_Directory");

        centralwidget = new QWidget(MainPPO);
        centralwidget->setObjectName("centralwidget");

        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName("gridLayout");

        LoadData = new QPushButton(centralwidget);
        LoadData->setObjectName("LoadData");

        gridLayout->addWidget(LoadData, 6, 1, 1, 1);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName("label_2");

        gridLayout->addWidget(label_2, 8, 0, 1, 1);

        analyzeDataButton = new QPushButton(centralwidget);
        analyzeDataButton->setObjectName("analyzeDataButton");

        gridLayout->addWidget(analyzeDataButton, 4, 1, 1, 1);

        runMLButton = new QPushButton(centralwidget);
        runMLButton->setObjectName("runMLButton");

        gridLayout->addWidget(runMLButton, 5, 0, 1, 1);

        generateDataButton = new QPushButton(centralwidget);
        generateDataButton->setObjectName("generateDataButton");
        generateDataButton->setStyleSheet(QString::fromUtf8(""));

        gridLayout->addWidget(generateDataButton, 4, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 3, 0, 1, 1);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName("label_3");

        gridLayout->addWidget(label_3, 8, 1, 1, 1);

        themeSwitchButton = new QPushButton(centralwidget);
        themeSwitchButton->setObjectName("themeSwitchButton");

        gridLayout->addWidget(themeSwitchButton, 0, 1, 1, 1);

        numPatientsSpinBox = new QSpinBox(centralwidget);
        numPatientsSpinBox->setObjectName("numPatientsSpinBox");

        gridLayout->addWidget(numPatientsSpinBox, 9, 0, 1, 1);

        textEdit = new QTextEdit(centralwidget);
        textEdit->setObjectName("textEdit");

        gridLayout->addWidget(textEdit, 2, 0, 1, 2);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 7, 0, 1, 1);

        label = new QLabel(centralwidget);
        label->setObjectName("label");
        QFont font;
        font.setPointSize(15);
        label->setFont(font);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        numMeasurementsSpinBox = new QSpinBox(centralwidget);
        numMeasurementsSpinBox->setObjectName("numMeasurementsSpinBox");

        gridLayout->addWidget(numMeasurementsSpinBox, 9, 1, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 1, 0, 1, 1);

        saveToCSVButton = new QPushButton(centralwidget);
        saveToCSVButton->setObjectName("saveToCSVButton");

        gridLayout->addWidget(saveToCSVButton, 6, 0, 1, 1);

        MainPPO->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainPPO);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 497, 21));
        menuAnalysis = new QMenu(menubar);
        menuAnalysis->setObjectName("menuAnalysis");
        menuExit = new QMenu(menubar);
        menuExit->setObjectName("menuExit");
        MainPPO->setMenuBar(menubar);
        statusbar = new QStatusBar(MainPPO);
        statusbar->setObjectName("statusbar");
        MainPPO->setStatusBar(statusbar);

        menubar->addAction(menuAnalysis->menuAction());
        menubar->addAction(menuExit->menuAction());

        menuAnalysis->addAction(actionCalculateAverage);
        menuAnalysis->addAction(actionCalculateMaxMin);
        menuAnalysis->addAction(actionHealthOverview);

        menuAnalysis->addAction(actionStandardDeviation);
        menuAnalysis->addAction(actionVariance);

        menuExit->addAction(actionSet_Default_Directory);
        menuExit->addAction(actionExit);

        retranslateUi(MainPPO);

        QMetaObject::connectSlotsByName(MainPPO);
    } // setupUi

    void retranslateUi(QMainWindow *MainPPO)
    {
        MainPPO->setWindowTitle(QCoreApplication::translate("MainPPO", "MainPPO", nullptr));
        actionCalculateAverage->setText(QCoreApplication::translate("MainPPO", "Average Values", nullptr));
        actionCalculateMaxMin->setText(QCoreApplication::translate("MainPPO", "Max/Min Values", nullptr));
        actionHealthOverview->setText(QCoreApplication::translate("MainPPO", "Health Overview", nullptr));
        actionExit->setText(QCoreApplication::translate("MainPPO", "Exit", nullptr));
        actionSet_Default_Directory->setText(QCoreApplication::translate("MainPPO", "Set Default Directory", nullptr));

        actionStandardDeviation->setText(QCoreApplication::translate("MainPPO", "Standard Deviation", nullptr));
        actionVariance->setText(QCoreApplication::translate("MainPPO", "Variance", nullptr));

        LoadData->setText(QCoreApplication::translate("MainPPO", "Load Data", nullptr));
        label_2->setText(QCoreApplication::translate("MainPPO", "Number of Patients :", nullptr));

        analyzeDataButton->setText(QCoreApplication::translate("MainPPO", "Analyze Data", nullptr));
        generateDataButton->setText(QCoreApplication::translate("MainPPO", "Generate Data", nullptr));
        saveToCSVButton->setText(QCoreApplication::translate("MainPPO", "Save to CSV", nullptr));
        themeSwitchButton->setText(QCoreApplication::translate("MainPPO", "Change Theme", nullptr));
        runMLButton->setText(QCoreApplication::translate("MainPPO", "Run Machine Learning", nullptr));

        label_3->setText(QCoreApplication::translate("MainPPO", "Number of Measurements:", nullptr));
        label->setText(QCoreApplication::translate("MainPPO", "Patients Data:", nullptr));
        menuAnalysis->setTitle(QCoreApplication::translate("MainPPO", "Analysis", nullptr));
        menuExit->setTitle(QCoreApplication::translate("MainPPO", "Options", nullptr));
    } // retranslateUi

};

namespace Ui

{
    class MainPPO: public Ui_MainPPO {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINPPO_H
