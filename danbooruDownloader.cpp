#include "danbooruDownloader.h"

bool downloadDanbooruImage(std::string file_url, int id, size_t pageNumber, size_t imageNumber, const std::string& basePath, scuff::Semaphore& maxJobs)
{

    std::scoped_lock w(maxJobs);

    std::stringstream ss;
    ss << basePath << pageNumber << " " << imageNumber << " " << id;

    std::string extension = file_url.substr(file_url.length() - 4);

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

    if (!fp) {
        QString wMsg = "Failed to open file ";
        wMsg += ss.str().c_str();
        Warn(wMsg);
        return false;
    }

    CURL* curl = curl_easy_init();

    if (globals::useAllTor || globals::useDanbooruTor)
    {
        struct curl_slist* dns = curl_slist_append(NULL, globals::danbooruDNS.c_str());
        curl_slist_append(dns, globals::danbooruCDNDNS.c_str());
        return curlDownloadToFilePointerTor(curl, dns, file_url, fp);
    }
    else
    {
        return curlDownloadToFilePointer(curl, file_url, fp);
    }
}

bool danbooruDownloader(const char* rawJson, size_t pageNumber, std::string basePath)
{

    scuff::json res = scuff::parseJson(rawJson);

    if (res.nChildren == 0)
    {
        QString wMsg = QString("No results returned at page %1").arg(pageNumber);
        Warn(wMsg);
        res.erase();
        return false;
    }

    if (!std::filesystem::exists(basePath))
    {
        if (!std::filesystem::create_directory(basePath))
        {
             QString wMsg = "Failed to create directory: " + QString::fromStdString(basePath);
             Warn(wMsg);
             res.erase();
             return false;
        }
    }

    std::vector<std::future<bool>> imgDownloadFutures = {};

    imgDownloadFutures.reserve(20);
    scuff::Semaphore maxJobs(globals::maxThreads);

    for (size_t i = 0; i < res.nChildren; ++i)
    {
        std::string file_url = res[i]["file_url"];
        int id = res[i]["id"];
        imgDownloadFutures.push_back(std::async(std::launch::async, downloadDanbooruImage, file_url, id, pageNumber - 1, i, basePath, std::ref(maxJobs)));
    }

    res.erase();
    return true;
}
