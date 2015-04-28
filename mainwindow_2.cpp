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

    #ifdef W_OS_WIN32
        ui->txtTmpDir->setText("C:/temp");
    #elifdef W_OS_LINUX
        ui->txtTmpDir->setText("/tmp");
    #endif

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
            }

            reply->deleteLater();
        }

        if (response.trimmed().isEmpty()) {
            response = tr("Unable to retrieve post response");
        }

        qDebug() << "OnGetReply(" << response << ")";
        //QMessageBox msg;
        //msg.setText(response);
        //msg.exec();
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
            qDebug() << fileList.length();
            AnonymizeAndUpload(fileList, isDICOM, tmpDir);
            /* clear the list */
            fileList.clear();
        }

        qApp->processEvents();
    }
    /* anonymize and upload the remaining files */
    AnonymizeAndUpload(fileList, isDICOM, tmpDir);

    /* delete the temp directory */
    if (tmpDir != "") {
        QDir dir(tmpDir);
        dir.removeRecursively();
    }

    QApplication::restoreOverrideCursor();
}


/* ------------------------------------------------- */
/* --------- AnonymizeAndUpload -------------------- */
/* ------------------------------------------------- */
void MainWindow::AnonymizeAndUpload(QVector<int> list, bool isDICOM, QString tmpDir)
{
    QStringList uploadList;

    qDebug("in AnonymizeAndUpload: got list of size %d", list.size());

    /* loop through the list of table row numbers, and try to anonymize (if DICOM) and then upload the file */
    for (int i=0; i< list.size(); i++) {
        QString f = ui->tableFiles->item(i,0)->text();
        QString newFilePath;

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
        qDebug("Inside AnonymizeAndUpload loop [%d]",i);

        if (isDICOM) {
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

                QByteArray hash = QCryptographicHash::hash(tagVal.toUtf8(), QCryptographicHash::Sha1);
                QString newTagVal = hash.toHex().toUpper();
                //qDebug("Replacing %s with %s",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());

                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0010");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );
            }

            /* check if the patient ID should be replaced */
            if (ui->chkReplacePatientID->isChecked()) {
                std::string s = sf.ToString(gdcm::Tag(0x0010,0x0020));
                QString tagVal = s.c_str();
                tagVal = tagVal.trimmed();

                QByteArray hash = QCryptographicHash::hash(tagVal.toUtf8(), QCryptographicHash::Sha1);
                QString newTagVal = hash.toHex().toUpper();

                //qDebug("Replacing %s with %s",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());

                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0020");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );
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

                //qDebug("Replacing %s with %s",tagVal.toStdString().c_str(),newTagVal.toStdString().c_str());

                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0030");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );
            }

            /* check if the patient birthdate should be removed */
            if (ui->chkRemovePatientBirthDate->isChecked()) {
                //gdcm::Attribute<0x0010,0x0030> tag;
                //tag.SetValue("0000-00-00");
                QString newTagVal = "0000-00-00";

                //qDebug("Removed birthdate");

                gdcm::Tag tag;
                tag.ReadFromCommaSeparatedString("0010,0030");
                replace_tags_value.push_back( std::make_pair(tag, newTagVal.toStdString().c_str()) );
            }

            ui->tableFiles->setCurrentCell(i,0);
            //ui->tableFiles->scrollTo(i);
            gdcm::Anonymizer anon;
            if (AnonymizeOneFileDumb(anon,newFilePath.toStdString().c_str(),newFilePath.toStdString().c_str(),empty_tags,remove_tags,replace_tags_value,false)) {
                ui->tableFiles->setItem(i,1,new QTableWidgetItem("Anonymized"));
            }
            else {
                ui->tableFiles->setItem(i,1,new QTableWidgetItem("Anon - Error"));
            }
        }
    }

    /* go through the list of files to be uploaded, and upload them as one big batch */
    UploadFileList(uploadList);
}


/* ------------------------------------------------- */
/* --------- AnonymizeOneFileDumb ------------------ */
/* ------------------------------------------------- */
/* borrowed from gdcmanon.cxx                        */
bool MainWindow::AnonymizeOneFileDumb(gdcm::Anonymizer &anon, const char *filename, const char *outfilename, std::vector<gdcm::Tag> const &empty_tags, std::vector<gdcm::Tag> const &remove_tags, std::vector< std::pair<gdcm::Tag, std::string> > const & replace_tags, bool continuemode)
{

    qDebug("Anonymizing one file [%s]", filename);

    gdcm::Reader reader;
    reader.SetFileName( filename );
    if( !reader.Read() ) {
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
/* --------- UploadFileList ------------------------ */
/* ------------------------------------------------- */
QString MainWindow::UploadFileList(QStringList list)
{
    QStringList connItems;
    QString connStr;

    if (ui->lstConn->count() < 1) {
        return "Nothing to upload";
    }
    connStr = ui->lstConn->currentItem()->text();
    connItems << connStr.split(",");
    connServer = connItems[0];
    connUsername = connItems[1];
    connPassword = connItems[2];

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
    loginPart.setBody("UploadDICOM");
    multiPart->append(loginPart);

    /* loop through the list of files */
    for (int i=0;i<list.size();i++) {
        qDebug("UploadFileList [%d] [%s]", i, list[i].toStdString().c_str());
        QString filepath  = list[i];
        //QHttpPart previewPathPart;
        //previewPathPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"preview_path\""));
        //previewPathPart.setBody(preview_path.toLatin1());
        //multiPart->append(previewPathPart);
        //continue;
        //QString preview_name = "preview.jpg";

        QFile *file = new QFile(filepath);
        QHttpPart filePart;
        //filePart.setHeader(QNetworkRequest::ContentTypeHeader,    QVariant("image/jpeg"));
        filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"files[]\"; filename=\""+ file->fileName() + "\""));

        if (!file->exists()) {
            //emit error(tr("Upload Error. File does not exist: ") + preview_path);
            //return;
        }
        file->open(QIODevice::ReadOnly);
        filePart.setBodyDevice(file);
        file->setParent(multiPart); // we cannot delete the file now, so delete it with the multiPart

        multiPart->append(filePart);
    }

    QNetworkAccessManager *networkManager = new QNetworkAccessManager(this);
    QNetworkReply* reply = networkManager->post(request, multiPart);
    multiPart->setParent(reply); // delete the multiPart with the reply
    connect(reply, SIGNAL(finished()), this, SLOT(onGetReply()));
    //connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT  (uploadError(QNetworkReply::NetworkError)));
    connect(reply, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT  (uploadProgress(qint64, qint64)));

    //while (reply->isRunning()) {
    //}
    return "hi";
}


void MainWindow::uploadProgress(qint64 a, qint64 b)
{
    qDebug() << "Uploading " << a  << "/" << b << "%" << (double)a/(double)b*100.0;
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
