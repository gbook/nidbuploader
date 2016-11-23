#include "mainwindow.h"
#include "ui_mainwindow.h"


/* ------------------------------------------------- */
/* --------- MainWindow ---------------------------- */
/* ------------------------------------------------- */
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    logfile.setFileName("output.log");
    logfile.open(QIODevice::WriteOnly | QIODevice::Text);

    idfile.setFileName("idmap.log");
    idfile.open(QIODevice::Append | QIODevice::Text);

    WriteLog("Entering MainWindow()");
    ui->setupUi(this);
    this->showMaximized();
    qsrand(QTime::currentTime().msec());

    numNetConn = 0;

    numFilesFound = 0;
    numBytesFound = 0;
    numAnonErrors = 0;
    numBytesSentSuccess = 0;
    numBytesSentFail = 0;
    numBytesSentTotal = 0;
    numFilesSentSuccess = 0;
    numFilesSentFail = 0;
    numFilesSentTotal = 0;
    numBytesLastSend = 0;
    numFilesLastSend = 0;

    networkManager = new QNetworkAccessManager(this);
    isUploading = false;

    PopulateModality();
    PopulateConnectionList();
    SetBuildDate();

    ui->cmbProxyType->addItem("(Select Proxy Type...)", "");
    ui->cmbProxyType->addItem("Default", "default");
    ui->cmbProxyType->addItem("Socks5", "socks5");
    ui->cmbProxyType->addItem("Http", "http");
    ui->cmbProxyType->addItem("HttpCaching", "httpcaching");
    ui->cmbProxyType->addItem("FtpCaching", "ftpcaching");

    SetTempDir();

    /* disable the upload button */
    ui->btnUploadAll->setEnabled(false);
    ui->btnResendFailedObjects->setEnabled(false);

    WriteLog("Leaving MainWindow()");
}


/* ------------------------------------------------- */
/* --------- ~MainWindow --------------------------- */
/* ------------------------------------------------- */
MainWindow::~MainWindow()
{
    delete ui;
    logfile.close();
    idfile.close();
}


/* ------------------------------------------------- */
/* --------- SetBuildDate -------------------------- */
/* ------------------------------------------------- */
void MainWindow::SetBuildDate() {
    QLabel *statusLabel = new QLabel(this); // create objects for the status bar label
    statusLabel->setText("Build date: " + QString::fromLocal8Bit(__DATE__)); // set text for the label
    ui->statusBar->addPermanentWidget(statusLabel); // add the control to the status bar
}


/* ------------------------------------------------- */
/* --------- PopulateModality ---------------------- */
/* ------------------------------------------------- */
void MainWindow::PopulateModality() {
    WriteLog("Entering PopulateModality()");
    ui->cmbModality->addItem("(Select Modality...)", "");
    ui->cmbModality->addItem("All DICOM", "DICOM");
    ui->cmbModality->addItem("MR (DICOM)","MR");
    ui->cmbModality->addItem("MR (Non-DICOM: .hdr .img .nii .nii.gz)","NIFTI");
    ui->cmbModality->addItem("CT (DICOM)","CT");
    ui->cmbModality->addItem("PET (DICOM)","PET");
    ui->cmbModality->addItem("Phillips Imaging (.par/.rec)", "PARREC");
    ui->cmbModality->addItem("EEG (.cnt .dat .3dd)", "EEG");
    ui->cmbModality->addItem("Eye Tracking (.edf)", "ET");
    ui->cmbModality->addItem("VIDEO (.wmv .avi .mpg .mpeg .mp4 .mkv)", "VIDEO");
    WriteLog("Leaving PopulateModality()");
}


/* ------------------------------------------------- */
/* --------- PopulateConnectionList ---------------- */
/* ------------------------------------------------- */
void MainWindow::PopulateConnectionList(){
    WriteLog("Entering PopulateConnectionList()");
    ui->lstConn->clear();
    QFile file("connections.txt");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QTextStream in(&file);
    QList< QStringList > lists;
    QString line;
    do {
        line = in.readLine();
        lists << line.split("\t");
    } while (!line.isNull());

    QString connName;
    for ( int row = 0; row < lists.size(); ++row ) {
        if (lists[row].size() > 2) {
            connName = lists[row][0] + ',' + lists[row][1] + ',' + lists[row][2];
            ui->lstConn->addItem(connName);
        }
    }
    WriteLog("Leaving PopulateConnectionList()");
}


/* ------------------------------------------------- */
/* --------- on_btnExit_clicked -------------------- */
/* ------------------------------------------------- */
void MainWindow::on_btnExit_clicked()
{
    exit(0);
}


/* ------------------------------------------------- */
/* --------- on_pushButton_clicked ----------------- */
/* ------------------------------------------------- */
void MainWindow::on_pushButton_clicked()
{
    QString server = ui->txtServer->text().trimmed();
    QString username = ui->txtUsername->text().trimmed();
    QString password = ui->txtPassword->text().trimmed();

    QByteArray phash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha1);

    QFile file("connections.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << server << "\t" << username << "\t" << phash.toHex().toUpper() << endl;
    file.close();

    PopulateConnectionList();

}


/* ------------------------------------------------- */
/* --------- on_btnTestConn_clicked ---------------- */
/* ------------------------------------------------- */
/* test the specified connection                     */
void MainWindow::on_btnTestConn_clicked()
{
    WriteLog("Calling SetProxy() in on_btnTestConn_clicked()...");
    networkManager->setProxy(GetProxy());
    WriteLog("Done calling SetProxy() in on_btnTestConn_clicked()...");

    if (GetConnectionParms(connServer, connUsername, connPassword)) {
        WriteLog("Should've gotten through GetConnectionParms()");
        /* set the hourglass cursor */
        QApplication::setOverrideCursor(Qt::WaitCursor);

        /* prepare the form to be sent */
        QUrl url;
        QByteArray postData;
        url.setUrl(connServer + "/api.php");
        QNetworkRequest request(url);
        request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
        postData.append('u').append("=").append(connUsername).append("&");
        postData.append('p').append("=").append(connPassword);

        WriteLog("about to send the test POST in on_btnTestConn_clicked()");
        /* submit the POST request and setup the reply/error handlers */
        QNetworkReply* reply = networkManager->post(request, postData);
        numNetConn++;
        connect(reply, SIGNAL(finished()), this, SLOT(onGetReply()));

        /* restore the regular cursor */
        QApplication::restoreOverrideCursor();
    }
}


/* ------------------------------------------------- */
/* --------- onGetReply ---------------------------- */
/* ------------------------------------------------- */
void MainWindow::onGetReply()
{
    WriteLog("Entering onGetReply()");
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    QString response;

    /* check if there was a reply */
    if (reply) {
        /* and check if there was an error along with the reply */
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }

        reply->deleteLater();
    }

    /* check for empty reply */
    if (response.trimmed().isEmpty())
        response = tr("Unable to retrieve POST response");

    /* if it starts with 'Welcome' its just an authentication check */
    WriteLog("OnGetReply(" + response + ")");
    if (response.left(7) == "Welcome")
        ShowMessageBox(response);
    else {
        WriteLog(response);
    }

    WriteLog("Leaving OnGetReply()");
}


