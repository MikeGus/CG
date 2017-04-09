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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGraphicsView *graphicsView;
    QTabWidget *tabWidget;
    QWidget *tab;
    QGridLayout *gridLayout;
    QSpacerItem *verticalSpacer;
    QLineEdit *lineEdit;
    QLabel *label_3;
    QLineEdit *lineEdit_3;
    QLabel *label_4;
    QLineEdit *lineEdit_2;
    QLabel *label_5;
    QLineEdit *lineEdit_4;
    QLabel *label;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QLabel *label_2;
    QPushButton *pushButton;
    QComboBox *comboBox;
    QWidget *tab_2;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QLineEdit *lineEdit_5;
    QLabel *label_7;
    QLineEdit *lineEdit_6;
    QLabel *label_8;
    QLineEdit *lineEdit_7;
    QLabel *label_10;
    QComboBox *comboBox_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_6;
    QSpacerItem *verticalSpacer_2;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(640, 369);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        graphicsView = new QGraphicsView(centralWidget);
        graphicsView->setObjectName(QStringLiteral("graphicsView"));
        graphicsView->setMinimumSize(QSize(300, 300));

        horizontalLayout->addWidget(graphicsView);

        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        gridLayout = new QGridLayout(tab);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 5, 0, 1, 1);

        lineEdit = new QLineEdit(tab);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        gridLayout->addWidget(lineEdit, 0, 1, 1, 1);

        label_3 = new QLabel(tab);
        label_3->setObjectName(QStringLiteral("label_3"));

        gridLayout->addWidget(label_3, 0, 2, 1, 1);

        lineEdit_3 = new QLineEdit(tab);
        lineEdit_3->setObjectName(QStringLiteral("lineEdit_3"));

        gridLayout->addWidget(lineEdit_3, 0, 3, 1, 1);

        label_4 = new QLabel(tab);
        label_4->setObjectName(QStringLiteral("label_4"));

        gridLayout->addWidget(label_4, 1, 0, 1, 1);

        lineEdit_2 = new QLineEdit(tab);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        gridLayout->addWidget(lineEdit_2, 1, 1, 1, 1);

        label_5 = new QLabel(tab);
        label_5->setObjectName(QStringLiteral("label_5"));

        gridLayout->addWidget(label_5, 1, 2, 1, 1);

        lineEdit_4 = new QLineEdit(tab);
        lineEdit_4->setObjectName(QStringLiteral("lineEdit_4"));

        gridLayout->addWidget(lineEdit_4, 1, 3, 1, 1);

        label = new QLabel(tab);
        label->setObjectName(QStringLiteral("label"));

        gridLayout->addWidget(label, 2, 0, 1, 2);

        pushButton_3 = new QPushButton(tab);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout->addWidget(pushButton_3, 3, 2, 1, 2);

        pushButton_2 = new QPushButton(tab);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        gridLayout->addWidget(pushButton_2, 4, 2, 1, 2);

        label_2 = new QLabel(tab);
        label_2->setObjectName(QStringLiteral("label_2"));

        gridLayout->addWidget(label_2, 0, 0, 1, 1);

        pushButton = new QPushButton(tab);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        gridLayout->addWidget(pushButton, 4, 0, 1, 2);

        comboBox = new QComboBox(tab);
        comboBox->setObjectName(QStringLiteral("comboBox"));

        gridLayout->addWidget(comboBox, 3, 0, 1, 2);

        gridLayout->setColumnStretch(0, 1);
        gridLayout->setColumnStretch(1, 1);
        gridLayout->setColumnStretch(2, 1);
        gridLayout->setColumnStretch(3, 1);
        gridLayout->setColumnMinimumWidth(0, 1);
        gridLayout->setColumnMinimumWidth(1, 1);
        gridLayout->setColumnMinimumWidth(2, 1);
        gridLayout->setColumnMinimumWidth(3, 1);
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        gridLayout_2 = new QGridLayout(tab_2);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        lineEdit_5 = new QLineEdit(tab_2);
        lineEdit_5->setObjectName(QStringLiteral("lineEdit_5"));

        gridLayout_2->addWidget(lineEdit_5, 0, 1, 1, 1);

        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));

        gridLayout_2->addWidget(label_7, 0, 2, 1, 1);

        lineEdit_6 = new QLineEdit(tab_2);
        lineEdit_6->setObjectName(QStringLiteral("lineEdit_6"));

        gridLayout_2->addWidget(lineEdit_6, 0, 3, 1, 1);

        label_8 = new QLabel(tab_2);
        label_8->setObjectName(QStringLiteral("label_8"));

        gridLayout_2->addWidget(label_8, 1, 0, 1, 1);

        lineEdit_7 = new QLineEdit(tab_2);
        lineEdit_7->setObjectName(QStringLiteral("lineEdit_7"));

        gridLayout_2->addWidget(lineEdit_7, 1, 1, 1, 1);

        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));

        gridLayout_2->addWidget(label_10, 2, 0, 1, 2);

        comboBox_2 = new QComboBox(tab_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));

        gridLayout_2->addWidget(comboBox_2, 3, 0, 1, 2);

        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_2->addWidget(pushButton_4, 3, 2, 1, 2);

        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_2->addWidget(pushButton_5, 4, 0, 1, 2);

        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_2->addWidget(pushButton_6, 4, 2, 1, 2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 5, 0, 1, 1);

        gridLayout_2->setColumnStretch(0, 1);
        gridLayout_2->setColumnStretch(1, 1);
        gridLayout_2->setColumnStretch(2, 1);
        gridLayout_2->setColumnStretch(3, 1);
        gridLayout_2->setColumnMinimumWidth(0, 1);
        gridLayout_2->setColumnMinimumWidth(1, 1);
        gridLayout_2->setColumnMinimumWidth(2, 1);
        gridLayout_2->setColumnMinimumWidth(3, 1);
        tabWidget->addTab(tab_2, QString());

        horizontalLayout->addWidget(tabWidget);

        horizontalLayout->setStretch(0, 3);
        horizontalLayout->setStretch(1, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 640, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\233\320\260\320\261\320\276\321\200\320\260\321\202\320\276\321\200\320\275\320\260\321\217 3", 0));
        lineEdit->setText(QApplication::translate("MainWindow", "0.0", 0));
        label_3->setText(QApplication::translate("MainWindow", "Y\321\206", 0));
        lineEdit_3->setText(QApplication::translate("MainWindow", "0.0", 0));
        label_4->setText(QApplication::translate("MainWindow", "A", 0));
        lineEdit_2->setText(QApplication::translate("MainWindow", "0.0", 0));
        label_5->setText(QApplication::translate("MainWindow", "B", 0));
        lineEdit_4->setText(QApplication::translate("MainWindow", "0.0", 0));
        label->setText(QApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274", 0));
        pushButton_3->setText(QApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", 0));
        pushButton_2->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\245\321\206", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\320\241\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\213\320\271", 0)
         << QApplication::translate("MainWindow", "\320\241\321\200\320\265\320\264\320\275\320\265\320\271 \321\202\320\276\321\207\320\272\320\270", 0)
         << QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\276\320\275\320\270\321\207. \321\203\321\200-\320\265", 0)
         << QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200. \321\203\321\200-\320\265", 0)
         << QApplication::translate("MainWindow", "\320\221\321\200\320\265\320\267\320\265\320\275\321\205\320\265\320\274", 0)
        );
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("MainWindow", "\320\255\320\273\320\273\320\270\320\277\321\201", 0));
        label_6->setText(QApplication::translate("MainWindow", "X\321\206.", 0));
        lineEdit_5->setText(QApplication::translate("MainWindow", "0.0", 0));
        label_7->setText(QApplication::translate("MainWindow", "Y\321\206.", 0));
        lineEdit_6->setText(QApplication::translate("MainWindow", "0.0", 0));
        label_8->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\264\320\270\321\203\321\201", 0));
        lineEdit_7->setText(QApplication::translate("MainWindow", "0.0", 0));
        label_10->setText(QApplication::translate("MainWindow", "\320\220\320\273\320\263\320\276\321\200\320\270\321\202\320\274", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MainWindow", "\320\241\321\202\320\260\320\275\320\264\320\260\321\200\321\202\320\275\321\213\320\271", 0)
         << QApplication::translate("MainWindow", "\320\241\321\200\320\265\320\264\320\275\320\265\320\271 \321\202\320\276\321\207\320\272\320\270", 0)
         << QApplication::translate("MainWindow", "\320\232\320\260\320\275\320\276\320\275\320\270\321\207. \321\203\321\200-\320\265", 0)
         << QApplication::translate("MainWindow", "\320\237\320\260\321\200\320\260\320\274\320\265\321\202\321\200. \321\203\321\200-\320\265", 0)
         << QApplication::translate("MainWindow", "\320\221\321\200\320\265\320\267\320\265\320\275\321\205\320\265\320\274", 0)
        );
        pushButton_4->setText(QApplication::translate("MainWindow", "\320\246\320\262\320\265\321\202", 0));
        pushButton_5->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\200\320\270\321\201\320\276\320\262\320\260\321\202\321\214", 0));
        pushButton_6->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", 0));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("MainWindow", "\320\236\320\272\321\200\321\203\320\266\320\275\320\276\321\201\321\202\321\214", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
