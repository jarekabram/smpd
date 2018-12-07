/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *tabP;
    QPushButton *PpushButtonSelectFolder;
    QGraphicsView *PgraphicsView;
    QGraphicsView *PgraphicsViewEdge;
    QWidget *tabFS;
    QPushButton *FSpushButtonOpenFile;
    QPushButton *FSpushButtonSaveFile;
    QComboBox *FScomboBox;
    QLabel *label;
    QRadioButton *FSradioButtonFisher;
    QRadioButton *FSradioButtonSFS;
    QPushButton *FSpushButtonCompute;
    QTextBrowser *FStextBrowserDatabaseInfo;
    QWidget *tabC;
    QPushButton *CpushButtonOpenFile;
    QPushButton *CpushButtonSaveFile;
    QComboBox *CcomboBoxK;
    QLabel *ClabelK;
    QPushButton *CpushButtonTrain;
    QLabel *ClabelClassifiers;
    QComboBox *CcomboBoxClassifiers;
    QPlainTextEdit *CplainTextEditTrainingPart;
    QPushButton *CpushButtonExecute;
    QLabel *ClabelTraningPart;
    QTextBrowser *CtextBrowser;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(991, 540);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 971, 491));
        tabP = new QWidget();
        tabP->setObjectName(QString::fromUtf8("tabP"));
        PpushButtonSelectFolder = new QPushButton(tabP);
        PpushButtonSelectFolder->setObjectName(QString::fromUtf8("PpushButtonSelectFolder"));
        PpushButtonSelectFolder->setGeometry(QRect(10, 10, 75, 31));
        PgraphicsView = new QGraphicsView(tabP);
        PgraphicsView->setObjectName(QString::fromUtf8("PgraphicsView"));
        PgraphicsView->setGeometry(QRect(680, 30, 256, 192));
        PgraphicsView->setInteractive(true);
        PgraphicsView->setViewportUpdateMode(QGraphicsView::MinimalViewportUpdate);
        PgraphicsViewEdge = new QGraphicsView(tabP);
        PgraphicsViewEdge->setObjectName(QString::fromUtf8("PgraphicsViewEdge"));
        PgraphicsViewEdge->setGeometry(QRect(680, 250, 256, 192));
        tabWidget->addTab(tabP, QString());
        tabFS = new QWidget();
        tabFS->setObjectName(QString::fromUtf8("tabFS"));
        FSpushButtonOpenFile = new QPushButton(tabFS);
        FSpushButtonOpenFile->setObjectName(QString::fromUtf8("FSpushButtonOpenFile"));
        FSpushButtonOpenFile->setGeometry(QRect(10, 10, 75, 31));
        FSpushButtonSaveFile = new QPushButton(tabFS);
        FSpushButtonSaveFile->setObjectName(QString::fromUtf8("FSpushButtonSaveFile"));
        FSpushButtonSaveFile->setGeometry(QRect(10, 60, 75, 31));
        FScomboBox = new QComboBox(tabFS);
        FScomboBox->setObjectName(QString::fromUtf8("FScomboBox"));
        FScomboBox->setGeometry(QRect(250, 10, 69, 31));
        label = new QLabel(tabFS);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(150, 10, 101, 31));
        FSradioButtonFisher = new QRadioButton(tabFS);
        FSradioButtonFisher->setObjectName(QString::fromUtf8("FSradioButtonFisher"));
        FSradioButtonFisher->setGeometry(QRect(251, 50, 71, 20));
        FSradioButtonFisher->setChecked(true);
        FSradioButtonSFS = new QRadioButton(tabFS);
        FSradioButtonSFS->setObjectName(QString::fromUtf8("FSradioButtonSFS"));
        FSradioButtonSFS->setGeometry(QRect(250, 80, 82, 21));
        FSpushButtonCompute = new QPushButton(tabFS);
        FSpushButtonCompute->setObjectName(QString::fromUtf8("FSpushButtonCompute"));
        FSpushButtonCompute->setGeometry(QRect(380, 10, 75, 31));
        FStextBrowserDatabaseInfo = new QTextBrowser(tabFS);
        FStextBrowserDatabaseInfo->setObjectName(QString::fromUtf8("FStextBrowserDatabaseInfo"));
        FStextBrowserDatabaseInfo->setGeometry(QRect(700, 10, 256, 192));
        tabWidget->addTab(tabFS, QString());
        tabC = new QWidget();
        tabC->setObjectName(QString::fromUtf8("tabC"));
        CpushButtonOpenFile = new QPushButton(tabC);
        CpushButtonOpenFile->setObjectName(QString::fromUtf8("CpushButtonOpenFile"));
        CpushButtonOpenFile->setGeometry(QRect(10, 10, 75, 31));
        CpushButtonSaveFile = new QPushButton(tabC);
        CpushButtonSaveFile->setObjectName(QString::fromUtf8("CpushButtonSaveFile"));
        CpushButtonSaveFile->setGeometry(QRect(10, 60, 75, 31));
        CcomboBoxK = new QComboBox(tabC);
        CcomboBoxK->setObjectName(QString::fromUtf8("CcomboBoxK"));
        CcomboBoxK->setGeometry(QRect(210, 61, 69, 31));
        ClabelK = new QLabel(tabC);
        ClabelK->setObjectName(QString::fromUtf8("ClabelK"));
        ClabelK->setGeometry(QRect(190, 70, 20, 31));
        CpushButtonTrain = new QPushButton(tabC);
        CpushButtonTrain->setObjectName(QString::fromUtf8("CpushButtonTrain"));
        CpushButtonTrain->setGeometry(QRect(380, 10, 75, 31));
        ClabelClassifiers = new QLabel(tabC);
        ClabelClassifiers->setObjectName(QString::fromUtf8("ClabelClassifiers"));
        ClabelClassifiers->setGeometry(QRect(150, 10, 71, 31));
        CcomboBoxClassifiers = new QComboBox(tabC);
        CcomboBoxClassifiers->setObjectName(QString::fromUtf8("CcomboBoxClassifiers"));
        CcomboBoxClassifiers->setGeometry(QRect(210, 10, 69, 31));
        CplainTextEditTrainingPart = new QPlainTextEdit(tabC);
        CplainTextEditTrainingPart->setObjectName(QString::fromUtf8("CplainTextEditTrainingPart"));
        CplainTextEditTrainingPart->setGeometry(QRect(380, 60, 71, 31));
        CpushButtonExecute = new QPushButton(tabC);
        CpushButtonExecute->setObjectName(QString::fromUtf8("CpushButtonExecute"));
        CpushButtonExecute->setGeometry(QRect(540, 10, 75, 31));
        ClabelTraningPart = new QLabel(tabC);
        ClabelTraningPart->setObjectName(QString::fromUtf8("ClabelTraningPart"));
        ClabelTraningPart->setGeometry(QRect(300, 70, 81, 31));
        CtextBrowser = new QTextBrowser(tabC);
        CtextBrowser->setObjectName(QString::fromUtf8("CtextBrowser"));
        CtextBrowser->setGeometry(QRect(700, 10, 256, 192));
        tabWidget->addTab(tabC, QString());
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 991, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        PpushButtonSelectFolder->setText(QApplication::translate("MainWindow", "Select Folder", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabP), QApplication::translate("MainWindow", "Preprocessing", nullptr));
        FSpushButtonOpenFile->setText(QApplication::translate("MainWindow", "Open File", nullptr));
        FSpushButtonSaveFile->setText(QApplication::translate("MainWindow", "Save File", nullptr));
        label->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt;\">Feature number:</span></p></body></html>", nullptr));
        FSradioButtonFisher->setText(QApplication::translate("MainWindow", "Fisher", nullptr));
        FSradioButtonSFS->setText(QApplication::translate("MainWindow", "SFS", nullptr));
        FSpushButtonCompute->setText(QApplication::translate("MainWindow", "Compute", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabFS), QApplication::translate("MainWindow", "Features Selection", nullptr));
        CpushButtonOpenFile->setText(QApplication::translate("MainWindow", "Open File", nullptr));
        CpushButtonSaveFile->setText(QApplication::translate("MainWindow", "Save File", nullptr));
        ClabelK->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt;\">k:</span></p></body></html>", nullptr));
        CpushButtonTrain->setText(QApplication::translate("MainWindow", "Train", nullptr));
        ClabelClassifiers->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt;\">Classifiers:</span></p></body></html>", nullptr));
        CpushButtonExecute->setText(QApplication::translate("MainWindow", "Execute", nullptr));
        ClabelTraningPart->setText(QApplication::translate("MainWindow", "<html><head/><body><p><span style=\" font-size:9pt;\">Training part:</span></p></body></html>", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tabC), QApplication::translate("MainWindow", "Classifiers", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
