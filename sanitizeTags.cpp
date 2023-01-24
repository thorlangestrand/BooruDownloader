#include "sanitizeTags.h"

std::string sanitizeTags(QString qStr)
{
    std::string str = qStr.toStdString();

    std::regex killSlashes("[\\\\]");
    std::regex removeDoubles("[\\\"]");
    std::regex removeSingles("[\']");

    std::string q = std::regex_replace(str, killSlashes, "");

    std::string w = std::regex_replace(q, removeDoubles, "");

    std::string e = std::regex_replace(w, removeSingles, "%27");

    return e;
}
