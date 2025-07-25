#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

#include <string> // IWYU pragma: export
#include <map>

// #include "semaphore.h"
///
/// \brief globals
///
/// Global variables used throughout the program
///
/// \see initGlobals
///
namespace globals
{

    enum saveKeys {
        gelbooruBasePathEnum,
        danbooruBasePathEnum,
        r34BasePathEnum,
        animePicturesBasePathEnum,
        yandereBasePathEnum,
        smtgbooruBasePathEnum,

        gelbooruPageDefaultEnum,
        danbooruPageDefaultEnum,
        danbooruNumDefaultEnum,
        r34PageDefaultEnum,
        animePicturesPageDefaultEnum,
        yanderePageDefaultEnum,
        smtgbooruPageDefaultEnum,

        gelbooruIPEnum,
        gelbooruIMG3IPEnum,
        gelbooruVIDIPEnum,
        danbooruIPEnum,
        danbooruCDNIPEnum,
        r34IPEnum,
        r34WIMGIPEnum,
        animePicturesIPEnum,
        animePicturesIMGIPEnum,
        smtgBooruIPEnum,
        yandereIPEnum,

        gelbooruDNSEnum,
        gelbooruIMG3DNSEnum,
        gelbooruVIDDNSEnum,
        danbooruDNSEnum,
        danbooruCDNDNSEnum,
        r34DNSEnum,
        r34WIMGDNSEnum,
        animePicturesDNSEnum,
        animePicturesIMGDNSEnum,
        smtgBooruDNSEnum,
        yandereDNSEnum,

        useGelbooruTorEnum,
        useDanbooruTorEnum,
        useR34TorEnum,
        useAnimePicturesTorEnum,
        useSmtgBooruTorEnum,
        useYandereTorEnum,
        useAllTorEnum,

        sslCertificateEnum,
        torProxyEnum,
        gelbooruUserIdEnum,
        gelbooruKeyEnum,
        danbooruUserEnum,
        danbooruKeyEnum,
        curlUserAgentEnum,
        maxThreadsEnum,
        defaultServiceEnum
    };

    // Yes this is completely schizophrenic, I am well aware
    inline std::map<saveKeys, const char*> keyNameMap ({

        {gelbooruBasePathEnum,          "gelbooruBasePath"},
        {danbooruBasePathEnum,          "danbooruBasePath"},
        {r34BasePathEnum,               "r34BasePath"},
        {animePicturesBasePathEnum,     "animePicturesBasePath"},
        {yandereBasePathEnum,           "yandereBasePath"},
        {smtgbooruBasePathEnum,         "smtgbooruBasePath"},

        {gelbooruPageDefaultEnum,       "gelbooruPageDefault"},
        {danbooruPageDefaultEnum,       "danbooruPageDefault"},
        {danbooruNumDefaultEnum,        "danbooruNumDefault"},
        {r34PageDefaultEnum,            "r34PageDefault"},
        {animePicturesPageDefaultEnum,  "animePicturesPageDefault"},
        {smtgbooruPageDefaultEnum,      "smtgbooruPageDefault"},
        {yanderePageDefaultEnum,        "yanderePageDefault"},

        {gelbooruIPEnum,                "gelbooruIP"},
        {gelbooruIMG3IPEnum,            "gelbooruIMG3IP"},
        {gelbooruVIDIPEnum,             "gelbooruVIDIP"},
        {danbooruIPEnum,                "danbooruIP"},
        {danbooruCDNIPEnum,             "danbooruCDNIP"},
        {r34IPEnum,                     "r34IP"},
        {r34WIMGIPEnum,                 "r34WIMGIP"},
        {animePicturesIPEnum,           "animePicturesIP"},
        {animePicturesIMGIPEnum,        "animePicturesIMGIP"},
        {smtgBooruIPEnum,               "smtgBooruIP"},
        {yandereIPEnum,                 "yandereIP"},

        {gelbooruDNSEnum,               "gelbooruDNS"},
        {gelbooruIMG3DNSEnum,           "gelbooruIMG3DNS"},
        {gelbooruVIDDNSEnum,            "gelbooruVIDDNS"},
        {danbooruDNSEnum,               "danbooruDNS"},
        {danbooruCDNDNSEnum,            "danbooruCDNDNS"},
        {r34DNSEnum,                    "r34DNS"},
        {r34WIMGDNSEnum,                "r34WIMGDNS"},
        {animePicturesDNSEnum,          "animePicturesDNS"},
        {animePicturesIMGDNSEnum,       "animePicturesIMGDNS"},
        {smtgBooruDNSEnum,              "smtgBooruDNS"},
        {yandereDNSEnum,                "yandereDNS"},

        {useGelbooruTorEnum,            "useGelbooruTor"},
        {useDanbooruTorEnum,            "useDanbooruTor"},
        {useR34TorEnum,                 "useR34Tor"},
        {useAnimePicturesTorEnum,       "useAnimePicturesTor"},
        {useSmtgBooruTorEnum,           "useSmtgBooruTor"},
        {useYandereTorEnum,             "useYandereTor"},
        {useAllTorEnum,                 "useAllTor"},

        {sslCertificateEnum,            "sslCertificate"},
        {torProxyEnum,                  "torProxy"},
        {gelbooruUserIdEnum,            "gelbooruUserId"},
        {gelbooruKeyEnum,               "gelbooruKey"},
        {danbooruUserEnum,              "danbooruUser"},
        {danbooruKeyEnum,               "danbooruKey"},
        {curlUserAgentEnum,             "curlUserAgent"},
        {maxThreadsEnum,                "maxThreads"},
        {defaultServiceEnum,            "defaultService"}
    });





