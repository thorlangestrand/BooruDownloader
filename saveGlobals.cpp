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

    std::string outSaner(workablePath + "\\config.json");

    if (!out.is_open())
    {
        Warn("Failed to open config file");
        return false;
    }

    scuff::json root = scuff::createRootNode();

    // Root folders
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruBasePathEnum], globals::gelbooruBasePath.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruBasePathEnum], globals::danbooruBasePath.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::r34BasePathEnum], globals::r34BasePath.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::animePicturesBasePathEnum], globals::animePicturesBasePath.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::yandereBasePathEnum], globals::yandereBasePath.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::smtgbooruBasePathEnum], globals::smtgbooruBasePath.toStdString().c_str());

    // Default page count to fetch etc.
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruPageDefaultEnum], globals::gelbooruPageDefault.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruPageDefaultEnum], globals::danbooruPageDefault.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruNumDefaultEnum], globals::danbooruNumDefault.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::r34PageDefaultEnum], globals::r34PageDefault.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::animePicturesPageDefaultEnum], globals::animePicturesPageDefault.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::yanderePageDefaultEnum], globals::yanderePageDefault.toStdString().c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::smtgbooruPageDefaultEnum], globals::smtgbooruPageDefault.toStdString().c_str());

    // IP addresses for manual dns configuration because uhh don't worry about it
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruIPEnum], globals::gelbooruIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruIMG3IPEnum], globals::gelbooruIMG3IP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruVIDIPEnum], globals::gelbooruVIDIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruIPEnum], globals::danbooruIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruCDNIPEnum], globals::danbooruCDNIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::r34IPEnum], globals::r34IP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::r34WIMGIPEnum], globals::r34WIMGIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::animePicturesIPEnum], globals::animePicturesIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::animePicturesIMGIPEnum], globals::animePicturesIMGIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::smtgBooruIPEnum], globals::smtgBooruIP.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::yandereIPEnum], globals::yandereIP.c_str());

    // DNS configuration (yeah don't worry about it too much)
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruDNSEnum], globals::gelbooruDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruIMG3DNSEnum], globals::gelbooruIMG3DNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::gelbooruVIDDNSEnum], globals::gelbooruVIDDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruDNSEnum], globals::danbooruDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruCDNDNSEnum], globals::danbooruCDNDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::r34DNSEnum], globals::r34DNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::r34WIMGDNSEnum], globals::r34WIMGDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::animePicturesDNSEnum], globals::animePicturesDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::animePicturesIMGDNSEnum], globals::animePicturesIMGDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::smtgBooruDNSEnum], globals::smtgBooruDNS.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::yandereDNSEnum], globals::yandereDNS.c_str());

    // Tor schizophrenia configuration (maybe worry about it a little)


    // General configuration for networking, keys, etc.
    root.addPureData(globals::keyNameMap[globals::saveKeys::sslCertificateEnum], globals::sslCertificate.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::torProxyEnum], globals::torProxy.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruUserEnum], globals::danbooruUser.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::danbooruKeyEnum], globals::danbooruKey.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::curlUserAgentEnum], globals::curlUserAgent.c_str());
    root.addPureData(globals::keyNameMap[globals::saveKeys::maxThreadsEnum], globals::maxThreads);
    root.addPureData(globals::keyNameMap[globals::saveKeys::defaultServiceEnum], static_cast<int>(globals::defaultService));

    scuff::saveToFile(outSaner.c_str(), root);

    root.erase(); // Always clean up after yourself!

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
