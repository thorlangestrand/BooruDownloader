#ifndef SMTGDOWNLOADER_H
#define SMTGDOWNLOADER_H

#include <curl/curl.h>
#include <iostream>
#include <regex>
#include <sstream>
#include <sys/stat.h>
#include <stdint.h>
#include <filesystem>
#include <future>
#include <vector>

#include "globals.h"
#include "warn.h"
#include "curlWriteFunctions.h"
#include "curlDownloadToFilePointer.h"
#include "semaphore.h"

struct smtgImageData;

///
/// \brief smtgDownloader
///
/// Download images contained in a page grabbed from
/// the /smtg/ booru
///
/// \param  rawPageHtml  - Raw html to be parsed
/// \param  pageNumber   - Page number
/// \param  savePathRoot - Base save poth
///
/// \return bool         - True if success, false if fail or no more images
///
/// \see parseSmtgPage
/// \see downloadSmtgImage
///
bool smtgDownloader(std::vector<std::string> htmlData, std::string savePathRoot);

///
/// \brief parseSmtgPage
///
/// Parse out the image ids out of a page
/// passed in by caller and store them in
/// imageIDs
///
/// \param  rawPageHtml     - Page to be parsed
/// \param  imageIds        - Container to store parsed IDs
/// \return bool            - True if success, false if fail
///
bool parseSmtgPage(const std::string& rawPageHtml, std::vector<std::string>& imageIDs, int pageNum);

///
/// \brief downloadSmtgImage
///
/// \param  image           - Struct containing image ID and whether or not
///                           it is animated
/// \param  savePathRoot    - Base path for saving
/// \param  pageNum         - Page number
/// \param  imgNum          - Image number
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
bool downloadSmtgImage(smtgImageData image, std::string savePathRoot, size_t pageNum, size_t imgNum, scuff::Semaphore& maxJobs);

#endif // SMTGDOWNLOADER_H
