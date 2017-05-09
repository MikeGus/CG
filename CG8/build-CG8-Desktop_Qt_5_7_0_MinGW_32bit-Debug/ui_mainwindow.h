/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <myqgraphicsview.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    MyQGraphicsView *graphicsView;
    QGridLayout *gridLayout;
    QRadioButton *radioFigure;
    QRadioButton *radioSplit;
    QPushButton *btnClearLines;
    QPushButton *btnClear;
    QRadioButton *radioFigureHoles;
    QRadioButton *radioSplitHoles;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(959, 461);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new MyQGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));

        horizontalLayout->addWidget(graphicsView);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        radioFigure = new QRadioButton(centralWidget);
        buttonGroup = new QButtonGroup(MainWindow);
        buttonGroup->setObjectName(QStringLiteral("buttonGroup"));
        buttonGroup->addButton(radioFigure);
        radioFigure->setObjectName(QStringLiteral("radioFigure"));

        gridLayout->addWidget(radioFigure, 0, 2, 1, 2);

        radioSplit = new QRadioButton(centralWidget);
        buttonGroup->addButton(radioSplit);
        radioSplit->setObjectName(QStringLiteral("radioSplit"));

        gridLayout->addWidget(radioSplit, 0, 0, 1, 2);

        btnClearLines = new QPushButton(centralWidget);
        btnClearLines->setObjectName(QStringLiteral("btnClearLines"));

        gridLayout->addWidget(btnClearLines, 3, 0, 1, 4);

        btnClear = new QPushButton(centralWidget);
        btnClear->setObjectName(QStringLiteral("btnClear"));

        gridLayout->addWidget(btnClear, 4, 0, 1, 4);

        radioFigureHoles = new QRadioButton(centralWidget);
        buttonGroup->addButton(radioFigureHoles);
        radioFigureHoles->setObjectName(QStringLiteral("radioFigureHoles"));

        gridLayout->addWidget(radioFigureHoles, 1, 2, 1, 2);

        radioSplitHoles = new QRadioButton(centralWidget);
        buttonGroup->addButton(radioSplitHoles);
        radioSplitHoles->setObjectName(QStringLiteral("radioSplitHoles"));

        gridLayout->addWidget(radioSplitHoles, 1, 0, 1, 2);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 2, 0, 1, 1);


        horizontalLayout->addLayout(gridLayout);

        horizontalLayout->setStretch(0, 2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 959, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\233\320\260\320\261\320\276\321\200\320\260\321\202\320\276\321\200\320\275\320\260\321\217 8", 0));
        radioFigure->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\276\321\202\321\201\320\265\320\272\320\260\320\265\320\274\320\276\320\263\320\276\n"
"\320\274\320\275\320\276\320\263\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\260", 0));
        radioSplit->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\276\320\261\320\273\320\260\321\201\321\202\320\270\n"
"\320\262\320\270\320\264\320\270\320\274\320\276\321\201\321\202\320\270", 0));
        btnClearLines->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\276\321\202\321\201\320\265\320\272\320\260\320\265\320\274\321\213\320\265 \320\274\320\275\320\276\320\263\320\276\321\203\320\263\320\276\320\273\321\214\320\275\320\270\320\272\320\270", 0));
        btnClear->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\262\321\201\321\221", 0));
        radioFigureHoles->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\262\320\275\321\203\321\202\321\200\320\265\320\275\320\275\320\270\321\205\n"
"\320\276\321\202\320\262\320\265\321\200\321\201\321\202\320\270\320\271", 0));
        radioSplitHoles->setText(QApplication::translate("MainWindow", "\320\222\320\262\320\276\320\264 \320\262\320\275\321\203\321\202\321\200\320\265\320\275\320\275\320\270\321\205\n"
"\320\276\321\202\320\262\320\265\321\200\321\201\321\202\320\270\320\271 \320\276\320\261\320\273. \320\262\320\270\320\264\320\270\320\274\320\276\321\201\321\202\320\270", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