    inline QString gelbooruBasePath =           "";       // Root savepath for the various services
    inline QString danbooruBasePath =           "";       // !IMPORTANT!
    inline QString r34BasePath =                "";       // The program EXPECTS these to exist and
    inline QString animePicturesBasePath =      "";       // will crash if they do not
    inline QString yandereBasePath =            "";
    inline QString smtgbooruBasePath =          "";

    inline QString gelbooruPageDefault =        "2";      // Default amount of pages to download for gelbooru
    inline QString danbooruPageDefault =        "10";     // Default amount of pages to download for danbooru
    inline QString danbooruNumDefault =         "20";     // Default amount of images to download per page for danbooru
    inline QString r34PageDefault =             "2";      // Default amount of pages to download for R34
    inline QString animePicturesPageDefault =   "2";      // Default amount of pages to download for anime-pictures
    inline QString smtgbooruPageDefault =       "2";      // Default amount of pages to download for smtgbooru
    inline QString yanderePageDefault =         "2";      // Default amount of pages to download for yande.re

    inline std::string gelbooruIP =             "67.202.114.141";       // Site IPs, used for tor lookups
    inline std::string gelbooruIMG3IP =         "104.21.234.5";
    inline std::string gelbooruVIDIP =          "172.107.228.194";

    inline std::string danbooruIP =             "172.67.70.99";
    inline std::string danbooruCDNIP =          "172.67.70.99";

    inline std::string r34IP =                  "172.67.68.251";
    inline std::string r34WIMGIP =              "172.67.68.251";

    inline std::string animePicturesIP =        "95.217.86.244";
    inline std::string animePicturesIMGIP =     "172.67.160.246";

    inline std::string smtgBooruIP =            "3.130.86.89";

    inline std::string yandereIP =              "198.251.89.183";


    inline std::string gelbooruDNS =            "gelbooru.com:443:67.202.114.141";                  // Dns resolution chains
    inline std::string gelbooruIMG3DNS =        "img3.gelbooru.com:443:104.21.234.5";               // Please do keep in mind that these obviously break if a site changes their ip
    inline std::string gelbooruVIDDNS =         "video-cdn3.gelbooru.com:443:172.107.228.194";

    inline std::string danbooruDNS =            "danbooru.donmai.us:443:172.67.70.99";
    inline std::string danbooruCDNDNS =         "cdn.donmai.us:443:172.67.70.99";

    inline std::string r34DNS =                 "rule34.xxx:443:172.67.68.251";
    inline std::string r34WIMGDNS =             "wimg.rule34.xxx:443:172.67.68.251";

    inline std::string animePicturesDNS =       "anime-pictures.net:443:95.217.86.244";
    inline std::string animePicturesIMGDNS =    "images.anime-pictures.net:443:172.67.160.246";

    inline std::string smtgBooruDNS =           "smtgbooru.org:80:3.130.86.89";

    inline std::string yandereDNS =             "yande.re:443:198.251.89.183";


    inline std::string sslCertificate =         "";                             // Certificate used for tor connections (expected .crt file)
    inline std::string torProxy =               "socks5://localhost:9150";      // SOCKS5 proxy
    inline std::string gelbooruUserId =         "";                             // User Id used for gelbooru
    inline std::string gelbooruKey =            "";                             // API key used for gelbooru
    inline std::string danbooruUser =           "";                             // User used for danbooru
    inline std::string danbooruKey =            "";                             // API key used for danbooru
    inline std::string curlUserAgent =          "ScuffDownloader/1.0";          // User agent used for curl

    inline unsigned int defaultService =        0;  // Default service to use
                                                    // 0 - Gelbooru
                                                    // 1 - Danbooru
                                                    // 2 - R34
                                                    // 3 - Anime-Pictures
                                                    // 4 - smtgbooru
                                                    // 5 - Yandere

    inline int maxThreads =                     12; // Maximum allowed amount of threads allowed at once

    // Use tor for services
    inline Qt::CheckState useGelbooruTor =             Qt::CheckState::Unchecked;
    inline Qt::CheckState useDanbooruTor =             Qt::CheckState::Unchecked;
    inline Qt::CheckState useR34Tor =                  Qt::CheckState::Unchecked;
    inline Qt::CheckState useAnimePicturesTor =        Qt::CheckState::Unchecked;
    inline Qt::CheckState useSmtgBooruTor =            Qt::CheckState::Unchecked;
    inline Qt::CheckState useAllTor =                  Qt::CheckState::Unchecked;
    inline Qt::CheckState useYandereTor =              Qt::CheckState::Unchecked;

    // inline scuff::Semaphore globalSem(globals::maxThreads);

}

#endif // GLOBALS_H
