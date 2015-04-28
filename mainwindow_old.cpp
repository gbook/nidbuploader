#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->showMaximized();
    qsrand(QTime::currentTime().msec());

    PopulateModality();
    PopulateConnectionList();

}

MainWindow::~MainWindow()
{
    delete ui;
}


/* ------------------------------------------------- */
/* --------- PopulateModality ---------------------- */
/* ------------------------------------------------- */
void MainWindow::PopulateModality() {
    ui->cmbModality->addItem("All DICOM", "DICOM");
    ui->cmbModality->addItem("MR","MR");
    ui->cmbModality->addItem("CT","CT");
    ui->cmbModality->addItem("PET","PET");
    ui->cmbModality->addItem("SPECT","SPECT");
    ui->cmbModality->addItem("EEG (.cnt)", "EEG");
    ui->cmbModality->addItem("Eye Tracking", "ET");
    ui->cmbModality->addItem("VIDEO (.wmv .avi .mpg .mpeg .mp4 .mkv)", "VIDEO");
}


/* ------------------------------------------------- */
/* --------- PopulateConnectionList ---------------- */
/* ------------------------------------------------- */
void MainWindow::PopulateConnectionList(){
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
    QString server = ui->txtServer->text();
    QString username = ui->txtUsername->text();
    QString password = ui->txtPassword->text();

    QFile file("connections.txt");
    file.open(QIODevice::Append | QIODevice::Text);
    QTextStream out(&file);
    out << server << "\t" << username << "\t" << password << endl;
    file.close();

    PopulateConnectionList();

}


/* ------------------------------------------------- */
/* --------- on_btnTestConn_clicked ---------------- */
/* ------------------------------------------------- */
void MainWindow::on_btnTestConn_clicked()
{
    QStringList connItems;
    QString connStr;

    if (ui->lstConn->count() < 1) {
        return;
    }
    connStr = ui->lstConn->currentItem()->text();
    connItems << connStr.split(",");
    connServer = connItems[0];
    connUsername = connItems[1];
    connPassword = connItems[2];

    /* set the hourglass cursor */
    QApplication::setOverrideCursor(Qt::WaitCursor);

    QUrl url;
    QByteArray postData;

    url.setUrl(connServer + "/api.php");
    QNetworkRequest request(url);
    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");

    postData.append('u').append("=").append(connUsername).append("&");
    postData.append('p').append("=").append(connPassword);

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    //networkManager.post(request,postData);
    //connect(networkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(serviceRequestFinished(QNetworkReply*)));
    QNetworkReply* reply = networkManager->post(request, postData);
    bool ok = connect(reply, SIGNAL(finished()), this, SLOT(onGetReply()));

    /* restore the regular cursor */
    QApplication::restoreOverrideCursor();
}


/* ------------------------------------------------- */
/* --------- onGetReply ---------------------------- */
/* ------------------------------------------------- */
void MainWindow::onGetReply()
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
                qDebug() << response;
            }

            reply->deleteLater();
        }

        if (response.trimmed().isEmpty()) {
            response = tr("Unable to retrieve post response");
        }

        QMessageBox msg;
        msg.setText(response);
        msg.exec();
        //emit complete(response);
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
    scanDirIter(QDir(ui->txtDataDir->text()));
    QApplication::restoreOverrideCursor();
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

    //QProgressDialog progress("Scanning for files...", "Cancel", 0, 100, this);
    //progress.setWindowModality(Qt::WindowModal);

    //int numFiles = 0;
    //bool getFileModality = false;
    //if (ui->chkGetModality->isChecked()) {
    //    getFileModality = true;
    //}

    /* iterate through all files */
    while (iterator.hasNext()) {
        iterator.next();
        if (!iterator.fileInfo().isDir()) {
            //QElapsedTimer timer;
            //timer.start();
            //QString filename = iterator.fileName();
            //qDebug() << filename;
            fullfile = iterator.filePath();
            //qDebug() << fullfile;
            /* check the file type */
            GetFileType(fullfile, fileType, fileModality, filePatientID);
            if (fileType == "DICOM") {
                //fileModality = "";
                //if (getFileModality)
                //    fileModality = GetDicomModality(fullfile);

                if (modality == "DICOM") {
                    AddFoundFile(&iterator,fullfile,fileType,fileModality, filePatientID);
                }
                else {
                    //fileModality = GetDicomModality(fullfile);
                    if (modality == fileModality) {
                        AddFoundFile(&iterator,fullfile,fileType,modality.toString(), filePatientID);
                    }
                }
            }
        }
    }
    //progress.setValue(100);
}


