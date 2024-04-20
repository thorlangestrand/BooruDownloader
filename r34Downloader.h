#ifndef R34DOWNLOADER_H
#define R34DOWNLOADER_H

#include <string>
#include <sstream>
#include <curl/curl.h>
#include <thread>
#include <filesystem>
#include <future>

#include "json.h"
#include "curlWriteFunctions.h"
#include "globals.h"
#include "semaphore.h"
#include "curlDownloadToFilePointer.h"
#include "warn.h"

///
/// \brief r34Downloader
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
/// \see json
///
bool r34Downloader(std::vector<std::string> dataStrings, const std::string& basePath);

///
/// \brief downloadR34Image
///
/// Downloads image to disk, either through normal means
/// or through tor given the status of globals
///
/// \param  file_url        - File to be downloaded
/// \param  id              - Image r34 id
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
bool downloadR34Image(std::string file_url, int id, size_t pageNumber, size_t imageNumber, const std::string& basePath, scuff::Semaphore& maxJobs);

#endif // R34DOWNLOADER_H
