#include "remotestatus.h"
#include "ui_remotestatus.h"

RemoteStatus::RemoteStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteStatus)
{
    ui->setupUi(this);

    /* load the previous list of transactions, if it exists */
    QFile file("transactions.csv");
    if (file.open(QIODevice::ReadOnly)) {
        QList<QStringList> rows;
        QString txndate, txnid, server, username, password;
        while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList cols = line.split(',');
            rows.append(cols);

            txndate = cols[0];
            txnid = cols[1];
            server = cols[2];
            username = cols[3];
            password = cols[4];

            mainWindow->WriteLog("testing");
        }
    }
}

RemoteStatus::~RemoteStatus()
{
    delete ui;
}


void RemoteStatus::SetMainWindow(MainWindow *m)
{
    mainWindow = m;
}
