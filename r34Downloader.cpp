#include "r34Downloader.h"

bool downloadR34Image(std::string url, int id, size_t pageNumber, size_t imageNumber, const std::string& basePath, scuff::Semaphore& maxJobs)
{

    std::scoped_lock w(maxJobs);

    std::stringstream ss;
    ss << basePath << pageNumber << " " << imageNumber << " " << id;


    std::string extension = url.substr(url.length() - 4);

    if (extension == "jpeg" || extension == ".jpg" || extension == ".png")
    {
        ss << ".png";
    }
    else if (extension == ".gif")
    {
        ss << ".gif";
    }
    else
    {
        ss << ".mp4";
    }

    FILE* fp = fopen(ss.str().c_str(), "wb");

    if (!fp)
    {
        QString wMsg = "Failed to open file ";
        wMsg += ss.str().c_str();
        Warn(wMsg);
        return false;
    }

    CURL* curl = curl_easy_init();

    if (globals::useAllTor || globals::useR34Tor)
    {
        struct curl_slist* dns = curl_slist_append(NULL, globals::r34DNS.c_str());
        curl_slist_append(dns, globals::r34WIMGDNS.c_str());
        return curlDownloadToFilePointerTor(curl, dns, url, fp);
    }
    else
    {
        return curlDownloadToFilePointer(curl, url, fp);
    }
}

bool r34Downloader(const char* rawJson, size_t pageNumber, const std::string& basePath)
{
    scuff::json res = scuff::parseJson(rawJson);

    if (res.nChildren == 0)
    {
//        QString wMsg = QString("No results returned at page %1").arg(pageNumber);
//        Warn(wMsg);
        res.erase();
        return false;
    }

    if (!std::filesystem::exists(basePath))
    {
        if (!std::filesystem::create_directory(basePath))
        {
             QString wMsg = "Failed to create directory: " + QString::fromStdString(basePath);
             Warn(wMsg);
             return false;
        }
    }

    std::vector<std::string> urls = {}; urls.reserve(100);
    std::vector<int> ids = {};          ids.reserve(100);

    for (size_t i = 0; i < res.nChildren; ++i)
    {
        urls.push_back(res[i]["file_url"]);
        ids.push_back(res[i]["id"]);
    }

    res.erase();


    scuff::Semaphore maxJobs(globals::maxThreads);


    std::vector<std::future<bool>> imageDownloadFutures = {};

    for (size_t i = 0; i < urls.size(); ++i)
    {
        imageDownloadFutures.push_back(std::async(std::launch::async, downloadR34Image, urls[i], ids[i], pageNumber, i, basePath, std::ref(maxJobs)));
    }

    return true;
}
