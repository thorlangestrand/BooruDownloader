#ifndef SAVEGLOBALS_H
#define SAVEGLOBALS_H

#include <filesystem>
#include <shlobj.h>
#include <combaseapi.h>
#include <knownfolders.h>
#include <fstream>

#include "globals.h"
#include "warn.h"
#include "utf8_parse.h"

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
