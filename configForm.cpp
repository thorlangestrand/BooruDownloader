#include "mainwindow.h"
#include "configForm.h"


/**
 * @brief ConfigForm::ConfigForm
 *
 * Create a window to modify and save global variables
 *
 * @param parent        - Pointer to main window
 */


///
/// \brief ConfigForm::ConfigForm
/// \param parent
///
ConfigForm::ConfigForm(MainWindow* parent)
    : QDialog(parent),
      mw(parent)
{

    QStringList servicesList =
    {
        "Gelbooru",
        "Danbooru",
        "R34",
        "Anime-Pictures",
        "smtgbooru",
        "Yandere"
    };

    // Option labels
    gelbooruBasePathLabel =             new QLabel("Gelbooru base savepath");
    danboouBasePathLabel =              new QLabel("Danbooru base savepath");
    r34BasePathLabel =                  new QLabel("R34 base savepath");
    animePicturesBasePathLabel =        new QLabel("Anime-Pictures base savepath");
    yandereBasePathLabel=               new QLabel("Yandere base savepath");
    smtgbooruBasePathLabel =            new QLabel("smtgbooru base savepath");
    gelbooruPageDefaultLabel =          new QLabel("Gelbooru page default");
    danboorupageDefaultLabel =          new QLabel("Danbooru page default");
    danbooruNumDefaultLabel =           new QLabel("Danbooru num default");
    r34PageDefaultLabel =               new QLabel("R34 page default");
    animePicturesPageDefaultLabel =     new QLabel("Anime-Pictures page default");
    yanderePageDefaultLabel =           new QLabel("Yandere page default");
    smtgbooruPageDefaultLabel =         new QLabel("smtgbooru page default");
    gelbooruUserLabel =                 new QLabel("Gelboru user id");
    gelbooruKeyLabel =                  new QLabel("Gelbooru key");
    danbooruUserLabel =                 new QLabel("Danbooru user");
    danbooruKeyLabel =                  new QLabel("Danbooru key");
    maxThreadsLabel =                   new QLabel("Maximum amount of threads");
    defaultServiceLabel =               new QLabel("Default service on startup");

    // Main options
    gelbooruBasePath =                  new QLineEdit(globals::gelbooruBasePath);
    danboouBasePath =                   new QLineEdit(globals::danbooruBasePath);
    r34BasePath =                       new QLineEdit(globals::r34BasePath);
    animePicturesBasePath =             new QLineEdit(globals::animePicturesBasePath);
    yandereBasePath =                   new QLineEdit(globals::yandereBasePath);
    smtgbooruBasePath =                 new QLineEdit(globals::smtgbooruBasePath);
    gelbooruPageDefault =               new QLineEdit(globals::gelbooruPageDefault);
    danboorupageDefault =               new QLineEdit(globals::danbooruPageDefault);
    danbooruNumDefault =                new QLineEdit(globals::danbooruNumDefault);
    r34PageDefault =                    new QLineEdit(globals::r34PageDefault);
    animePicturesPageDefault =          new QLineEdit(globals::animePicturesPageDefault);
    yanderePageDefault =                new QLineEdit(globals::yanderePageDefault);
    smtgbooruPageDefault =              new QLineEdit(globals::smtgbooruPageDefault);
    gelbooruUser =                      new QLineEdit(globals::gelbooruUserId.c_str());
    gelbooruKey =                       new QLineEdit(globals::gelbooruKey.c_str());
    danbooruUser =                      new QLineEdit(globals::danbooruUser.c_str());
    danbooruKey =                       new QLineEdit(globals::danbooruKey.c_str());
    maxThreads =                        new QLineEdit(QString::number(globals::maxThreads));
    defaultService =                    new QComboBox;
    defaultService->addItems(servicesList);
    defaultService->setCurrentIndex(globals::defaultService);
    networkConfig =                     new QPushButton("Configure Network Settings");

    connect(networkConfig, &QPushButton::clicked, this, &ConfigForm::newNetworkConfigForm);


    // Accept/reject buttons
    buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &ConfigForm::verify);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &ConfigForm::reject);



    mainLayout = new QGridLayout;
    mainLayout->setHorizontalSpacing(10);
    mainLayout->setVerticalSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    mainLayout->addWidget(gelbooruBasePathLabel,            0, 0);  mainLayout->addWidget(gelbooruBasePath,             0, 1);
    mainLayout->addWidget(danboouBasePathLabel,             1, 0);  mainLayout->addWidget(danboouBasePath,              1, 1);
    mainLayout->addWidget(r34BasePathLabel,                 2, 0);  mainLayout->addWidget(r34BasePath,                  2, 1);
    mainLayout->addWidget(animePicturesBasePathLabel,       3, 0);  mainLayout->addWidget(animePicturesBasePath,        3, 1);
    mainLayout->addWidget(yandereBasePathLabel,             4, 0);  mainLayout->addWidget(yandereBasePath,               4, 1);
    mainLayout->addWidget(smtgbooruBasePathLabel,           5, 0);  mainLayout->addWidget(smtgbooruBasePath,            5, 1);
    mainLayout->addWidget(gelbooruPageDefaultLabel,         6, 0);  mainLayout->addWidget(gelbooruPageDefault,          6, 1);
    mainLayout->addWidget(danboorupageDefaultLabel,         7, 0);  mainLayout->addWidget(danboorupageDefault,          7, 1);
    mainLayout->addWidget(danbooruNumDefaultLabel,          8, 0);  mainLayout->addWidget(danbooruNumDefault,           8, 1);
    mainLayout->addWidget(r34PageDefaultLabel,              9, 0);  mainLayout->addWidget(r34PageDefault,               9, 1);
    mainLayout->addWidget(animePicturesPageDefaultLabel,    10, 0); mainLayout->addWidget(animePicturesPageDefault,     10, 1);
    mainLayout->addWidget(yanderePageDefaultLabel,          11, 0); mainLayout->addWidget(yanderePageDefault,           11, 1);
    mainLayout->addWidget(smtgbooruPageDefaultLabel,        12, 0); mainLayout->addWidget(smtgbooruPageDefault,         12, 1);
    mainLayout->addWidget(gelbooruUserLabel,                13, 0); mainLayout->addWidget(gelbooruUser,                 13, 1);
    mainLayout->addWidget(gelbooruKeyLabel,                 14, 0); mainLayout->addWidget(gelbooruKey,                  14, 1);
    mainLayout->addWidget(danbooruUserLabel,                15, 0); mainLayout->addWidget(danbooruUser,                 15, 1);
    mainLayout->addWidget(danbooruKeyLabel,                 16, 0); mainLayout->addWidget(danbooruKey,                  16, 1);
    mainLayout->addWidget(maxThreadsLabel,                  17, 0); mainLayout->addWidget(maxThreads,                   17, 1);
    mainLayout->addWidget(defaultServiceLabel,              18, 0); mainLayout->addWidget(defaultService,               18, 1);
    mainLayout->addWidget(networkConfig,                    19, 1);
    mainLayout->addWidget(buttonBox, 20, 0, 1, 2);

    ConfigForm::setLayout(mainLayout);
    ConfigForm::setWindowTitle("Configure Settings");
}

