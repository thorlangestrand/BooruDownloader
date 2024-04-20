#include "gelbooruDownloader.h"

bool downloadGelbooruImage(std::string file_url, int id, size_t pageNumber, size_t imageNumber, const std::string& basePath, scuff::Semaphore& maxJobs)
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

    if (globals::useAllTor || globals::useGelbooruTor)
    {
        struct curl_slist* dns = curl_slist_append(NULL, globals::gelbooruDNS.c_str());
        curl_slist_append(dns, globals::gelbooruIMG3DNS.c_str());
        curl_slist_append(dns, globals::gelbooruVIDDNS.c_str());
        return curlDownloadToFilePointerTor(curl, dns, file_url, fp);
    }
    else
    {
        return curlDownloadToFilePointer(curl, file_url, fp);
    }
}




struct imageDataG {
    int pageNumber;
    int fileNumber;
    int id;
    std::string file_url;
};


/**
 * @brief gelbooruDownloader
 * THIS IS ALL FUCKED
 * ALL THE COMMENTS ARE FUCKED
 * I WILL MAYBE FIX THEM LATER
 * LOL
 * Download a page of images defined in rawJson and save them to disk
 * based on search tags and provided base path
 *
 * This runs single-threaded so it is quite slow, but I could not get
 * multithreading to work when going through a tor proxy
 *
 * @param rawJson           -   Unprocessed response from gelbooru
 *                              @see scuff::parseJson
 * @param index             -   Which page of the gelbooru search we're on. One page is 100 results
 * @param basePath          -   Base path for images to be stored at, e.g. C:\images\fate_(series)
 * @return bool             -   True if no issues, false if something went wrong / we're out of results
 */
bool gelbooruDownloader(std::vector<std::string> dataStrings, std::string basePath)
{
    // Collecting all the image data in one place so it can be bulk downloaded smoothly
    std::vector<imageDataG> images = {};

    for (size_t i = 0; i < dataStrings.size(); ++i)
    {
        scuff::json res = scuff::parseJson(dataStrings[i].c_str());

        int rsNchildren = res["post"].nChildren;

        for (int j = 0; j < rsNchildren; ++j)
        {
            scuff::json thisPost = res["post"][j];
            images.push_back({static_cast<int>(i), static_cast<int>(j), thisPost["id"], thisPost["file_url"]});
        }

        res.erase();

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

    scuff::Semaphore maxJobs(globals::maxThreads);
    std::vector<std::future<bool>> imgDownloadFutures = {};

    imgDownloadFutures.reserve(images.size());

    for (size_t i = 0; i < images.size(); ++i)
    {
        imgDownloadFutures.push_back(std::async(std::launch::async, downloadGelbooruImage, images[i].file_url, images[i].id, images[i].pageNumber, images[i].fileNumber, basePath, std::ref(maxJobs)));
    }

    return true;
}