/* ------------------------------------------------- */
/* --------- onGetReplyUpload ---------------------- */
/* ------------------------------------------------- */
void MainWindow::onGetReplyUpload()
{
    WriteLog("Entering onGetReplyUpload()");
    isUploading = false;

    WriteLog(QString("(Z) numFilesSentTotal: [%1] numFilesSentSuccess: [%2] numFilesSentFail: [%3]").arg(numFilesSentTotal).arg(numFilesSentSuccess).arg(numFilesSentFail));

    //qDebug() << "numNetConn (A): " << numNetConn;
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) { response = tr("Received empty POST response"); }

    WriteLog("OnGetReplyUpload(" + response + ")");

    /* parse the response. Should be comma delimited. First item in list is response:
        SUCCESS, LOGINERROR, UPLOADERROR, */
    QStringList md5list = response.split(",");
    QString responsecode = md5list.takeFirst();

    if (responsecode == "SUCCESS") {
        /* loop through the list of sent files (local) and see if the MD5 is in the received list of MD5s */
        for (int i=0;i<lastUploadList.count();i++) {

            /* get the MD5(s) from the tableview and check if they were received */
            int ii = lastUploadList[i];
            QString md5 = ui->tableFiles->item(ii,8)->text();
            WriteLog(QString("Checking if MD5 [%1] was received by remote server").arg(md5));
            bool found = false;
            if (md5list.contains(md5,Qt::CaseInsensitive)) {
                found = true;
            }
            if (md5.contains(",")) {
                /* the tableview contains a comma, and therefor more than one MD5. Need to check all of them */
                QStringList multiMD5list = md5.split(",");
                found = true;
                foreach (const QString &str, multiMD5list) {
                    if (!md5list.contains(str)) {
                        found = false;
                    }
                }
            }
            /* populate the table if the MD5 is valid or not */
            if (found) {
                ui->tableFiles->item(ii,1)->setForeground(QBrush(Qt::green));
                ui->tableFiles->item(ii,1)->setText("Received");
                numFilesSentSuccess++;
            }
            else {
                ui->tableFiles->item(ii,1)->setForeground(QBrush(Qt::red));
                ui->tableFiles->item(ii,1)->setText("MD5 Error");
                numFilesSentFail++;
            }
        }
        numBytesSentSuccess += numBytesLastSend;
        ui->lblUploadFilesSentSuccess->setText(QString("%1").arg(numFilesSentSuccess));
    }
    else {
        /* got a response other than 'success'... so we can't assume any of the files were received */
        for (int i=0;i<lastUploadList.count();i++) {
            int ii = lastUploadList[i];
            ui->tableFiles->item(ii,1)->setForeground(QBrush(Qt::red));
            ui->tableFiles->item(ii,1)->setText(responsecode);
            numFilesSentFail++;
        }
    }

    /* set the last sent statistics */
    numFilesLastSend = 0;
    numBytesLastSend = 0;
    numNetConn--;
    WriteLog("Leaving onGetReplyUpload()");
}


/* ------------------------------------------------- */
/* --------- onNetworkError ------------------------ */
/* ------------------------------------------------- */
void MainWindow::onNetworkError(QNetworkReply::NetworkError networkError)
{
    WriteLog("Entering onNetworkError()");

    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());
    WriteLog("Error [" + reply->errorString() + "]");

    /* if this function is called, the last queued network request should be finished */
    isUploading = false;
    numNetConn--;

    WriteLog(QString("(E) numFilesSentTotal: [%1] numFilesSentSuccess: [%2] numFilesSentFail: [%3]").arg(numFilesSentTotal).arg(numFilesSentSuccess).arg(numFilesSentFail));

    /* update the upload stats and reset the counts for the last upload */
    numBytesSentFail += numBytesLastSend;
    numFilesSentFail += numFilesLastSend;
    numFilesLastSend = 0;
    numBytesLastSend = 0;
    //qDebug() << err.errorString();

    QBrush colorRed(Qt::red);
    for (int i=0;i<lastUploadList.count();i++) {
        int ii = lastUploadList[i];
        ui->tableFiles->item(ii,1)->setForeground(colorRed);
        ui->tableFiles->item(ii,1)->setText("Upload fail");
    }

    WriteLog(QString("(F) numFilesSentTotal: [%1] numFilesSentSuccess: [%2] numFilesSentFail: [%3]").arg(numFilesSentTotal).arg(numFilesSentSuccess).arg(numFilesSentFail));

    ui->lblUploadFilesSentFail->setText(QString("%1").arg(numFilesSentFail));

    WriteLog("Leaving onNetworkError()");
}

/* ------------------------------------------------- */
/* --------- on_btnSelectDataDir_clicked ----------- */
/* ------------------------------------------------- */
void MainWindow::on_btnSelectDataDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->txtDataDir->setText(dir);
}


/* ------------------------------------------------- */
/* --------- on_btnSearch_clicked ------------------ */
/* ------------------------------------------------- */
void MainWindow::on_btnSearch_clicked()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
    WriteLog("Starting search of directory [" + ui->txtDataDir->text() + "]");
    scanDirIter(QDir(ui->txtDataDir->text()));
    WriteLog("Finished search of directory [" + ui->txtDataDir->text() + "]");
    QApplication::restoreOverrideCursor();

    /* enable the upload button */
    ui->btnUploadAll->setEnabled(true);
}


/* ------------------------------------------------- */
/* --------- scanDirIter --------------------------- */
/* ------------------------------------------------- */
void MainWindow::scanDirIter(QDir dir)
{
    QVariant modality = ui->cmbModality->currentData();
    QString fullfile;
    QDirIterator iterator(dir.absolutePath(), QDirIterator::Subdirectories);
    QString fileModality;
    QString fileType;
    QString filePatientID;

    elapsedFileSearchTime.start();
    startFileSearchTime = QDateTime::currentDateTime();
    ui->lblFileStartTime->setText(startFileSearchTime.toString(Qt::TextDate));

    WriteLog("Searching directory [" + dir.path() + "]");

    /* iterate through all files in the parent directory */
    while (iterator.hasNext()) {
        iterator.next();
        if (!iterator.fileInfo().isDir()) {
            fullfile = iterator.filePath();
            WriteLog("Came across file [" + fullfile + "]...");
            /* check the file type */
            GetFileType(fullfile, fileType, fileModality, filePatientID);
            if (fileType == "DICOM") {
                if (modality == "DICOM") {
                    AddFoundFile(&iterator,fullfile,fileType,fileModality, filePatientID);
                }
                else {
                    if (modality == fileModality) {
                        AddFoundFile(&iterator,fullfile,fileType,modality.toString(), filePatientID);
                    }
                }
            }
            if ((fileType == "PARREC") && (modality == "PARREC")) {
                AddFoundFile(&iterator,fullfile,fileType,fileModality, filePatientID);
            }
            if ((fileType == "EEG") && (modality == "EEG")) {
                AddFoundFile(&iterator,fullfile,fileType,fileModality, filePatientID);
            }
            if ((fileType == "ET") && (modality == "ET")) {
                WriteLog("scanDirIter says this file is an ET");
                AddFoundFile(&iterator,fullfile,fileType,fileModality, filePatientID);
            }
            if ((fileType == "NIFTI") && (modality == "NIFTI")) {
                AddFoundFile(&iterator,fullfile,fileType,fileModality, filePatientID);
            }
        }
    }
}


/* ------------------------------------------------- */
/* --------- GetFileType --------------------------- */
/* ------------------------------------------------- */
void MainWindow::GetFileType(QString f, QString &fileType, QString &fileModality, QString &filePatientID)
{
    WriteLog("In GetFileType(" + f + ")");
    fileModality = QString("");
    gdcm::Reader r;
    r.SetFileName(f.toStdString().c_str());
    if (r.Read()) {
        //qDebug("%s is a DICOM file",f.toStdString().c_str());
        fileType = QString("DICOM");
        gdcm::StringFilter sf;
        sf = gdcm::StringFilter();
        sf.SetFile(r.GetFile());
        std::string s;

        /* get modality */
        s = sf.ToString(gdcm::Tag(0x0008,0x0060));
        fileModality = QString(s.c_str());

        /* get patientID */
        s = sf.ToString(gdcm::Tag(0x0010,0x0020));
        filePatientID = QString(s.c_str());
    }
    else {
        WriteLog("[" + f + "] is not a DICOM file");
        /* check if EEG, and Polhemus */
        if ((f.toLower().endsWith(".cnt")) || (f.toLower().endsWith(".dat")) || (f.toLower().endsWith(".3dd"))) {
            WriteLog("Found an EEG file [" + f + "]");
            fileType = "EEG";
            fileModality = "EEG";
            QFileInfo fn = QFileInfo(f);
            QStringList parts = fn.baseName().split("_");
            filePatientID = parts[0];
        }
        /* check if ET */
        else if (f.toLower().endsWith(".edf")) {
            WriteLog("Found an ET file [" + f + "]");
            fileType = "ET";
            fileModality = "ET";
            QFileInfo fn = QFileInfo(f);
            QStringList parts = fn.baseName().split("_");
            filePatientID = parts[0];
        }
        /* check if MR (Non-DICOM) analyze or nifti */
        else if ((f.toLower().endsWith(".nii")) || (f.toLower().endsWith(".nii.gz")) || (f.toLower().endsWith(".hdr")) || (f.toLower().endsWith(".img"))) {
            WriteLog("Found an analyze or Nifti image [" + f + "]");
            fileType = "NIFTI";
            fileModality = "NIFTI";
            QFileInfo fn = QFileInfo(f);
            QStringList parts = fn.baseName().split("_");
            filePatientID = parts[0];
        }
        /* check if par/rec */
        else if (f.endsWith(".par")) {
            WriteLog("Found a PARREC image [" + f + "]");
            fileType = "PARREC";
            fileModality = "PARREC";

            QFile inputFile(f);
            if (inputFile.open(QIODevice::ReadOnly))
            {
               QTextStream in(&inputFile);
               while ( !in.atEnd() )
               {
                  QString line = in.readLine();
                  if (line.contains("Patient name")) {
                      QStringList parts = line.split(":",QString::SkipEmptyParts);
                      filePatientID = parts[1].trimmed();
                  }
                  if (line.contains("MRSERIES")) {
                      fileModality = "MR";
                  }
               }
               inputFile.close();
            }
        }
        else {
            WriteLog("Filetype is unknown [" + f + "]");
            fileType = "Unknown";
        }
    }
}


