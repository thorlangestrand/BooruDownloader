#ifndef CURLDOWNLOADTOSTRINGBUFFER_H
#define CURLDOWNLOADTOSTRINGBUFFER_H

#include <string>
#include <curl/curl.h>

#include "curlWriteFunctions.h"
#include "globals.h"
#include "warn.h"       // IWYU pragma: export

///
/// \brief curlDownloadToStringBuffer
///
/// Takes ownership of curl pointer and deletes it
///
/// Downloads data to buffer given by outBuf from url
///
/// Gives a warning if anything goes wrong during write
/// \see Warn
///
/// \param  curl   - curl pointer used for downloads
/// \param  url    - url to be downloaded from
/// \param  outBuf - buffer to be written to
///
/// \return bool   - false if failed, true if succeed
///
bool curlDownloadToStringBuffer(CURL* curl, const std::string& url, std::string& outBuf);

///
/// \brief curlDownloadToStringBufferTor
///
/// Takes ownership of curl pointer and deletes it
///
/// Downloads data to buffer given by outBuf through tor from url
///
/// Gives a warning if anything goes wrong during write
/// \see Warn
///
/// \param  curl   - curl pointer used for downloads
/// \param  dns    - custom dns resolve
/// \param  url    - url to be downloaded from
/// \param  outBuf - buffer to be written to
///
/// \return bool   - false if failed, true if succeed
///
bool curlDownloadToStringBufferTor(CURL* curl, struct curl_slist* dns, const std::string& url, std::string& outBuf);

#endif // CURLDOWNLOADTOSTRINGBUFFER_H
