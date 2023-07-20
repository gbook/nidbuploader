/********************************************************************************
** Form generated from reading UI file 'remotestatus.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_REMOTESTATUS_H
#define UI_REMOTESTATUS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_RemoteStatus
{
public:
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_3;
    QComboBox *cmbTransactions;
    QPushButton *btnRefresh;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnViewRemoteStatus;
    QLabel *lblStatus;
    QLabel *label;
    QTableWidget *tableBlockReceipt;
    QLabel *label_2;
    QTableWidget *tableArchiveStatus;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *btnClose;

    void setupUi(QDialog *RemoteStatus)
    {
        if (RemoteStatus->objectName().isEmpty())
            RemoteStatus->setObjectName("RemoteStatus");
        RemoteStatus->resize(912, 637);
        verticalLayout_2 = new QVBoxLayout(RemoteStatus);
        verticalLayout_2->setObjectName("verticalLayout_2");
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        label_3 = new QLabel(RemoteStatus);
        label_3->setObjectName("label_3");

        horizontalLayout->addWidget(label_3);

        cmbTransactions = new QComboBox(RemoteStatus);
        cmbTransactions->setObjectName("cmbTransactions");

        horizontalLayout->addWidget(cmbTransactions);

        btnRefresh = new QPushButton(RemoteStatus);
        btnRefresh->setObjectName("btnRefresh");
        btnRefresh->setMaximumSize(QSize(16777215, 16777215));

        horizontalLayout->addWidget(btnRefresh);

        horizontalSpacer = new QSpacerItem(50, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        btnViewRemoteStatus = new QPushButton(RemoteStatus);
        btnViewRemoteStatus->setObjectName("btnViewRemoteStatus");

        horizontalLayout->addWidget(btnViewRemoteStatus);


        verticalLayout_2->addLayout(horizontalLayout);

        lblStatus = new QLabel(RemoteStatus);
        lblStatus->setObjectName("lblStatus");
        lblStatus->setStyleSheet(QString::fromUtf8("color: red"));

        verticalLayout_2->addWidget(lblStatus);

        label = new QLabel(RemoteStatus);
        label->setObjectName("label");

        verticalLayout_2->addWidget(label);

        tableBlockReceipt = new QTableWidget(RemoteStatus);
        if (tableBlockReceipt->columnCount() < 5)
            tableBlockReceipt->setColumnCount(5);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tableBlockReceipt->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableBlockReceipt->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableBlockReceipt->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableBlockReceipt->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableBlockReceipt->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        tableBlockReceipt->setObjectName("tableBlockReceipt");

        verticalLayout_2->addWidget(tableBlockReceipt);

        label_2 = new QLabel(RemoteStatus);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        tableArchiveStatus = new QTableWidget(RemoteStatus);
        if (tableArchiveStatus->columnCount() < 9)
            tableArchiveStatus->setColumnCount(9);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(0, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(1, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(2, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(3, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(4, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(5, __qtablewidgetitem10);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(6, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(7, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        tableArchiveStatus->setHorizontalHeaderItem(8, __qtablewidgetitem13);
        tableArchiveStatus->setObjectName("tableArchiveStatus");

        verticalLayout_2->addWidget(tableArchiveStatus);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 0, -1, -1);
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        btnClose = new QPushButton(RemoteStatus);
        btnClose->setObjectName("btnClose");

        horizontalLayout_2->addWidget(btnClose);


        verticalLayout_2->addLayout(horizontalLayout_2);


        retranslateUi(RemoteStatus);

        QMetaObject::connectSlotsByName(RemoteStatus);
    } // setupUi

    void retranslateUi(QDialog *RemoteStatus)
    {
        RemoteStatus->setWindowTitle(QCoreApplication::translate("RemoteStatus", "Remote Status", nullptr));
        label_3->setText(QCoreApplication::translate("RemoteStatus", "Previous Submissions", nullptr));
        btnRefresh->setText(QCoreApplication::translate("RemoteStatus", "Refresh Submission History", nullptr));
        btnViewRemoteStatus->setText(QCoreApplication::translate("RemoteStatus", "View Remote Status", nullptr));
        lblStatus->setText(QString());
        label->setText(QCoreApplication::translate("RemoteStatus", "Block Receipt Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableBlockReceipt->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("RemoteStatus", "Block", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableBlockReceipt->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("RemoteStatus", "Start", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableBlockReceipt->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("RemoteStatus", "End", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableBlockReceipt->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("RemoteStatus", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableBlockReceipt->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("RemoteStatus", "Message", nullptr));
        label_2->setText(QCoreApplication::translate("RemoteStatus", "Archiving Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableArchiveStatus->horizontalHeaderItem(0);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("RemoteStatus", "Original ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableArchiveStatus->horizontalHeaderItem(1);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("RemoteStatus", "New UID", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableArchiveStatus->horizontalHeaderItem(2);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("RemoteStatus", "New StudyNum", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableArchiveStatus->horizontalHeaderItem(3);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("RemoteStatus", "Study Datetime", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableArchiveStatus->horizontalHeaderItem(4);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("RemoteStatus", "Modality", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableArchiveStatus->horizontalHeaderItem(5);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("RemoteStatus", "Equipment", nullptr));
        QTableWidgetItem *___qtablewidgetitem11 = tableArchiveStatus->horizontalHeaderItem(6);
        ___qtablewidgetitem11->setText(QCoreApplication::translate("RemoteStatus", "Protocol", nullptr));
        QTableWidgetItem *___qtablewidgetitem12 = tableArchiveStatus->horizontalHeaderItem(7);
        ___qtablewidgetitem12->setText(QCoreApplication::translate("RemoteStatus", "# files", nullptr));
        QTableWidgetItem *___qtablewidgetitem13 = tableArchiveStatus->horizontalHeaderItem(8);
        ___qtablewidgetitem13->setText(QCoreApplication::translate("RemoteStatus", "Status", nullptr));
        btnClose->setText(QCoreApplication::translate("RemoteStatus", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class RemoteStatus: public Ui_RemoteStatus {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_REMOTESTATUS_H
