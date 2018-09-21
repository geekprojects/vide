#ifndef __VIDE_BUFFER_H_
#define __VIDE_BUFFER_H_

#include <vector>
#include <string>
#include <wchar.h>

struct LineToken
{
    std::wstring text;
    uint32_t colour;
};

struct Line
{
    std::wstring text;
    std::wstring lineEnding;

    std::vector<LineToken*> tokens;

    Line()
    {
        text = L"";
        lineEnding = L"";
    }

    ~Line()
    {
        clearTokens();
    }

    void clearTokens();
};

class Buffer
{
 private:
    std::vector<Line*> m_lines;

 public:
    Buffer();
    ~Buffer();

    size_t getLineCount() { return m_lines.size(); }
    size_t getLineLength(unsigned int line)
    {
        if (line >= m_lines.size())
        {
            return -1;
        }
        return m_lines.at(line)->text.length();
    }

    std::vector<Line*>& getLines() { return m_lines; }
    Line* getLine(int y) { return m_lines.at(y); }

    void dump();

    static Buffer* loadFile(const char* filename);
};

#endif

