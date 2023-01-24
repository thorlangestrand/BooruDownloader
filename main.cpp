#include <QApplication>
#include <QFile>

#include <iostream>

#include "mainwindow.h"
#include "initGlobals.h"

int main(int argc, char *argv[])
{
    // Initialize globals
    // Globals are saved at C:\users\[user]\appdata\local\scuffdownloader\config.scuff
    QApplication a(argc, argv);
    if (!initGlobals())
    {
        Warn("Failed to initialize globals, exiting...");
        return 1;
    }

    // Stylesheet
    QFile styleSheetFile(":/stylesheets/stylesheets/ManjaroMix.qss");
    styleSheetFile.open(QFile::ReadOnly);
    QString styleSheet = QLatin1String(styleSheetFile.readAll());
    a.setStyleSheet(styleSheet);
    MainWindow w;
    w.show();
    return a.exec();
}