/* ------------------------------------------------- */
/* --------- GetDicomModality ---------------------- */
/* ------------------------------------------------- */
QString MainWindow::GetDicomModality(QString f)
{
    gdcm::Reader r;
    r.SetFileName(f.toStdString().c_str());
    if (!r.CanRead()) {
        return "NONDICOM";
    }
    gdcm::StringFilter sf;
    sf = gdcm::StringFilter();
    sf.SetFile(r.GetFile());
    std::string s = sf.ToString(gdcm::Tag(0x0008,0x0060));

    QString qs = s.c_str();

    return qs;
}


/* ------------------------------------------------- */
/* --------- AddFoundFile -------------------------- */
/* ------------------------------------------------- */
bool MainWindow::AddFoundFile(QDirIterator *it, QString f, QString fType, QString modality, QString filePatientID)
{
    qint64 size = 0;
    QString sSize, cDate;
    QFileInfo info;

    /* add this file to the main list */
    files << f;

    /* check if its a .par/.rec so the real size can calculated */
    if (fType == "PARREC") {
        QString recfile = it->filePath();
        recfile.replace(".par",".rec");
        WriteLog(QString(".rec file path: [%1]").arg(recfile));

        QFile rec(recfile);
        qint64 recsize = rec.size();
        size += recsize;
    }

    /* get some info about the file */
    info = it->fileInfo();
    size += info.size();
    cDate = info.created().toString();
    sSize = humanReadableSize(size);

    /* add a row to the table and populate it with info */
    const int currentRow = ui->tableFiles->rowCount();
    ui->tableFiles->setRowCount(currentRow + 1);
    ui->tableFiles->setItem(currentRow, 0, new QTableWidgetItem(f));
    ui->tableFiles->setItem(currentRow, 1, new QTableWidgetItem("Readable"));
    ui->tableFiles->setItem(currentRow, 2, new QTableWidgetItem(fType));
    ui->tableFiles->setItem(currentRow, 3, new QTableWidgetItem(modality));
    ui->tableFiles->setItem(currentRow, 4, new QTableWidgetItem(filePatientID));
    ui->tableFiles->setItem(currentRow, 5, new QTableWidgetItem(cDate));
    ui->tableFiles->setItem(currentRow, 6, new QTableWidgetItem(sSize));
    ui->tableFiles->setItem(currentRow, 7, new QTableWidgetItem(""));
    ui->tableFiles->setItem(currentRow, 8, new QTableWidgetItem(""));
    ui->tableFiles->setItem(currentRow, 9, new QTableWidgetItem(QString("%1").arg(size)));

    /* update the various statuses and metrics */
    numFilesFound++;
    numBytesFound += size;
    ui->lblFileCount->setText(QString("Found %1 files").arg(ui->tableFiles->rowCount()));
    ui->lblFileBytesFound->setText(humanReadableSize(numBytesFound));
    ui->lblNumFilesFound->setText(QString("%1").arg(numFilesFound));
    ui->lblFileElapsedTime->setText(QString("%1").arg(timeConversion(elapsedFileSearchTime.elapsed())));

    /* check to see if the filename is in the correct format */
    if ((ui->cmbModality->currentData() == "EEG") || (ui->cmbModality->currentData() == "ET")) {
        QString filebasename = QFileInfo(f).baseName();
        QStringList parts = filebasename.split("_");

        WriteLog(QString("FileBaseName: %1 Number of parts: %2").arg(filebasename, parts.count()));

        if ((parts.count() != 5) && (parts.count() != 6)) {
            /* color the line red */
            QBrush colorRed(Qt::red);
            ui->tableFiles->item(ui->tableFiles->rowCount()-1,0)->setForeground(colorRed);
            ui->tableFiles->item(ui->tableFiles->rowCount()-1,1)->setText("Invalid filename");
            ui->tableFiles->item(ui->tableFiles->rowCount()-1,1)->setToolTip("Filename should be in the format S1234ABC_YYYYMMDDHHMISS_task_operator_series_filenum.ext");
        }
    }

    ui->tableFiles->scrollToBottom();
    qApp->processEvents();

    return true;
}


/* ------------------------------------------------- */
/* --------- on_btnTmpDir_clicked ------------------ */
/* ------------------------------------------------- */
void MainWindow::on_btnTmpDir_clicked()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"), "", QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);
    ui->txtTmpDir->setText(dir);
}


/* ------------------------------------------------- */
/* --------- on_btnUploadAll_clicked --------------- */
/* ------------------------------------------------- */
void MainWindow::on_btnUploadAll_clicked()
{
    DoUpload(true);

    /* enable this resend button */
    ui->btnResendFailedObjects->setEnabled(true);
}


/* ------------------------------------------------- */
/* --------- DoUpload ------------------------------ */
/* ------------------------------------------------- */
void MainWindow::DoUpload(bool uploadAll) {
    networkManager->setProxy(GetProxy());

    WriteLog("Entering on_btnUploadAll_clicked()");
    if (ui->lstConn->selectedItems().length() < 1) {
        ShowMessageBox("No connection selected");
        return;
    }

    /* check the fields before attempting to upload */
    if (ui->cmbInstanceID->currentData() == "") {
        ShowMessageBox("Instance ID is blank");
        ui->cmbInstanceID->setFocus();
        return;
    }
    if (ui->cmbProjectID->currentData() == "") {
        ShowMessageBox("Project ID is blank");
        ui->cmbProjectID->setFocus();
        return;
    }
    if (ui->cmbSiteID->currentData() == "") {
        ShowMessageBox("Site ID is blank");
        ui->cmbSiteID->setFocus();
        return;
    }
    /* check if there is a temp dir specified (if needed) */
    if ((ui->chkRemovePatientBirthDate->isChecked() || ui->chkReplacePatientBirthDate->isChecked() || ui->chkReplacePatientID->isChecked() || ui->chkReplacePatientName->isChecked()) && (ui->txtTmpDir->text() == "")) {
        ShowMessageBox("Temp dir is blank");
        ui->txtTmpDir->setFocus();
        return;
    }

    ui->lblStatus->setText("Starting upload transaction");
    elapsedUploadTime.start();
    startUploadTime = QDateTime::currentDateTime();
    ui->lblUploadStart->setText(startUploadTime.toString(Qt::TextDate));

    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString modality = ui->cmbModality->currentData().toString();
    bool isDICOM = false;
    bool isPARREC = false;
    bool isNIFTI = false;

    /* if its a DICOM file, create a tmp directory to anonymize it */
    if ((modality == "DICOM") || (modality == "MR") || (modality == "CT") || (modality == "PET") || (modality == "SPECT") || (modality == "US")) {
        isDICOM = true;
    }
    if (modality == "PARREC") {
        isPARREC = true;
    }
    if (modality == "NIFTI") {
        isNIFTI = true;
    }

    QVector<int> fileList;

    /* start a transaction */
    StartTransaction();

    /* wait for a valid transaction number */
    while (transactionNumber <= 0) {
        QTest::qWait(100);
    }

    /* this will anonymize and then upload all of the files in the list */
    int rowCount = ui->tableFiles->rowCount();
    int currentUploadSize = 0;
    ui->progTotal->setRange(0,rowCount);
    for (int i=0; i<rowCount; i++){

        /* check if its status */
        QString status = ui->tableFiles->item(i,1)->text();
        if (uploadAll || ( status.contains("error",Qt::CaseInsensitive) && !uploadAll ) ) {

            /* add this item to the list */
            fileList.append(i);
            currentUploadSize += ui->tableFiles->item(i,7)->text().toInt();

            ui->lblStatus->setText("Preparing file...");

            int compareSize;
            if ((i+1) < rowCount) {
                compareSize = currentUploadSize + ui->tableFiles->item(i+1,7)->text().toInt();
            }
            else {
                compareSize = currentUploadSize;
            }
            /* more than 500MB or 300 files, split it up */
            if ((compareSize > 500000000) || (fileList.size() >= 300)) {
                AnonymizeAndUpload(fileList, isDICOM, isPARREC);
                /* clear the list */
                fileList.clear();
                currentUploadSize = 0;
            }

            ui->progTotal->setValue(i+1);
            qApp->processEvents();
        }
    }
    /* anonymize and upload the remaining files */
    AnonymizeAndUpload(fileList, isDICOM, isPARREC);

    /* end the transaction */
    EndTransaction();
    ui->lblStatus->setText("Ending upload transaction");

    QApplication::restoreOverrideCursor();

}

