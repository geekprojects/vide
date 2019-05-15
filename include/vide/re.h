#ifndef __VIDE_RE_H_
#define __VIDE_RE_H_

#include <pcre.h>

#include <string>
#include <vector>

struct Match
{
    int start;
    int end;
};

class RegularExpression
{
 private:
    pcre32* m_re;

 public:
     RegularExpression();
     ~RegularExpression();

     bool compile(std::wstring pattern);

     std::vector<Match> match(std::wstring text);

     std::wstring replace(std::wstring text, std::wstring replacement);
};

#endif

