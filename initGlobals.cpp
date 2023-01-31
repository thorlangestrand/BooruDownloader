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
        saveGlobals();
        return true;
    }


    std::ifstream in(workablePath + "\\config.scuff");

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


    std::getline(in, buf); globals::useGelbooruTor =            (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useDanbooruTor =            (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useR34Tor =                 (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useAnimePicturesTor =       (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useSmtgBooruTor =           (Qt::CheckState)std::stoi(buf);
    std::getline(in, buf); globals::useAllTor =                 (Qt::CheckState)std::stoi(buf);

    std::getline(in, globals::sslCertificate);
    std::getline(in, globals::torProxy);
    std::getline(in, globals::danbooruUser);
    std::getline(in, globals::danbooruKey);
    std::getline(in, globals::curlUserAgent);
    std::getline(in, buf); globals::defaultService =            std::stoi(buf);
    std::getline(in, buf); globals::maxThreads =                std::stoi(buf);

    // globals::globalSem.setThreads(globals::maxThreads);

    return true;
}
