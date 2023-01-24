#include "checkTorConnection.h"

bool checkTorConnection()
{
    std::string resBuffer = "";
    CURL* curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "https://check.torproject.org/api/ip");
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &resBuffer);
    curl_easy_setopt(curl, CURLOPT_VERBOSE, 0);
    curl_easy_setopt(curl, CURLOPT_CAINFO, globals::sslCertificate.c_str());
    curl_easy_setopt(curl, CURLOPT_PROXY, globals::torProxy.c_str());

    CURLcode r = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    if (r != CURLcode::CURLE_OK)
    {
        return false;
    }

    scuff::json res = scuff::parseJson(resBuffer.c_str());

    bool v = res["IsTor"];
    res.erase();
    return v;
}
