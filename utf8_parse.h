#ifndef UTF8_PARSE_H
#define UTF8_PARSE_H

#include <string>           // IWYU pragma: export
#include <stringapiset.h>

///
/// \brief utf8_encode
///
/// Convert string to wstring
///
/// \param  wstr   - wide string input
/// \return string - utf-8 encoded string
///
std::string utf8_encode(const std::wstring& wstr);

///
/// \brief utf8_decode
///
/// Convert wstring to string
///
/// \param  str     - string input
/// \return wstring - wstring encoded data
///
std::wstring utf8_decode(const std::string& str);

#endif // UTF8_PARSE_H
