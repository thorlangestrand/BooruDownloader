#include "curlDownloadToFilePointer.h"

bool curlDownloadToFilePointer(CURL* curl, std::string url, FILE* fp)
{
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackFile);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_CAINFO, globals::sslCertificate.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, globals::curlUserAgent.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300L);

    CURLcode cRes = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    /// Should add some error handling / logging in here probably
    if (cRes == CURLE_OPERATION_TIMEDOUT)
    {
        fclose(fp);
        return true;
    }

    if (cRes != CURLE_OK)
    {
        QString wMsg = QString("Error performing curl. Error code: %1").arg((int)cRes);
        Warn(wMsg);
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}

bool curlDownloadToFilePointerTor(CURL* curl, struct curl_slist* dns, std::string url, FILE* fp)
{
    curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallbackFile);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, fp);
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1);
    curl_easy_setopt(curl, CURLOPT_CAINFO, globals::sslCertificate.c_str());
    curl_easy_setopt(curl, CURLOPT_USERAGENT, globals::curlUserAgent.c_str());
    curl_easy_setopt(curl, CURLOPT_TIMEOUT, 300L);
    curl_easy_setopt(curl, CURLOPT_PROXY, globals::torProxy.c_str());
    curl_easy_setopt(curl, CURLOPT_RESOLVE, dns);


    CURLcode cRes = curl_easy_perform(curl);
    curl_easy_cleanup(curl);

    /// Should add some error handling / logging in here probably
    if (cRes == CURLE_OPERATION_TIMEDOUT)
    {
        fclose(fp);
        return true;
    }

    if (cRes != CURLE_OK)
    {
        QString wMsg = QString("Error performing curl. Error code: %1").arg((int)cRes);
        Warn(wMsg);
        fclose(fp);
        return false;
    }

    fclose(fp);
    return true;
}
