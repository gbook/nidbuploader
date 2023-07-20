/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.5.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *verticalGroupBox;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_19;
    QVBoxLayout *verticalLayout_10;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_5;
    QLineEdit *txtDataDir;
    QPushButton *btnSelectDataDir;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QComboBox *cmbModality;
    QPushButton *btnSearch;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *chkUseMD5;
    QLabel *label_24;
    QVBoxLayout *verticalLayout_8;
    QTableWidget *tableFiles;
    QHBoxLayout *horizontalLayout_13;
    QLabel *lblFileCount;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnRemoveSelected;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox2;
    QHBoxLayout *horizontalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *serverLabel;
    QLineEdit *txtServer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *usernameLabel;
    QLineEdit *txtUsername;
    QHBoxLayout *horizontalLayout_7;
    QLabel *passwordLabel;
    QLineEdit *txtPassword;
    QPushButton *pushButton;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_9;
    QLabel *label;
    QPushButton *btnRemoveConn;
    QPushButton *btnTestConn;
    QCheckBox *chkDebug;
    QListWidget *lstConn;
    QLabel *lblConnMessage;
    QFormLayout *formLayout_2;
    QLabel *lblProxyHostname;
    QLineEdit *proxyHostname;
    QLabel *lblProxyPort;
    QSpinBox *proxyPort;
    QLabel *lblProxyUsername;
    QLineEdit *proxyUsername;
    QLabel *lblProxyPassword;
    QLineEdit *proxyPassword;
    QCheckBox *chkUseProxy;
    QComboBox *cmbProxyType;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *grpAnonymize;
    QVBoxLayout *verticalLayout_4;
    QCheckBox *chkReplacePatientName;
    QCheckBox *chkReplacePatientID;
    QCheckBox *chkReplacePatientBirthDate;
    QCheckBox *chkRemovePatientBirthDate;
    QHBoxLayout *horizontalLayout_14;
    QLabel *label_7;
    QLineEdit *txtTmpDir;
    QPushButton *btnTmpDir;
    QLabel *label_19;
    QGroupBox *groupBox1_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *chkMatchIDOnly;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_4;
    QComboBox *cmbInstanceID;
    QPushButton *btnLoadInstanceIDs;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_3;
    QComboBox *cmbProjectID;
    QPushButton *btnLoadProjectIDs;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_8;
    QComboBox *cmbSiteID;
    QPushButton *btnLoadSiteIDs;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_18;
    QComboBox *cmbEquipmentID;
    QPushButton *btnLoadEquipmentIDs;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout_7;
    QProgressBar *progTotal;
    QProgressBar *progAnon;
    QProgressBar *progUpload;
    QFormLayout *formLayout;
    QLabel *label_17;
    QLabel *lblNumFilesFound;
    QLabel *label_6;
    QLabel *lblFileStartTime;
    QLabel *label_10;
    QLabel *lblFileElapsedTime;
    QLabel *label_11;
    QLabel *lblFileBytesFound;
    QLabel *label_14;
    QLabel *lblNumAnonErrors;
    QLabel *label_9;
    QLabel *lblUploadStart;
    QLabel *label_12;
    QLabel *lblUploadElapsed;
    QLabel *label_13;
    QLabel *lblUploadFilesSentSuccess;
    QLabel *label_15;
    QLabel *lblUploadFilesSentFail;
    QLabel *label_16;
    QLabel *lblUploadSpeed;
    QLabel *lblStatus;
    QPushButton *btnViewRemoteStatus;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *btnExit;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *btnCancel;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *btnResendFailedObjects;
    QPushButton *btnUploadAll;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(1371, 921);
        QIcon icon;
        icon.addFile(QString::fromUtf8("squirrel.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName("centralWidget");
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout_2 = new QVBoxLayout(centralWidget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(-1, 9, -1, -1);
        verticalGroupBox = new QGroupBox(centralWidget);
        verticalGroupBox->setObjectName("verticalGroupBox");
        QFont font;
        font.setBold(true);
        verticalGroupBox->setFont(font);
        verticalGroupBox->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #444;\n"
"    border-radius: 3px;\n"
"    margin-top: 0.5em;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        verticalGroupBox->setFlat(false);
        verticalGroupBox->setCheckable(false);
        verticalLayout_5 = new QVBoxLayout(verticalGroupBox);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName("horizontalLayout_19");
        horizontalLayout_19->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName("verticalLayout_10");
        verticalLayout_10->setContentsMargins(-1, 0, 0, -1);
        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(5);
        horizontalLayout_18->setObjectName("horizontalLayout_18");
        horizontalLayout_18->setContentsMargins(-1, -1, 0, 0);
        label_5 = new QLabel(verticalGroupBox);
        label_5->setObjectName("label_5");
        QFont font1;
        font1.setBold(false);
        label_5->setFont(font1);

        horizontalLayout_18->addWidget(label_5);

        txtDataDir = new QLineEdit(verticalGroupBox);
        txtDataDir->setObjectName("txtDataDir");
        txtDataDir->setFont(font1);

        horizontalLayout_18->addWidget(txtDataDir);

        btnSelectDataDir = new QPushButton(verticalGroupBox);
        btnSelectDataDir->setObjectName("btnSelectDataDir");
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnSelectDataDir->sizePolicy().hasHeightForWidth());
        btnSelectDataDir->setSizePolicy(sizePolicy1);
        btnSelectDataDir->setMaximumSize(QSize(25, 16777215));
        btnSelectDataDir->setFont(font1);
        btnSelectDataDir->setAutoDefault(true);

        horizontalLayout_18->addWidget(btnSelectDataDir);


        verticalLayout_10->addLayout(horizontalLayout_18);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName("horizontalLayout_2");
        horizontalLayout_2->setContentsMargins(-1, 4, -1, -1);
        label_2 = new QLabel(verticalGroupBox);
        label_2->setObjectName("label_2");
        label_2->setFont(font1);

        horizontalLayout_2->addWidget(label_2);

        cmbModality = new QComboBox(verticalGroupBox);
        cmbModality->setObjectName("cmbModality");
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(cmbModality->sizePolicy().hasHeightForWidth());
        cmbModality->setSizePolicy(sizePolicy2);
        cmbModality->setFont(font1);

        horizontalLayout_2->addWidget(cmbModality);


        verticalLayout_10->addLayout(horizontalLayout_2);


        horizontalLayout_19->addLayout(verticalLayout_10);

        btnSearch = new QPushButton(verticalGroupBox);
        btnSearch->setObjectName("btnSearch");
        btnSearch->setFont(font1);
        btnSearch->setAutoDefault(true);

        horizontalLayout_19->addWidget(btnSearch);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_2);


        verticalLayout_5->addLayout(horizontalLayout_19);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName("horizontalLayout_17");
        horizontalLayout_17->setContentsMargins(-1, 0, -1, -1);
        chkUseMD5 = new QCheckBox(verticalGroupBox);
        chkUseMD5->setObjectName("chkUseMD5");
        chkUseMD5->setFont(font1);
        chkUseMD5->setChecked(true);

        horizontalLayout_17->addWidget(chkUseMD5);

        label_24 = new QLabel(verticalGroupBox);
        label_24->setObjectName("label_24");
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        QBrush brush1(QColor(120, 120, 120, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        label_24->setPalette(palette);
        label_24->setFont(font1);
        label_24->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(label_24);


        verticalLayout_5->addLayout(horizontalLayout_17);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setObjectName("verticalLayout_8");
        verticalLayout_8->setContentsMargins(-1, 0, -1, -1);
        tableFiles = new QTableWidget(verticalGroupBox);
        if (tableFiles->columnCount() < 11)
            tableFiles->setColumnCount(11);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        __qtablewidgetitem->setFont(font);
        tableFiles->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(4, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(5, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(6, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(7, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(8, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(9, __qtablewidgetitem9);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        tableFiles->setHorizontalHeaderItem(10, __qtablewidgetitem10);
        tableFiles->setObjectName("tableFiles");
        tableFiles->setFont(font1);
        tableFiles->setFrameShape(QFrame::StyledPanel);
        tableFiles->setAlternatingRowColors(true);
        tableFiles->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableFiles->setShowGrid(true);
        tableFiles->setGridStyle(Qt::DotLine);
        tableFiles->setSortingEnabled(false);
        tableFiles->setWordWrap(false);
        tableFiles->setColumnCount(11);
        tableFiles->horizontalHeader()->setDefaultSectionSize(120);
        tableFiles->verticalHeader()->setDefaultSectionSize(19);

        verticalLayout_8->addWidget(tableFiles);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName("horizontalLayout_13");
        horizontalLayout_13->setContentsMargins(-1, 0, -1, -1);
        lblFileCount = new QLabel(verticalGroupBox);
        lblFileCount->setObjectName("lblFileCount");
        QPalette palette1;
        QBrush brush2(QColor(0, 0, 127, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush2);
        QBrush brush3(QColor(0, 0, 0, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush3);
        QBrush brush4(QColor(0, 0, 0, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush4);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush3);
        QBrush brush5(QColor(0, 0, 0, 128));
        brush5.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush5);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        QBrush brush6(QColor(0, 0, 0, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush6);
#endif
        lblFileCount->setPalette(palette1);
        lblFileCount->setFont(font1);

        horizontalLayout_13->addWidget(lblFileCount);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer);

        btnRemoveSelected = new QPushButton(verticalGroupBox);
        btnRemoveSelected->setObjectName("btnRemoveSelected");
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(btnRemoveSelected->sizePolicy().hasHeightForWidth());
        btnRemoveSelected->setSizePolicy(sizePolicy3);
        btnRemoveSelected->setMinimumSize(QSize(0, 0));
        btnRemoveSelected->setMaximumSize(QSize(100, 16777215));
        btnRemoveSelected->setFont(font1);

        horizontalLayout_13->addWidget(btnRemoveSelected);


        verticalLayout_8->addLayout(horizontalLayout_13);


        verticalLayout_5->addLayout(verticalLayout_8);

        verticalLayout_5->setStretch(2, 1);

        verticalLayout_2->addWidget(verticalGroupBox);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName("horizontalLayout_10");
        horizontalLayout_10->setContentsMargins(-1, 0, -1, -1);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName("verticalLayout_9");
        verticalLayout_9->setContentsMargins(-1, 0, 0, 0);
        groupBox2 = new QGroupBox(centralWidget);
        groupBox2->setObjectName("groupBox2");
        QFont font2;
        font2.setBold(true);
        font2.setUnderline(false);
        groupBox2->setFont(font2);
        groupBox2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #444;\n"
"    border-radius: 3px;\n"
"    margin-top: 0.5em;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        horizontalLayout_6 = new QHBoxLayout(groupBox2);
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_6->setObjectName("horizontalLayout_6");
        horizontalLayout_6->setContentsMargins(1, 1, 1, 1);
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName("horizontalLayout");
        horizontalLayout->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout->setContentsMargins(-1, 0, -1, -1);
        serverLabel = new QLabel(groupBox2);
        serverLabel->setObjectName("serverLabel");
        QSizePolicy sizePolicy4(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(serverLabel->sizePolicy().hasHeightForWidth());
        serverLabel->setSizePolicy(sizePolicy4);
        serverLabel->setFont(font1);

        horizontalLayout->addWidget(serverLabel);

        txtServer = new QLineEdit(groupBox2);
        txtServer->setObjectName("txtServer");
        txtServer->setMinimumSize(QSize(200, 0));
        txtServer->setFont(font1);
        txtServer->setFrame(true);

        horizontalLayout->addWidget(txtServer);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(1);
        horizontalLayout_5->setObjectName("horizontalLayout_5");
        horizontalLayout_5->setContentsMargins(-1, 0, -1, -1);
        usernameLabel = new QLabel(groupBox2);
        usernameLabel->setObjectName("usernameLabel");
        sizePolicy4.setHeightForWidth(usernameLabel->sizePolicy().hasHeightForWidth());
        usernameLabel->setSizePolicy(sizePolicy4);
        usernameLabel->setMaximumSize(QSize(16777215, 16777215));
        usernameLabel->setFont(font1);

        horizontalLayout_5->addWidget(usernameLabel);

        txtUsername = new QLineEdit(groupBox2);
        txtUsername->setObjectName("txtUsername");
        txtUsername->setFont(font1);

        horizontalLayout_5->addWidget(txtUsername);


        verticalLayout->addLayout(horizontalLayout_5);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName("horizontalLayout_7");
        passwordLabel = new QLabel(groupBox2);
        passwordLabel->setObjectName("passwordLabel");
        sizePolicy4.setHeightForWidth(passwordLabel->sizePolicy().hasHeightForWidth());
        passwordLabel->setSizePolicy(sizePolicy4);
        passwordLabel->setFont(font1);

        horizontalLayout_7->addWidget(passwordLabel);

        txtPassword = new QLineEdit(groupBox2);
        txtPassword->setObjectName("txtPassword");
        txtPassword->setFont(font1);
        txtPassword->setEchoMode(QLineEdit::Password);

        horizontalLayout_7->addWidget(txtPassword);


        verticalLayout->addLayout(horizontalLayout_7);

        pushButton = new QPushButton(groupBox2);
        pushButton->setObjectName("pushButton");
        sizePolicy1.setHeightForWidth(pushButton->sizePolicy().hasHeightForWidth());
        pushButton->setSizePolicy(sizePolicy1);
        pushButton->setFont(font1);
        pushButton->setAutoDefault(true);

        verticalLayout->addWidget(pushButton);


        horizontalLayout_6->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(1);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_3->setContentsMargins(-1, 0, 0, -1);
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName("horizontalLayout_9");
        label = new QLabel(groupBox2);
        label->setObjectName("label");
        label->setFont(font1);

        horizontalLayout_9->addWidget(label);

        btnRemoveConn = new QPushButton(groupBox2);
        btnRemoveConn->setObjectName("btnRemoveConn");
        sizePolicy1.setHeightForWidth(btnRemoveConn->sizePolicy().hasHeightForWidth());
        btnRemoveConn->setSizePolicy(sizePolicy1);
        btnRemoveConn->setFont(font1);

        horizontalLayout_9->addWidget(btnRemoveConn);

        btnTestConn = new QPushButton(groupBox2);
        btnTestConn->setObjectName("btnTestConn");
        sizePolicy3.setHeightForWidth(btnTestConn->sizePolicy().hasHeightForWidth());
        btnTestConn->setSizePolicy(sizePolicy3);
        btnTestConn->setMinimumSize(QSize(0, 0));
        btnTestConn->setMaximumSize(QSize(100, 16777215));
        btnTestConn->setFont(font1);
        btnTestConn->setAutoDefault(true);

        horizontalLayout_9->addWidget(btnTestConn);

        chkDebug = new QCheckBox(groupBox2);
        chkDebug->setObjectName("chkDebug");
        chkDebug->setMaximumSize(QSize(80, 16777215));
        chkDebug->setFont(font1);

        horizontalLayout_9->addWidget(chkDebug);


        verticalLayout_3->addLayout(horizontalLayout_9);

        lstConn = new QListWidget(groupBox2);
        lstConn->setObjectName("lstConn");
        QSizePolicy sizePolicy5(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(lstConn->sizePolicy().hasHeightForWidth());
        lstConn->setSizePolicy(sizePolicy5);
        lstConn->setMinimumSize(QSize(0, 40));
        lstConn->setMaximumSize(QSize(1000, 70));
        lstConn->setFont(font1);

        verticalLayout_3->addWidget(lstConn);

        lblConnMessage = new QLabel(groupBox2);
        lblConnMessage->setObjectName("lblConnMessage");
        sizePolicy4.setHeightForWidth(lblConnMessage->sizePolicy().hasHeightForWidth());
        lblConnMessage->setSizePolicy(sizePolicy4);
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblConnMessage->setPalette(palette2);
        lblConnMessage->setFont(font1);
        lblConnMessage->setFrameShape(QFrame::NoFrame);

        verticalLayout_3->addWidget(lblConnMessage);

        verticalLayout_3->setStretch(1, 1);

        horizontalLayout_6->addLayout(verticalLayout_3);

        formLayout_2 = new QFormLayout();
        formLayout_2->setSpacing(6);
        formLayout_2->setObjectName("formLayout_2");
        formLayout_2->setVerticalSpacing(1);
        formLayout_2->setContentsMargins(-1, 0, -1, -1);
        lblProxyHostname = new QLabel(groupBox2);
        lblProxyHostname->setObjectName("lblProxyHostname");
        lblProxyHostname->setEnabled(false);
        lblProxyHostname->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::LabelRole, lblProxyHostname);

        proxyHostname = new QLineEdit(groupBox2);
        proxyHostname->setObjectName("proxyHostname");
        proxyHostname->setEnabled(false);
        proxyHostname->setFont(font1);

        formLayout_2->setWidget(1, QFormLayout::FieldRole, proxyHostname);

        lblProxyPort = new QLabel(groupBox2);
        lblProxyPort->setObjectName("lblProxyPort");
        lblProxyPort->setEnabled(false);
        lblProxyPort->setFont(font1);

        formLayout_2->setWidget(2, QFormLayout::LabelRole, lblProxyPort);

        proxyPort = new QSpinBox(groupBox2);
        proxyPort->setObjectName("proxyPort");
        proxyPort->setEnabled(false);
        proxyPort->setFont(font1);
        proxyPort->setMaximum(999999);
        proxyPort->setValue(8080);

        formLayout_2->setWidget(2, QFormLayout::FieldRole, proxyPort);

        lblProxyUsername = new QLabel(groupBox2);
        lblProxyUsername->setObjectName("lblProxyUsername");
        lblProxyUsername->setEnabled(false);
        lblProxyUsername->setFont(font1);

        formLayout_2->setWidget(3, QFormLayout::LabelRole, lblProxyUsername);

        proxyUsername = new QLineEdit(groupBox2);
        proxyUsername->setObjectName("proxyUsername");
        proxyUsername->setEnabled(false);
        proxyUsername->setFont(font1);

        formLayout_2->setWidget(3, QFormLayout::FieldRole, proxyUsername);

        lblProxyPassword = new QLabel(groupBox2);
        lblProxyPassword->setObjectName("lblProxyPassword");
        lblProxyPassword->setEnabled(false);
        lblProxyPassword->setFont(font1);

        formLayout_2->setWidget(4, QFormLayout::LabelRole, lblProxyPassword);

        proxyPassword = new QLineEdit(groupBox2);
        proxyPassword->setObjectName("proxyPassword");
        proxyPassword->setEnabled(false);
        proxyPassword->setFont(font1);
        proxyPassword->setInputMethodHints(Qt::ImhNoPredictiveText|Qt::ImhSensitiveData);

        formLayout_2->setWidget(4, QFormLayout::FieldRole, proxyPassword);

        chkUseProxy = new QCheckBox(groupBox2);
        chkUseProxy->setObjectName("chkUseProxy");
        chkUseProxy->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::LabelRole, chkUseProxy);

        cmbProxyType = new QComboBox(groupBox2);
        cmbProxyType->setObjectName("cmbProxyType");
        cmbProxyType->setEnabled(false);
        cmbProxyType->setFont(font1);

        formLayout_2->setWidget(0, QFormLayout::FieldRole, cmbProxyType);


        horizontalLayout_6->addLayout(formLayout_2);

        horizontalLayout_6->setStretch(1, 50);

        verticalLayout_9->addWidget(groupBox2);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName("horizontalLayout_8");
        horizontalLayout_8->setContentsMargins(-1, 0, 0, 9);
        grpAnonymize = new QGroupBox(centralWidget);
        grpAnonymize->setObjectName("grpAnonymize");
        grpAnonymize->setEnabled(true);
        sizePolicy4.setHeightForWidth(grpAnonymize->sizePolicy().hasHeightForWidth());
        grpAnonymize->setSizePolicy(sizePolicy4);
        grpAnonymize->setFont(font);
        grpAnonymize->setAutoFillBackground(false);
        grpAnonymize->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #444;\n"
"    border-radius: 3px;\n"
"    margin-top: 0.5em;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        grpAnonymize->setFlat(false);
        grpAnonymize->setCheckable(false);
        verticalLayout_4 = new QVBoxLayout(grpAnonymize);
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setSizeConstraint(QLayout::SetMinimumSize);
        verticalLayout_4->setContentsMargins(1, 1, 1, 1);
        chkReplacePatientName = new QCheckBox(grpAnonymize);
        chkReplacePatientName->setObjectName("chkReplacePatientName");
        chkReplacePatientName->setEnabled(true);
        chkReplacePatientName->setFont(font1);
        chkReplacePatientName->setChecked(true);

        verticalLayout_4->addWidget(chkReplacePatientName);

        chkReplacePatientID = new QCheckBox(grpAnonymize);
        chkReplacePatientID->setObjectName("chkReplacePatientID");
        chkReplacePatientID->setFont(font1);
        chkReplacePatientID->setChecked(false);

        verticalLayout_4->addWidget(chkReplacePatientID);

        chkReplacePatientBirthDate = new QCheckBox(grpAnonymize);
        chkReplacePatientBirthDate->setObjectName("chkReplacePatientBirthDate");
        chkReplacePatientBirthDate->setFont(font1);
        chkReplacePatientBirthDate->setChecked(false);

        verticalLayout_4->addWidget(chkReplacePatientBirthDate);

        chkRemovePatientBirthDate = new QCheckBox(grpAnonymize);
        chkRemovePatientBirthDate->setObjectName("chkRemovePatientBirthDate");
        chkRemovePatientBirthDate->setFont(font1);

        verticalLayout_4->addWidget(chkRemovePatientBirthDate);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName("horizontalLayout_14");
        label_7 = new QLabel(grpAnonymize);
        label_7->setObjectName("label_7");
        label_7->setMaximumSize(QSize(16777215, 20));
        label_7->setFont(font1);

        horizontalLayout_14->addWidget(label_7);

        txtTmpDir = new QLineEdit(grpAnonymize);
        txtTmpDir->setObjectName("txtTmpDir");
        sizePolicy3.setHeightForWidth(txtTmpDir->sizePolicy().hasHeightForWidth());
        txtTmpDir->setSizePolicy(sizePolicy3);
        txtTmpDir->setMaximumSize(QSize(16777215, 16777215));
        txtTmpDir->setFont(font1);

        horizontalLayout_14->addWidget(txtTmpDir);

        btnTmpDir = new QPushButton(grpAnonymize);
        btnTmpDir->setObjectName("btnTmpDir");
        sizePolicy1.setHeightForWidth(btnTmpDir->sizePolicy().hasHeightForWidth());
        btnTmpDir->setSizePolicy(sizePolicy1);
        btnTmpDir->setMaximumSize(QSize(23, 16777215));
        btnTmpDir->setFont(font1);

        horizontalLayout_14->addWidget(btnTmpDir);


        verticalLayout_4->addLayout(horizontalLayout_14);

        label_19 = new QLabel(grpAnonymize);
        label_19->setObjectName("label_19");
        label_19->setMaximumSize(QSize(16777215, 16777215));
        QPalette palette3;
        QBrush brush7(QColor(102, 102, 102, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush7);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush3);
        QBrush brush8(QColor(0, 0, 0, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush8);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush7);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush3);
        QBrush brush9(QColor(0, 0, 0, 128));
        brush9.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush9);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        QBrush brush10(QColor(0, 0, 0, 128));
        brush10.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush10);
#endif
        label_19->setPalette(palette3);
        label_19->setFont(font1);

        verticalLayout_4->addWidget(label_19);


        horizontalLayout_8->addWidget(grpAnonymize);

        groupBox1_2 = new QGroupBox(centralWidget);
        groupBox1_2->setObjectName("groupBox1_2");
        groupBox1_2->setFont(font);
        groupBox1_2->setStyleSheet(QString::fromUtf8("QGroupBox {\n"
"    border: 1px solid #444;\n"
"    border-radius: 3px;\n"
"    margin-top: 0.5em;\n"
"    padding: 10px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 10px;\n"
"    padding: 0 3px 0 3px;\n"
"}"));
        verticalLayout_6 = new QVBoxLayout(groupBox1_2);
        verticalLayout_6->setSpacing(1);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName("verticalLayout_6");
        verticalLayout_6->setContentsMargins(1, 1, 1, 1);
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName("horizontalLayout_16");
        horizontalLayout_16->setContentsMargins(-1, 0, -1, -1);
        chkMatchIDOnly = new QCheckBox(groupBox1_2);
        chkMatchIDOnly->setObjectName("chkMatchIDOnly");
        chkMatchIDOnly->setFont(font1);
        chkMatchIDOnly->setChecked(true);

        horizontalLayout_16->addWidget(chkMatchIDOnly);


        verticalLayout_6->addLayout(horizontalLayout_16);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName("horizontalLayout_11");
        label_4 = new QLabel(groupBox1_2);
        label_4->setObjectName("label_4");
        label_4->setFont(font1);

        horizontalLayout_11->addWidget(label_4);

        cmbInstanceID = new QComboBox(groupBox1_2);
        cmbInstanceID->setObjectName("cmbInstanceID");
        sizePolicy3.setHeightForWidth(cmbInstanceID->sizePolicy().hasHeightForWidth());
        cmbInstanceID->setSizePolicy(sizePolicy3);
        cmbInstanceID->setFont(font1);

        horizontalLayout_11->addWidget(cmbInstanceID);

        btnLoadInstanceIDs = new QPushButton(groupBox1_2);
        btnLoadInstanceIDs->setObjectName("btnLoadInstanceIDs");
        btnLoadInstanceIDs->setMaximumSize(QSize(23, 16777215));
        btnLoadInstanceIDs->setFont(font1);
        btnLoadInstanceIDs->setFlat(false);

        horizontalLayout_11->addWidget(btnLoadInstanceIDs);


        verticalLayout_6->addLayout(horizontalLayout_11);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName("horizontalLayout_3");
        label_3 = new QLabel(groupBox1_2);
        label_3->setObjectName("label_3");
        label_3->setFont(font1);

        horizontalLayout_3->addWidget(label_3);

        cmbProjectID = new QComboBox(groupBox1_2);
        cmbProjectID->setObjectName("cmbProjectID");
        sizePolicy2.setHeightForWidth(cmbProjectID->sizePolicy().hasHeightForWidth());
        cmbProjectID->setSizePolicy(sizePolicy2);
        cmbProjectID->setFont(font1);

        horizontalLayout_3->addWidget(cmbProjectID);

        btnLoadProjectIDs = new QPushButton(groupBox1_2);
        btnLoadProjectIDs->setObjectName("btnLoadProjectIDs");
        btnLoadProjectIDs->setMaximumSize(QSize(23, 16777215));
        btnLoadProjectIDs->setFont(font1);

        horizontalLayout_3->addWidget(btnLoadProjectIDs);


        verticalLayout_6->addLayout(horizontalLayout_3);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName("horizontalLayout_12");
        label_8 = new QLabel(groupBox1_2);
        label_8->setObjectName("label_8");
        label_8->setFont(font1);

        horizontalLayout_12->addWidget(label_8);

        cmbSiteID = new QComboBox(groupBox1_2);
        cmbSiteID->setObjectName("cmbSiteID");
        sizePolicy2.setHeightForWidth(cmbSiteID->sizePolicy().hasHeightForWidth());
        cmbSiteID->setSizePolicy(sizePolicy2);
        cmbSiteID->setFont(font1);

        horizontalLayout_12->addWidget(cmbSiteID);

        btnLoadSiteIDs = new QPushButton(groupBox1_2);
        btnLoadSiteIDs->setObjectName("btnLoadSiteIDs");
        btnLoadSiteIDs->setMaximumSize(QSize(23, 16777215));
        btnLoadSiteIDs->setFont(font1);

        horizontalLayout_12->addWidget(btnLoadSiteIDs);


        verticalLayout_6->addLayout(horizontalLayout_12);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName("horizontalLayout_15");
        horizontalLayout_15->setContentsMargins(-1, 0, -1, -1);
        label_18 = new QLabel(groupBox1_2);
        label_18->setObjectName("label_18");
        label_18->setFont(font1);

        horizontalLayout_15->addWidget(label_18);

        cmbEquipmentID = new QComboBox(groupBox1_2);
        cmbEquipmentID->setObjectName("cmbEquipmentID");
        sizePolicy2.setHeightForWidth(cmbEquipmentID->sizePolicy().hasHeightForWidth());
        cmbEquipmentID->setSizePolicy(sizePolicy2);
        cmbEquipmentID->setFont(font1);

        horizontalLayout_15->addWidget(cmbEquipmentID);

        btnLoadEquipmentIDs = new QPushButton(groupBox1_2);
        btnLoadEquipmentIDs->setObjectName("btnLoadEquipmentIDs");
        btnLoadEquipmentIDs->setMaximumSize(QSize(23, 16777215));
        btnLoadEquipmentIDs->setFont(font1);

        horizontalLayout_15->addWidget(btnLoadEquipmentIDs);


        verticalLayout_6->addLayout(horizontalLayout_15);

        verticalSpacer = new QSpacerItem(20, 2, QSizePolicy::Minimum, QSizePolicy::MinimumExpanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_8->addWidget(groupBox1_2);


        verticalLayout_9->addLayout(horizontalLayout_8);


        horizontalLayout_10->addLayout(verticalLayout_9);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(1);
        verticalLayout_7->setObjectName("verticalLayout_7");
        verticalLayout_7->setContentsMargins(-1, -1, 0, -1);
        progTotal = new QProgressBar(centralWidget);
        progTotal->setObjectName("progTotal");
        sizePolicy.setHeightForWidth(progTotal->sizePolicy().hasHeightForWidth());
        progTotal->setSizePolicy(sizePolicy);
        progTotal->setMaximumSize(QSize(16777215, 15));
        progTotal->setValue(0);
        progTotal->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(progTotal);

        progAnon = new QProgressBar(centralWidget);
        progAnon->setObjectName("progAnon");
        sizePolicy.setHeightForWidth(progAnon->sizePolicy().hasHeightForWidth());
        progAnon->setSizePolicy(sizePolicy);
        progAnon->setMaximumSize(QSize(16777215, 15));
        progAnon->setValue(0);
        progAnon->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_7->addWidget(progAnon);

        progUpload = new QProgressBar(centralWidget);
        progUpload->setObjectName("progUpload");
        sizePolicy.setHeightForWidth(progUpload->sizePolicy().hasHeightForWidth());
        progUpload->setSizePolicy(sizePolicy);
        progUpload->setMaximumSize(QSize(16777215, 15));
        progUpload->setValue(0);
        progUpload->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(progUpload);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName("formLayout");
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        formLayout->setLabelAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        formLayout->setVerticalSpacing(3);
        label_17 = new QLabel(centralWidget);
        label_17->setObjectName("label_17");

        formLayout->setWidget(0, QFormLayout::LabelRole, label_17);

        lblNumFilesFound = new QLabel(centralWidget);
        lblNumFilesFound->setObjectName("lblNumFilesFound");

        formLayout->setWidget(0, QFormLayout::FieldRole, lblNumFilesFound);

        label_6 = new QLabel(centralWidget);
        label_6->setObjectName("label_6");
        label_6->setFont(font);

        formLayout->setWidget(1, QFormLayout::LabelRole, label_6);

        lblFileStartTime = new QLabel(centralWidget);
        lblFileStartTime->setObjectName("lblFileStartTime");

        formLayout->setWidget(1, QFormLayout::FieldRole, lblFileStartTime);

        label_10 = new QLabel(centralWidget);
        label_10->setObjectName("label_10");
        label_10->setFont(font);

        formLayout->setWidget(2, QFormLayout::LabelRole, label_10);

        lblFileElapsedTime = new QLabel(centralWidget);
        lblFileElapsedTime->setObjectName("lblFileElapsedTime");

        formLayout->setWidget(2, QFormLayout::FieldRole, lblFileElapsedTime);

        label_11 = new QLabel(centralWidget);
        label_11->setObjectName("label_11");
        label_11->setFont(font);

        formLayout->setWidget(3, QFormLayout::LabelRole, label_11);

        lblFileBytesFound = new QLabel(centralWidget);
        lblFileBytesFound->setObjectName("lblFileBytesFound");

        formLayout->setWidget(3, QFormLayout::FieldRole, lblFileBytesFound);

        label_14 = new QLabel(centralWidget);
        label_14->setObjectName("label_14");

        formLayout->setWidget(4, QFormLayout::LabelRole, label_14);

        lblNumAnonErrors = new QLabel(centralWidget);
        lblNumAnonErrors->setObjectName("lblNumAnonErrors");
        QPalette palette4;
        QBrush brush11(QColor(170, 0, 0, 255));
        brush11.setStyle(Qt::SolidPattern);
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush11);
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblNumAnonErrors->setPalette(palette4);

        formLayout->setWidget(4, QFormLayout::FieldRole, lblNumAnonErrors);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName("label_9");

        formLayout->setWidget(5, QFormLayout::LabelRole, label_9);

        lblUploadStart = new QLabel(centralWidget);
        lblUploadStart->setObjectName("lblUploadStart");

        formLayout->setWidget(5, QFormLayout::FieldRole, lblUploadStart);

        label_12 = new QLabel(centralWidget);
        label_12->setObjectName("label_12");

        formLayout->setWidget(6, QFormLayout::LabelRole, label_12);

        lblUploadElapsed = new QLabel(centralWidget);
        lblUploadElapsed->setObjectName("lblUploadElapsed");

        formLayout->setWidget(6, QFormLayout::FieldRole, lblUploadElapsed);

        label_13 = new QLabel(centralWidget);
        label_13->setObjectName("label_13");

        formLayout->setWidget(8, QFormLayout::LabelRole, label_13);

        lblUploadFilesSentSuccess = new QLabel(centralWidget);
        lblUploadFilesSentSuccess->setObjectName("lblUploadFilesSentSuccess");

        formLayout->setWidget(8, QFormLayout::FieldRole, lblUploadFilesSentSuccess);

        label_15 = new QLabel(centralWidget);
        label_15->setObjectName("label_15");

        formLayout->setWidget(9, QFormLayout::LabelRole, label_15);

        lblUploadFilesSentFail = new QLabel(centralWidget);
        lblUploadFilesSentFail->setObjectName("lblUploadFilesSentFail");
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush11);
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush11);
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        lblUploadFilesSentFail->setPalette(palette5);

        formLayout->setWidget(9, QFormLayout::FieldRole, lblUploadFilesSentFail);

        label_16 = new QLabel(centralWidget);
        label_16->setObjectName("label_16");

        formLayout->setWidget(7, QFormLayout::LabelRole, label_16);

        lblUploadSpeed = new QLabel(centralWidget);
        lblUploadSpeed->setObjectName("lblUploadSpeed");

        formLayout->setWidget(7, QFormLayout::FieldRole, lblUploadSpeed);


        verticalLayout_7->addLayout(formLayout);

        lblStatus = new QLabel(centralWidget);
        lblStatus->setObjectName("lblStatus");
        sizePolicy4.setHeightForWidth(lblStatus->sizePolicy().hasHeightForWidth());
        lblStatus->setSizePolicy(sizePolicy4);
        QFont font3;
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setKerning(true);
        font3.setStyleStrategy(QFont::PreferAntialias);
        lblStatus->setFont(font3);
        lblStatus->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_7->addWidget(lblStatus);

        btnViewRemoteStatus = new QPushButton(centralWidget);
        btnViewRemoteStatus->setObjectName("btnViewRemoteStatus");

        verticalLayout_7->addWidget(btnViewRemoteStatus);


        horizontalLayout_10->addLayout(verticalLayout_7);

        horizontalLayout_10->setStretch(0, 2);

        verticalLayout_2->addLayout(horizontalLayout_10);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName("horizontalLayout_4");
        btnExit = new QPushButton(centralWidget);
        btnExit->setObjectName("btnExit");

        horizontalLayout_4->addWidget(btnExit);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        btnCancel = new QPushButton(centralWidget);
        btnCancel->setObjectName("btnCancel");

        horizontalLayout_4->addWidget(btnCancel);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        btnResendFailedObjects = new QPushButton(centralWidget);
        btnResendFailedObjects->setObjectName("btnResendFailedObjects");

        horizontalLayout_4->addWidget(btnResendFailedObjects);

        btnUploadAll = new QPushButton(centralWidget);
        btnUploadAll->setObjectName("btnUploadAll");
        btnUploadAll->setAutoDefault(true);

        horizontalLayout_4->addWidget(btnUploadAll);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalLayout_2->setStretch(0, 1);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName("menuBar");
        menuBar->setGeometry(QRect(0, 0, 1371, 20));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName("statusBar");
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        btnSearch->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "NiDB Uploader", nullptr));
        verticalGroupBox->setTitle(QCoreApplication::translate("MainWindow", "Data Selection", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Data Directory:", nullptr));
        txtDataDir->setPlaceholderText(QCoreApplication::translate("MainWindow", "select a data directory", nullptr));
#if QT_CONFIG(tooltip)
        btnSelectDataDir->setToolTip(QCoreApplication::translate("MainWindow", "Click to select directory", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSelectDataDir->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Modality", nullptr));
#if QT_CONFIG(tooltip)
        btnSearch->setToolTip(QCoreApplication::translate("MainWindow", "Search for files matching the specified modality", nullptr));
#endif // QT_CONFIG(tooltip)
        btnSearch->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        chkUseMD5->setText(QCoreApplication::translate("MainWindow", "Calculate MD5 hash of files (may be slow)", nullptr));
        label_24->setText(QCoreApplication::translate("MainWindow", "Make sure the UIDs specified below actually exist on the server!", nullptr));
        QTableWidgetItem *___qtablewidgetitem = tableFiles->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QCoreApplication::translate("MainWindow", "Original File", nullptr));
        QTableWidgetItem *___qtablewidgetitem1 = tableFiles->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QCoreApplication::translate("MainWindow", "Status", nullptr));
        QTableWidgetItem *___qtablewidgetitem2 = tableFiles->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        QTableWidgetItem *___qtablewidgetitem3 = tableFiles->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QCoreApplication::translate("MainWindow", "Modality", nullptr));
        QTableWidgetItem *___qtablewidgetitem4 = tableFiles->horizontalHeaderItem(4);
        ___qtablewidgetitem4->setText(QCoreApplication::translate("MainWindow", "Protocol", nullptr));
        QTableWidgetItem *___qtablewidgetitem5 = tableFiles->horizontalHeaderItem(5);
        ___qtablewidgetitem5->setText(QCoreApplication::translate("MainWindow", "Patient ID", nullptr));
        QTableWidgetItem *___qtablewidgetitem6 = tableFiles->horizontalHeaderItem(6);
        ___qtablewidgetitem6->setText(QCoreApplication::translate("MainWindow", "File Date", nullptr));
        QTableWidgetItem *___qtablewidgetitem7 = tableFiles->horizontalHeaderItem(7);
        ___qtablewidgetitem7->setText(QCoreApplication::translate("MainWindow", "File Size", nullptr));
        QTableWidgetItem *___qtablewidgetitem8 = tableFiles->horizontalHeaderItem(8);
        ___qtablewidgetitem8->setText(QCoreApplication::translate("MainWindow", "Anon File", nullptr));
        QTableWidgetItem *___qtablewidgetitem9 = tableFiles->horizontalHeaderItem(9);
        ___qtablewidgetitem9->setText(QCoreApplication::translate("MainWindow", "Anon MD5 hash", nullptr));
        QTableWidgetItem *___qtablewidgetitem10 = tableFiles->horizontalHeaderItem(10);
        ___qtablewidgetitem10->setText(QCoreApplication::translate("MainWindow", "Bytes", nullptr));
        lblFileCount->setText(QCoreApplication::translate("MainWindow", "Found 0 files", nullptr));
        btnRemoveSelected->setText(QCoreApplication::translate("MainWindow", "Remove Selected", nullptr));
        groupBox2->setTitle(QCoreApplication::translate("MainWindow", "NiDB Server Connection", nullptr));
        serverLabel->setText(QCoreApplication::translate("MainWindow", "Server", nullptr));
        txtServer->setText(QCoreApplication::translate("MainWindow", "https://", nullptr));
        usernameLabel->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        passwordLabel->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Add Connection -->", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Connection List", nullptr));
        btnRemoveConn->setText(QCoreApplication::translate("MainWindow", "Remove", nullptr));
        btnTestConn->setText(QCoreApplication::translate("MainWindow", "Test Connection", nullptr));
        chkDebug->setText(QCoreApplication::translate("MainWindow", "Debug", nullptr));
        lblConnMessage->setText(QCoreApplication::translate("MainWindow", "ConnectionMessage:", nullptr));
        lblProxyHostname->setText(QCoreApplication::translate("MainWindow", "Hostname", nullptr));
        lblProxyPort->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        lblProxyUsername->setText(QCoreApplication::translate("MainWindow", "Username", nullptr));
        lblProxyPassword->setText(QCoreApplication::translate("MainWindow", "Password", nullptr));
        chkUseProxy->setText(QCoreApplication::translate("MainWindow", "Use proxy", nullptr));
        grpAnonymize->setTitle(QCoreApplication::translate("MainWindow", "Anonymization (DICOM only)", nullptr));
#if QT_CONFIG(tooltip)
        chkReplacePatientName->setToolTip(QCoreApplication::translate("MainWindow", "For DICOM only. Replaces PatientName with SHA1(PatientName)", nullptr));
#endif // QT_CONFIG(tooltip)
        chkReplacePatientName->setText(QCoreApplication::translate("MainWindow", "Replace PatientName (0010,0010)", nullptr));
#if QT_CONFIG(tooltip)
        chkReplacePatientID->setToolTip(QCoreApplication::translate("MainWindow", "For DICOM only. Replaces PatientID with SHA1(PatientID)", nullptr));
#endif // QT_CONFIG(tooltip)
        chkReplacePatientID->setText(QCoreApplication::translate("MainWindow", "Replace PatientID (0010,0020)", nullptr));
#if QT_CONFIG(tooltip)
        chkReplacePatientBirthDate->setToolTip(QCoreApplication::translate("MainWindow", "For DICOM only. Replaces PatientBirthDate with year only", nullptr));
#endif // QT_CONFIG(tooltip)
        chkReplacePatientBirthDate->setText(QCoreApplication::translate("MainWindow", "Replace PatientBirthDate (0010,0030)", nullptr));
        chkRemovePatientBirthDate->setText(QCoreApplication::translate("MainWindow", "Remove PatientBirthDate", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Temp directory", nullptr));
        btnTmpDir->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "Use \"C:temp\" on Windows, \"/tmp\" on Linux", nullptr));
        groupBox1_2->setTitle(QCoreApplication::translate("MainWindow", "Destination", nullptr));
        chkMatchIDOnly->setText(QCoreApplication::translate("MainWindow", "Match by ID only", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Instance", nullptr));
#if QT_CONFIG(tooltip)
        btnLoadInstanceIDs->setToolTip(QCoreApplication::translate("MainWindow", "Load instance list", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLoadInstanceIDs->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Project", nullptr));
#if QT_CONFIG(tooltip)
        btnLoadProjectIDs->setToolTip(QCoreApplication::translate("MainWindow", "Load project list", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLoadProjectIDs->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Site", nullptr));
#if QT_CONFIG(tooltip)
        btnLoadSiteIDs->setToolTip(QCoreApplication::translate("MainWindow", "Load site list", nullptr));
#endif // QT_CONFIG(tooltip)
        btnLoadSiteIDs->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "Equipment", nullptr));
        btnLoadEquipmentIDs->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        progTotal->setFormat(QCoreApplication::translate("MainWindow", "Total %p%", nullptr));
#if QT_CONFIG(tooltip)
        progAnon->setToolTip(QCoreApplication::translate("MainWindow", "Anonymization", nullptr));
#endif // QT_CONFIG(tooltip)
        progAnon->setFormat(QCoreApplication::translate("MainWindow", "Anonymization %p%", nullptr));
        progUpload->setFormat(QCoreApplication::translate("MainWindow", "Upload %p%", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "Number files found", nullptr));
        lblNumFilesFound->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "File search start time", nullptr));
        lblFileStartTime->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "File search elapsed time", nullptr));
#if QT_CONFIG(tooltip)
        lblFileElapsedTime->setToolTip(QCoreApplication::translate("MainWindow", "HH:MM:SS.ms", nullptr));
#endif // QT_CONFIG(tooltip)
        lblFileElapsedTime->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "File search bytes found", nullptr));
        lblFileBytesFound->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "Anonymization errors", nullptr));
        lblNumAnonErrors->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Upload start time", nullptr));
        lblUploadStart->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Upload elapsed time", nullptr));
