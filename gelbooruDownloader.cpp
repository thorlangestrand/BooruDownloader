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






/**
 * @brief gelbooruDownloader
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
bool gelbooruDownloader(const char* rawJson, size_t pageNumber, std::string basePath)
{

  scuff::json res = scuff::parseJson(rawJson);

  if (res["post"].nChildren == 0)
  {
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

  scuff::Semaphore maxJobs(globals::maxThreads);

  std::vector<std::future<bool>> imgDownloadFutures = {};
  imgDownloadFutures.reserve(100);

  for (size_t i = 0; i < res["post"].nChildren; ++i)
  {
      std::string file_url = res["post"][i]["file_url"];
      int id = res["post"][i]["id"];
      imgDownloadFutures.push_back(std::async(std::launch::async, downloadGelbooruImage, file_url, id, pageNumber, i, basePath, std::ref(maxJobs)));
  }

  res.erase();
  return true;
}