ConfigForm::~ConfigForm()
{
    // Delete labels
    delete gelbooruBasePathLabel;
    delete danboouBasePathLabel;
    delete r34BasePathLabel;
    delete animePicturesBasePathLabel;
    delete yandereBasePathLabel;
    delete smtgbooruBasePathLabel;
    delete gelbooruPageDefaultLabel;
    delete danboorupageDefaultLabel;
    delete danbooruNumDefaultLabel;
    delete r34PageDefaultLabel;
    delete animePicturesPageDefaultLabel;
    delete yanderePageDefaultLabel;
    delete smtgbooruPageDefaultLabel;
    delete gelbooruUserLabel;
    delete gelbooruKeyLabel;
    delete danbooruUserLabel;
    delete danbooruKeyLabel;
    delete maxThreadsLabel;
    delete defaultServiceLabel;

    // Delete input fields
    delete gelbooruBasePath;
    delete danboouBasePath;
    delete r34BasePath;
    delete animePicturesBasePath;
    delete yandereBasePath;
    delete smtgbooruBasePath;
    delete gelbooruPageDefault;
    delete danboorupageDefault;
    delete danbooruNumDefault;
    delete r34PageDefault;
    delete animePicturesPageDefault;
    delete yanderePageDefault;
    delete smtgbooruPageDefault;
    delete networkConfig;
    delete gelbooruUser;
    delete gelbooruKey;
    delete danbooruUser;
    delete danbooruKey;
    delete maxThreads;
    delete defaultService;

    // Delete buttons
    delete buttonBox;

    // Delete grid layout
    delete mainLayout;
}

