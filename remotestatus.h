#ifndef REMOTESTATUS_H
#define REMOTESTATUS_H
#include "mainwindow.h"

#include <QDialog>
#include <QFile>

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

private:
    Ui::RemoteStatus *ui;
};

#endif // REMOTESTATUS_H
