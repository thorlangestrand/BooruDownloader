#ifndef CURLWRITEFUNCTIONS_H
#define CURLWRITEFUNCTIONS_H

#include <stddef.h>
#include <string>

///
/// \brief WriteCallbackString
///
/// Callback function used to write data from curl
/// to a string buffer
///
/// \param contents  - Data
/// \param size      - Size of one data item
/// \param nmemb     - Number of members
/// \param userp     - String pointer to be written to
///
/// \return size_t   - Written byte size
///
size_t WriteCallbackString(void* contents, size_t size, size_t nmemb, void* userp);

///
/// \brief WriteCallbackFile
///
/// Callback function used to write data from curl
/// to a file pointer
///
/// \param contents  - Data
/// \param size      - Size of one data item
/// \param nmemb     - Number of members
/// \param userp     - File pointer
///
/// \return size_t   - Written byte size
///
size_t WriteCallbackFile(void* contents, size_t size, size_t nmemb, void* userp);

#endif // CURLWRITEFUNCTIONS_H
