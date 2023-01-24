#ifndef NETWORKCONFIGFORM_H
#define NETWORKCONFIGFORM_H

#include <QDialog>
#include <QLabel>
#include <QComboBox>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QGridLayout>
#include <QMessageBox>
#include <QIcon>
#include <QFile>
#include <QFileDialog>
#include <QDir>
#include <QMainWindow>
#include <QPushButton>
#include <QCheckBox>

#include <vector>
#include <string.h>

#include "globals.h"

class ConfigForm;
class networkConfigForm : public QDialog {
public:
    explicit networkConfigForm(ConfigForm* parent);
    ~networkConfigForm();


    // Labels
    QLabel* gelbooruIPLabel =               nullptr;
    QLabel* gelbooruIMG3IPLabel =           nullptr;
    QLabel* gelbooruVIDIPLabel =            nullptr;
    QLabel* danbooruIPLabel =               nullptr;
    QLabel* danbooruCDNIPLabel =            nullptr;
    QLabel* r34IPLabel =                    nullptr;
    QLabel* r34WIMGIPLabel =                nullptr;
    QLabel* animePicturesIPLabel =          nullptr;
    QLabel* animePicturesIMGIPLabel =       nullptr;
    QLabel* smtgBooruIPLabel =              nullptr;

    QLabel* gelbooruDNSLabel =              nullptr;
    QLabel* gelbooruIMG3DNSLabel =          nullptr;
    QLabel* gelbooruVIDDNSLabel =           nullptr;
    QLabel* danbooruDNSLabel =              nullptr;
    QLabel* danbooruCDNDNSLabel =           nullptr;
    QLabel* r34DNSLabel =                   nullptr;
    QLabel* r34WIMGDNSLabel =               nullptr;
    QLabel* animePicturesDNSLabel =         nullptr;
    QLabel* animePicturesIMGDNSLabel =      nullptr;
    QLabel* smtgBooruDNSLabel =             nullptr;

    QLabel* curlUserAgentLabel =            nullptr;


    QLabel* sslCertificateLabel =           nullptr;
    QLabel* torProxyLabel =                 nullptr;

    QLabel* useTorServiceLabel =            nullptr;

    QLabel* useGelbooruTorLabel =           nullptr;
    QLabel* useDanbooruTorLabel =           nullptr;
    QLabel* useR34TorLabel =                nullptr;
    QLabel* useAnimePicturesTorLabel =      nullptr;
    QLabel* useSmtgBooruTorLabel =          nullptr;
    QLabel* useAllTorLabel =                nullptr;


    // Input
    QLineEdit* gelbooruIP =                 nullptr;
    QLineEdit* gelbooruIMG3IP =             nullptr;
    QLineEdit* gelbooruVIDIP =              nullptr;
    QLineEdit* danbooruIP =                 nullptr;
    QLineEdit* danbooruCDNIP =              nullptr;
    QLineEdit* r34IP =                      nullptr;
    QLineEdit* r34WIMGIP =                  nullptr;
    QLineEdit* animePicturesIP =            nullptr;
    QLineEdit* animePicturesIMGIP =         nullptr;
    QLineEdit* smtgBooruIP =                nullptr;

    QLineEdit* gelbooruDNS =                nullptr;
    QLineEdit* gelbooruIMG3DNS =            nullptr;
    QLineEdit* gelbooruVIDDNS =             nullptr;
    QLineEdit* danbooruDNS =                nullptr;
    QLineEdit* danbooruCDNDNS =             nullptr;
    QLineEdit* r34DNS =                     nullptr;
    QLineEdit* r34WIMGDNS =                 nullptr;
    QLineEdit* animePicturesDNS =           nullptr;
    QLineEdit* animePicturesIMGDNS =        nullptr;
    QLineEdit* smtgBooruDNS =               nullptr;

    QLineEdit* curlUserAgent =              nullptr;

    QLineEdit* sslCertificate =             nullptr;
    QLineEdit* torProxy =                   nullptr;

    QCheckBox* useGelbooruTor =             nullptr;
    QCheckBox* useDanbooruTor =             nullptr;
    QCheckBox* useR34Tor =                  nullptr;
    QCheckBox* useAnimePicturesTor =        nullptr;
    QCheckBox* useSmtgBooruTor =            nullptr;
    QCheckBox* useAllTor =                  nullptr;

    // Accept/reject
    QDialogButtonBox* buttonBox =           nullptr;

    // Layout
    QGridLayout* mainLayout =               nullptr;

    // Pointer to parent
    ConfigForm* parentForm =                nullptr;


public:

    /// Functions to automatically update DNS
    /// input fields on ip input change

    void updateGBDNS();
    void updateGBIMG3DNS();
    void updateGBVIDDNS();

    void updateDBDNS();
    void updateDBCDNDNS();

    void updateR34DNS();
    void updateR34WIMGDNS();

    void updateAPDNS();
    void updateAPIMGDNS();

    void updateSMTGDNS();


public slots:
    void verify();
    void reject();
};

#endif // NETWORKCONFIGFORM_H
