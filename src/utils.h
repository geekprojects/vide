#ifndef __VIDE_UTILS_H_
#define __VIDE_UTILS_H_

#include <string>

class Utils
{
 public:
    static std::string wstring2string(std::wstring str);
    static std::wstring string2wstring(std::string str);
    static std::wstring string2wstring(const char* str);
};

#endif
