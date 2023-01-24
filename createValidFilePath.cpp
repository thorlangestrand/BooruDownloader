#include "sanitizeTags.h"

QString createValidFilePath(QString basePath, QString sanitizedTags)
{
    // #######################################
    // #                 YEP                 #
    // #######################################

    // Setting up regex because I'm too SBS to do them all at once

    std::regex forwardSlash("[/]");
    std::regex colon("[:]");
    std::regex star("[*]");
    std::regex question("[?]");
    std::regex leftCarat("[<]");
    std::regex rightCarat("[>]");
    std::regex orSymbol("[|]");

    // Cleaning up http ugliness
    std::regex apostrophe("%27");

    // Base tags
    std::string validBase = sanitizedTags.toStdString();

    // Whole bunch of shit
    std::string q = std::regex_replace(validBase, forwardSlash, "");

    std::string w = std::regex_replace(q, colon, " ");
    std::string e = std::regex_replace(w, star, "");
    std::string r = std::regex_replace(e, question, "");
    std::string t = std::regex_replace(r, leftCarat, "");
    std::string y = std::regex_replace(t, rightCarat, "");
    std::string u = std::regex_replace(y, orSymbol, "");
    std::string i = std::regex_replace(u, apostrophe, "'");

    QString gigaSanitized = QString::fromStdString(i);
    gigaSanitized = gigaSanitized.trimmed();
    QString completeBase = basePath + "\\" + gigaSanitized + "\\";
    
    return completeBase;
}
