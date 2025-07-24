#ifndef CHECKTORCONNECTION_H
#define CHECKTORCONNECTION_H

#include <curl/curl.h>

#include "json.h"                   // IWYU pragma: export
#include "globals.h"                // IWYU pragma: export
#include "curlWriteFunctions.h"     // IWYU pragma: export

///
/// \brief checkTorConnection
///
/// Checks whether tor successfully connected
///
/// \return bool        - true if success, false if fail
///
bool checkTorConnection();

#endif // CHECKTORCONNECTION_H
