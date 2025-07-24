#include "saveGlobals.h"

bool saveGlobals()
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

    std::ofstream out(workablePath + "\\config.scuff");

    std::string outSaner(workablePath+ "\\config.json");

    if (!out.is_open())
    {
        Warn("Failed to open config file");
        return false;
    }

    scuff::json root = scuff::createRootNode();

    root.addPureData(globals::saveKeys::gelbooruBasePathEnum, globals::gelbooruBasePath.toStdString().c_str());
    root.addPureData(globals::saveKeys::danbooruBasePathEnum,globals::danbooruBasePath.toStdString().c_str());
    root.addPureData(, globals::r34BasePath.toStdString().c_str());
    root.addPureData("animePicturesBasePath",globals::animePicturesBasePath.toStdString().c_str());
    root.addPureData("smtgbooruBasePath", globals::smtgbooruBasePath.toStdString().c_str());
    root.addPureData("yandereBasePath",globals::yandereBasePath.toStdString().c_str());

    scuff::saveToFile(outSaner.c_str(), root);

    out
    << globals::gelbooruBasePath.toStdString() << "\n"
    << globals::danbooruBasePath.toStdString() << "\n"
    << globals::r34BasePath.toStdString() << "\n"
    << globals::animePicturesBasePath.toStdString() << "\n"
    << globals::yandereBasePath.toStdString() << "\n"
    << globals::smtgbooruBasePath.toStdString() << "\n"

    << globals::gelbooruPageDefault.toStdString() << "\n"
    << globals::danbooruPageDefault.toStdString() << "\n"
    << globals::danbooruNumDefault.toStdString() << "\n"
    << globals::r34PageDefault.toStdString() << "\n"
    << globals::animePicturesPageDefault.toStdString() << "\n"
    << globals::smtgbooruPageDefault.toStdString() << "\n"

    << globals::gelbooruIP << "\n"
    << globals::gelbooruIMG3IP << "\n"
    << globals::gelbooruVIDIP << "\n"

    << globals::danbooruIP << "\n"
    << globals::danbooruCDNIP << "\n"

    << globals::r34IP << "\n"
    << globals::r34WIMGIP << "\n"

    << globals::animePicturesIP << "\n"
    << globals::animePicturesIMGIP << "\n"

    << globals::smtgBooruIP << "\n"

    << globals::gelbooruDNS << "\n"
    << globals::gelbooruIMG3DNS << "\n"
    << globals::gelbooruVIDDNS << "\n"

    << globals::danbooruDNS << "\n"
    << globals::danbooruCDNDNS << "\n"

    << globals::r34DNS << "\n"
    << globals::r34WIMGDNS << "\n"

    << globals::animePicturesDNS << "\n"
    << globals::animePicturesIMGDNS << "\n"

    << globals::smtgBooruDNS << "\n"

    << globals::useGelbooruTor << "\n"
    << globals::useDanbooruTor << "\n"
    << globals::useR34Tor << "\n"
    << globals::useAnimePicturesTor << "\n"
    << globals::useSmtgBooruTor << "\n"
    << globals::useAllTor << "\n"

    << globals::sslCertificate << "\n"
    << globals::torProxy << "\n"

    << globals::danbooruUser << "\n"
    << globals::danbooruKey << "\n"
    << globals::curlUserAgent << "\n"

    << globals::defaultService << "\n"

    << globals::maxThreads << "\n";
    out.close();
    return true;
}