/* ------------------------------------------------- */
/* --------- AnonymizeAndUpload -------------------- */
/* ------------------------------------------------- */
void MainWindow::AnonymizeAndUpload(QVector<int> list, bool isDICOM, bool isPARREC)
{
    lastUploadList = list;

    WriteLog("Entering AnonymizeAndUpload()");
    QStringList uploadList;
    QStringList md5list;
    QString tmpDir = "";

    /* if its a DICOM or PARREC file, create a tmp directory to anonymize it */
    if (isDICOM || isPARREC) {
        /* create a temp directory */
        tmpDir = ui->txtTmpDir->text() + "/" + GenerateRandomString(15);
        QDir dir;
        dir.mkpath(tmpDir);
        WriteLog(QString("Creating tmpDir [%1]").arg(tmpDir.toStdString().c_str()));
    }

    WriteLog(QString("in AnonymizeAndUpload: got list of size %1").arg(list.size()));

    /* loop through the list of table row numbers, and try to anonymize (if DICOM) and then upload the file */
    ui->progAnon->setRange(0,list.size());
    for (int i=0; i< list.size(); i++) {
        int ii = list[i];
        QString f = ui->tableFiles->item(ii,0)->text();
        QString newFilePath;
        QString newPathPar;
        QString newPathRec;

        /* update the elapsed time and status */
        ui->lblUploadElapsed->setText(QString("%1").arg(timeConversion(elapsedUploadTime.elapsed())));
        ui->lblStatus->setText("Anonymizing...");

        if (isDICOM) {
            /* copy file to temp dir */
            newFilePath = tmpDir + "/" + GenerateRandomString(15) + ".dcm";
            QFile::copy(f,newFilePath);
            //qDebug("Copying [%s] to [%s]", f.toStdString().c_str(), newFilePath.toStdString().c_str());
            /* add this filepath to the list of files to be uploaded */
            uploadList << newFilePath;
            gdcm::Reader r;
            gdcm::File file;
            gdcm::StringFilter sf;
            gdcm::DataSet ds;
            r.SetFileName(newFilePath.toStdString().c_str());
            r.Read();
            sf = gdcm::StringFilter();
            sf.SetFile(r.GetFile());
            file = r.GetFile();
            ds = file.GetDataSet();

            sf = gdcm::StringFilter();
            sf.SetFile(r.GetFile());
            std::vector<gdcm::Tag> empty_tags;
            std::vector<gdcm::Tag> remove_tags;
            std::vector< std::pair<gdcm::Tag, std::string> > replace_tags_value;

            /* check if the patient name should be replaced */
            if (ui->chkReplacePatientName->isChecked()) {
                std::string s = sf.ToString(gdcm::Tag(0x0010,0x0010));
                QString tagVal = s.c_str();
                tagVal = tagVal.trimmed();
                tagVal = tagVal.toLower();

                QByteArray hash = QCryptographicHash::hash(tagVal.toUtf8(), QCryptographicHash::Sha1);
                QString newTagVal = hash.toHex().toUpper();
                WriteLog(QString("Replacing DICOM PatientName [%1] with [%2]").arg(tagVal.toStdString().c_str()).arg(newTagVal.toStdString().c_str()));

                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0010");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );
            }

            /* check if the patient ID should be replaced */
            if (ui->chkReplacePatientID->isChecked()) {
                std::string s = sf.ToString(gdcm::Tag(0x0010,0x0020));
                QString tagVal = s.c_str();
                QString tagValOrig = tagVal;
                tagVal = tagVal.trimmed();
                tagVal = tagVal.toLower();

                QByteArray hash = QCryptographicHash::hash(tagVal.toUtf8(), QCryptographicHash::Sha1);
                QString newTagVal = hash.toHex().toUpper();

                WriteLog(QString("Replacing DICOM PatientID [%1] with [%2]").arg(tagVal.toStdString().c_str()).arg(newTagVal.toStdString().c_str()));
                //qDebug("Replacing %s with %s",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());

                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0020");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );

                QTextStream out(&idfile);
                out << "Orig ID: [" << tagValOrig << "]  New ID: [" << newTagVal << "]" << endl;
            }

            /* check if the patient birthdate should be replaced */
            if (ui->chkReplacePatientBirthDate->isChecked()) {
                std::string s = sf.ToString(gdcm::Tag(0x0010,0x0030));
                QString tagVal = s.c_str();
                tagVal = tagVal.trimmed();
                int year;
                if (tagVal.length() == 8) {
                    year = tagVal.left(4).toInt();
                }
                else if (tagVal.contains(":")) {
                    QStringList parts = tagVal.split(":");
                    year = parts[0].toInt();
                }
                else if (tagVal.contains("-")) {
                    QStringList parts = tagVal.split("-");
                    year = parts[0].toInt();
                }
                else {
                    QDate dob;
                    dob.fromString(tagVal);
                    year = dob.year();
                }

                QString newTagVal = QString::number(year) + "-00-00";

                //qDebug("Replacing [%s] with [%s]",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());
                WriteLog(QString("Replacing DICOM PatientBirthDate [%1] with [%2]").arg(tagVal.toStdString().c_str()).arg(newTagVal.toStdString().c_str()));

                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0030");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );
            }

            /* check if the patient birthdate should be removed */
            if (ui->chkRemovePatientBirthDate->isChecked()) {
                QString newTagVal = "0000-00-00";
                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0030");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );
            }

            ui->tableFiles->setCurrentCell(ii,0);
            gdcm::Anonymizer anon;
            if (AnonymizeOneFileDumb(anon,newFilePath.toStdString().c_str(),newFilePath.toStdString().c_str(),empty_tags,remove_tags,replace_tags_value,false)) {
                ui->tableFiles->setItem(ii,1,new QTableWidgetItem("Anonymized"));
            }
            else {
                ui->tableFiles->setItem(ii,1,new QTableWidgetItem("Error anonymizing"));
            }

            ui->tableFiles->setItem(ii,7,new QTableWidgetItem(newFilePath));
            /* get the MD5 hash after anonymization */
            if (ui->chkUseMD5->isChecked()) {
                QByteArray md5 = GetFileChecksum(newFilePath,QCryptographicHash::Md5);
                md5list << QString("%1").arg(md5.toStdString().c_str());
                ui->tableFiles->setItem(ii,8,new QTableWidgetItem(QString("%1").arg(md5.toUpper().toStdString().c_str())));
            }
            else {
                md5list << "0";
            }
        }
        else if (isPARREC) {
            /* copy file to temp dir */
            newFilePath = tmpDir + "/" + GenerateRandomString(15);
            newPathPar = newFilePath + ".par";
            newPathRec = newFilePath + ".rec";
            QString f2 = f;
            f2.replace(".par",".rec");

            QFile::copy(f,newPathPar);
            QFile::copy(f2,newPathRec);

            /* add these filepaths to the list of files to be uploaded */
            uploadList << newPathPar;
            uploadList << newPathRec;
            ui->tableFiles->setItem(ii,7,new QTableWidgetItem(newPathPar));
            if (ui->chkUseMD5->isChecked()) {
                QByteArray md5_1 = GetFileChecksum(newPathPar,QCryptographicHash::Md5);
                md5list << QString("%1").arg(md5_1.toStdString().c_str());
                QByteArray md5_2 = GetFileChecksum(newPathRec,QCryptographicHash::Md5);
                md5list << QString("%1").arg(md5_2.toStdString().c_str());
                ui->tableFiles->setItem(ii,8,new QTableWidgetItem(QString("%1,%2").arg(md5_1.toUpper().toStdString().c_str()).arg(md5_2.toUpper().toStdString().c_str())));
            }
            else {
                md5list << "0";
            }
        }
        else {
            newFilePath = f;
            /* add this filepath to the list of files to be uploaded */
            uploadList << newFilePath;
            ui->tableFiles->setItem(ii,7,new QTableWidgetItem(newFilePath));
            if (ui->chkUseMD5->isChecked()) {
                QByteArray md5 = GetFileChecksum(newFilePath,QCryptographicHash::Md5);
                md5list << QString("%1").arg(md5.toStdString().c_str());;
                ui->tableFiles->setItem(ii,8,new QTableWidgetItem(QString("%1").arg(md5.toUpper().toStdString().c_str())));
            }
            else {
                md5list << "0";
            }
        }

        ui->tableFiles->setCurrentCell(ii,0);
        ui->progAnon->setValue(i+1);
        qApp->processEvents();
    }

    /* go through the list of files to be uploaded, and upload them as one big batch */
    totalUploaded += UploadFileList(uploadList, md5list);

    /* wait for everything to finish before deleting the directory */
    while (isUploading) {
        QTest::qWait(1000);
        //WriteLog("Waiting...");
    }

    /* delete the temp directory */
    if (tmpDir != "") {
        QDir dir(tmpDir);
        WriteLog("Attempting to remove tmpDir [" + tmpDir + "]");
        if (!dir.removeRecursively()) {
            WriteLog("Unable to remove [" + tmpDir + "] ... the drive will fill up with junk soon");
        }
        else {
            WriteLog("Successfully deleted [" + tmpDir + "]");
        }
    }

    WriteLog("Leaving AnonymizeAndUpload()");
}


