#include "danbooruDownloader.h"

bool downloadDanbooruImage(std::string file_url, std::string large_file_url, int id, size_t pageNumber, size_t imageNumber, const std::string& basePath, scuff::Semaphore& maxJobs)
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
        file_url = large_file_url;
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

struct imageDataD {
    int pageNumber;
    int fileNumber;
    int id;
    std::string file_url;
    std::string large_file_url;
};

bool danbooruDownloader(std::vector<std::string> dataStrings, std::string basePath)
{


    // Collecting all the image data in one place so it can be bulk downloaded smoothly
    std::vector<imageDataD> images = {};

    for (size_t i = 0; i < dataStrings.size(); ++i)
    {
        scuff::json res = scuff::parseJson(dataStrings[i].c_str());

        int rsNchildren = res.nChildren;

        for (int j = 0; j < rsNchildren; ++j)
        {
            scuff::json thisPost = res[j];
            images.push_back({static_cast<int>(i), static_cast<int>(j), thisPost["id"], thisPost["file_url"], thisPost["large_file_url"]});
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
        imgDownloadFutures.push_back(std::async(std::launch::async, downloadDanbooruImage, images[i].file_url, images[i].large_file_url, images[i].id, images[i].pageNumber, images[i].fileNumber, basePath, std::ref(maxJobs)));
    }

    return true;
}