#if QT_CONFIG(tooltip)
        lblUploadElapsed->setToolTip(QCoreApplication::translate("MainWindow", "HH:MM:SS.ms", nullptr));
#endif // QT_CONFIG(tooltip)
        lblUploadElapsed->setText(QCoreApplication::translate("MainWindow", "00:00:00", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "Upload files sent (success)", nullptr));
        lblUploadFilesSentSuccess->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "Upload files sent (fail)", nullptr));
        lblUploadFilesSentFail->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "Upload speed", nullptr));
        lblUploadSpeed->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        lblStatus->setText(QCoreApplication::translate("MainWindow", "Status...", nullptr));
        btnViewRemoteStatus->setText(QCoreApplication::translate("MainWindow", "View Remote Status", nullptr));
        btnExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        btnCancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
#if QT_CONFIG(tooltip)
        btnResendFailedObjects->setToolTip(QCoreApplication::translate("MainWindow", "This will try to resend all objects that were not uploaded successfully", nullptr));
#endif // QT_CONFIG(tooltip)
        btnResendFailedObjects->setText(QCoreApplication::translate("MainWindow", "Resend Failed Objects", nullptr));
#if QT_CONFIG(tooltip)
        btnUploadAll->setToolTip(QCoreApplication::translate("MainWindow", "Uploads and anonymizes if necessary", nullptr));
#endif // QT_CONFIG(tooltip)
        btnUploadAll->setText(QCoreApplication::translate("MainWindow", "Upload", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
