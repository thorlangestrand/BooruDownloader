#ifndef SAVEGLOBALS_H
#define SAVEGLOBALS_H

#include <filesystem>       // IWYU pragma: export
#include <shlobj.h>
#include <combaseapi.h>
#include <knownfolders.h>
#include <fstream>          // IWYU pragma: export

#include "globals.h"        // IWYU pragma: export
#include "warn.h"           // IWYU pragma: export
#include "utf8_parse.h"     // IWYU pragma: export

///
/// \brief saveGlobals
///
/// Save global variables to file
///
/// \return bool - True if success, false if fail
///
/// \see Warn
///
bool saveGlobals();

#endif // SAVEGLOBALS_H
