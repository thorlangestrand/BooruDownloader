#include "yandereDownloader.h"


// 40 per page, order seems arbitrary which is strange. Treat it like gelbooru with only page count opts

struct imageDataY  {
    int pageNumber;
    int fileNumber;
    int id;
    std::string file_url;
};

#include <QDebug>

bool yandereDownloader(std::vector<std::string> dataStrings, std::string basePath) {

    // Collecting all the image data in one place so it can be bulk downloaded smoothly
    std::vector<imageDataY> images = {};

    for (size_t i = 0; i < dataStrings.size(); ++i)
    {
        scuff::json res = scuff::parseJson(dataStrings[i].c_str());

        size_t rsNchildren = res["post"].nChildren;

        for (size_t j = 0; j < rsNchildren; ++j)
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

    qDebug() << images[0].id << " " << images[0].file_url << "\n";
    qDebug() << "HELP\n";


    return true;
}
