#ifndef JSON_H
#define JSON_H

#include <map>
#include <vector>
#include <iostream>
#include <algorithm>
#include <cctype>

namespace scuff {
  class json;
  void parseScope(json* scope, unsigned int& jsonPointer, const char* json);
  void parseArrayScope(json* scope, unsigned int& jsonPointer, const char* json);
  void getLabel(unsigned int& jsonPointer, const char* json, std::string& out);
  json parseJson(const char* rawJson);

  enum ScopeDataType { STRING = 0, INT = 1, DOUBLE = 2, BOOL = 3, JSNULL = 4, LL = 5, ULL = 6 };

  class json {
  public:
    const char* spacer = "  ";
    bool array = false;
    bool pureObjectData = false; // the two hardest things in coding
    void* pData = nullptr;
    ScopeDataType pdsType = ScopeDataType::STRING;
    std::string label = "";
    size_t nChildren = 0;
    std::vector<json*> arrChildren;
    std::map<std::string, json*> children;

    json(bool _array = false, std::string _label = "");
    json(std::string _label, std::string _data, bool _str);

    virtual ~json() {}


    // Opted for no explicit deep copy constructor
    // and instead having a different function for deep deletion
    void erase();

    json operator[] (std::string key) {
      if (array) {
        std::cout << "ERROR: attempted hasmap index on array\n";
        return json();
      }
      try {
        return *children.at(key);
      }
      catch (std::out_of_range& e)
      {
        std::cout << "Error thrown by: " << e.what() << "\n";
        std::cout << "No child " << key << " found at object with name " << label << "\n";
        return json();
      }
    }

    json operator[] (const char* key) {
      if (array) {
        std::cout << "ERROR: attempted hasmap index on array\n";
        return json();
      }
      try {
        return *children.at(key);
      }
      catch (std::out_of_range& e)
      {
        std::cout << "Error thrown by: " << e.what() << "\n";
        std::cout << "No child " << key << " found at object with name " << label << "\n";
        return json();
      }
    }


    json operator[] (size_t index) {
      if (!array) {
        std::cout << "ERROR: attempted index search on non-array\n";
        return json();
      }
      if (index >= nChildren) {
        std::cout << "ERROR: passed index is out of bounds for array " << label << "\n";
        return json();
      }
      return *arrChildren[index];
    }

    json operator[] (int index) {
      if (!array) {
        std::cout << "ERROR: attempted index search on non-array\n";
        return json();
      }
      if (index >= (int)nChildren) {
        std::cout << "ERROR: passed index is out of bounds for array " << label << "\n";
        return json();
      }
      return *arrChildren[index];
    }

    operator int() const {
      if (!pureObjectData) {
        std::cout << "ERROR: attempted int conversion on impure data structure with name " << label << "\n";
        return 0;
      }
      if (pdsType == ScopeDataType::JSNULL) {
        std::cout << "ERROR: attempted int conversion on nullptr at item with name " << label << "\n";
        return 0;
      }
      if (pdsType == ScopeDataType::STRING) {
        std::cout << "ERROR: attempted int conversion on string at item with name " << label << "\n";
        return 0;
      }

      // Data can only be int, double or bool, all valid conversions
      // Doing this truncates doubles instead of rounding them so that's something to be aware of
      return *(int*)pData;
    }

    operator size_t() const {
      if (!pureObjectData) {
        std::cout << "ERROR: attempted int conversion on impure data structure with name " << label << "\n";
        return 0;
      }
      if (pdsType == ScopeDataType::JSNULL) {
        std::cout << "ERROR: attempted int conversion on nullptr at item with name " << label << "\n";
        return 0;
      }
      if (pdsType == ScopeDataType::STRING) {
        std::cout << "ERROR: attempted int conversion on string at item with name " << label << "\n";
        return 0;
      }

      // Data can only be int, double or bool, all valid conversions
      // This can add garbage if the original size of the data is not 64 bits
      // Now that I think of it I'm not handling 64 bit numbers at all am i, lol
      // Well javascript can only handle 53 bit precision so it'll probably be fine.
      return *(unsigned long long*)pData;
    }

