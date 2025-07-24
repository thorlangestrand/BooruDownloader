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

    if (!out.is_open())
    {
        Warn("Failed to open config file");
        return false;
    }

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
