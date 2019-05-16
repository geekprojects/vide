
#include <vide/re.h>

using namespace std;

RegularExpression::RegularExpression()
{
    m_re = NULL;
}

RegularExpression::~RegularExpression()
{
    if (m_re != NULL)
    {
        pcre32_free(m_re);
    }
}

bool RegularExpression::compile(wstring pattern)
{
    const char* error;
    int   erroffset;

    m_re = pcre32_compile((PCRE_SPTR32)pattern.c_str(), 0, &error, &erroffset, 0);
    printf("RegularExpression::compile: m_re=%p\n", m_re);
    if (m_re == NULL)
    {
        printf("pcre_compile failed (offset: %d), %s\n", erroffset, error);
        return false;
    }

    return true;
}

vector<Match> RegularExpression::match(wstring text)
{
    vector<Match> matches;
    if (m_re == NULL)
    {
        return matches;
    }

    unsigned int offset = 0;
    unsigned int len    = text.length();
    int ovector[10 * 3];
    while (offset < len)
    {
        int rc;

        rc = pcre32_exec(m_re, 0, (PCRE_SPTR32)text.c_str(), len, offset, 0, ovector, 10 * 3);
        if (rc < 0)
        {
            break;
        }

        for(int i = 0; i < rc; ++i)
        {
            Match match;
            match.start = ovector[2*i];
            match.end = ovector[(2*i) + 1];
            matches.push_back(match);
        }
        offset = ovector[1];
    }
    return matches;
}

wstring RegularExpression::replace(std::wstring text, std::wstring replacement)
{
    if (m_re == NULL)
    {
        return text;
    }

    vector<Match> matches = match(text);
    wstring out = text;
    int delta = 0;
    for (Match match : matches)
    {
        int len = match.end - match.start;
        out.replace(match.start + delta, len, replacement);
        delta += replacement.length() - len;
        printf("Delta: %d\n", delta);
    }

    return out;
}

#if 0
int main(int argc, char** argv)
{
    //wstring pattern = L"th[a-z]*";
    //wstring replacement = L"wibble";
    wstring pattern = L"t[a-z]*";
    wstring str = L"test this thing and that thing";
    wstring replacement = L"???";

    RegularExpression re;
    re.compile(pattern);
    wstring out = re.replace(str, replacement);

    printf("out: %ls\n", out.c_str());

    return 0;
}
#endif

