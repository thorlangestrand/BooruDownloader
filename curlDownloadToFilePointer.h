#ifndef CURLDOWNLOADTOFILEPOINTER_H
#define CURLDOWNLOADTOFILEPOINTER_H

#include <string>
#include <curl/curl.h>

#include "curlWriteFunctions.h"
#include "globals.h"
#include "warn.h"

///
/// \brief curlDownloadToFilePointer
///
/// Takes ownership of curl and fp pointers
///
/// Downloads file to file pointer given by fp
/// via curl from url
///
/// Gives a warning if anything goes wrong during save
/// \see Warn
///
/// \param  curl - curl pointer used for downloads
/// \param  url  - url to be downloaded from
/// \param  fp   - file to be downloaded to
///
/// \return bool - false if failed, true if succeed
///
bool curlDownloadToFilePointer(CURL* curl, std::string url, FILE* fp);

///
/// \brief curlDownloadToFilePointer
///
/// Takes ownership of curl and fp pointers
///
/// Downloads file to file pointer given by fp
/// via curl through tor from url
///
/// Gives a warning if anything goes wrong during save
/// \see Warn
///
/// \param  curl - curl pointer used for downloads
/// \param  dns  - custom dns resolve
/// \param  url  - url to be downloaded from
/// \param  fp   - file to be downloaded to
///
/// \return bool - false if failed, true if succeed
///
bool curlDownloadToFilePointerTor(CURL* curl, struct curl_slist* dns, std::string url, FILE* fp);

#endif // CURLDOWNLOADTOFILEPOINTER_H
