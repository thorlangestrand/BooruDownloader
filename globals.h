#ifndef GLOBALS_H
#define GLOBALS_H

#include <QString>

#include <string>
#include "semaphore.h"
///
/// \brief globals
///
/// Global variables used throughout the program
///
/// \see initGlobals
///
namespace globals
{
    inline QString gelbooruBasePath =           "";       // Root savepath for the various services
    inline QString danbooruBasePath =           "";       // !IMPORTANT!
    inline QString r34BasePath =                "";       // The program EXPECTS these to exist and
    inline QString animePicturesBasePath =      "";       // will crash if they do not
    inline QString smtgbooruBasePath =          "";

    inline QString gelbooruPageDefault =        "2";      // Default amount of pages to download for gelbooru
    inline QString danbooruPageDefault =        "10";     // Default amount of pages to download for danbooru
    inline QString danbooruNumDefault =         "20";     // Default amount of images to download per page for danbooru
    inline QString r34PageDefault =             "2";      // Default amount of pages to download for R34
    inline QString animePicturesPageDefault =   "2";      // Default amount of pages to download for anime-pictures
    inline QString smtgbooruPageDefault =       "2";      // Default amount of pages to download for smtgbooru

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


    inline std::string gelbooruDNS =            "gelbooru.com:443:67.202.114.141";                  // Dns resolution chains
    inline std::string gelbooruIMG3DNS =        "img3.gelbooru.com:443:104.21.234.5";
    inline std::string gelbooruVIDDNS =         "video-cdn3.gelbooru.com:443:172.107.228.194";

    inline std::string danbooruDNS =            "danbooru.donmai.us:443:172.67.70.99";
    inline std::string danbooruCDNDNS =         "cdn.donmai.us:443:172.67.70.99";

    inline std::string r34DNS =                 "rule34.xxx:443:172.67.68.251";
    inline std::string r34WIMGDNS =             "wimg.rule34.xxx:443:172.67.68.251";

    inline std::string animePicturesDNS =       "anime-pictures.net:443:95.217.86.244";
    inline std::string animePicturesIMGDNS =    "images.anime-pictures.net:443:172.67.160.246";

    inline std::string smtgBooruDNS =           "smtgbooru.org:80:3.130.86.89";


    inline std::string sslCertificate =         "";                             // Certificate used for tor connections (expected .crt file)
    inline std::string torProxy =               "socks5://localhost:9150";      // SOCKS5 proxy
    inline std::string danbooruUser =           "";                             // User used for danbooru
    inline std::string danbooruKey =            "";                             // API key used for danbooru
    inline std::string curlUserAgent =          "ScuffDownloader/1.0";          // User agent used for curl

    inline unsigned int defaultService =        0;  // Default service to use
                                                    // 0 - Gelbooru
                                                    // 1 - Danbooru
                                                    // 2 - R34
                                                    // 3 - Anime-Pictures
                                                    // 4 - smtgbooru

    inline int maxThreads =                     12; // Maximum allowed amount of threads allowed at once

    // Use tor for services
    inline Qt::CheckState useGelbooruTor =             Qt::CheckState::Unchecked;
    inline Qt::CheckState useDanbooruTor =             Qt::CheckState::Unchecked;
    inline Qt::CheckState useR34Tor =                  Qt::CheckState::Unchecked;
    inline Qt::CheckState useAnimePicturesTor =        Qt::CheckState::Unchecked;
    inline Qt::CheckState useSmtgBooruTor =            Qt::CheckState::Unchecked;
    inline Qt::CheckState useAllTor =                  Qt::CheckState::Unchecked;

    // inline scuff::Semaphore globalSem(globals::maxThreads);

}

#endif // GLOBALS_H
