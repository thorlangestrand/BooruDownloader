#include "animePicturesDownloader.h"

struct imageData
{
   std::string id = "";
   std::string url = "";
   bool animated = false;
};

void parseAnimePicturesPage(const char* page, int pageLen, std::vector<imageData>& imageIds)
{

    int index = 0;

    int bufSize = 128;
    char* buf;

    char c;
    do {
      c = page[index++];

      if (c == '<')
      {
        int i = 0;

        bufSize = 128;
        buf = (char*)malloc(sizeof(char) * bufSize);

        do {
          c = page[index++];

          if (c == ' ')
          {
            memset(buf, 0, bufSize);
            i = 0;
            continue;
          }

          if (c == '=')
          {
            if (strcmp(buf, "srcset") == 0)
            {
              memset(buf, 0, bufSize);

              i = 0;

              do {
                c = page[index++];
                if (i >= bufSize) { bufSize *= 2; buf = (char*)realloc(buf, bufSize); }
                buf[i++] = c;
              } while (c != ',');
              buf[--i] = '\0';


              char* namingThings = strstr(buf, "previews/");
              bool animated = strstr(namingThings, "gif");

              char* isHard = (char*)malloc(bufSize);


              i = 0;
              do {
                c = namingThings[i + 8]; // Offset [previews] (not required to extract data)
                isHard[i++] = c;
              } while (c != '_');

              // free(namingThings); !!!
              // Cannot free pointer returned by strstr
              // as it returns a pointer somewhere along the line of the original data
              // As far as I know this is undefined behaviour

              isHard[--i] = '\0'; // Clear _ with terminator

              imageIds.push_back({ isHard, "", animated });
              free(isHard);

              break;
            }
          }

          if (i == bufSize)
          {
              bufSize *= 2; buf = (char*)realloc(buf, bufSize);
          }

          buf[i++] = c;
        } while (c != '>');

        free(buf);
      }

    } while (index < pageLen);
}




bool testAnimePicturesUrl(const std::string& url)
{
  std::string buf = "";
  CURL* curl = curl_easy_init();


  if (globals::useAllTor || globals::useAnimePicturesTor)
  {
      struct curl_slist* dns = curl_slist_append(NULL, globals::animePicturesDNS.c_str());
      curl_slist_append(dns, globals::animePicturesIMGDNS.c_str());
      curl_easy_setopt(curl, CURLOPT_RESOLVE, dns);
  }

  curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackString);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, &buf);
  curl_easy_setopt(curl, CURLOPT_NOBODY, 1);
  curl_easy_setopt(curl, CURLOPT_CAINFO, globals::sslCertificate.c_str());

  CURLcode cRes = curl_easy_perform(curl);

  if (cRes != CURLE_OK)
  {
      QString wMsg = QString("Error performing curl. Error code: %1").arg((int)cRes);
      Warn(wMsg);
      curl_easy_cleanup(curl);
      return false;
  }

  long http_code = 0;
  curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
  curl_easy_cleanup(curl);
  return http_code != 404;
}



imageData parseAnimePicturesImage(const imageData& img)
{
  std::string url = "https://images.anime-pictures.net";
  url += img.id;

  // If the image is animated that's all well and good, can only be gif
  if (img.animated)
  {
    url += ".gif";
    return { img.id, url, true };
  }

  // If it's not, however, we need to test .jpg, .jpeg and .png to see
  // whether or not they show 404
  // This is not exactly optimal but I can't think of another way of
  // doing it

  url += ".jpg";

  if (testAnimePicturesUrl(url))
  {
    return { img.id, url, false };
  }

  url.erase(url.length() - 4);
  url += ".jpeg";

  if (testAnimePicturesUrl(url))
  {
    return { img.id, url, false };
  }

  url.erase(url.length() - 5);
  url += ".png";

  if (testAnimePicturesUrl(url))
  {
    return { img.id, url , false };
  }

  return { img.id, "" , false };
}

bool downloadAnimePicturesImage(const char* imageUrl, std::string savePath, scuff::Semaphore& maxJobs)
{
    std::scoped_lock w(maxJobs);


    FILE* fp = fopen(savePath.c_str(), "wb");

    if (!fp)
    {
        QString wMsg = "Failed to open file ";
        wMsg += savePath.c_str();
        Warn(wMsg);
        return false;
    }
    CURL* curl = curl_easy_init();
    if (globals::useAllTor || globals::useAnimePicturesTor)
    {
        struct curl_slist* dns = curl_slist_append(NULL, globals::animePicturesDNS.c_str());
        curl_slist_append(dns, globals::animePicturesIMGDNS.c_str());
        return curlDownloadToFilePointerTor(curl, dns, imageUrl, fp);
    }
    else
    {
        return curlDownloadToFilePointer(curl, imageUrl, fp);
    }
}


bool animePicturesDownloader(const std::string& rawHtml, size_t pageNumber, const std::string& basePath)
{


    std::vector<imageData> images = {};

    parseAnimePicturesPage(rawHtml.c_str(), rawHtml.size(), images);

    if (images.size() == 0)
    {
//        QString wMsg = QString("No results returned at page %1").arg(pageNumber);
//        Warn(wMsg);
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

    std::vector<std::future<imageData>> urlFutures = {};

    for (size_t i = 0; i < images.size(); ++i)
    {
        urlFutures.push_back(std::async(std::launch::async, parseAnimePicturesImage, images[i]));
    }


    std::vector<imageData> urls = {};

    for (size_t i = 0; i < images.size(); ++i)
    {
        urlFutures[i].wait();
        urls.push_back(urlFutures[i].get());
    }


    scuff::Semaphore maxJobs(globals::maxThreads);
    std::vector<std::future<bool>> imageDownloadFutures = {};
    imageDownloadFutures.reserve(80);

    for (size_t i = 0; i < urls.size(); ++i)
    {
        std::stringstream ss;
        ss << basePath << pageNumber << " " << i << " " << urls[i].id.substr(5) << (urls[i].animated ? ".gif" : ".png");
        imageDownloadFutures.push_back(std::async(std::launch::async, downloadAnimePicturesImage, urls[i].url.c_str(), ss.str(), std::ref(maxJobs)));
    }

    return true;
}

























































