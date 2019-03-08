#include "remotestatus.h"
#include "ui_remotestatus.h"

/* ------------------------------------------------- */
/* --------- RemoteStatus -------------------------- */
/* ------------------------------------------------- */
RemoteStatus::RemoteStatus(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RemoteStatus)
{
    ui->setupUi(this);

    ui->tableBlockReceipt->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableArchiveStatus->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

    LoadTransactionHistory();
}


/* ------------------------------------------------- */
/* --------- ~RemoteStatus ------------------------- */
/* ------------------------------------------------- */
RemoteStatus::~RemoteStatus()
{
    delete ui;
}


/* ------------------------------------------------- */
/* --------- SetMainWindow ------------------------- */
/* ------------------------------------------------- */
void RemoteStatus::SetMainWindow(MainWindow *m)
{
    mainWindow = m;

}


/* ------------------------------------------------- */
/* --------- on_cmbTransactions_currentIndexChanged  */
/* ------------------------------------------------- */
void RemoteStatus::on_cmbTransactions_currentIndexChanged(int index)
{
    //qDebug() << "currentIndex [" << index << "]";

    //qDebug() << "on_cmbTransactions_currentIndexChanged() called";

    if ((index >= 0) && (index < txnHistory.count())) {
        QString txnid = txnHistory[index][1];
        QString server = txnHistory[index][2];
        QString username = txnHistory[index][3];
        QString password = txnHistory[index][4];
    }

    //GetRemoteStatus(txnid, server, username, password);
}


/* ------------------------------------------------- */
/* --------- on_btnClose_clicked ------------------- */
/* ------------------------------------------------- */
void RemoteStatus::on_btnClose_clicked()
{
    this->close();
}


/* ------------------------------------------------- */
/* --------- LoadTransactionHistory ---------------- */
/* ------------------------------------------------- */
bool RemoteStatus::LoadTransactionHistory()
{
    //qDebug() << "LoadTransactionHistory() called";

    ui->lblStatus->setText("Loading transaction history...");
    bool ret = false;
    /* load the previous list of transactions, if it exists */
    QFile file("transactions.csv");
    if (file.open(QIODevice::ReadOnly)) {
        ui->cmbTransactions->clear();
        ret = true; /* the file exists and was able to be opened */

        QString txndate, txnid, server, username, password;

        while (!file.atEnd()) {
            QString line = file.readLine();
            QStringList cols = line.split(',');

            cols[0] = txndate = cols[0].trimmed();
            cols[1] = cols[1].trimmed();
            cols[2] = cols[2].trimmed();
            cols[3] = cols[3].trimmed();
            cols[4] = cols[4].trimmed();

            txnHistory.append(cols);

            ui->cmbTransactions->addItem(txndate);
        }
    }
    //qDebug() << "LoadTransactionHistory() done";

    ui->lblStatus->setText("Transaction history loaded");
    return ret;
}


/* ------------------------------------------------- */
/* --------- on_btnViewRemoteStatus_clicked -------- */
/* ------------------------------------------------- */
void RemoteStatus::on_btnViewRemoteStatus_clicked()
{
    int index = ui->cmbTransactions->currentIndex();
    //qDebug() << "currentIndex [" << index << "]";

    if ((index >= 0) && (index < txnHistory.count())) {
        QString txnid = txnHistory[index][1];
        QString server = txnHistory[index][2];
        QString username = txnHistory[index][3];
        QString password = txnHistory[index][4];

        //qDebug() << "Checkpoint 1 " << txnid << ", " << server << ", " << username << ", "<< password;

        GetRemoteStatus(txnid, server, username, password);
    }
    else {
        //qDebug() << "index was weird [" << index << "]";
    }
}


