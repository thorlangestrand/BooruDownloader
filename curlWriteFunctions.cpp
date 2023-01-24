#include "curlWriteFunctions.h"

size_t WriteCallbackString(void* contents, size_t size, size_t nmemb, void* userp)
{
  ((std::string*)userp)->append((char*)contents, size * nmemb);
  return size * nmemb;
}


size_t WriteCallbackFile(void* contents, size_t size, size_t nmemb, void* userp)
{
  return fwrite(contents, size, nmemb, (FILE*)userp);
}
