/********************************************************************************
** Form generated from reading UI file 'QHtml.ui'
**
** Created by: Qt User Interface Compiler version 5.12.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QHTML_H
#define UI_QHTML_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QHtmlClass
{
public:
    QPushButton *startbutton;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QTableWidget *tableWidget;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QTextEdit *LogOutput;
    QTableWidget *filterList;
    QPushButton *addFilterParamBtn;
    QPushButton *setFilterParamBtn;
    QPushButton *setFilterParamBtn_2;

    void setupUi(QWidget *QHtmlClass)
    {
        if (QHtmlClass->objectName().isEmpty())
            QHtmlClass->setObjectName(QString::fromUtf8("QHtmlClass"));
        QHtmlClass->resize(1121, 769);
        startbutton = new QPushButton(QHtmlClass);
        startbutton->setObjectName(QString::fromUtf8("startbutton"));
        startbutton->setGeometry(QRect(830, 0, 91, 51));
        verticalLayoutWidget = new QWidget(QHtmlClass);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(0, 0, 821, 391));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        tableWidget = new QTableWidget(verticalLayoutWidget);
        if (tableWidget->columnCount() < 7)
            tableWidget->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableWidget->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));

        verticalLayout->addWidget(tableWidget);

        verticalLayoutWidget_2 = new QWidget(QHtmlClass);
        verticalLayoutWidget_2->setObjectName(QString::fromUtf8("verticalLayoutWidget_2"));
        verticalLayoutWidget_2->setGeometry(QRect(830, 70, 281, 311));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei"));
        font.setPointSize(15);
        label->setFont(font);

        verticalLayout_2->addWidget(label);

        LogOutput = new QTextEdit(verticalLayoutWidget_2);
        LogOutput->setObjectName(QString::fromUtf8("LogOutput"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei"));
        LogOutput->setFont(font1);

        verticalLayout_2->addWidget(LogOutput);

        filterList = new QTableWidget(QHtmlClass);
        if (filterList->columnCount() < 7)
            filterList->setColumnCount(7);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        filterList->setHorizontalHeaderItem(0, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        filterList->setHorizontalHeaderItem(1, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        filterList->setHorizontalHeaderItem(2, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        filterList->setHorizontalHeaderItem(3, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        filterList->setHorizontalHeaderItem(4, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        filterList->setHorizontalHeaderItem(5, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        filterList->setHorizontalHeaderItem(6, __qtablewidgetitem13);
        filterList->setObjectName(QString::fromUtf8("filterList"));
        filterList->setGeometry(QRect(0, 480, 611, 192));
        addFilterParamBtn = new QPushButton(QHtmlClass);
        addFilterParamBtn->setObjectName(QString::fromUtf8("addFilterParamBtn"));
        addFilterParamBtn->setGeometry(QRect(630, 630, 111, 41));
        setFilterParamBtn = new QPushButton(QHtmlClass);
        setFilterParamBtn->setObjectName(QString::fromUtf8("setFilterParamBtn"));
        setFilterParamBtn->setGeometry(QRect(760, 630, 111, 41));
        setFilterParamBtn_2 = new QPushButton(QHtmlClass);
        setFilterParamBtn_2->setObjectName(QString::fromUtf8("setFilterParamBtn_2"));
        setFilterParamBtn_2->setGeometry(QRect(890, 630, 111, 41));

        retranslateUi(QHtmlClass);
        QObject::connect(setFilterParamBtn_2, SIGNAL(clicked()), QHtmlClass, SLOT(DelteFilterParam()));

        QMetaObject::connectSlotsByName(QHtmlClass);
    } // setupUi

    void retranslateUi(QWidget *QHtmlClass)
    {
        QHtmlClass->setWindowTitle(QApplication::translate("QHtmlClass", "QHtml", nullptr));
        startbutton->setText(QApplication::translate("QHtmlClass", "\345\274\200\345\247\213", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableWidget->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("QHtmlClass", "\346\211\277\345\205\221\344\272\272", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableWidget->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("QHtmlClass", "\351\207\221\351\242\235(\344\270\207\345\205\203)", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableWidget->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("QHtmlClass", "\345\210\260\346\234\237\346\227\245", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableWidget->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("QHtmlClass", "\346\257\217\345\215\201\344\270\207\346\211\243\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableWidget->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QApplication::translate("QHtmlClass", "\345\271\264\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableWidget->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QApplication::translate("QHtmlClass", "\347\221\225\347\226\265", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableWidget->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QApplication::translate("QHtmlClass", "\344\272\244\346\230\223\345\271\263\345\235\207\346\227\266\351\225\277", nullptr));
        label->setText(QApplication::translate("QHtmlClass", "\346\227\245\345\277\227", nullptr));
        LogOutput->setHtml(QApplication::translate("QHtmlClass", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Microsoft YaHei'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p></body></html>", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = filterList->horizontalHeaderItem(0);
        ___qtablewidgetitem7->setText(QApplication::translate("QHtmlClass", "\351\223\266\350\241\214", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = filterList->horizontalHeaderItem(1);
        ___qtablewidgetitem8->setText(QApplication::translate("QHtmlClass", "\351\207\221\351\242\235\357\274\210\346\234\200\345\260\217\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = filterList->horizontalHeaderItem(2);
        ___qtablewidgetitem9->setText(QApplication::translate("QHtmlClass", "\351\207\221\351\242\235\357\274\210\346\234\200\345\244\247\357\274\211", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = filterList->horizontalHeaderItem(3);
        ___qtablewidgetitem10->setText(QApplication::translate("QHtmlClass", "\345\271\264\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = filterList->horizontalHeaderItem(4);
        ___qtablewidgetitem11->setText(QApplication::translate("QHtmlClass", "\346\257\217\345\215\201\344\270\207\346\211\243\346\201\257", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = filterList->horizontalHeaderItem(5);
        ___qtablewidgetitem12->setText(QApplication::translate("QHtmlClass", "\345\211\251\344\275\231\346\227\266\351\227\264(\346\234\200\345\260\217)", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = filterList->horizontalHeaderItem(6);
        ___qtablewidgetitem13->setText(QApplication::translate("QHtmlClass", "\345\211\251\344\275\231\346\227\266\351\227\264(\346\234\200\345\244\247)", nullptr));
        addFilterParamBtn->setText(QApplication::translate("QHtmlClass", "\346\267\273\345\212\240\347\255\233\351\200\211", nullptr));
        setFilterParamBtn->setText(QApplication::translate("QHtmlClass", "\350\256\276\347\275\256\347\255\233\351\200\211", nullptr));
        setFilterParamBtn_2->setText(QApplication::translate("QHtmlClass", "\345\210\240\351\231\244\347\255\233\351\200\211", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QHtmlClass: public Ui_QHtmlClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QHTML_H
