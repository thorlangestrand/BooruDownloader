#ifndef SANITIZETAGS_H
#define SANITIZETAGS_H

#include <QString>

#include <string>
#include <regex>    // IWYU pragma: export

///
/// \brief sanitizeTags
///
/// Removes ', " and \ from tags and replaces
/// them with url encodings where applicable
///
/// \param  qStr   - String to be sanitized
///
/// \return string - Sanitized tags
///
std::string sanitizeTags(QString qStr);


///
/// \brief createValidFilePath
///
/// Replaces tokens that cannot be used in
/// windows file path but can still be used
/// as valid parts of tags
///
/// \param  basePath       - Base path taken from ui
/// \param  sanitizedTags  - Tags with certain elements removed
///
/// \return QString        - Valid file path for windows 10
///
QString createValidFilePath(QString basePath, QString sanitizedTags);

#endif // SANITIZETAGS_H
