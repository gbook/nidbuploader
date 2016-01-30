#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFile>
#include <QTextStream>
#include <QListWidget>
#include <QMessageBox>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QFileDialog>
#include <QDirIterator>
#include <QProgressDialog>
#include <QCryptographicHash>
#include <QHttpMultiPart>
#include "gdcmReader.h"
#include "gdcmWriter.h"
#include "gdcmAttribute.h"
#include "gdcmStringFilter.h"
#include "gdcmAnonymizer.h"
#include <QTest>
#include <QSignalMapper>
#include <QDateTime>
#include <QNetworkProxy>

#ifdef _WIN32_
    #include <cstdlib>
#elif __linux
    #include <unistd.h>
#endif

/* this supposedly will make the program run on WinXP */
//#include <QtPlugin>
//Q_IMPORT_PLUGIN (QWindowsIntegrationPlugin)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void SetBuildDate();
    void PopulateModality();

    void PopulateConnectionList();
    void scanDirIter(QDir dir);
    void GetFileType(QString f, QString &fileType, QString &fileModality, QString &filePatientID);
    bool GetConnectionParms(QString &s, QString &u, QString &p);
    QString GetDicomModality(QString f);
    bool AddFoundFile(QDirIterator *it, QString f, QString fType, QString modality, QString filePatientID);
    QString GenerateRandomString(int len);
    void AnonymizeAndUpload(QVector<int> list, bool isDICOM, bool isPARREC);
    bool AnonymizeOneFileDumb(gdcm::Anonymizer &anon, const char *filename, const char *outfilename, std::vector<gdcm::Tag> const &empty_tags, std::vector<gdcm::Tag> const &remove_tags, std::vector< std::pair<gdcm::Tag, std::string> > const & replace_tags, bool continuemode = false);
    int UploadFileList(QStringList list, QStringList md5list);
    void SetTempDir();
    void ShowMessageBox(QString msg);
    QString timeConversion(int msecs);
    QString humanReadableSize(quint64 intSize);
    QByteArray GetFileChecksum(const QString &fileName, QCryptographicHash::Algorithm hashAlgorithm);
    bool fileExists(QString path);

    void StartTransaction();
    void EndTransaction();

    QNetworkProxy GetProxy();
    void WriteLog(QString msg);

    QNetworkAccessManager *networkManager;

    QVector<int> lastUploadList;

    QString connServer;
    QString connUsername;
    QString connPassword;

    QStringList files;

    int totalUploaded;

    int numNetConn;
    bool isUploading;

    QDateTime startFileSearchTime;
    QTime elapsedFileSearchTime;
    int numFilesFound;
    qint64 numBytesFound;

    QDateTime startUploadTime;
    QTime uploadTime;
    QTime elapsedUploadTime;
    int numAnonErrors;
    qint64 numBytesSentSuccess;
    qint64 numBytesSentFail;
    qint64 numBytesSentTotal;
    qint64 numFilesSentSuccess;
    qint64 numFilesSentFail;
    qint64 numFilesSentTotal;
    int numBytesLastSend; /* number of bytes sent in last upload attempt */
    int numFilesLastSend; /* number of files sent in last upload attempt */

    int transactionNumber; /* the transaction number to use during the current upload */

    QFile logfile; /* the logfile */
    QFile idfile; /* the file containing IDs */

private slots:
    void progressChanged(qint64 a, qint64 b);

    //void uploadError(QNetworkReply::NetworkError err);

    void on_btnExit_clicked();

    void on_pushButton_clicked();

    void on_btnTestConn_clicked();

    void onGetReply();
    void onGetReplyUpload();
    void onNetworkError(QNetworkReply::NetworkError networkError);

    void onGetReplyInstanceList();
    void onGetReplyProjectList();
    void onGetReplySiteList();
    void onGetReplyEquipmentList();
    void onGetReplyStartTransaction();
    void onGetReplyEndTransaction();

    void on_btnSelectDataDir_clicked();

    void on_btnSearch_clicked();

    void on_btnTmpDir_clicked();

    void on_btnUploadAll_clicked();

    void on_chkReplacePatientName_clicked();

    void on_chkReplacePatientID_clicked();

    void on_chkReplacePatientBirthDate_clicked();

    void on_chkRemovePatientBirthDate_clicked();

    void on_lstConn_clicked(const QModelIndex &index);

    void on_btnRemoveConn_clicked();

    void on_btnLoadInstanceIDs_clicked();

    void on_btnLoadProjectIDs_clicked();

    void on_btnLoadSiteIDs_clicked();

    void on_cmbInstanceID_currentIndexChanged(int index);

    void on_btnRemoveSelected_clicked();

    void on_btnLoadEquipmentIDs_clicked();

    void on_chkUseProxy_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