/* ------------------------------------------------- */
/* --------- AnonymizeOneFileDumb ------------------ */
/* ------------------------------------------------- */
/* borrowed in its entirety from gdcmanon.cxx        */
bool MainWindow::AnonymizeOneFileDumb(gdcm::Anonymizer &anon, const char *filename, const char *outfilename, std::vector<gdcm::Tag> const &empty_tags, std::vector<gdcm::Tag> const &remove_tags, std::vector< std::pair<gdcm::Tag, std::string> > const & replace_tags, bool continuemode)
{
    gdcm::Reader reader;
    reader.SetFileName( filename );
    if( !reader.Read() ) {
        numAnonErrors++;
        ui->lblNumAnonErrors->setText(QString("%1").arg(numAnonErrors));
        std::cerr << "Could not read : " << filename << std::endl;
        if( continuemode ) {
            std::cerr << "Skipping from anonymization process (continue mode)." << std::endl;
            return true;
        }
        else
        {
            std::cerr << "Check [--continue] option for skipping files." << std::endl;
            return false;
        }
    }
    gdcm::File &file = reader.GetFile();

    anon.SetFile( file );

    if( empty_tags.empty() && replace_tags.empty() && remove_tags.empty() ) {
        std::cerr << "No operation to be done." << std::endl;
        return false;
    }

    std::vector<gdcm::Tag>::const_iterator it = empty_tags.begin();
    bool success = true;
    for(; it != empty_tags.end(); ++it) {
        success = success && anon.Empty( *it );
    }
    it = remove_tags.begin();
    for(; it != remove_tags.end(); ++it) {
        success = success && anon.Remove( *it );
    }

    std::vector< std::pair<gdcm::Tag, std::string> >::const_iterator it2 = replace_tags.begin();
    for(; it2 != replace_tags.end(); ++it2) {
        success = success && anon.Replace( it2->first, it2->second.c_str() );
    }

    gdcm::Writer writer;
    writer.SetFileName( outfilename );
    writer.SetFile( file );
    if( !writer.Write() ) {
        numAnonErrors++;
        ui->lblNumAnonErrors->setText(QString("%1").arg(numAnonErrors));
        std::cerr << "Could not Write : " << outfilename << std::endl;
        if( strcmp(filename,outfilename) != 0 ) {
            gdcm::System::RemoveFile( outfilename );
        }
        else
        {
            std::cerr << "gdcmanon just corrupted: " << filename << " for you (data lost)." << std::endl;
        }
        return false;
    }
    return success;
}


/* ------------------------------------------------- */
/* --------- GetConnectionParms -------------------- */
/* ------------------------------------------------- */
bool MainWindow::GetConnectionParms(QString &s, QString &u, QString &p)
{
    QStringList connItems;
    QString connStr;

    WriteLog("Inside GenConnectionParms()");

    /* check if any connections exist */
    if (ui->lstConn->count() < 1) {
        ui->lblConnMessage->setText("No connections setup");
        return false;
    }
    /* check if any connections are selected */
    connStr = ui->lstConn->currentItem()->text();
    if (connStr.trimmed() == "") {
        ui->lblConnMessage->setText("No connection selected");
        return false;
    }

    connStr = ui->lstConn->currentItem()->text();
    connItems << connStr.split(",");
    s = connItems[0];
    u = connItems[1];
    p = connItems[2];

    WriteLog("Leaving GenConnectionParms()");
    return true;
}


