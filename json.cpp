#include "json.h"
namespace scuff
{
  json::json(bool _array, std::string _label): array(_array), label(_label) {}
  
  json::json(std::string _label, std::string _data, bool _str) {
    pureObjectData = true;
    array = false;
    label = _label;
    if (_str) {
      pData = new std::string(_data);
    }
    else {
      _data.erase(std::remove(_data.begin(), _data.end(), ' '), _data.end());
      if (_data == "null")
      {
        pdsType = ScopeDataType::JSNULL;
        pData = nullptr;
      }
      else if (_data == "false" || _data == "true")
      {
        pdsType = ScopeDataType::BOOL;
        if (_data == "false") { pData = new bool(false); }
        else if (_data == "true") { pData = new bool(true); }
      }
      else {
        bool pDouble = false;
        for (size_t i = 0; i < _data.size(); ++i) {
          if (_data[i] == '.') { pDouble = true; break; }
        }
        if (pDouble) {
          pdsType = ScopeDataType::DOUBLE;
          try {
            pData = new double(std::stod(_data));
          }
          catch (std::invalid_argument&)
          {
            std::cout << "Failed stod call at value: " << _data << "\n";
            exit(1);
          }
        }
        else {
          pdsType = ScopeDataType::INT;
          try {
            pData = new int(std::stoi(_data));
          }
          catch (std::invalid_argument&)
          {
            std::cout << "Failed stoi call at value: " << _data << " due to data not being an integer\n";
            exit(1);
          }
          // If above int limit
          catch (std::out_of_range&)
          {
            // Check if negative
            if (_data[0] == '-')
            {
              pdsType = ScopeDataType::LL;
              try {
                pData = new long long(std::stoll(_data));
              }
              catch (std::out_of_range&)
              {
                std::cout << "Data " << _data << " out of range for 64 bit signed numbers\n";
                exit(1);
              }
            }

            else {

              pdsType = ScopeDataType::ULL;

              try {
                pData = new unsigned long long(std::stoull(_data));
              }
              catch (std::out_of_range&)
              {
                std::cout << "Data " << _data << " out of range for 64 bit unsigned numbers\n";
                exit(1);
              }
            }
          }
        }
      }
    }
  }






  void json::erase()
  {
    for (size_t i = 0; i < nChildren;++i) {
      arrChildren[i]->erase();
      delete arrChildren[i];
    }
    for (std::map<std::string, scuff::json*>::const_iterator it = children.begin(); it != children.cend();)
    {
      it->second->erase();
      delete it->second;
      children.erase(it++);
    }
  }


  // Find label
  void getLabel(unsigned int& jsonPointer, const char* rawJson, std::string& out)
  {
    size_t labelSearch = jsonPointer;
    unsigned char nQuotes = 0;
    size_t quotePos[2] = {};
    do {
      if (rawJson[labelSearch] == '\"') { quotePos[nQuotes++] = labelSearch; }
      --labelSearch;
    } while (nQuotes != 2);
    for (size_t i = quotePos[1] + 1; i < quotePos[0]; ++i) { out += rawJson[i]; }
  }