/* ------------------------------------------------- */
/* --------- GetRemoteStatus ----------------------- */
/* ------------------------------------------------- */
void RemoteStatus::GetRemoteStatus(QString txnid, QString server, QString username, QString password) {
    //mainWindow->networkManager->setProxy(mainWindow->GetProxy());

    ui->lblStatus->setText("Sending remote status request...");

    /* get the status through the API */
    QApplication::setOverrideCursor(Qt::WaitCursor);

    //qDebug() << "Checkpoint A " << txnid << ", " << server << ", " << username << ", "<< password;
    QUrl url(server + "/api.php");
    QNetworkRequest request(url);
    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart loginPart;
    /* username */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
    loginPart.setBody(username.toLatin1()); multiPart->append(loginPart);
    /* password */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
    loginPart.setBody(password.toLatin1()); multiPart->append(loginPart);
    /* action */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
    loginPart.setBody("getArchiveStatus"); multiPart->append(loginPart);
    /* transactionid */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"transactionid\""));
    loginPart.setBody(txnid.toLatin1()); multiPart->append(loginPart);
    QNetworkReply* reply = mainWindow->networkManager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    connect(reply, SIGNAL(finished()), this, SLOT(onGetReplyRemoteArchiveStatus()));
    //qDebug() << "Checkpoint B";

    QUrl url2(server + "/api.php");
    QNetworkRequest request2(url2);
    QHttpMultiPart *multiPart2 = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart loginPart2;
    /* username */
    loginPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
    loginPart2.setBody(username.toLatin1()); multiPart2->append(loginPart2);
    /* password */
    loginPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
    loginPart2.setBody(password.toLatin1()); multiPart2->append(loginPart2);
    /* action */
    loginPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
    loginPart2.setBody("getTransactionStatus"); multiPart2->append(loginPart2);
    /* transactionid */
    loginPart2.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"transactionid\""));
    loginPart2.setBody(txnid.toLatin1()); multiPart2->append(loginPart2);
    QNetworkReply* reply2 = mainWindow->networkManager->post(request2, multiPart2);
    multiPart2->setParent(reply2); // delete the multiPart with the reply
    connect(reply2, SIGNAL(finished()), this, SLOT(onGetReplyRemoteTransactionStatus()));
    //qDebug() << "Checkpoint C";

    QApplication::restoreOverrideCursor();
    ui->lblStatus->setText("Waiting for response");
}


/* ------------------------------------------------- */
/* --------- onGetReplyRemoteArchiveStatus --------- */
/* ------------------------------------------------- */
void RemoteStatus::onGetReplyRemoteArchiveStatus()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            qint64 available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    //qDebug() << response;
    ui->tableArchiveStatus->setRowCount(0);

    if (response.trimmed() == "LOGINERROR") {
        ui->lblStatus->setText("Login Error!");
    }
    else if (response.trimmed().isEmpty()) {
        ui->lblStatus->setText("Received empty response");
    }
    else {
        ui->lblStatus->setText("Got remote status from server");

        /* format the JSON the way the Qt parser is expecting it */
        response.replace("\\\"","\"");
        response.replace("\\n", " ");
        response.replace("\\t", " ");
        response.replace("\\/", "/");

        /* parse the JSON information that was returned */
        QJsonObject json(QJsonDocument::fromJson(response.toUtf8()).object());

        //qDebug() << "Finished getting the JSON object";

        foreach(const QString& key, json.keys()) {
            QJsonArray jsonarray = json[key].toArray();
            QJsonValue value = json.value(key);
            //qDebug() << "Key = " << key << ", Value = " << value.toString();

            QString status = json[key].toObject()["result"].toString();
            QString patientID = json[key].toObject()["patientid_orig"].toString();
            QString modality = json[key].toObject()["modality_orig"].toString();
            QString stationName = json[key].toObject()["stationname_orig"].toString();
            QString studyDate = json[key].toObject()["studydatetime_orig"].toString();
            QString seriesDesc = json[key].toObject()["seriesdesc_orig"].toString();
            QString uid = json[key].toObject()["subject_uid"].toString();
            QString studynum = json[key].toObject()["study_num"].toString();
            QString numfiles = json[key].toObject()["numfiles"].toString();

            const int currentRow = ui->tableArchiveStatus->rowCount();
            ui->tableArchiveStatus->setRowCount(currentRow + 1);
            ui->tableArchiveStatus->setItem(currentRow, 0, new QTableWidgetItem(patientID));
            ui->tableArchiveStatus->setItem(currentRow, 1, new QTableWidgetItem(uid));
            ui->tableArchiveStatus->setItem(currentRow, 2, new QTableWidgetItem(studynum));
            ui->tableArchiveStatus->setItem(currentRow, 3, new QTableWidgetItem(studyDate));
            ui->tableArchiveStatus->setItem(currentRow, 4, new QTableWidgetItem(modality));
            ui->tableArchiveStatus->setItem(currentRow, 5, new QTableWidgetItem(stationName));
            ui->tableArchiveStatus->setItem(currentRow, 6, new QTableWidgetItem(seriesDesc));
            ui->tableArchiveStatus->setItem(currentRow, 7, new QTableWidgetItem(numfiles));
            ui->tableArchiveStatus->setItem(currentRow, 8, new QTableWidgetItem(status));
        }
    }
}


