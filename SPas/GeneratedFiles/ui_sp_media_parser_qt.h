/********************************************************************************
** Form generated from reading UI file 'sp_media_parser_qt.ui'
**
** Created by: Qt User Interface Compiler version 5.8.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SP_MEDIA_PARSER_QT_H
#define UI_SP_MEDIA_PARSER_QT_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SPasClass
{
public:
    QAction *openFile;
    QAction *actionabout;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QTableWidget *FrameListTableWidget;
    QLabel *FrameShowBinaryTextLabel;
    QLabel *MediaInfoLable;
    QTextEdit *FrameShowBinaryText;
    QTextEdit *MediaInfo;
    QMenuBar *menuBar;
    QMenu *menu;
    QMenu *menuview;
    QMenu *menuinfo;

    void setupUi(QMainWindow *SPasClass)
    {
        if (SPasClass->objectName().isEmpty())
            SPasClass->setObjectName(QStringLiteral("SPasClass"));
        SPasClass->resize(964, 728);
        openFile = new QAction(SPasClass);
        openFile->setObjectName(QStringLiteral("openFile"));
        actionabout = new QAction(SPasClass);
        actionabout->setObjectName(QStringLiteral("actionabout"));
        centralWidget = new QWidget(SPasClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        horizontalLayout = new QHBoxLayout(centralWidget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 6);
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setEnabled(true);
        groupBox->setInputMethodHints(Qt::ImhHiddenText);
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        FrameListTableWidget = new QTableWidget(groupBox);
        if (FrameListTableWidget->columnCount() < 11)
            FrameListTableWidget->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        FrameListTableWidget->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        FrameListTableWidget->setObjectName(QStringLiteral("FrameListTableWidget"));
        FrameListTableWidget->setEnabled(true);
        FrameListTableWidget->setContextMenuPolicy(Qt::CustomContextMenu);
        FrameListTableWidget->setColumnCount(11);
        FrameListTableWidget->horizontalHeader()->setVisible(true);
        FrameListTableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        FrameListTableWidget->horizontalHeader()->setHighlightSections(true);
        FrameListTableWidget->verticalHeader()->setVisible(false);
        FrameListTableWidget->verticalHeader()->setHighlightSections(true);

        gridLayout->addWidget(FrameListTableWidget, 0, 0, 1, 2);

        FrameShowBinaryTextLabel = new QLabel(groupBox);
        FrameShowBinaryTextLabel->setObjectName(QStringLiteral("FrameShowBinaryTextLabel"));

        gridLayout->addWidget(FrameShowBinaryTextLabel, 1, 0, 1, 1);

        MediaInfoLable = new QLabel(groupBox);
        MediaInfoLable->setObjectName(QStringLiteral("MediaInfoLable"));

        gridLayout->addWidget(MediaInfoLable, 1, 1, 1, 1);

        FrameShowBinaryText = new QTextEdit(groupBox);
        FrameShowBinaryText->setObjectName(QStringLiteral("FrameShowBinaryText"));

        gridLayout->addWidget(FrameShowBinaryText, 2, 0, 1, 1);

        MediaInfo = new QTextEdit(groupBox);
        MediaInfo->setObjectName(QStringLiteral("MediaInfo"));

        gridLayout->addWidget(MediaInfo, 2, 1, 1, 1);

        gridLayout->setRowStretch(0, 6);
        gridLayout->setRowStretch(2, 3);
        gridLayout->setColumnStretch(0, 1);

        horizontalLayout->addWidget(groupBox);

        SPasClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(SPasClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 964, 26));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        menuview = new QMenu(menuBar);
        menuview->setObjectName(QStringLiteral("menuview"));
        menuinfo = new QMenu(menuBar);
        menuinfo->setObjectName(QStringLiteral("menuinfo"));
        SPasClass->setMenuBar(menuBar);

        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuview->menuAction());
        menuBar->addAction(menuinfo->menuAction());
        menu->addAction(openFile);
        menuinfo->addAction(actionabout);

        retranslateUi(SPasClass);

        QMetaObject::connectSlotsByName(SPasClass);
    } // setupUi

    void retranslateUi(QMainWindow *SPasClass)
    {
        SPasClass->setWindowTitle(QApplication::translate("SPasClass", "SPas", Q_NULLPTR));
        openFile->setText(QApplication::translate("SPasClass", "open", Q_NULLPTR));
        actionabout->setText(QApplication::translate("SPasClass", "about", Q_NULLPTR));
        groupBox->setTitle(QString());
        QTableWidgetItem *___qtablewidgetitem = FrameListTableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SPasClass", "\345\270\247\345\272\217\345\217\267", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem1 = FrameListTableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SPasClass", "\345\270\247\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem2 = FrameListTableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SPasClass", "\345\270\247\351\225\277\345\272\246", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem3 = FrameListTableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SPasClass", "\345\270\247\345\201\217\347\247\273", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem4 = FrameListTableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("SPasClass", "\351\237\263\350\247\206\351\242\221\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem5 = FrameListTableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("SPasClass", "\347\274\226\347\240\201\347\261\273\345\236\213", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem6 = FrameListTableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("SPasClass", "\347\274\226\347\240\201\346\240\274\345\274\217", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem7 = FrameListTableWidget->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QApplication::translate("SPasClass", "\345\210\206\350\276\250\347\216\207/\345\256\275", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem8 = FrameListTableWidget->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QApplication::translate("SPasClass", "\345\210\206\350\276\250\347\216\207/\351\253\230", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem9 = FrameListTableWidget->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QApplication::translate("SPasClass", "\345\270\247\347\216\207", Q_NULLPTR));
        QTableWidgetItem *___qtablewidgetitem10 = FrameListTableWidget->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QApplication::translate("SPasClass", "\346\227\266\351\227\264\346\210\263", Q_NULLPTR));
        FrameShowBinaryTextLabel->setText(QApplication::translate("SPasClass", "Binary Text", Q_NULLPTR));
        MediaInfoLable->setText(QApplication::translate("SPasClass", "Media Info", Q_NULLPTR));
        menu->setTitle(QApplication::translate("SPasClass", "file", Q_NULLPTR));
        menuview->setTitle(QApplication::translate("SPasClass", "view", Q_NULLPTR));
        menuinfo->setTitle(QApplication::translate("SPasClass", "help", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class SPasClass: public Ui_SPasClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SP_MEDIA_PARSER_QT_H