  /**
   * @brief
   *
   * Parse data in array scope
   *
   * @param scope         Current scope
   * @param jsonPointer   Pointer to current char location in json
   * @param json          Json to be parsed
   */
  void parseArrayScope(json* scope, unsigned int& jsonPointer, const char* rawJson)
  {

    char c;
    do {
    beginArrParse:
      c = rawJson[jsonPointer];


      // If new object scope
      if (c == '{')
      {
        json* newScope = new json(false);
        scope->arrChildren.resize(scope->nChildren + 1);
        scope->arrChildren[scope->nChildren++] = newScope;
        parseScope(newScope, ++jsonPointer, rawJson);
      }
      // Open new array scope
      else if (c == '[')
      {
        json* newScope = new json(true);
        scope->arrChildren.resize(scope->nChildren + 1);
        scope->arrChildren[scope->nChildren++] = newScope;
        parseArrayScope(newScope, ++jsonPointer, rawJson);
      }
      // Clear spaces
      else if (c == ' ')
      {
        for (;;)
        {
          c = rawJson[jsonPointer];
          if (c != ' ') { goto beginArrParse; }
          ++jsonPointer;
        }
      }
      // If none of the earlier cases are true there are only 4 states we can have
      // at the current json pointer
      // String
      // Number
      // Bool
      // Null
      // Here is where I'd implement a handler for instances like
      // "data": [1,1,2,3,5,8]
      else {
        c != ']' && ++jsonPointer;
      }
    } while (c != ']');
  }
  /**
    * @brief
    * Parse data in object scope
    *
    * @param scope         Current scope
    * @param jsonPointer   Pointer to current char location in json
    * @param json          Json to be parsed
    *
    */
  void parseScope(json* scope, unsigned int& jsonPointer, const char* rawJson)
  {

    char c;
    std::string buf = "";
    bool inQuotes = false;
    do {
    beginScopeParse:
      c = rawJson[jsonPointer];

      if (c == '\"')
      {
        buf = "";

        unsigned int tmpP = jsonPointer;
        do {
          c = rawJson[jsonPointer];
          if (c == '\"') { inQuotes = !inQuotes; }
          else if (!inQuotes && (c == '{' || c == '[')) { goto beginScopeParse; }
          ++jsonPointer;
        } while ((c != ',' && c != '}' && c != ']') || inQuotes);

        buf = "";

        // Extract label
        // At this point c can only be ',' '}' or ']' so this is safe
        while (c != '\"') {
          c = rawJson[++tmpP];

          if (c == '\"') { break; }
          buf += c;
        }

        //std::cout << '\n';
        std::string label = buf;
        buf = "";

        // Clear whitespace
        while (rawJson[tmpP + 1] == ' ' || rawJson[tmpP + 1] == ':') { ++tmpP; }

        // Move pointer one step forward to check for string
        c = rawJson[++tmpP];
        buf += c;

        // Account for sillies to put silly things like \" in their strings
        if (c == '\"') {
          bool escaped = false;
          do {
            c = rawJson[++tmpP];
            if (c == '\\') { escaped = true; }
            else if (escaped) {
              escaped = false;
              buf += c;
              c = rawJson[++tmpP];
            }
            buf += c;
          } while (c != '\"');
        }
        // If not string
        else {
          do {
            c = rawJson[++tmpP];
            buf += c;
          } while (c != ',' && c != '}');
        }

        bool str = false;
        std::string data = "";

        // Trim trailing whitespace and quotes from strings
        if (buf[0] == '\"')
        {
          str = true;
          size_t nQuotes = 0;
          bool escaped = false;
          for (size_t i = 0; nQuotes != 2; ++i)
          {
            if (buf[i] == '\\') { escaped = true; }
            else if (escaped) { data += buf[i]; escaped = false; }
            else if (buf[i] == '\"' && !escaped) { ++nQuotes; }
            else { data += buf[i]; }
          }
        }
        else {
          // Trim whitespace and trailing characters from non-string members
          for (size_t i = 0; i < buf.size(); ++i)
          {
            if (buf[i] == ' ' || buf[i] == ',' || buf[i] == '}' || buf[i] == '\n') { break; }
            data += buf[i];
          }
        }

        // Create new pure data scope
        json* pds = new json(label, data, str);
        scope->children[label] = pds;

        jsonPointer = tmpP;

      }
      else if (c == '{')
      {
        buf = "";
        getLabel(jsonPointer, rawJson, buf);
        json* newScope = new json(false, buf);
        scope->children[buf] = newScope;
        parseScope(newScope, ++jsonPointer, rawJson);
      }
      else if (c == '[')
      {
        buf = "";
        getLabel(jsonPointer, rawJson, buf);
        json* newScope = new json(true, buf);
        scope->children[buf] = newScope;
        parseArrayScope(newScope, ++jsonPointer, rawJson);
      }
      else if (c == ' ')
      {
        for (;;)
        {
          c = rawJson[jsonPointer];
          if (c != ' ') { goto beginScopeParse; }
          ++jsonPointer;
        }
      }
      c != '}' && ++jsonPointer;
    } while (c != '}');
  }


  json parseJson(const char* rawJson) {

    json root = json(false);

    unsigned int jsonPointer = 1;

    if (rawJson[0] == '[') { root.array = true; parseArrayScope(&root, jsonPointer, rawJson); }
    else { parseScope(&root, jsonPointer, rawJson); }

    return root;
  };



}
