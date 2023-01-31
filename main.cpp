#include <QApplication>
#include <QFile>

#include <iostream>

#include "mainwindow.h"
#include "initGlobals.h"

int main(int argc, char *argv[])
{
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
