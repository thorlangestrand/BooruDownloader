#include "networkConfigForm.h"
#include "configForm.h"

networkConfigForm::networkConfigForm(ConfigForm* parent)
    : QDialog(parent),
      parentForm(parent)
{


    gelbooruIPLabel =                   new QLabel("Gelbooru IP");
    gelbooruIMG3IPLabel =               new QLabel("Gelbooru IMG3 IP");
    gelbooruVIDIPLabel =                new QLabel("Gelbooru VID IP");
    danbooruIPLabel =                   new QLabel("Danbooru IP");
    danbooruCDNIPLabel =                new QLabel("Danbooru CDN IP");
    r34IPLabel =                        new QLabel("R34 IP");
    r34WIMGIPLabel =                    new QLabel("R34 WIMG IP");
    animePicturesIPLabel=               new QLabel("Anime-Pictures IP");
    animePicturesIMGIPLabel =           new QLabel("Anime-Pictures IMG IP");
    smtgBooruIPLabel =                  new QLabel("Smtgbooru IP");

    gelbooruDNSLabel =                  new QLabel("Gelbooru DNS");
    gelbooruIMG3DNSLabel =              new QLabel("Gelbooru IMG3 DNS");
    gelbooruVIDDNSLabel =               new QLabel("Gelbooru VID DNS");
    danbooruDNSLabel =                  new QLabel("Danbooru DNS");
    danbooruCDNDNSLabel =               new QLabel("Danbooru CDN DNS");
    r34DNSLabel =                       new QLabel("R34 DNS");
    r34WIMGDNSLabel =                   new QLabel("R34 WIMG DNS");
    animePicturesDNSLabel =             new QLabel("Anime-Pictures DNS");
    animePicturesIMGDNSLabel =          new QLabel("Anime-Pictures IMG DNS");
    smtgBooruDNSLabel =                 new QLabel("Smtgbooru DNS");

    curlUserAgentLabel =                new QLabel("Curl User Agent");
    sslCertificateLabel =               new QLabel("SSL Certificate location");
    torProxyLabel =                     new QLabel("Tor Proxy IP");

    useTorServiceLabel =                new QLabel("Choose services to go through tor");
    useGelbooruTorLabel =               new QLabel("Gelbooru");
    useDanbooruTorLabel =               new QLabel("Danbooru");
    useR34TorLabel =                    new QLabel("R34");
    useAnimePicturesTorLabel =          new QLabel("Anime-Pictures");
    useSmtgBooruTorLabel =              new QLabel("Smtgbooru");
    useYandereTorLabel =                new QLabel("Yandere");
    useAllTorLabel =                    new QLabel("All");




    gelbooruDNSLabel =                  new QLabel("Gelbooru DNS");
    gelbooruIMG3DNSLabel =              new QLabel("Gelbooru IMG3 DNS");
    gelbooruVIDDNSLabel =               new QLabel("Gelbooru VID DNS");
    sslCertificateLabel =               new QLabel("SSL Certificate");
    torProxyLabel =                     new QLabel("Tor Proxy");


    gelbooruIP =                        new QLineEdit(globals::gelbooruIP.c_str());
    gelbooruIMG3IP =                    new QLineEdit(globals::gelbooruIMG3IP.c_str());
    gelbooruVIDIP =                     new QLineEdit(globals::gelbooruVIDIP.c_str());
    danbooruIP =                        new QLineEdit(globals::danbooruIP.c_str());
    danbooruCDNIP =                     new QLineEdit(globals::danbooruCDNIP.c_str());
    r34IP =                             new QLineEdit(globals::r34IP.c_str());
    r34WIMGIP =                         new QLineEdit(globals::r34WIMGIP.c_str());
    animePicturesIP =                   new QLineEdit(globals::animePicturesIP.c_str());
    animePicturesIMGIP =                new QLineEdit(globals::animePicturesIMGIP.c_str());
    smtgBooruIP =                       new QLineEdit(globals::smtgBooruIP.c_str());
    gelbooruDNS =                       new QLineEdit(globals::gelbooruDNS.c_str());
    gelbooruIMG3DNS =                   new QLineEdit(globals::gelbooruIMG3DNS.c_str());
    gelbooruVIDDNS =                    new QLineEdit(globals::gelbooruVIDDNS.c_str());
    danbooruDNS =                       new QLineEdit(globals::danbooruDNS.c_str());
    danbooruCDNDNS =                    new QLineEdit(globals::danbooruCDNDNS.c_str());
    r34DNS =                            new QLineEdit(globals::r34DNS.c_str());
    r34WIMGDNS =                        new QLineEdit(globals::r34WIMGDNS.c_str());
    animePicturesDNS =                  new QLineEdit(globals::animePicturesDNS.c_str());
    animePicturesIMGDNS =               new QLineEdit(globals::animePicturesIMGDNS.c_str());
    smtgBooruDNS =                      new QLineEdit(globals::smtgBooruDNS.c_str());

    curlUserAgent =                     new QLineEdit(globals::curlUserAgent.c_str());
    sslCertificate =                    new QLineEdit(globals::sslCertificate.c_str());
    torProxy =                          new QLineEdit(globals::torProxy.c_str());

    useGelbooruTor =                    new QCheckBox(); useGelbooruTor->setCheckState(globals::useGelbooruTor);
    useDanbooruTor =                    new QCheckBox(); useDanbooruTor->setCheckState(globals::useDanbooruTor);
    useR34Tor =                         new QCheckBox(); useR34Tor->setCheckState(globals::useR34Tor);
    useAnimePicturesTor =               new QCheckBox(); useAnimePicturesTor->setCheckState(globals::useAnimePicturesTor);
    useSmtgBooruTor =                   new QCheckBox(); useSmtgBooruTor->setCheckState(globals::useSmtgBooruTor);
    useYandereTor =                     new QCheckBox(); useYandereTor->setCheckState(globals::useYandereTor);
    useAllTor =                         new QCheckBox(); useAllTor->setCheckState(globals::useAllTor);



    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonBox, &QDialogButtonBox::accepted, this, &networkConfigForm::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &networkConfigForm::reject);

    // Automatically update dns settings on ip change
    connect(gelbooruIP, &QLineEdit::textChanged, this, &networkConfigForm::updateGBDNS);
    connect(gelbooruIMG3IP, &QLineEdit::textChanged, this, &networkConfigForm::updateGBIMG3DNS);
    connect(gelbooruVIDIP, &QLineEdit::textChanged, this, &networkConfigForm::updateGBVIDDNS);
    connect(danbooruIP, &QLineEdit::textChanged, this, &networkConfigForm::updateDBDNS);
    connect(danbooruCDNIP, &QLineEdit::textChanged, this, &networkConfigForm::updateDBCDNDNS);
    connect(r34IP, &QLineEdit::textChanged, this, &networkConfigForm::updateR34DNS);
    connect(r34WIMGIP, &QLineEdit::textChanged, this, &networkConfigForm::updateR34WIMGDNS);
    connect(animePicturesIP, &QLineEdit::textChanged, this, &networkConfigForm::updateAPDNS);
    connect(animePicturesIMGIP, &QLineEdit::textChanged, this, &networkConfigForm::updateAPIMGDNS);
    connect(smtgBooruIP, &QLineEdit::textChanged, this, &networkConfigForm::updateSMTGDNS);


    mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(0);
    mainLayout->setVerticalSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);


    mainLayout->addWidget(gelbooruIPLabel,          0, 0);  mainLayout->addWidget(gelbooruIP,           0, 1);
    mainLayout->addWidget(gelbooruIMG3IPLabel,      1, 0);  mainLayout->addWidget(gelbooruIMG3IP,       1, 1);
    mainLayout->addWidget(gelbooruVIDIPLabel,       2, 0);  mainLayout->addWidget(gelbooruVIDIP,        2, 1);
    mainLayout->addWidget(danbooruIPLabel,          3, 0);  mainLayout->addWidget(danbooruIP,           3, 1);
    mainLayout->addWidget(danbooruCDNIPLabel,       4, 0);  mainLayout->addWidget(danbooruCDNIP,        4, 1);
    mainLayout->addWidget(r34IPLabel,               5, 0);  mainLayout->addWidget(r34IP,                5, 1);
    mainLayout->addWidget(r34WIMGIPLabel,           6, 0);  mainLayout->addWidget(r34WIMGIP,            6, 1);
    mainLayout->addWidget(animePicturesIPLabel,     7, 0);  mainLayout->addWidget(animePicturesIP,      7, 1);
    mainLayout->addWidget(animePicturesIMGIPLabel,  8, 0);  mainLayout->addWidget(animePicturesIMGIP,   8, 1);
    mainLayout->addWidget(smtgBooruIPLabel,         9, 0);  mainLayout->addWidget(smtgBooruIP,          9, 1);
    mainLayout->addWidget(gelbooruDNSLabel,         10, 0); mainLayout->addWidget(gelbooruDNS,          10, 1);
    mainLayout->addWidget(gelbooruIMG3DNSLabel,     11, 0); mainLayout->addWidget(gelbooruIMG3DNS,      11, 1);
    mainLayout->addWidget(gelbooruVIDDNSLabel,      12, 0); mainLayout->addWidget(gelbooruVIDDNS,       12, 1);
    mainLayout->addWidget(danbooruDNSLabel,         13, 0); mainLayout->addWidget(danbooruDNS,          13, 1);
    mainLayout->addWidget(danbooruCDNDNSLabel,      14, 0); mainLayout->addWidget(danbooruCDNDNS,       14 ,1);
    mainLayout->addWidget(r34DNSLabel,              15, 0); mainLayout->addWidget(r34DNS,               15, 1);
    mainLayout->addWidget(r34WIMGDNSLabel,          16, 0); mainLayout->addWidget(r34WIMGDNS,           16, 1);
    mainLayout->addWidget(animePicturesDNSLabel,    17, 0); mainLayout->addWidget(animePicturesDNS,     17, 1);
    mainLayout->addWidget(animePicturesIMGDNSLabel, 18, 0); mainLayout->addWidget(animePicturesIMGDNS,  18, 1);
    mainLayout->addWidget(smtgBooruDNSLabel,        19, 0); mainLayout->addWidget(smtgBooruDNS,         19, 1);
    mainLayout->addWidget(curlUserAgentLabel,       20, 0); mainLayout->addWidget(curlUserAgent,        20, 1);
    mainLayout->addWidget(sslCertificateLabel,      21, 0); mainLayout->addWidget(sslCertificate,       21, 1);
    mainLayout->addWidget(torProxyLabel,            22, 0); mainLayout->addWidget(torProxy,             22, 1);
    mainLayout->addWidget(useTorServiceLabel,       23, 0);
    mainLayout->addWidget(useGelbooruTorLabel,      24, 0); mainLayout->addWidget(useGelbooruTor,       24, 1);
    mainLayout->addWidget(useDanbooruTorLabel,      25, 0); mainLayout->addWidget(useDanbooruTor,       25, 1);
    mainLayout->addWidget(useR34TorLabel,           26, 0); mainLayout->addWidget(useR34Tor,            26, 1);
    mainLayout->addWidget(useAnimePicturesTorLabel, 27, 0); mainLayout->addWidget(useAnimePicturesTor,  27, 1);
    mainLayout->addWidget(useSmtgBooruTorLabel,     28, 0); mainLayout->addWidget(useSmtgBooruTor,      28, 1);
    mainLayout->addWidget(useYandereTorLabel,       29, 0); mainLayout->addWidget(useYandereTor,        29, 1);
    mainLayout->addWidget(useAllTorLabel,           30, 0); mainLayout->addWidget(useAllTor,            30, 1);




    mainLayout->addWidget(buttonBox, 31, 0, 1, 2);

    networkConfigForm::setLayout(mainLayout);
    networkConfigForm::setWindowTitle("Configure Network Settings");



}

