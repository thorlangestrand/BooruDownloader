#include "initGlobals.h"
/**
 * NB: Spaces between lines is just visual to split
 * up different categories, they are not present
 * in the actual file saved to disk
 *
 * FILE FORMAT
 *
 * [QSTRING]        gelbooruBasePath
 * [QSTRING]        danbooruBasePath
 * [QSTRING]        r34BasePath
 * [QSTRING]        animePicturesBasePath
 * [QSTRING]        smtgBooruBasePath
 *
 * [QSTRING]        gelbooruPageDefault
 * [QSTRING]        danbooruPageDefault
 * [QSTRING]        danbooruNumDefault
 * [QSTRING]        r34PageDefault
 * [QSTRING]        animePicturesPageDefault
 * [QSTRING]        smtgBooruPageDefault
 *
 * [STRING]         gelbooruIP
 * [STRING]         gelbooruIMG3IP
 * [STRING]         gelbooruVIDIP
 *
 * [STRING]         danbooruIP
 * [STRING]         danbooruCDNIP
 *
 * [STRING]         r34IP
 * [STRING]         r34WIMGIP
 *
 * [STRING]         animePicturesIP
 * [STRING]         animePicturesIMGIP
 *
 * [STRING]         smtgBooruIP
 *
 * [STRING]         gelbooruDNS
 * [STRING]         gelbooruIMG3DNS
 * [STRING]         gelbooruVIDDNS
 *
 * [STRING]         danbooruDNS
 * [STRING]         danbooruCDNDNS
 *
 * [STRING]         r34DNS
 * [STRING]         r34WIMGDNS
 *
 * [STRING]         animePicturesDNS
 * [STRING]         animePicturesIMGDNS
 *
 * [STRING]         smtgBooruDNS
 *
 * [QT::CheckState] useGelbooruTor
 * [QT::CheckState] useDanbooruTor
 * [QT::CheckState] useR34Tor
 * [QT::CheckState] useAnimePicturesTor
 * [QT::CheckState] useSmtgBooruTor
 * [QT::CheckState] useAllTor
 *
 * [STRING]         sslCertificate
 * [STRING]         torProxy
 *
 * [STRING]         danbooruUser
 * [STRING]         danbooruKey
 * [STRING]         curl user agent
 *
 * [INT]            defaultService
 * [INT]            maxThreads
 */