    operator double() const {
      if (!pureObjectData) {
        std::cout << "ERROR: attempted double conversion on impure data structure with name " << label << "\n";
        return 0;
      }
      if (pdsType == ScopeDataType::JSNULL) {
        std::cout << "ERROR: attempted double conversion on nullptr at item with name " << label << "\n";
        return 0;
      }
      if (pdsType == ScopeDataType::STRING) {
        std::cout << "ERROR: attempted double conversion on string at item with name " << label << "\n";
        return 0;
      }

      // Data can only be int, double or bool, all valid conversions
      return *(double*)pData;
    }

    operator std::string() const {
      if (!pureObjectData) {
        std::cout << "ERROR: attempted std::string conversion on impure data structure with name " << label << "\n";
        return std::string();
      }
      if (pdsType == ScopeDataType::JSNULL) {
        std::cout << "ERROR: attempted std::string conversion on nullptr at item with name " << label << "\n";
        return std::string();
      }

      switch (pdsType)
      {
      case ScopeDataType::STRING: {
        return *(std::string*)pData;
      }
      case ScopeDataType::BOOL: {
        return std::to_string(*(bool*)pData);
      }
      case ScopeDataType::INT: {
        return std::to_string(*(int*)pData);
      }
      case ScopeDataType::DOUBLE: {
        return std::to_string(*(double*)pData);
      }
      case ScopeDataType::LL: {
        return std::to_string(*(long long*)pData);
      }
      case ScopeDataType::ULL: {
        return std::to_string(*(unsigned long long*)pData);
      }
      default: {
        return std::string();
      }
      }
    }




    operator bool() const {
      if (!pureObjectData) {
        std::cout << "ERROR: attempted bool conversion on impure data structure with name " << label << "\n";
        return 0;
      }
      if (pdsType == ScopeDataType::JSNULL) {
        std::cout << "ERROR: attempted bool conversion on nullptr at item with name " << label << "\n";
        return 0;
      }

      // Hey, if you wanna cast a double to a bool more power to you brother
      // Fun fact: bools can technically range from 0 to 255, meaning if you
      // raw cast a bool to 200 and send it to std::cout, it will print 200 due to some
      // cursed conversions
      switch (pdsType)
      {
      case ScopeDataType::STRING: {
        return !(*(std::string*)pData).empty(); // If empty string cast to false, if non-empty cast to true
      }
      case ScopeDataType::BOOL: {
        return *(bool*)pData;
      }
      case ScopeDataType::INT: {
        return !(*(int*)pData == 0); // If 0 cast to false, else cast to true
      }
      case ScopeDataType::DOUBLE: {
        return !(*(double*)pData == 0.0); // If 0 cast to false, else cast to true
      }
      case ScopeDataType::LL: {
        return (!*(long long*)pData) == 0;
      }
      case ScopeDataType::ULL: {
        return (!*(unsigned long long*)pData) == 0;
      }
      default: {
        return false;
      }
      }
    }





    /// @brief
    /// To explain this badness: this only gets called when the item is printed directly
    /// That makes it require slightly different logic from the print function, such as
    /// a depth meter
    /// @param out
    /// @param scope
    /// @return
    friend std::ostream& operator << (std::ostream& out, const json& scope) {
      size_t depth = 0;

      if (scope.label.length())
      {
        out << '\"' << scope.label << '\"' << ": ";
      }

      if (scope.pureObjectData)
      {
        switch (scope.pdsType)
        {
        case ScopeDataType::STRING: {
          out << '\"' << *(std::string*)(scope.pData) << '\"';
          break;
        }
        case ScopeDataType::INT: {
          out << *(int*)(scope.pData);
          break;
        }
        case ScopeDataType::DOUBLE: {
          out << *(double*)(scope.pData);
          break;
        }
        case ScopeDataType::BOOL: {
          out << *(bool*)(scope.pData);
          break;
        }
        case ScopeDataType::JSNULL: {
          out << "null";
          break;
        }
        case ScopeDataType::LL: {
          out << *(long long*)scope.pData;
          break;
        }
        case ScopeDataType::ULL: {
          out << *(unsigned long long*)scope.pData;
          break;
        }
        default: {
          std::cout << "Error invalid json!";
          break;
        }
        }

        out << '\n';
        return out;
      }
      else if (scope.array)
      {
        out << "[\n";

        for (size_t i = 0; i < scope.arrChildren.size(); ++i)
        {
          if (i != scope.nChildren - 1) { scope.arrChildren[i]->print(out, depth + 1, true); }
          else { scope.arrChildren[i]->print(out, depth + 1, true, true); }
        }

        out << "]\n";
        return out;
      }
      else {
        out << "{\n";

        for (std::map<std::string, json*>::const_iterator it = scope.children.begin(); it != scope.children.end(); it++)
        {
          if (it != scope.children.end() && std::next(it) == scope.children.end())
          {
            it->second->print(out, depth + 1, false, true);
          }
          else {
            it->second->print(out, depth + 1, false, false);            
          }
        }
        out << "}\n";
        return out;
      }
      return out;
    }