/* ------------------------------------------------- */
/* --------- GetFileType --------------------------- */
/* ------------------------------------------------- */
void MainWindow::GetFileType(QString f, QString &fileType, QString &fileModality, QString &filePatientID)
{
    fileModality = QString("");
    //qDebug("%s",f.toStdString().c_str());
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
        //QFile file(f);
        //file.open(QIODevice::ReadOnly);
        //qDebug("%s",file.errorString().toStdString().c_str());
        //qDebug("[%s] is not a DICOM file",f.toStdString().c_str());
        if (f.endsWith(".cnt")) {
            fileType = "EEG";
        }
        else {
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
    qint64 size;
    QString sSize, cDate;
    QFileInfo info;

    files << f;
    info = it->fileInfo();
    size = info.size();
    cDate = info.created().toString();
    sSize = QString::number(size/1024) + " kB";

    const int currentRow = ui->tableFiles->rowCount();
    ui->tableFiles->setRowCount(currentRow + 1);

    ui->tableFiles->setItem(currentRow, 0, new QTableWidgetItem(f));
    ui->tableFiles->setItem(currentRow, 1, new QTableWidgetItem("readable"));
    ui->tableFiles->setItem(currentRow, 2, new QTableWidgetItem(fType));
    ui->tableFiles->setItem(currentRow, 3, new QTableWidgetItem(modality));
    ui->tableFiles->setItem(currentRow, 4, new QTableWidgetItem(filePatientID));
    ui->tableFiles->setItem(currentRow, 5, new QTableWidgetItem(cDate));
    ui->tableFiles->setItem(currentRow, 6, new QTableWidgetItem(sSize));

    ui->lblFileCount->setText(QString("Found %1 files").arg(ui->tableFiles->rowCount()));
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
    QApplication::setOverrideCursor(Qt::WaitCursor);
    QString modality = ui->cmbModality->currentData().toString();
    QString tmpDir = "";
    bool isDICOM = false;

    /* if its a DICOM file, create a tmp directory to anonymize it */
    if ((modality == "DICOM") || (modality == "MR") || (modality == "CT") || (modality == "PET") || (modality == "SPECT") || (modality == "US")) {
        isDICOM = true;
        /* create a temp directory */
        tmpDir = ui->txtTmpDir->text() + "/" + GenerateRandomString(15);
        QDir dir;
        dir.mkpath(tmpDir);
        qDebug("Creating tmpDir [%s]", tmpDir.toStdString().c_str());
    }

    QVector<int> fileList;

    /* this will anonymize and then upload all of the files in the list */
    int rowCount = ui->tableFiles->rowCount();
    for (int i=0; i<rowCount; i++){

        /* add this item to the list */
        fileList.append(i);

        if (fileList.length() >= 100) {
            AnonymizeAndUpload(fileList, isDICOM, tmpDir);
            /* clear the list */
            fileList.empty();
        }

        qApp->processEvents();
    }
    /* anonymize and upload the remaining files */
    AnonymizeAndUpload(fileList, isDICOM, tmpDir);

    /* delete the temp directory */
    if (tmpDir != "") {
        //QDir dir(tmpDir);
        //dir.removeRecursively();
    }

    QApplication::restoreOverrideCursor();
}


/* ------------------------------------------------- */
/* --------- AnonymizeAndUpload -------------------- */
/* ------------------------------------------------- */
void MainWindow::AnonymizeAndUpload(QVector<int> list, bool isDICOM, QString tmpDir)
{
    QStringList uploadList;

    /* loop through the list of table row numbers, and try to anonymize (if DICOM) and then upload the file */
    for (int i=0; i< list.size(); i++) {
        QString f = ui->tableFiles->item(i,0)->text();
        QString newFilePath;
        bool success = true;

        if (isDICOM) {
            /* copy file to temp dir */
            newFilePath = tmpDir + "/" + GenerateRandomString(15) + ".dcm";
            QFile::copy(f,newFilePath);
            qDebug("Copying [%s] to [%s]", f.toStdString().c_str(), newFilePath.toStdString().c_str());
        }
        else {
            newFilePath = f;
        }

        /* add this filepath to the list of files to be uploaded */
        uploadList << newFilePath;

        ui->tableFiles->setCurrentCell(i,0);
        qDebug("0");

        if (isDICOM) {
            qDebug("1");
            gdcm::Reader r;
            r.SetFileName(newFilePath.toStdString().c_str());
            if (r.CanRead()) {
                qDebug("2");
                bool fileChanged = false;
                gdcm::File file;
                gdcm::StringFilter sf;
                gdcm::DataSet ds;
                qDebug("3");

                if ((ui->chkReplacePatientName->isChecked()) || (ui->chkReplacePatientID->isChecked()) || (ui->chkReplacePatientBirthDate->isChecked()) || (ui->chkRemovePatientBirthDate->isChecked())) {
                    r.Read();
                    sf = gdcm::StringFilter();
                    sf.SetFile(r.GetFile());
                    file = r.GetFile();
                    ds = file.GetDataSet();
                }
                qDebug("4");
                /* check if the patient name should be replaced */
                if (ui->chkReplacePatientName->isChecked()) {
                    std::string s = sf.ToString(gdcm::Tag(0x0010,0x0010));
                    QString tagVal = s.c_str();
                    tagVal = tagVal.trimmed();

                    QByteArray hash = QCryptographicHash::hash(tagVal.toUtf8(), QCryptographicHash::Sha1);
                    QString newTagVal = hash.toHex().toUpper();

                    // The output of gdcm::Reader is a gdcm::File
                    // Contruct a static(*) type for Image Comments :
                    gdcm::Attribute<0x0010,0x0010> tag;
                    tag.SetValue(newTagVal.toStdString().c_str());
                    // Now replace the Image Comments from the dataset with our:
                    ds.Replace( tag.GetAsDataElement() );
                    qDebug("Replacing %s with %s",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());
                    fileChanged = true;
                }
                qDebug("5");

                /* check if the patient ID should be replaced */
                if (ui->chkReplacePatientID->isChecked()) {
                    //gdcm::StringFilter sf;
                    //sf = gdcm::StringFilter();
                    //sf.SetFile(r.GetFile());
                    std::string s = sf.ToString(gdcm::Tag(0x0010,0x0020));
                    QString tagVal = s.c_str();
                    tagVal = tagVal.trimmed();

                    QByteArray hash = QCryptographicHash::hash(tagVal.toUtf8(), QCryptographicHash::Sha1);
                    QString newTagVal = hash.toHex().toUpper();

                    // The output of gdcm::Reader is a gdcm::File
                    //file = r.GetFile();
                    //gdcm::DataSet &ds = file.GetDataSet();
                    // Contruct a static(*) type for Image Comments :
                    gdcm::Attribute<0x0010,0x0020> tag;
                    tag.SetValue(newTagVal.toStdString().c_str());
                    // Now replace the Image Comments from the dataset with our:
                    ds.Replace( tag.GetAsDataElement() );
                    qDebug("Replacing %s with %s",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());
                    fileChanged = true;
                }

                qDebug("6");
                /* check if the patient birthdate should be replaced */
                if (ui->chkReplacePatientBirthDate->isChecked()) {
                    //gdcm::StringFilter sf;
                    //sf = gdcm::StringFilter();
                    //sf.SetFile(r.GetFile());
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

                    // The output of gdcm::Reader is a gdcm::File
                    //file = r.GetFile();
                    //gdcm::DataSet &ds = file.GetDataSet();
                    // Contruct a static(*) type for Image Comments :
                    gdcm::Attribute<0x0010,0x0030> tag;
                    tag.SetValue(newTagVal.toStdString().c_str());
                    // Now replace the Image Comments from the dataset with our:
                    ds.Replace( tag.GetAsDataElement() );
                    qDebug("Replacing %s with %s",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());
                    fileChanged = true;
                }
                qDebug("7");

                /* check if the patient birthdate should be removed */
                if (ui->chkRemovePatientBirthDate->isChecked()) {
                    //file = r.GetFile();
                    //gdcm::DataSet &ds = file.GetDataSet();
                    // Contruct a static(*) type for Image Comments :
                    gdcm::Attribute<0x0010,0x0020> tag;
                    tag.SetValue("0000-00-00");
                    // Now replace the Image Comments from the dataset with our:
                    ds.Replace( tag.GetAsDataElement() );
                    qDebug("Removed birthdate");
                    fileChanged = true;
                }
                qDebug("8");

                //if (1 == 2) {
                if (fileChanged) {
                    // Write the modified DataSet back to disk
                    qDebug("A");
                    gdcm::Writer writer;
                    qDebug("B");
                    writer.CheckFileMetaInformationOff(); // Do not attempt to reconstruct the file meta to preserve the file as close to the original as possible.
                    qDebug("C");
                    writer.SetFileName( QString(newFilePath + "b").toStdString().c_str() );
                    qDebug("D");
                    writer.SetFile( file );
                    qDebug("E");
                    if( !writer.Write() ) {
                        qDebug("F");
                        std::cerr << "Could not write: " << newFilePath.toStdString().c_str() << std::endl;
                        success = false;
                    }
                    qDebug("G");
                    ui->tableFiles->setItem(i,1,new QTableWidgetItem("anonymized"));
                    qDebug("H");
                }
                qDebug("9");
            } // end if isDICOM
            qDebug("10");

            /* go through the list of files to be uploaded, and upload them as one big batch */
        }
    }
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
