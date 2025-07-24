#ifndef YANDEREDOWNLOADER_H
#define YANDEREDOWNLOADER_H

#include <string>
#include <sstream>                      // IWYU pragma: export
#include <filesystem>                   // IWYU pragma: export
#include <curl/curl.h>                  // IWYU pragma: export
#include <future>                       // IWYU pragma: export
#include <vector>

#include "json.h"                       // IWYU pragma: export
#include "globals.h"                    // IWYU pragma: export
#include "curlWriteFunctions.h"         // IWYU pragma: export
#include "curlDownloadToFilePointer.h"  // IWYU pragma: export
#include "semaphore.h"                  // IWYU pragma: export
#include "warn.h"                       // IWYU pragma: export

bool yandereDownloader(std::vector<std::string> dataStrings, std::string basePath);

#endif // YANDEREDOWNLOADER_H
