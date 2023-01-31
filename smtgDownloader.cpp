#include "smtgDownloader.h"

struct smtgImageData
{
    std::string id = "";
    bool animated = false;
};

void parseSmtgPage(const std::string& rawPageHtml, std::vector<smtgImageData>& imageIDs)
{
    size_t index = 0;
    size_t pageLen = rawPageHtml.length();
    size_t bufSize = 128;
    bool animated = false;

    char c;
    char* buf = (char*)malloc(sizeof(char) * bufSize);

    do {
      c = rawPageHtml[index++];
      if (c == '<')
      {
        size_t i = 0;
        bufSize = 128; // Reset buffer size to standard size every run
        do {
          c = rawPageHtml[index++];

          if (c == ' ')
          {
            memset(buf, 0, bufSize);
            i = 0;
            continue;
          }

          if (c == '=')
          {
            if (strcmp(buf, "data-mime") == 0)
            {
                memset(buf, 0, bufSize);

                do {
                  c = rawPageHtml[index++];
                } while (c!='\'');
                i = 0;

                do {
                    c = rawPageHtml[index++];
                    buf[i++] = c;
                } while(c!='\'');
                buf[--i] = '\0';

                if (strcmp(buf, "image/gif") == 0)
                {
                    animated = true;
                }
                else
                {
                    animated = false;
                }
            }

            if (strcmp(buf, "data-post-id") == 0)
            {
              memset(buf, 0, bufSize);

              do {
                c = rawPageHtml[index++];
              } while (c != '\'');
              i = 0;

              do {
                c = rawPageHtml[index++];
                buf[i++] = c;
              } while (c != '\'');
              buf[--i] = '\0';

              imageIDs.push_back({buf, animated});

              break;
            }
          }

          // Extend buffer if need be
          if (i == bufSize)
          {
              bufSize *= 2;
              buf = (char*)realloc(buf, bufSize);
          }

          buf[i++] = c;

        } while (c != '>');
      }
    } while (index < pageLen);
    free(buf);
}

bool downloadSmtgImage(smtgImageData image, std::string savePathRoot, size_t pageNum, size_t imgNum, scuff::Semaphore& maxJobs)
{

    std::scoped_lock w(maxJobs);
    std::stringstream ss;

    ss << "http://www.smtgbooru.org/index.php?q=image/" << image.id;

    std::string imgUrl = ss.str();

    ss.str(std::string());  // Reset content
    ss.clear();             // Reset flags

    ss << savePathRoot << " " << pageNum << " " << imgNum << " "<< image.id << (image.animated ? ".gif" : ".png");

    FILE* fp = fopen(ss.str().c_str(), "wb");
    if (!fp)
    {
        QString wMsg = "Failed to open file ";
        wMsg += ss.str().c_str();
        Warn(wMsg);
        return false;
    }

    CURL* curl = curl_easy_init();

    if (globals::useAllTor || globals::useSmtgBooruTor)
    {
        struct curl_slist* dns = curl_slist_append(NULL, globals::smtgBooruDNS.c_str());
        return curlDownloadToFilePointerTor(curl, dns, imgUrl, fp);
    }
    else
    {
        return curlDownloadToFilePointer(curl, imgUrl, fp);
    }

    return true;
}

bool smtgDownloader(const std::string& rawHtml, size_t pageNumber, std::string savePathRoot)
{
    std::vector<smtgImageData> imageIDs = {};
    parseSmtgPage(rawHtml, imageIDs);

    if (imageIDs.size() == 0)
    {
        return false;
    }

    if (!std::filesystem::exists(savePathRoot))
    {
        if (!std::filesystem::create_directory(savePathRoot))
        {
            QString wMsg = "Failed to create directory ";
            wMsg += savePathRoot.c_str();
            Warn(wMsg);
            return false;
        }
    }

    scuff::Semaphore maxJobs(globals::maxThreads);
    std::vector<std::future<bool>> imgDownloadFutures = {};

    for (size_t i = 0; i < imageIDs.size(); ++i)
    {
        imgDownloadFutures.push_back(std::async(std::launch::async, downloadSmtgImage, imageIDs[i], savePathRoot, pageNumber, i, std::ref(maxJobs)));
    }

    return true;
}