/* ------------------------------------------------- */
/* --------- onGetReplyRemoteTransactionStatus ----- */
/* ------------------------------------------------- */
void RemoteStatus::onGetReplyRemoteTransactionStatus()
{
    //qDebug() << "Entering onGetReplyRemoteTransactionStatus()";

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            qint64 available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    //qDebug() << response;

    ui->tableBlockReceipt->setRowCount(0);

    if (response.trimmed() == "LOGINERROR") {
        ui->lblStatus->setText("Login Error!");
    }
    else if ((response.trimmed().isEmpty()) || response.trimmed() == "null") {
        ui->lblStatus->setText("Received empty response");
    }
    else {
        ui->lblStatus->setText("Got remote status from server");

        /* format the JSON the way the Qt parser is expecting it */
        response.replace("\\\"","\"");
        response.replace("\\n", " ");
        response.replace("\\t", " ");
        response.replace("\\/", "/");

        /* parse the JSON information that was returned */
        QJsonObject json(QJsonDocument::fromJson(response.toUtf8()).object());

        //qDebug() << "Finished getting the JSON object";

        foreach(const QString& key, json.keys()) {
            QJsonArray jsonarray = json[key].toArray();
            QJsonValue value = json.value(key);
            //qDebug() << "Key = " << key << ", Value = " << value.toString();

            QString status = json[key].toObject()["import_status"].toString();
            QString startdate = json[key].toObject()["import_startdate"].toString();
            QString enddate = json[key].toObject()["import_enddate"].toString();
            QString message = json[key].toObject()["import_message"].toString();
            //int numfail = json[key].toObject()["numfilesfail"].toInt();
            //int numsuccess = json[key].toObject()["numfilessuccess"].toInt();
            //int numtotal = json[key].toObject()["numfilestotal"].toInt();

            const int currentRow = ui->tableBlockReceipt->rowCount();
            ui->tableBlockReceipt->setRowCount(currentRow + 1);
            ui->tableBlockReceipt->setItem(currentRow, 0, new QTableWidgetItem(key));
            ui->tableBlockReceipt->setItem(currentRow, 1, new QTableWidgetItem(startdate));
            ui->tableBlockReceipt->setItem(currentRow, 2, new QTableWidgetItem(enddate));
            ui->tableBlockReceipt->setItem(currentRow, 3, new QTableWidgetItem(status));
            ui->tableBlockReceipt->setItem(currentRow, 4, new QTableWidgetItem(message));

            //qDebug() << key << ", " << status << ", " << startdate << ", " << enddate << ", " << numfail << ", " << numsuccess << ", " << numtotal << ", ";
        }
    }
}


/* ------------------------------------------------- */
/* --------- on_btnRefresh_clicked ----------------- */
/* ------------------------------------------------- */
void RemoteStatus::on_btnRefresh_clicked()
{
    LoadTransactionHistory();
}
