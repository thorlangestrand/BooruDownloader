#ifndef ANIMEPICTURESDOWNLOADER_H
#define ANIMEPICTURESDOWNLOADER_H

#include <vector>
#include <string>
#include <string.h>
#include <future>
#include <sstream>
#include <filesystem>
#include <curl/curl.h>

#include "warn.h"
#include "semaphore.h"
#include "curlWriteFunctions.h"
#include "globals.h"
#include "curlDownloadToFilePointer.h"

struct imageData;

///
/// \brief animePicturesDownloader
///
/// Downloads images from given anime-pictures site by
/// parsing out html passed by calling function and returns bool
/// based on success or failure
///
/// \param  rawHtml      - HTML to be parsed
/// \param  pageNumber   - Current page
/// \param  basePath     - Base path of images stored
///
/// \return bool         - True if success, false if error or no more images
///
/// \see parseAnimePicturesPage
/// \see downloadAnimePicturesImage
///
bool animePicturesDownloader(std::vector<std::string> rawHtmlPages, const std::string& basePath);

///
/// \brief parseAnimePicturesPage
///
/// Parses an anime-pictures page and puts the image id and
/// url into a vector of imageData passed by calling function
///
/// \param page         - HTML to be parsed
/// \param pageLen      - Size of HTML
/// \param imageIds     - Container to hold image ids and urls
///
void parseAnimePicturesPage(char* page, int pageLen, std::vector<imageData>& imageIds, int pageNumber);

///
/// \brief parseAnimePicturesImage
///
/// It is not possible to know what format the image
/// is in from the url alone. This function runs multiple
/// tests through testAnimePicturesUrl and returns an
/// imageData object containing the image id, url and
/// whether or not it is animated
///
/// \param  img       - Image to be tested
///
/// \return ImageData - Image data with valid file download,
///                     id and animated status
///
/// \see    testAnimePicturesUrl
///
imageData parseAnimePicturesImage(const imageData& img);

///
/// \brief testAnimePicturesUrl
///
/// Test whether or not an anime-pictures image exists
/// This is done by simply checking the 404 status of a
/// requested url
///
/// It's slow and inefficient but I've not come up with
/// a better solution as the site does not supply an official
/// api for this information
///
/// \param  url    - Url to be tested
///
/// \return bool   - False if 404, true if exists
///
bool testAnimePicturesUrl(const std::string& url);

///
/// \brief downloadAnimePicturesImage
///
/// Downloads image to disk, either through normal means
/// or through tor given the status of globals
///
/// \param  imageUrl     - Url of image to be downloaded
/// \param  savePath     - Path to save file to
/// \param  maxJobs      - Semaphore to limit concurrency to max threads
///                        given by globals
///
/// \return bool         - True if success, false if fail
///
/// \see    globals
/// \see    curlDownloadToFilePointer
/// \see    curlDownloadToFilePointerTor
/// \see    Semaphore
/// \see    Warn
///
bool downloadAnimePicturesImage(const char* imageUrl, std::string savePath, scuff::Semaphore& maxJobs);

#endif // ANIMEPICTURESDOWNLOADER_H