/* ------------------------------------------------- */
/* --------- UploadFileList ------------------------ */
/* ------------------------------------------------- */
int MainWindow::UploadFileList(QStringList list, QStringList md5list)
{
    WriteLog("Entering UploadFileList()");
    QString modality = ui->cmbModality->currentData().toString();

    if (!GetConnectionParms(connServer, connUsername, connPassword)) {
        return 0;
    }

    numFilesSentTotal += list.count();
    /* set the last sent statistics */
    numFilesLastSend = list.count();
    numBytesLastSend = list.count();

    QUrl url(connServer + "/api.php");
    QNetworkRequest request(url);

    QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    QHttpPart loginPart;
    /* username */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
    loginPart.setBody(connUsername.toLatin1());
    multiPart->append(loginPart);
    /* password */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
    loginPart.setBody(connPassword.toLatin1());
    multiPart->append(loginPart);
    /* action */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
    if (modality == "PARREC") { loginPart.setBody("UploadDICOM"); }
    else if ((modality == "EEG") || (modality == "ET")) { loginPart.setBody("UploadDICOM"); }
    else { loginPart.setBody("UploadDICOM"); }
    multiPart->append(loginPart);
    /* numfiles */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"numfiles\""));
    loginPart.setBody(QString::number(list.count()).toLatin1());
    WriteLog(QString::number(list.count()).toLatin1());
    multiPart->append(loginPart);
    /* instanceid */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"instanceid\""));
    loginPart.setBody(ui->cmbInstanceID->currentData().toString().toLatin1());
    multiPart->append(loginPart);
    /* projectid */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"projectid\""));
    loginPart.setBody(ui->cmbProjectID->currentData().toString().toLatin1());
    multiPart->append(loginPart);
    /* siteid */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"siteid\""));
    loginPart.setBody(ui->cmbSiteID->currentData().toString().toLatin1());
    multiPart->append(loginPart);
    /* equipment */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"equipmentid\""));
    loginPart.setBody(ui->cmbEquipmentID->currentData().toString().toLatin1());
    multiPart->append(loginPart);
    /* transaction number */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"transactionid\""));
    loginPart.setBody(QString::number(transactionNumber).toLatin1());
    multiPart->append(loginPart);
    WriteLog("TransactionID: " + QString::number(transactionNumber).toLatin1());
    /* matchIDOnly */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"matchidonly\""));
    if (ui->chkMatchIDOnly->isChecked())
        loginPart.setBody("1");
    else
        loginPart.setBody("0");
    multiPart->append(loginPart);
    /* dataformat */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"dataformat\""));
    if (modality == "DICOM") { loginPart.setBody("dicom"); WriteLog("dataformat set to [dicom]"); }
    else if (modality == "PARREC") { loginPart.setBody("parrec"); WriteLog("dataformat set to [parrec]"); }
    else if (modality == "EEG") { loginPart.setBody("eeg"); WriteLog("dataformat set to [eeg]"); }
    else if (modality == "ET") { loginPart.setBody("et"); WriteLog("dataformat set to [et]"); }
    else if (modality == "NIFTI") { loginPart.setBody("nifti"); WriteLog("dataformat set to [nifti]"); }
    else { loginPart.setBody(""); WriteLog("dataformat set to []"); }
    multiPart->append(loginPart);

    QStringList md5stringlist;
    /* loop through the list of files */
    ui->progUpload->setRange(0,100);
    for (int i=0;i<list.size();i++) {
        qDebug("UploadFileList [%d] [%s]", i, list[i].toStdString().c_str());
        QFile *file = new QFile(list[i]);
        QHttpPart filePart;
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"files[]\"; filename=\""+ file->fileName() + "\""));
        file->open(QIODevice::ReadOnly);
        filePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart
        multiPart->append(filePart);
        /* create the MD5 list [file|md5,file2|md5,etc] */
        QFileInfo fileInfo(file->fileName());
        QString filename(fileInfo.fileName());
        md5stringlist << md5list[i];
    }

    /* add the MD5 list  */
    QString md5string = md5stringlist.join(",");
    /* equipment */
    loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"md5list\""));
    loginPart.setBody(md5string.toLatin1());
    multiPart->append(loginPart);

    /* check if there was a previous upload still going on */
    while (isUploading) {
        ui->lblStatus->setText("Waiting for previous upload to complete...");
        QTest::qWait(1000);
    }

    /* do the POST and setup the event handlers for it */
    QNetworkReply* reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    numNetConn++;
    isUploading = true;
    connect(reply, SIGNAL(finished()), this, SLOT(onGetReplyUpload()));
    connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(onNetworkError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)), SLOT(progressChanged(qint64, qint64)));

    WriteLog(QString("Finished queueing %1 files for upload...").arg(list.size()));

    /* update the elapsed time */
    ui->lblUploadElapsed->setText(QString("%1").arg(timeConversion(elapsedUploadTime.elapsed())));
    uploadTime.start();

    return list.size();
}


/* ------------------------------------------------- */
/* --------- progressChanged ----------------------- */
/* ------------------------------------------------- */
void MainWindow::progressChanged(qint64 a, qint64 b)
{
    if (b > 0) {
        //qDebug() << "Uploading " << a  << "/" << b << "%" << (double)a/(double)b*100.0;
        ui->progUpload->setValue(((double)a/(double)b)*100.0);
        //qApp->processEvents(); // for some reason when this is uncommented, the upload freezes
    }

    /* calculate the download speed */
    double speed = a * 1000.0 / uploadTime.elapsed();
    QString unit;
    if (speed < 1024) {
        unit = "bytes/sec";
    } else if (speed < 1024*1024) {
        speed /= 1024;
        unit = "kB/s";
    } else {
        speed /= 1024*1024;
        unit = "MB/s";
    }
    ui->lblUploadSpeed->setText(QString::fromLatin1("%1 %2").arg(speed, 3, 'f', 1).arg(unit));

    /* update the elapsed time and status */
    ui->lblUploadElapsed->setText(QString("%1").arg(timeConversion(elapsedUploadTime.elapsed())));
    ui->lblStatus->setText("Uploading...");
}


/* ------------------------------------------------- */
/* --------- GenerateRandomString ------------------ */
/* ------------------------------------------------- */
QString MainWindow::GenerateRandomString(int len)
{
   const QString possibleCharacters("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789");

   QString randomString;
   for(int i=0; i<len; ++i)
   {
       int index = qrand() % possibleCharacters.length();
       QChar nextChar = possibleCharacters.at(index);
       randomString.append(nextChar);
   }
   return randomString;
}


/* ------------------------------------------------- */
/* --------- SetTempDir ---------------------------- */
/* ------------------------------------------------- */
void MainWindow::SetTempDir()
{
    if (ui->chkRemovePatientBirthDate->isChecked() || ui->chkReplacePatientBirthDate->isChecked() || ui->chkReplacePatientID->isChecked() || ui->chkReplacePatientName->isChecked()) {
        ui->txtTmpDir->setEnabled(true);
        //#ifdef W_OS_WIN32
            ui->txtTmpDir->setText("C:/temp");
        //#endif
        //#ifdef W_OS_LINUX
        //    ui->txtTmpDir->setText("/tmp");
        //#endif
    }
    else {
        ui->txtTmpDir->setDisabled(true);
    }
}

/* anonymize checkbox event handlers */
void MainWindow::on_chkReplacePatientName_clicked() { SetTempDir(); }
void MainWindow::on_chkReplacePatientID_clicked() { SetTempDir(); }
void MainWindow::on_chkReplacePatientBirthDate_clicked() { SetTempDir(); }
void MainWindow::on_chkRemovePatientBirthDate_clicked() { SetTempDir(); }


/* ------------------------------------------------- */
/* --------- on_lstConn_clicked -------------------- */
/* ------------------------------------------------- */
void MainWindow::on_lstConn_clicked(const QModelIndex &index)
{
    index;
    ui->lblConnMessage->setText("");
}


/* ------------------------------------------------- */
/* --------- on_btnRemoveConn_clicked -------------- */
/* ------------------------------------------------- */
void MainWindow::on_btnRemoveConn_clicked()
{
    qDeleteAll(ui->lstConn->selectedItems());
}


/* ------------------------------------------------- */
/* --------- on_btnLoadInstanceIDs_clicked --------- */
/* ------------------------------------------------- */
void MainWindow::on_btnLoadInstanceIDs_clicked()
{
    networkManager->setProxy(GetProxy());
    /* get list of instances through the API */

    if (ui->lstConn->count() < 1) {
        ShowMessageBox("No connections available");
    }
    else if (ui->lstConn->selectedItems().length() < 1) {
        ShowMessageBox("No connection selected");
    }
    else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        if (GetConnectionParms(connServer, connUsername, connPassword)) {
            QUrl url(connServer + "/api.php");
            QNetworkRequest request(url);
            QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            QHttpPart loginPart;
            /* username */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
            loginPart.setBody(connUsername.toLatin1()); multiPart->append(loginPart);
            /* password */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
            loginPart.setBody(connPassword.toLatin1()); multiPart->append(loginPart);
            /* action */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
            loginPart.setBody("getInstanceList"); multiPart->append(loginPart);

            QNetworkReply* reply = networkManager->post(request, multiPart);
            multiPart->setParent(reply); // delete the multiPart with the reply
            connect(reply, SIGNAL(finished()), this, SLOT(onGetReplyInstanceList()));
            QApplication::restoreOverrideCursor();
        }
    }
}


