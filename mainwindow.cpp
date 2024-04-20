#include "mainwindow.h"
#include "ui_mainwindow.h"
// #include <qDebug>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BooruDownloader v1.0");
    ui->chooseServiceComboBox->addItem("Gelbooru");
    ui->chooseServiceComboBox->addItem("Danbooru");
    ui->chooseServiceComboBox->addItem("R34");
    ui->chooseServiceComboBox->addItem("Anime-Pictures");
    ui->chooseServiceComboBox->addItem("smtgbooru");
    ui->chooseServiceComboBox->setCurrentIndex(globals::defaultService);
    QShortcut* exitCtrShiftlW = new QShortcut(QKeySequence("Ctrl+Shift+W"), this);
    QObject::connect(exitCtrShiftlW, &QShortcut::activated, this, [](){ exit(0); });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::resetConsoleText()
{
    ui->consoleTextBrowser->setText("See? I told you it'd be fine\n(～￣▽￣)～");
}

void MainWindow::on_sendPushButton_clicked()
{

    // Check if pageCount is a valid integer once parsed, if not then return
    if (!is_number(ui->pagesLineEdit->text().toStdString()))
    {
        QMessageBox::information(this, "Invalid Pagecount", "Attempted invalid pagecount: " + ui->pagesLineEdit->text());
        return;
    }

    // If Danbooru is selected check if pageLim is a valid integer once parsed, if not then return
    if (!is_number(ui->numLineEdit->text().toStdString()) && ui->chooseServiceComboBox->currentIndex() == Services::Danbooru)
    {
        QMessageBox::information(this, "Invalid Pagelim", "Attempted invalid pagelim: " + ui->numLineEdit->text());
        return;
    }

    // Get pagesCount from GUI
    size_t pagesCount = ui->pagesLineEdit->text().toUInt();

    // Get tags from GUI and set tags in global so can be accessed by downloaders
    MainWindow::tags = ui->tagsLineEdit->text();

    // Get basepath from GUI
    QString basePath = ui->setPathLineEdit->text();

    QString sanitizedTags = QString::fromStdString(sanitizeTags(tags));

    // Completely valid filepath
    QString validFilePath = createValidFilePath(basePath, sanitizedTags);

    MainWindow::filePath = validFilePath;

    // Displayed to screen, temporary debug thingimajigger
    ui->consoleTextBrowser->setText("Have no fear, for the program has not crashed\nIt is merely taking a nap\nφ(*￣0￣)");

    // Choose service
    switch(ui->chooseServiceComboBox->currentIndex())
    {
    // Gelbooru
    case Services::Gelbooru: {

        std::vector<std::string> dataStrings = {};

        for (size_t i = 0; i < pagesCount; ++i)
        {
            MainWindow::selected = Services::Gelbooru;

            CURL* curl = curl_easy_init();

            if (!curl)
            {
                Warn("Critical error failed to initialize curl!");
                resetConsoleText();
                return;
            }

            std::stringstream ss;
            ss << "https://gelbooru.com/index.php?page=dapi&s=post&q=index&json=1&tags=" << sanitizedTags.toStdString() << "&pid=" << i;
            std::string url = ss.str();
            std::regex removeSpaces("[ ]");
            url = std::regex_replace(url, removeSpaces, "%20");
            url = std::regex_replace(url, std::regex("order:score"), "sort:score");

            std::string resBuffer = "";

            if (globals::useAllTor ||  globals::useGelbooruTor)
            {
                if (!checkTorConnection())
                {
                    Warn("Tor connection failed!");
                    resetConsoleText();
                    return;
                }

                struct curl_slist* dns = curl_slist_append(NULL, globals::gelbooruDNS.c_str());

                if (!curlDownloadToStringBufferTor(curl, dns, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }
            else
            {
                if (!curlDownloadToStringBuffer(curl, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }
            dataStrings.push_back(resBuffer);
        }

        if (!gelbooruDownloader(dataStrings, validFilePath.toStdString()))
        {
            resetConsoleText();
            return;
        }
        break;
    }
    // Danbooru
    case Services::Danbooru: {

        std::vector<std::string> dataStrings = {};

        int n = ui->numLineEdit->text().toInt();

        for (size_t i = 1; i <= pagesCount; ++i)
        {
            MainWindow::selected = Services::Danbooru;

            CURL* curl = curl_easy_init();
            if (!curl)
            {
                Warn("Failed to initialize curl");
                resetConsoleText();
                return;
            }


            std::stringstream ss;
            ss << "https://danbooru.donmai.us/posts.json?login=" << globals::danbooruUser << "&api_key="
               << globals::danbooruKey << "&tags=" << sanitizedTags.toStdString()
               << "&page=" << i << "&limit=" << n;
            std::string url = ss.str();
            std::regex removeSpaces("[ ]");
            url = std::regex_replace(url, removeSpaces, "%20");
            url = std::regex_replace(url, std::regex("sort:score"), "order:score");

            std::string resBuffer = "";

            if (globals::useAllTor || globals::useDanbooruTor)
            {
                if (!checkTorConnection())
                {
                    Warn("Tor connection failed!");
                    resetConsoleText();
                    return;
                }

                struct curl_slist* dns = curl_slist_append(NULL, globals::danbooruDNS.c_str());

                if (!curlDownloadToStringBufferTor(curl, dns, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }
            else
            {
                if (!curlDownloadToStringBuffer(curl, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }

            dataStrings.push_back(resBuffer);
        }

        if (!danbooruDownloader(dataStrings, validFilePath.toStdString()))
        {
            resetConsoleText();
            return;
        }
        break;
    }
    case Services::R34: {

        std::vector<std::string> dataStrings = {};

        for (size_t i = 0; i < pagesCount; ++i)
        {
            MainWindow::selected = Services::R34;


            CURL* curl = curl_easy_init();
            if (!curl)
            {
                Warn("Failed to initialize curl");
                resetConsoleText();
                return;
            }

            std::stringstream ss;
            ss << "https://api.rule34.xxx/index.php?page=dapi&s=post&q=index&json=1&tags=" << sanitizedTags.toStdString() << "&pid=" << i;
            std::string url = ss.str();
            std::regex removeSpaces("[ ]");
            url = std::regex_replace(url, std::regex("[ ]"), "%20");
            url = std::regex_replace(url, std::regex("order:score"), "sort:score");


            std::string resBuffer = "";

            if (globals::useAllTor || globals::useR34Tor)
            {
                if (!checkTorConnection())
                {
                    Warn("Tor connection failed!");
                    resetConsoleText();
                    return;
                }

                struct curl_slist* dns = curl_slist_append(NULL, globals::r34DNS.c_str());

                if (!curlDownloadToStringBufferTor(curl, dns, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }
            else
            {
                if (!curlDownloadToStringBuffer(curl, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }
            dataStrings.push_back(resBuffer);

        }

        if (!r34Downloader(dataStrings, validFilePath.toStdString()))
        {
            resetConsoleText();
            return;
        }

        break;
    }
    case Services::AnimeImages: {

        std::vector<std::string> dataStrings = {};

        for (size_t i = 0; i < pagesCount; ++i)
        {



            CURL* curl = curl_easy_init();
            if (!curl)
            {
                Warn("Critical error failed to initialize curl!");
                resetConsoleText();
                return;
            }

            std::string rTags = sanitizedTags.toStdString();

            rTags = std::regex_replace(rTags, std::regex("order:score|sort:score"), "&order_by=rating");
            rTags = std::regex_replace(rTags, std::regex(" "),"");

            std::stringstream ss;
            ss << "https://anime-pictures.net/posts?page=" << i << "&search_tag=" << rTags;

            std::string url = ss.str();
            std::regex removeSpaces("[ ]");
            url = std::regex_replace(url, removeSpaces, "%20");
            std::string resBuffer = "";

            if (globals::useAllTor || globals::useAnimePicturesTor)
            {
                if (!checkTorConnection())
                {
                    Warn("Tor connection failed!");
                    resetConsoleText();
                    return;
                }

                struct curl_slist* dns = curl_slist_append(NULL, globals::animePicturesDNS.c_str());

                if (!curlDownloadToStringBufferTor(curl, dns, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }
            else
            {
                if (!curlDownloadToStringBuffer(curl, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }

            dataStrings.push_back(resBuffer);

        }

        if (!animePicturesDownloader(dataStrings, validFilePath.toStdString()))
        {
            resetConsoleText();
            return;
        }

        break;
    }
    case Services::smtgbooru: {

        std::vector<std::string> dataStrings = {};

        // NOTE
        // smtgbooru indexes from 1
        for (size_t i = 1; i <= pagesCount; ++i)
        {
            CURL* curl = curl_easy_init();
            if (!curl)
            {
                Warn("Critical error failed to initialize curl!");
                resetConsoleText();
                return;
            }

            std::stringstream ss;
            ss << "http://www.smtgbooru.org/index.php?q=post/list/" << sanitizedTags.toStdString() << "/" << i;


            std::string url = ss.str();
            std::regex removeSpaces("[ ]");
            url = std::regex_replace(url, removeSpaces, "%20");
            std::string resBuffer = "";

            if (globals::useAllTor || globals::useSmtgBooruTor)
            {
                if (!checkTorConnection())
                {
                    Warn("Tor connection failed!");
                    resetConsoleText();
                    return;
                }

                struct curl_slist* dns = curl_slist_append(NULL, globals::smtgBooruDNS.c_str());

                if (!curlDownloadToStringBufferTor(curl, dns, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }
            else
            {
                if (!curlDownloadToStringBuffer(curl, url, resBuffer))
                {
                    resetConsoleText();
                    return;
                }
            }

            dataStrings.push_back(resBuffer);

        }

        if (!smtgDownloader(dataStrings, validFilePath.toStdString()))
        {
            resetConsoleText();
            return;
        }

        break;
    }
    default: {
        Warn("Unknown service selected, this message should never be shown");
        break;
        }
    }
    resetConsoleText();
}


void MainWindow::on_chooseServiceComboBox_currentIndexChanged(int index)
{
switch(index)
{
    case Services::Gelbooru: {
        ui->pagesLineEdit->setText(globals::gelbooruPageDefault);
        ui->numLineEdit->setText("ヾ(≧▽≦*)o");
        ui->setPathLineEdit->setText(globals::gelbooruBasePath);
        break;
    }
    // Danbooru, standard 10 pages 20 items per page
    case Services::Danbooru: {
        ui->pagesLineEdit->setText(globals::danbooruPageDefault);
        ui->numLineEdit->setText(globals::danbooruNumDefault);
        ui->setPathLineEdit->setText(globals::danbooruBasePath);
        break;
    }
    case Services::R34: {
        ui->pagesLineEdit->setText(globals::r34PageDefault);
        ui->numLineEdit->setText("ヾ(•ω•`)o");
        ui->setPathLineEdit->setText(globals::r34BasePath);
        break;
    }
    case Services::AnimeImages: {
        ui->pagesLineEdit->setText(globals::animePicturesPageDefault);
        ui->numLineEdit->setText("（。＾▽＾）");
        ui->setPathLineEdit->setText(globals::animePicturesBasePath);
        break;
    }
    case Services::smtgbooru: {
        ui->pagesLineEdit->setText(globals::smtgbooruPageDefault);
        ui->numLineEdit->setText("(●ˇ∀ˇ●)");
        ui->setPathLineEdit->setText(globals::smtgbooruBasePath);
        break;
    }
    default: {
        // Purely to satisfy the compiler, it can (should) never reach this point
        Warn("Unknown service selected, this message should never be shown");
        break;
    }
    }
}


void MainWindow::on_tagsLineEdit_returnPressed()
{
    MainWindow::on_sendPushButton_clicked();
}


void MainWindow::on_pagesLineEdit_returnPressed()
{
    MainWindow::on_sendPushButton_clicked();
}

void MainWindow::on_numLineEdit_returnPressed()
{
    MainWindow::on_sendPushButton_clicked();
}

// Open config window
void MainWindow::on_CFG_button_clicked()
{
    ConfigForm* cfgFrm = new ConfigForm(this);
    cfgFrm->resize({700, cfgFrm->height()});
    cfgFrm->show();
}

// Update globals based on config window data
// and save to disk
void MainWindow::acceptForm(ConfigForm* cfgFrm)
{
    globals::gelbooruBasePath =             cfgFrm->gelbooruBasePath->text();
    globals::danbooruBasePath =             cfgFrm->danboouBasePath->text();
    globals::r34BasePath =                  cfgFrm->r34BasePath->text();
    globals::animePicturesBasePath =        cfgFrm->animePicturesBasePath->text();
    globals::smtgbooruBasePath =            cfgFrm->smtgbooruBasePath->text();
    globals::gelbooruPageDefault =          cfgFrm->gelbooruPageDefault->text();
    globals::danbooruPageDefault =          cfgFrm->danboorupageDefault->text();
    globals::danbooruNumDefault =           cfgFrm->danbooruNumDefault->text();
    globals::r34PageDefault =               cfgFrm->r34PageDefault->text();
    globals::animePicturesPageDefault =     cfgFrm->animePicturesPageDefault->text();
    globals::smtgbooruPageDefault =         cfgFrm->smtgbooruPageDefault->text();
    globals::danbooruKey =                  cfgFrm->danbooruKey->text().toStdString();
    globals::maxThreads =                   cfgFrm->maxThreads->text().toInt();
    globals::defaultService =               cfgFrm->defaultService->currentIndex();

    switch(ui->chooseServiceComboBox->currentIndex())
    {
    case Services::Gelbooru: {
        ui->pagesLineEdit->setText(globals::gelbooruPageDefault);
        ui->setPathLineEdit->setText(globals::gelbooruBasePath);
        break;
    }
    case Services::Danbooru: {
        ui->pagesLineEdit->setText(globals::danbooruPageDefault);
        ui->numLineEdit->setText(globals::danbooruNumDefault);
        ui->setPathLineEdit->setText(globals::danbooruBasePath);
        break;
    }
    case Services::R34: {
        ui->pagesLineEdit->setText(globals::r34PageDefault);
        ui->setPathLineEdit->setText(globals::r34BasePath);
        break;
    }
    case Services::AnimeImages: {
        ui->pagesLineEdit->setText(globals::animePicturesPageDefault);
        ui->setPathLineEdit->setText(globals::animePicturesBasePath);
        break;
    }
    case Services::smtgbooru: {
        ui->pagesLineEdit->setText(globals::smtgbooruPageDefault);
        ui->setPathLineEdit->setText(globals::smtgbooruBasePath);
        break;
    }
    default: {
        // If it reaches here something has gone horribly wrong
        Warn("Something went horribly wrong and chooseServiceComboBox index went out of range");
        break;
    }
    }

    if (!saveGlobals())
    {
        Warn("Failed to save globals to disk!");
    }

    delete cfgFrm;

}

void MainWindow::rejectForm(ConfigForm* cfgFrm)
{
    delete cfgFrm;
}











