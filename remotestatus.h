#ifndef REMOTESTATUS_H
#define REMOTESTATUS_H
#include "mainwindow.h"

#include <QDialog>
#include <QFile>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QJsonArray>

namespace Ui {
class RemoteStatus;
}

class RemoteStatus : public QDialog
{
    Q_OBJECT

public:
    explicit RemoteStatus(QWidget *parent = nullptr);
    ~RemoteStatus();

    void SetMainWindow(MainWindow *m);
    MainWindow *mainWindow;

    bool LoadTransactionHistory();
    void GetRemoteStatus(QString txnid, QString server, QString username, QString password);

private slots:
    void onGetReplyRemoteArchiveStatus();
    void onGetReplyRemoteTransactionStatus();

    void on_cmbTransactions_currentIndexChanged(int index);

    void on_btnClose_clicked();

    void on_btnViewRemoteStatus_clicked();

    void on_btnRefresh_clicked();

private:
    Ui::RemoteStatus *ui;

    QList<QStringList> txnHistory;

};

#endif // REMOTESTATUS_H