/* ------------------------------------------------- */
/* --------- on_btnLoadProjectIDs_clicked ---------- */
/* ------------------------------------------------- */
void MainWindow::on_btnLoadProjectIDs_clicked()
{
    networkManager->setProxy(GetProxy());
    /* get list of instances through the API */
    if (ui->lstConn->count() < 1) {
        ShowMessageBox("No connections available");
    }
    else if (ui->lstConn->selectedItems().length() < 1) {
        ShowMessageBox("No connection selected");
    }
    else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        if (GetConnectionParms(connServer, connUsername, connPassword)) {
            QUrl url(connServer + "/api.php");
            QNetworkRequest request(url);
            QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            QHttpPart loginPart;
            /* username */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
            loginPart.setBody(connUsername.toLatin1()); multiPart->append(loginPart);
            /* password */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
            loginPart.setBody(connPassword.toLatin1()); multiPart->append(loginPart);
            /* action */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
            loginPart.setBody("getProjectList"); multiPart->append(loginPart);
            /* instance */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"instance\""));
            loginPart.setBody(ui->cmbInstanceID->currentData().toString().toLatin1()); multiPart->append(loginPart);

            QNetworkReply* reply = networkManager->post(request, multiPart);
            multiPart->setParent(reply); // delete the multiPart with the reply
            connect(reply, SIGNAL(finished()), this, SLOT(onGetReplyProjectList()));
            QApplication::restoreOverrideCursor();
        }
    }
}


/* ------------------------------------------------- */
/* --------- on_btnLoadSiteIDs_clicked ------------- */
/* ------------------------------------------------- */
void MainWindow::on_btnLoadSiteIDs_clicked()
{
    networkManager->setProxy(GetProxy());
    /* get list of instances through the API */

    if (ui->lstConn->count() < 1) {
        ShowMessageBox("No connections available");
    }
    else if (ui->lstConn->selectedItems().length() < 1) {
        ShowMessageBox("No connection selected");
    }
    else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        if (GetConnectionParms(connServer, connUsername, connPassword)) {
            QUrl url(connServer + "/api.php");
            QNetworkRequest request(url);
            QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            QHttpPart loginPart;
            /* username */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
            loginPart.setBody(connUsername.toLatin1()); multiPart->append(loginPart);
            /* password */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
            loginPart.setBody(connPassword.toLatin1()); multiPart->append(loginPart);
            /* action */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
            loginPart.setBody("getSiteList"); multiPart->append(loginPart);
            /* instance */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"instance\""));
            loginPart.setBody(ui->cmbInstanceID->currentData().toString().toLatin1()); multiPart->append(loginPart);

            QNetworkReply* reply = networkManager->post(request, multiPart);
            multiPart->setParent(reply); // delete the multiPart with the reply
            connect(reply, SIGNAL(finished()), this, SLOT(onGetReplySiteList()));
            QApplication::restoreOverrideCursor();
        }
    }
}


/* ------------------------------------------------- */
/* --------- on_btnLoadEquipmentIDs_clicked -------- */
/* ------------------------------------------------- */
void MainWindow::on_btnLoadEquipmentIDs_clicked()
{
    networkManager->setProxy(GetProxy());
    /* get list of instances through the API */

    if (ui->lstConn->count() < 1) {
        ShowMessageBox("No connections available");
    }
    else if (ui->lstConn->selectedItems().length() < 1) {
        ShowMessageBox("No connection selected");
    }
    else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        if (GetConnectionParms(connServer, connUsername, connPassword)) {
            QUrl url(connServer + "/api.php");
            QNetworkRequest request(url);
            QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            QHttpPart loginPart;
            /* username */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
            loginPart.setBody(connUsername.toLatin1()); multiPart->append(loginPart);
            /* password */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
            loginPart.setBody(connPassword.toLatin1()); multiPart->append(loginPart);
            /* action */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
            loginPart.setBody("getEquipmentList"); multiPart->append(loginPart);

            QNetworkReply* reply = networkManager->post(request, multiPart);
            multiPart->setParent(reply); // delete the multiPart with the reply
            connect(reply, SIGNAL(finished()), this, SLOT(onGetReplyEquipmentList()));
            QApplication::restoreOverrideCursor();
        }
    }

}


/* ------------------------------------------------- */
/* --------- onGetReplyInstanceList ---------------- */
/* ------------------------------------------------- */
void MainWindow::onGetReplyInstanceList()
{
    //qDebug() << "numNetConn (A): " << numNetConn;
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) { response = tr("No instances available"); }

    QStringList listItems;
    ui->cmbInstanceID->clear();
    listItems << response.split(",");

    for (int i=0; i<listItems.size(); i++) {
        QStringList parts;
        parts << listItems[i].split("|");
        if (parts.length() > 1) {
            ui->cmbInstanceID->addItem(QString(parts[0] + " - " + parts[1]), parts[0]);
        }
        else {
            ui->cmbInstanceID->addItem(parts[0], parts[0]);
        }
    }
}


/* ------------------------------------------------- */
/* --------- onGetReplyProjectList ----------------- */
/* ------------------------------------------------- */
void MainWindow::onGetReplyProjectList()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) { response = tr("No projects within this instance"); }

    /* parse the returned string and populate the drop down menu */
    QStringList listItems;
    ui->cmbProjectID->clear();
    listItems << response.split(",");

    for (int i=0; i<listItems.size(); i++) {
        QStringList parts;
        parts << listItems[i].split("|");
        if (parts.length() > 1) {
            ui->cmbProjectID->addItem(QString(parts[0] + " - " + parts[1]), parts[0]);
        }
        else {
            ui->cmbProjectID->addItem(parts[0], parts[0]);
        }
    }
}


/* ------------------------------------------------- */
/* --------- onGetReplySiteList -------------------- */
/* ------------------------------------------------- */
void MainWindow::onGetReplySiteList()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) { response = tr("No sites available"); }

    /* parse the returned string and populate the drop down menu */
    QStringList listItems;
    ui->cmbSiteID->clear();
    listItems << response.split(",");

    for (int i=0; i<listItems.size(); i++) {
        QStringList parts;
        parts << listItems[i].split("|");
        if (parts.length() > 1) {
            ui->cmbSiteID->addItem(QString(parts[0] + " - " + parts[1]), parts[0]);
        }
        else {
            ui->cmbSiteID->addItem(parts[0], parts[0]);
        }
    }
}


/* ------------------------------------------------- */
/* --------- onGetReplyEquipmentList --------------- */
/* ------------------------------------------------- */
void MainWindow::onGetReplyEquipmentList()
{
    //qDebug() << "numNetConn (A): " << numNetConn;
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) { response = tr("No equipment available"); }
    WriteLog(response);

    /* parse the returned string and populate the drop down menu */
    QStringList listItems;
    ui->cmbEquipmentID->clear();
    listItems << response.split(",");

    for (int i=0; i<listItems.size(); i++) {
        QStringList parts;
        parts << listItems[i].split("|");
        if (parts.length() > 1) {
            ui->cmbEquipmentID->addItem(QString(parts[0] + " - " + parts[1]), parts[0]);
        }
        else {
            ui->cmbEquipmentID->addItem(parts[0], parts[0]);
        }
    }
}


/* ------------------------------------------------- */
/* --------- StartTransaction ---------------------- */
/* ------------------------------------------------- */
void MainWindow::StartTransaction()
{
    WriteLog("Entering StartTransaction()");
    networkManager->setProxy(GetProxy());
    /* get list of instances through the API */

    transactionNumber = 0;

    if (ui->lstConn->count() < 1) {
        ShowMessageBox("No connections available");
    }
    else if (ui->lstConn->selectedItems().length() < 1) {
        ShowMessageBox("No connection selected");
    }
    else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        if (GetConnectionParms(connServer, connUsername, connPassword)) {
            QUrl url(connServer + "/api.php");
            QNetworkRequest request(url);
            QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            QHttpPart loginPart;
            /* username */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
            loginPart.setBody(connUsername.toLatin1()); multiPart->append(loginPart);
            /* password */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
            loginPart.setBody(connPassword.toLatin1()); multiPart->append(loginPart);
            /* action */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
            loginPart.setBody("startTransaction"); multiPart->append(loginPart);

            QNetworkReply* reply = networkManager->post(request, multiPart);
            multiPart->setParent(reply); // delete the multiPart with the reply
            connect(reply, SIGNAL(finished()), this, SLOT(onGetReplyStartTransaction()));
            QApplication::restoreOverrideCursor();
        }
    }
    WriteLog("Leaving StartTransaction()");
}


/* ------------------------------------------------- */
/* --------- onGetReplyStartTransaction ------------ */
/* ------------------------------------------------- */
void MainWindow::onGetReplyStartTransaction()
{
    //qDebug() << "numNetConn (A): " << numNetConn;
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) { response = tr("Did not get a transaction number"); }
    else {
        transactionNumber = response.trimmed().toInt();
    }
    if (transactionNumber < 0) {
        WriteLog("transaction number was negative");
    }
    WriteLog("The following is the response from the starttransaction thing");
    WriteLog(response);
}