void ConfigForm::verify()
{
    accept();
    mw->acceptForm(this);
}

void ConfigForm::reject()
{
    mw->rejectForm(this);
}



void ConfigForm::acceptForm(networkConfigForm* netConfigForm)
{

    /// Here's a difficult choice
    /// One path is to wait for the main form to accept
    /// before changes take place, however that might cause
    /// unintended consequences and lead to loads of spaghetti
    /// For example, a user makes changes in the network panel and then
    /// changes their mind and goes back to change it again.
    /// If we wait for the main form to accept before sending data
    /// to the global store, we must then store the data temporarily
    ///
    /// This would lead to 1 of 2 scenarios
    ///
    /// 1: The user has stale data when going back to edit the network form
    /// due to the data stored in temporary memory in ConfigForm after
    /// their edit not being reflected in the newly generated form
    /// 2: We have create a check for whether or not the network form has
    /// already been accepted this session. This will lead to copious amounts
    /// of spaghetti
    ///
    /// For these reasons I believe it is best to save to disk and
    /// update global store variables as soon as the sub-form is accepted
    /// This will allow us to have completely up to date info in the primary
    /// config form

    globals::gelbooruIP =           netConfigForm->gelbooruIP->text().toStdString();
    globals::gelbooruIMG3IP =       netConfigForm->gelbooruIMG3IP->text().toStdString();
    globals::gelbooruVIDIP =        netConfigForm->gelbooruVIDIP->text().toStdString();
    globals::danbooruIP =           netConfigForm->danbooruIP->text().toStdString();
    globals::danbooruCDNIP =        netConfigForm->danbooruCDNIP->text().toStdString();
    globals::r34IP =                netConfigForm->r34IP->text().toStdString();
    globals::r34WIMGIP =            netConfigForm->r34WIMGIP->text().toStdString();
    globals::animePicturesIP =      netConfigForm->animePicturesIP->text().toStdString();
    globals::animePicturesIMGIP =   netConfigForm->animePicturesIMGIP->text().toStdString();
    globals::smtgBooruIP =          netConfigForm->smtgBooruIP->text().toStdString();
    globals::gelbooruDNS =          netConfigForm->gelbooruDNS->text().toStdString();
    globals::gelbooruIMG3DNS =      netConfigForm->gelbooruIMG3DNS->text().toStdString();
    globals::gelbooruVIDDNS =       netConfigForm->gelbooruVIDDNS->text().toStdString();
    globals::danbooruDNS =          netConfigForm->danbooruDNS->text().toStdString();
    globals::danbooruCDNDNS =       netConfigForm->danbooruCDNDNS->text().toStdString();
    globals::r34DNS =               netConfigForm->r34DNS->text().toStdString();
    globals::r34WIMGDNS =           netConfigForm->r34WIMGDNS->text().toStdString();
    globals::animePicturesDNS =     netConfigForm->animePicturesDNS->text().toStdString();
    globals::animePicturesIMGDNS =  netConfigForm->animePicturesIMGDNS->text().toStdString();
    globals::smtgBooruDNS =         netConfigForm->smtgBooruDNS->text().toStdString();

    globals::curlUserAgent =        netConfigForm->curlUserAgent->text().toStdString();
    globals::sslCertificate =       netConfigForm->sslCertificate->text().toStdString();
    globals::torProxy =             netConfigForm->torProxy->text().toStdString();

    globals::useGelbooruTor =       netConfigForm->useGelbooruTor->checkState();
    globals::useDanbooruTor =       netConfigForm->useDanbooruTor->checkState();
    globals::useR34Tor =            netConfigForm->useR34Tor->checkState();
    globals::useAnimePicturesTor =  netConfigForm->useAnimePicturesTor->checkState();
    globals::useSmtgBooruTor =      netConfigForm->useSmtgBooruTor->checkState();
    globals::useAllTor =            netConfigForm->useAllTor->checkState();

    if (!saveGlobals())
    {
        Warn("Failed to save globals to disk!");
    }

    delete netConfigForm;
}

void ConfigForm::rejectForm(networkConfigForm* netConfigForm)
{
    delete netConfigForm;
}


void ConfigForm::newNetworkConfigForm()
{
    networkConfigForm* netConfigForm = new networkConfigForm(this);
    netConfigForm->resize({700, netConfigForm->height()});
    netConfigForm->show();
}