networkConfigForm::~networkConfigForm()
{
    delete gelbooruIPLabel;
    delete gelbooruIMG3IPLabel;
    delete gelbooruVIDIPLabel;
    delete danbooruIPLabel;
    delete danbooruCDNIPLabel;
    delete r34IPLabel;
    delete r34WIMGIPLabel;
    delete animePicturesIPLabel;
    delete animePicturesIMGIPLabel;
    delete smtgBooruIPLabel;
    delete gelbooruDNSLabel;
    delete gelbooruIMG3DNSLabel;
    delete gelbooruVIDDNSLabel;
    delete danbooruDNSLabel;
    delete danbooruCDNDNSLabel;
    delete r34DNSLabel;
    delete r34WIMGDNSLabel;
    delete animePicturesDNSLabel;
    delete animePicturesIMGDNSLabel;
    delete smtgBooruDNSLabel;
    delete curlUserAgentLabel;
    delete sslCertificateLabel;
    delete torProxyLabel;
    delete useTorServiceLabel;
    delete useGelbooruTorLabel;
    delete useDanbooruTorLabel;
    delete useR34TorLabel;
    delete useAnimePicturesTorLabel;
    delete useSmtgBooruTorLabel;
    delete useYandereTorLabel;
    delete useAllTorLabel;

    delete gelbooruIP;
    delete gelbooruIMG3IP;
    delete gelbooruVIDIP;
    delete danbooruIP;
    delete danbooruCDNIP;
    delete r34IP;
    delete r34WIMGIP;
    delete animePicturesIP;
    delete animePicturesIMGIP;
    delete smtgBooruIP;
    delete gelbooruDNS;
    delete gelbooruIMG3DNS;
    delete gelbooruVIDDNS;
    delete danbooruDNS;
    delete danbooruCDNDNS;
    delete r34DNS;
    delete r34WIMGDNS;
    delete animePicturesDNS;
    delete animePicturesIMGDNS;
    delete smtgBooruDNS;
    delete curlUserAgent;
    delete sslCertificate;
    delete torProxy;
    delete useGelbooruTor;
    delete useDanbooruTor;
    delete useR34Tor;
    delete useAnimePicturesTor;
    delete useSmtgBooruTor;
    delete useYandereTor;
    delete useAllTor;

    delete buttonBox;

    delete mainLayout;
}

