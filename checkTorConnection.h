#ifndef CHECKTORCONNECTION_H
#define CHECKTORCONNECTION_H

#include <curl/curl.h>

#include "json.h"
#include "globals.h"
#include "curlWriteFunctions.h"

///
/// \brief checkTorConnection
///
/// Checks whether tor successfully connected
///
/// \return bool        - true if success, false if fail
///
bool checkTorConnection();

#endif // CHECKTORCONNECTION_H
