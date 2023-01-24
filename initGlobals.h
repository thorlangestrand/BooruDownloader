#ifndef INITGLOBALS_H
#define INITGLOBALS_H

#include <filesystem>
#include <shlobj.h>
#include <combaseapi.h>
#include <knownfolders.h>

#include "utf8_parse.h"
#include "globals.h"
#include "saveGlobals.h"
#include "warn.h"

///
/// \brief initGlobals
///
/// Initialize globals from disk if config file
/// located in C:\users\${USER}\local\ScuffDownloader
/// exists
///
/// If folder ScuffDownloader does not exist, attempt
/// to create it
///
/// If config file does not exist, initialize with default
/// globals defined in globals.h
///
/// \see    globals.h
///
/// \return bool - true if globals initialized correctly,
///                false if errors
///
bool initGlobals();

#endif // INITGLOBALS_H