void networkConfigForm::updateGBDNS()
{

    std::stringstream ss;
    ss << "gelbooru.com:443:" << gelbooruIP->text().toStdString();
    gelbooruDNS->setText(ss.str().c_str());

}

void networkConfigForm::updateGBIMG3DNS()
{
    std::stringstream ss;
    ss << "img3.gelbooru.com:443:" << gelbooruIMG3IP->text().toStdString();
    gelbooruIMG3DNS->setText(ss.str().c_str());
}

void networkConfigForm::updateGBVIDDNS()
{
    std::stringstream ss;
    ss << "video-cdn3.gelbooru.com:443:" << gelbooruVIDIP->text().toStdString();
    gelbooruVIDDNS->setText(ss.str().c_str());
}

void networkConfigForm::updateDBDNS()
{
    std::stringstream ss;
    ss << "danbooru.donmai.us:443:" << danbooruIP->text().toStdString();
    danbooruDNS->setText(ss.str().c_str());
}

void networkConfigForm::updateDBCDNDNS()
{
    std::stringstream ss;
    ss << "cdn.donmai.us:443:" << danbooruCDNIP->text().toStdString();
    danbooruCDNDNS->setText(ss.str().c_str());
}

void networkConfigForm::updateR34DNS()
{
    std::stringstream ss;
    ss << "rule34.xxx:443:" << r34IP->text().toStdString();
    r34DNS->setText(ss.str().c_str());
}

void networkConfigForm::updateR34WIMGDNS()
{
    std::stringstream ss;
    ss << "wimg.rule34.xxx:443:" << r34WIMGIP->text().toStdString();
    r34WIMGDNS->setText(ss.str().c_str());
}

void networkConfigForm::updateAPDNS()
{
    std::stringstream ss;
    ss << "anime-pictures.net:443:" << animePicturesIP->text().toStdString();
    animePicturesDNS->setText(ss.str().c_str());
}

void networkConfigForm::updateAPIMGDNS()
{
    std::stringstream ss;
    ss << "images.anime-pictures.net:443:" << animePicturesIMGIP->text().toStdString();
    animePicturesIMGDNS->setText(ss.str().c_str());
}

void networkConfigForm::updateSMTGDNS()
{
    std::stringstream ss;
    ss << "smtgbooru.org:80:" << smtgBooruIP->text().toStdString();
    smtgBooruDNS->setText(ss.str().c_str());
}


void networkConfigForm::verify()
{
    accept();
    parentForm->acceptForm(this);
}

void networkConfigForm::reject()
{
    parentForm->rejectForm(this);
}