#include <QDebug>
bool initGlobals()
{
    LPWSTR path = NULL;

    HRESULT hr = SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &path);

    if (!SUCCEEDED(hr))
    {
        Warn("Catastrophic failure failed to locate appdata");
        return false;
    }

    CoTaskMemFree(path);

    std::string workablePath = utf8_encode(path);

    workablePath += "\\ScuffDownloader";


    if (!std::filesystem::exists(workablePath))
    {
        if (!std::filesystem::create_directory(workablePath))
        {
            QString wMsg = "Failed to create directory at path: " + QString::fromStdString(workablePath);
            Warn(wMsg);
            return false;
        }
    }

    // If no config file found create one and initialize with default values
    if (!std::filesystem::exists(workablePath + "\\config.scuff"))
    {
        Warn("No config file detected, using default configuration");

        LPWSTR pPath = NULL;
        HRESULT pHr = SHGetKnownFolderPath(FOLDERID_Pictures, 0, NULL, &pPath);

        CoTaskMemFree(pPath);
        std::string basePath = utf8_encode(pPath);

        if (!SUCCEEDED(pHr))
        {
            Warn("Failed to locate Pictures folder");
            return saveGlobals();
        }

        globals::gelbooruBasePath =      QString::fromStdString(basePath);
        globals::danbooruBasePath =      QString::fromStdString(basePath);
        globals::r34BasePath =           QString::fromStdString(basePath);
        globals::animePicturesBasePath = QString::fromStdString(basePath);
        globals::smtgbooruBasePath =     QString::fromStdString(basePath);

        return saveGlobals();
    }

    if (!std::filesystem::exists(workablePath + "\\config.json"))
    {
        Warn("No json config file detected, using default configuration");

        LPWSTR pPath = NULL;
        HRESULT pHr = SHGetKnownFolderPath(FOLDERID_Pictures, 0, NULL, &pPath);

        CoTaskMemFree(pPath);
        std::string basePath = utf8_encode(pPath);

        if (!SUCCEEDED(pHr))
        {
            Warn("Failed to locate Pictures folder");
            return saveGlobals();
        }

        globals::gelbooruBasePath =      QString::fromStdString(basePath);
        globals::danbooruBasePath =      QString::fromStdString(basePath);
        globals::r34BasePath =           QString::fromStdString(basePath);
        globals::animePicturesBasePath = QString::fromStdString(basePath);
        globals::smtgbooruBasePath =     QString::fromStdString(basePath);

        return saveGlobals();

    }

    std::string outSaner(workablePath + "\\config.json");

    std::ifstream in(workablePath + "\\config.scuff");


    uint64_t fileSize = std::filesystem::file_size(workablePath+"\\config.json");
    std::string content(fileSize, '\0');
    std::ifstream jsonStream(workablePath + "\\config.json");

    if (!jsonStream.is_open()) {
        Warn("Failed to open config file");
        return false;
    }

    jsonStream.read(&content[0],fileSize);
    qDebug() << content.c_str();

    scuff::json configData = scuff::parseJson(content.c_str());
    qDebug() << QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::yandereBasePathEnum]]);

    // Root folders
    globals::gelbooruBasePath =          QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::gelbooruBasePathEnum]]);
    globals::danbooruBasePath =          QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::danbooruBasePathEnum]]);
    globals::r34BasePath =               QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::r34BasePathEnum]]);
    globals::animePicturesBasePath =     QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::animePicturesBasePathEnum]]);
    globals::yandereBasePath =           QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::yandereBasePathEnum]]);
    globals::smtgbooruBasePath =         QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::smtgbooruBasePathEnum]]);

    // Default page count to fetch etc.
    globals::gelbooruPageDefault =       QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::gelbooruPageDefaultEnum]]);
    globals::danbooruPageDefault =       QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::danbooruPageDefaultEnum]]);
    globals::danbooruNumDefault =        QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::danbooruNumDefaultEnum]]);
    globals::r34PageDefault =            QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::r34PageDefaultEnum]]);
    globals::animePicturesPageDefault =  QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::animePicturesPageDefaultEnum]]);
    globals::yanderePageDefault =        QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::yanderePageDefaultEnum]]);
    globals::smtgbooruPageDefault =      QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::smtgbooruPageDefaultEnum]]);


    // IP addresses
    globals::gelbooruIP =                static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruIPEnum]]);
    globals::gelbooruIMG3IP =            static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruIMG3IPEnum]]);
    globals::gelbooruVIDIP =             static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruVIDIPEnum]]);
    globals::danbooruIP =                static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::danbooruIPEnum]]);
    globals::danbooruCDNIP =             static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::danbooruCDNIPEnum]]);
    globals::r34IP =                     static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::r34IPEnum]]);
    globals::r34WIMGIP =                 static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::r34WIMGIPEnum]]);
    globals::animePicturesIP =           static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::animePicturesIMGIPEnum]]);
    globals::animePicturesIMGIP =        static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::animePicturesIMGIPEnum]]);
    globals::smtgBooruIP =               static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::smtgBooruIPEnum]]);
    globals::yandereIP =                 static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::yandereIPEnum]]);

    // DNS
    globals::gelbooruDNS =               static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruDNSEnum]]);
    globals::gelbooruIMG3DNS =           static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruIMG3DNSEnum]]);
    globals::gelbooruVIDDNS =            static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruVIDDNSEnum]]);
    globals::danbooruDNS =               static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::danbooruDNSEnum]]);
    globals::danbooruCDNDNS =            static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::danbooruCDNDNSEnum]]);
    globals::r34DNS =                    static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::r34DNSEnum]]);
    globals::r34WIMGDNS =                static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::r34WIMGDNSEnum]]);
    globals::animePicturesDNS =          static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::animePicturesDNSEnum]]);
    globals::animePicturesIMGDNS =       static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::animePicturesIMGDNSEnum]]);
    globals::smtgBooruDNS =              static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::smtgBooruDNSEnum]]);
    globals::yandereDNS =                static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::yandereDNSEnum]]);


    // Tor schizophrenia (not added yet ig lol)

    globals::useGelbooruTor = static_cast<Qt::CheckState>(static_cast<int>(configData[globals::keyNameMap[globals::saveKeys::useGelbooruTorEnum]]));
    globals::useDanbooruTor= static_cast<Qt::CheckState>(static_cast<int>(configData[globals::keyNameMap[globals::saveKeys::useDanbooruTorEnum]]));
    globals::useR34Tor= static_cast<Qt::CheckState>(static_cast<int>(configData[globals::keyNameMap[globals::saveKeys::useR34TorEnum]]));
    globals::useAnimePicturesTor= static_cast<Qt::CheckState>(static_cast<int>(configData[globals::keyNameMap[globals::saveKeys::useAnimePicturesTorEnum]]));
    globals::useSmtgBooruTor= static_cast<Qt::CheckState>(static_cast<int>(configData[globals::keyNameMap[globals::saveKeys::useSmtgBooruTorEnum]]));
    globals::useYandereTor= static_cast<Qt::CheckState>(static_cast<int>(configData[globals::keyNameMap[globals::saveKeys::useYandereTorEnum]]));
    globals::useAllTor= static_cast<Qt::CheckState>(static_cast<int>(configData[globals::keyNameMap[globals::saveKeys::useAllTorEnum]]));


    // General configuration
    globals::sslCertificate =            static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::sslCertificateEnum]]);
    globals::torProxy =                  static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::torProxyEnum]]);
    globals::gelbooruUserId =            static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruUserIdEnum]]);
    globals::gelbooruKey =               static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::gelbooruKeyEnum]]);
    globals::danbooruUser =              static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::danbooruUserEnum]]);
    globals::danbooruKey =               static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::danbooruKeyEnum]]);
    globals::curlUserAgent =             static_cast<std::string>(configData[globals::keyNameMap[globals::saveKeys::curlUserAgentEnum]]);

    globals::maxThreads =                configData[globals::keyNameMap[globals::saveKeys::maxThreadsEnum]];
    globals::defaultService =            configData[globals::keyNameMap[globals::saveKeys::defaultServiceEnum]];

    // globals::= QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::]]);
    // globals::= QString::fromStdString(configData[globals::keyNameMap[globals::saveKeys::]]);



    configData.erase(); // Always clean up after yourself!

    return true;
    if (!in.is_open())
    {
        Warn("Failed to open config file");
        return false;
    }

    /// Here I'm just naively assuming no one's gonna be messing with the config file
    std::string buf = "";
    std::getline(in, buf); globals::gelbooruBasePath =          QString::fromStdString(buf);
    std::getline(in, buf); globals::danbooruBasePath =          QString::fromStdString(buf);
    std::getline(in, buf); globals::r34BasePath =               QString::fromStdString(buf);
    std::getline(in, buf); globals::animePicturesBasePath =     QString::fromStdString(buf);
    std::getline(in, buf); globals::yandereBasePath =           QString::fromStdString(buf);
    std::getline(in, buf); globals::smtgbooruBasePath =         QString::fromStdString(buf);

    std::getline(in, buf); globals::gelbooruPageDefault =       QString::fromStdString(buf);
    std::getline(in, buf); globals::danbooruPageDefault =       QString::fromStdString(buf);
    std::getline(in, buf); globals::danbooruNumDefault =        QString::fromStdString(buf);
    std::getline(in, buf); globals::r34PageDefault =            QString::fromStdString(buf);
    std::getline(in, buf); globals::animePicturesPageDefault =  QString::fromStdString(buf);
    std::getline(in, buf); globals::smtgbooruPageDefault =      QString::fromStdString(buf);

    std::getline(in, globals::gelbooruIP);
    std::getline(in, globals::gelbooruIMG3IP);
    std::getline(in, globals::gelbooruVIDIP);

    std::getline(in, globals::danbooruIP);
    std::getline(in, globals::danbooruCDNIP);

    std::getline(in, globals::r34IP);
    std::getline(in, globals::r34WIMGIP);

    std::getline(in, globals::animePicturesIP);
    std::getline(in, globals::animePicturesIMGIP);

    std::getline(in, globals::smtgBooruIP);

    std::getline(in, globals::gelbooruDNS);
    std::getline(in, globals::gelbooruIMG3DNS);
    std::getline(in, globals::gelbooruVIDDNS);

    std::getline(in, globals::danbooruDNS);
    std::getline(in, globals::danbooruCDNDNS);

    std::getline(in, globals::r34DNS);
    std::getline(in, globals::r34WIMGDNS);

    std::getline(in, globals::animePicturesDNS);
    std::getline(in, globals::animePicturesIMGDNS);

    std::getline(in, globals::smtgBooruDNS);

    std::getline(in, globals::yandereDNS);


    std::getline(in, buf); globals::useGelbooruTor =            (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useDanbooruTor =            (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useR34Tor =                 (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useAnimePicturesTor =       (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useSmtgBooruTor =           (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useYandereTor =             (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useAllTor =                 (Qt::CheckState)std::stoi(buf);

    std::getline(in, globals::sslCertificate);
    std::getline(in, globals::torProxy);
    std::getline(in, globals::danbooruUser);
    std::getline(in, globals::danbooruKey);
    std::getline(in, globals::curlUserAgent);
    std::getline(in, buf); globals::defaultService =            std::stoi(buf);
    std::getline(in, buf); globals::maxThreads =                std::stoi(buf);

    // globals::globalSem.setThreads(globals::maxThreads);
    in.close();

    return true;
}