/* ------------------------------------------------- */
/* --------- EndTransaction ------------------------ */
/* ------------------------------------------------- */
void MainWindow::EndTransaction()
{
    networkManager->setProxy(GetProxy());
    /* get list of instances through the API */

    if (ui->lstConn->count() < 1) {
        ShowMessageBox("No connections available");
    }
    else if (ui->lstConn->selectedItems().length() < 1) {
        ShowMessageBox("No connection selected");
    }
    else {
        QApplication::setOverrideCursor(Qt::WaitCursor);
        if (GetConnectionParms(connServer, connUsername, connPassword)) {
            QUrl url(connServer + "/api.php");
            QNetworkRequest request(url);
            QHttpMultiPart *multiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);
            QHttpPart loginPart;
            /* username */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"u\""));
            loginPart.setBody(connUsername.toLatin1()); multiPart->append(loginPart);
            /* password */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"p\""));
            loginPart.setBody(connPassword.toLatin1()); multiPart->append(loginPart);
            /* action */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"action\""));
            loginPart.setBody("endTransaction"); multiPart->append(loginPart);
            /* transaction number */
            loginPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"transactionid\""));
            loginPart.setBody(QString::number(transactionNumber).toLatin1()); multiPart->append(loginPart);

            QNetworkReply* reply = networkManager->post(request, multiPart);
            multiPart->setParent(reply); // delete the multiPart with the reply
            connect(reply, SIGNAL(finished()), this, SLOT(onGetReplyEndTransaction()));
            QApplication::restoreOverrideCursor();
        }
    }
}


/* ------------------------------------------------- */
/* --------- onGetReplyEndTransaction ------------ */
/* ------------------------------------------------- */
void MainWindow::onGetReplyEndTransaction()
{
    //qDebug() << "numNetConn (A): " << numNetConn;
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(sender());

    QString response;
    if (reply) {
        if (reply->error() == QNetworkReply::NoError) {
            const int available = reply->bytesAvailable();
            if (available > 0) {
                const QByteArray buffer(reply->readAll());
                response = QString::fromUtf8(buffer);
            }
        } else {
            response = tr("Error: %1 status: %2").arg(reply->errorString(), reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toString());
        }
        reply->deleteLater();
    }

    if (response.trimmed().isEmpty()) { response = tr("No equipment available"); }
    WriteLog(response);

}


/* ------------------------------------------------- */
/* --------- on_cmbInstanceID_currentIndexChanged -- */
/* ------------------------------------------------- */
void MainWindow::on_cmbInstanceID_currentIndexChanged(int index)
{
    index;
    on_btnLoadProjectIDs_clicked();
}


/* ------------------------------------------------- */
/* --------- ShowMessageBox ------------------------ */
/* ------------------------------------------------- */
void MainWindow::ShowMessageBox(QString msg) {
    QMessageBox msgBox;
    msgBox.setText(msg);
    msgBox.exec();
}


/* ------------------------------------------------- */
/* --------- timeConversion ------------------------ */
/* ------------------------------------------------- */
QString MainWindow::timeConversion(int msecs)
{
    QString formattedTime;

    int hours = msecs/(1000*60*60);
    int minutes = (msecs-(hours*1000*60*60))/(1000*60);
    int seconds = (msecs-(minutes*1000*60)-(hours*1000*60*60))/1000;
    int milliseconds = msecs-(seconds*1000)-(minutes*1000*60)-(hours*1000*60*60);

    formattedTime.append(QString("%1").arg(hours, 2, 10, QLatin1Char('0')) + ":" +
                         QString( "%1" ).arg(minutes, 2, 10, QLatin1Char('0')) + ":" +
                         QString( "%1" ).arg(seconds, 2, 10, QLatin1Char('0')) + ":" +
                         QString( "%1" ).arg(milliseconds, 3, 10, QLatin1Char('0')));

    return formattedTime;
}


/* ------------------------------------------------- */
/* --------- humanReadableSize --------------------- */
/* ------------------------------------------------- */
QString MainWindow::humanReadableSize(quint64 intSize)
{
    QString unit;
    double size;
    if (intSize < 1024 * 1024) {
        size = 1. + intSize / 1024.;
        unit = QObject::tr("kB");
    } else if (intSize < 1024 * 1024 * 1024) {
        size = 1. + intSize / 1024. / 1024.;
        unit = QObject::tr("MB");
    } else {
        size = 1. + intSize / 1024. / 1024. / 1024.;
        unit = QObject::tr("GB");
    }
    size = qRound(size * 10) / 10.0;
    return QString::fromLatin1("%L1 %2").arg(size, 0, 'g', 4).arg(unit);
}


/* ------------------------------------------------- */
/* --------- on_btnRemoveSelected_clicked ---------- */
/* ------------------------------------------------- */
void MainWindow::on_btnRemoveSelected_clicked()
{

    QSet<int> selectedRows; //we use a set to prevent doubles
    QList<QTableWidgetItem*> itemList = ui->tableFiles->selectedItems();
    QTableWidgetItem * item;
    foreach(item, itemList)
        selectedRows.insert(item->row());

    /* get a list, and sort it big to small */
    QList<int> rows = selectedRows.toList();
    qSort(rows.begin(), rows.end(), qGreater<int>());

    /* now actually do the removing */
    foreach(int row, rows)
        ui->tableFiles->removeRow(row);
}


/* ------------------------------------------------- */
/* --------- GetProxy ------------------------------ */
/* ------------------------------------------------- */
QNetworkProxy MainWindow::GetProxy()
{
    QNetworkProxy proxy;
    if (ui->chkUseProxy->isChecked()) {
        QVariant proxyType = ui->cmbProxyType->currentData();

        if (proxyType == "") { proxy.setType(QNetworkProxy::NoProxy); }
        if (proxyType == "default") { proxy.setType(QNetworkProxy::DefaultProxy); }
        if (proxyType == "socks5") { proxy.setType(QNetworkProxy::Socks5Proxy); }
        if (proxyType == "http") { proxy.setType(QNetworkProxy::HttpProxy); }
        if (proxyType == "httpcaching") { proxy.setType(QNetworkProxy::HttpCachingProxy); }
        if (proxyType == "ftpcaching") { proxy.setType(QNetworkProxy::FtpCachingProxy); }

        proxy.setHostName(ui->proxyHostname->text());
        proxy.setPort(ui->proxyPort->value());
        proxy.setUser(ui->proxyUsername->text());
        proxy.setPassword(ui->proxyPassword->text());
    }
    else {
        proxy.setType(QNetworkProxy::NoProxy);
    }
    return proxy;
}


/* ------------------------------------------------- */
/* --------- WriteLog ------------------------------ */
/* ------------------------------------------------- */
QByteArray MainWindow::GetFileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm)
{
    QFile f(fileName);
    if (f.open(QFile::ReadOnly)) {
        QCryptographicHash hash(hashAlgorithm);
        if (hash.addData(&f)) {
            return hash.result().toHex();
        }
    }
    return QByteArray();
}


/* ------------------------------------------------- */
/* --------- WriteLog ------------------------------ */
/* ------------------------------------------------- */
void MainWindow::WriteLog(QString msg)
{
    /* print to file and to the log window */
    QTextStream out(&logfile);
    out << "[" << QTime::currentTime().toString() << "] " << msg << endl;
    qDebug() << msg;
}


/* ------------------------------------------------- */
/* --------- fileExists ---------------------------- */
/* ------------------------------------------------- */
bool MainWindow::fileExists(QString path) {
    QFileInfo checkFile(path);
    // check if file exists and if yes: Is it really a file and no directory?
    if (checkFile.exists() && checkFile.isFile()) {
        return true;
    } else {
        return false;
    }
}


/* ------------------------------------------------- */
/* --------- on_btnResendFailedObjects_clicked ----- */
/* ------------------------------------------------- */
void MainWindow::on_btnResendFailedObjects_clicked()
{
    DoUpload(false);
}
