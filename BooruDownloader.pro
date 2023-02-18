QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17
# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

RC_FILE += uicon.rc

SOURCES += \
    animePicturesDownloader.cpp \
    checkTorConnection.cpp \
    configForm.cpp \
    createValidFilePath.cpp \
    curlDownloadToFilePointer.cpp \
    curlDownloadToStringBuffer.cpp \
    curlWriteFunctions.cpp \
    danbooruDownloader.cpp \
    gelbooruDownloader.cpp \
    initGlobals.cpp \
    isNum.cpp \
    json.cpp \
    main.cpp \
    mainwindow.cpp \
    networkConfigForm.cpp \
    r34Downloader.cpp \
    sanitizeTags.cpp \
    saveGlobals.cpp \
    semaphore.cpp \
    smtgDownloader.cpp \
    utf8_parse.cpp \
    warn.cpp

HEADERS += \
    animePicturesDownloader.h \
    checkTorConnection.h \
    configForm.h \
    curl/curl.h \
    curl/curlver.h \
    curl/easy.h \
    curl/mprintf.h \
    curl/multi.h \
    curl/options.h \
    curl/stdcheaders.h \
    curl/system.h \
    curl/typecheck-gcc.h \
    curl/urlapi.h \
    curlDownloadToFilePointer.h \
    curlDownloadToStringBuffer.h \
    curlWriteFunctions.h \
    danbooruDownloader.h \
    gelbooruDownloader.h \
    globals.h \
    initGlobals.h \
    isNum.hpp \
    json.h \
    json.h \
    json.h \
    mainwindow.h \
    networkConfigForm.h \
    r34Downloader.h \
    sanitizeTags.h \
    saveGlobals.h \
    semaphore.h \
    servicesEnums.h \
    smtgDownloader.h \
    utf8_parse.h \
    warn.h

FORMS += \
    mainwindow.ui

LIBS += -lole32 -luuid
# ole32 for the COM library; CoTaskMemFree
# uuid for libuuid;          knownfolders

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc \
    stylesheets.qrc

DISTFILES += \
    uicon.rc

# These paths will have to be updated for where you keep your .a files
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../lib/curl/x64_mingw/ -lcurl
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../lib/curl/x64_mingw/ -lcurl
else:unix: LIBS += -L$$PWD/../../lib/curl/x64_mingw/ -lcurl

INCLUDEPATH += $$PWD/../../lib/curl/x64_mingw
DEPENDPATH += $$PWD/../../lib/curl/x64_mingw
