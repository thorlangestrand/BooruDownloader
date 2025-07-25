#include "yandereDownloader.h"

bool downloadYandereImage(std::string file_url, std::string file_ext, int id, size_t pageNumber, size_t fileNumber, const std::string& basePath, scuff::Semaphore& maxJobs) {
    std::scoped_lock w(maxJobs);

    std::stringstream ss;
    ss << basePath << pageNumber << " " << fileNumber << " " << id << "." << file_ext;

    FILE* fp = fopen(ss.str().c_str(), "wb");
    if (!fp) {
        QString wMsg = "Failed to open file ";
        wMsg += ss.str().c_str();
        Warn(wMsg);
        return false;
    }

    CURL* curl = curl_easy_init();

    if (globals::useAllTor || globals::useYandereTor)
    {
        struct curl_slist* dns = curl_slist_append(NULL, globals::yandereDNS.c_str());
        return curlDownloadToFilePointerTor(curl, dns, file_url, fp);
    }
    else
    {
        return curlDownloadToFilePointer(curl, file_url, fp);
    }


    return true;
}

struct imageDataY  {
    size_t pageNumber;
    size_t fileNumber;
    int id;
    std::string file_url;
    std::string file_ext;
};

bool yandereDownloader(std::vector<std::string> dataStrings, std::string basePath) {

    // Collecting all the image data in one place so it can be bulk downloaded smoothly
    std::vector<imageDataY> images = {};

    qDebug() << dataStrings[0];
    for (size_t i = 0; i < dataStrings.size(); ++i)
    {
        scuff::json res = scuff::parseJson(dataStrings[i].c_str());

        for (size_t j = 0; j < res.nChildren; ++j) {
            scuff::json thisPost = res[j];
            images.push_back({
                i,
                j,
                thisPost["id"],
                thisPost["file_url"],
                thisPost["file_ext"]
            });
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
        imgDownloadFutures.push_back(std::async(std::launch::async, downloadYandereImage, images[i].file_url, images[i].file_ext, images[i].id, images[i].pageNumber, images[i].fileNumber, basePath, std::ref(maxJobs)));
    }

    return true;
}