    void print(std::ostream& out, size_t depth, bool arrmember = false, bool finalArrMember = false) {
      if (pureObjectData) {
        for (size_t i = 0; i < depth; ++i) { out << spacer; }
        out << '\"' << label << '\"' << ": ";
        switch (pdsType)
        {
        case ScopeDataType::STRING: {
          out << '\"' << *(std::string*)(pData) << '\"';
          break;
        }
        case ScopeDataType::INT: {
          out << *(int*)(pData);
          break;
        }
        case ScopeDataType::DOUBLE: {
          out << *(double*)(pData);
          break;
        }
        case ScopeDataType::BOOL: {
          out << *(bool*)(pData);
          break;
        }
        case ScopeDataType::JSNULL: {
          out << "null";
          break;
        }
        case ScopeDataType::LL: {
          out << *(long long*)pData;
          break;
        }
        case ScopeDataType::ULL: {
          out << *(unsigned long long*)pData;
          break;
        }
        default: {
          out << "Error invalid json!";
          break;
        }
        }
        if (!finalArrMember) { out << ","; }
        out << '\n';
      }
      else if (array) {
        for (size_t i = 0; i < depth; ++i) { out << spacer; }
        if (!arrmember) { out << '\"' << label << '\"' << ": "; }
        out << "[\n";

        for (size_t i = 0; i < arrChildren.size(); ++i)
        {
          if (i != nChildren - 1) { arrChildren[i]->print(out, depth + 1, true); }
          else { arrChildren[i]->print(out, depth + 1, true, true); }
        }
        for (size_t i = 0; i < depth; ++i) { out << spacer; }
        out << "]\n";
      }
      else {
        for (size_t i = 0; i < depth; ++i) { out << spacer; }
        if (!arrmember) { out << "\"" << label << "\"" << ": "; }
        out << "{\n";

        for (std::pair<const std::string, json*>& it : children)
        {
          it.second->print(out, depth + 1, false, it.first == children.rbegin()->first);
        }
        for (size_t i = 0; i < depth; ++i) { out << spacer; }
        out << "}";
        if (!finalArrMember) { out << ","; }
        out << "\n";
      }
    }
  };

  class PureObjectDataScope : public json {
  public:
    ~PureObjectDataScope() override
    {
      switch (pdsType)
      {
      case ScopeDataType::STRING: {
        delete (std::string*)pData;
        break;
      }
      case ScopeDataType::INT: {
        delete (int*)pData;
        break;
      }
      case ScopeDataType::DOUBLE: {
        delete (double*)pData;
        break;
      }
      case ScopeDataType::BOOL: {
        delete (bool*)pData;
        break;
      }
      case ScopeDataType::JSNULL: {
        // Deleting a null pointer seems like a fun idea
        break;
      }
      default: {
        std::cout << "Error invalid json!";
        break;
      }
      }
    }
  };

  class PureObjectArrayMember : public json {
  public:




    ~PureObjectArrayMember() override
    {
      switch (pdsType)
      {
      case ScopeDataType::STRING: {
        delete (std::string*)pData;
        break;
      }
      case ScopeDataType::INT: {
        delete (int*)pData;
        break;
      }
      case ScopeDataType::DOUBLE: {
        delete (double*)pData;
        break;
      }
      case ScopeDataType::BOOL: {
        delete (bool*)pData;
        break;
      }
      case ScopeDataType::JSNULL: {
        // Deleting a null pointer seems like a fun idea
        break;
      }
      default: {
        std::cout << "Error invalid json!";
        break;
      }
      }
    }
  };

}

#endif //JSON_H
