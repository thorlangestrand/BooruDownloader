#ifndef GELBOORUDOWNLOADER_H
#define GELBOORUDOWNLOADER_H

#include <string>
#include <sstream>
#include <filesystem>
#include <curl/curl.h>
#include <future>
#include <vector>

#include "json.h"
#include "globals.h"
#include "curlWriteFunctions.h"
#include "curlDownloadToFilePointer.h"
#include "semaphore.h"
#include "warn.h"

///
/// \brief gelbooruDownloader
///
/// Downloads images in page given by rawJson
///
/// \param  rawJson      - Pointer to unparsed json, not freed as it's
///                        given by c_str()
/// \param  pageNumber   - Page number
/// \param  basePath     - Base save poth
///
/// \return bool         - True if success, false if fail or no more images
///
/// \see    json
///
bool gelbooruDownloader(std::vector<std::string>, std::string basePath);

///
/// \brief downloadGelbooruImage
///
/// Downloads image to disk, either through normal means
/// or through tor given the status of globals
///
/// \param  file_url        - File to be downloaded
/// \param  id              - Image gelbooru id
/// \param  pageNumber      - Page number
/// \param  imageNumber     - Image number
/// \param  basePath        - Base save path
/// \param  maxJobs         - Semaphore to limit concurrency to max threads
///                           given by globals
///
/// \return bool            - True if success, false if fail
///
/// \see    globals
/// \see    curlDownloadToFilePointer
/// \see    curlDownloadToFilePointerTor
/// \see    Semaphore
/// \see    Warn
///
bool downloadGelbooruImage(std::string file_url, int id, size_t pageNumber, size_t imageNumber, const std::string& basePath, scuff::Semaphore& maxJobs);

#endif // GELBOORUDOWNLOADER_H
