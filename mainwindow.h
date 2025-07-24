#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDebug>
#include <QtWidgets>
#include <QMessageBox>
#include <QFile>
#include <QEventLoop>

#include <regex>                        // IWYU pragma: export
#include <sstream>                      // IWYU pragma: export
#include <curl/curl.h>

#include "globals.h"                    // IWYU pragma: export
#include "configForm.h"
#include "checkTorConnection.h"         // IWYU pragma: export
#include "r34Downloader.h"              // IWYU pragma: export
#include "animePicturesDownloader.h"
#include "danbooruDownloader.h"
#include "isNum.hpp"                    // IWYU pragma: export
#include "sanitizeTags.h"               // IWYU pragma: export
#include "servicesEnums.h"              // IWYU pragma: export
#include "gelbooruDownloader.h"
#include "smtgDownloader.h"             // IWYU pragma: export
#include "yandereDownloader.h"
#include "saveGlobals.h"                // IWYU pragma: export
#include "globals.h"
#include "curlDownloadToStringBuffer.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void rejectForm(ConfigForm* cfgFrm);
    void acceptForm(ConfigForm* cfgFrm);

    void resetConsoleText();

private slots:
    void on_sendPushButton_clicked();

    void on_chooseServiceComboBox_currentIndexChanged(int index);

    void on_tagsLineEdit_returnPressed();

    void on_pagesLineEdit_returnPressed();

    void on_numLineEdit_returnPressed();

    void on_CFG_button_clicked();
private:
    Ui::MainWindow *ui;
    QString tags = "";
    QString basePath = "";
    QString filePath = "";
    int selected;
};

#endif // MAINWINDOW_H
