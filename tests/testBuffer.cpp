
#include <gtest/gtest.h>

#include <vide/vide.h>
#include <vide/editor.h>

using namespace std;

string g_line1 = "Hello world! \u2605";
string g_line2 = "Another line! \u263A";
string g_testText = g_line1 + "\n" + g_line2;

TEST(VideBufferTest, getLineCount)
{
    Buffer* buffer = Buffer::loadString("test.txt", g_testText);

    EXPECT_EQ(2lu, buffer->getLineCount());

    delete buffer;
}

TEST(VideBufferTest, getLineLength)
{
    Buffer* buffer = Buffer::loadString("test.txt", g_testText);

    EXPECT_EQ(14lu, buffer->getLineLength(0));

    delete buffer;
}

TEST(VideBufferTest, writeToMem)
{
    Buffer* buffer = Buffer::loadString("test.txt", g_testText);

    uint32_t size;
    char* out;
    out = buffer->writeToMem(size);
    EXPECT_EQ(g_testText.length(), size);
    EXPECT_EQ(g_testText, string(out));

    delete buffer;
}

TEST(VideBufferTest, getLine)
{
    Buffer* buffer = Buffer::loadString("test.txt", g_testText);

    Line* line;

    line = buffer->getLine(0);
    EXPECT_NE(nullptr, line);

    line = buffer->getLine(10);
    EXPECT_EQ(nullptr, line);

    delete buffer;
}


TEST(VideBufferTest, getToken)
{
    Buffer* buffer = Buffer::loadString("test.txt", g_testText);

    Vide* vide = new Vide();
    TextFileTypeManager* ftm = new TextFileTypeManager(vide);

    ftm->tokenise(buffer);

    TokenAt tokenAt = buffer->getToken(Position(1, 8));
    EXPECT_EQ(wstring(L"line!"), tokenAt.token->text);

    delete ftm;
    delete vide;
    delete buffer;
}

TEST(VideBufferTest, insertLine)
{
    Buffer* buffer = Buffer::loadString("test.txt", g_testText);

    Line* newLine1 = new Line();
    newLine1->text = L"ADDED1";
    newLine1->lineEnding = "\n";
    buffer->insertLine(-1, newLine1);

    Line* newLine2 = new Line();
    newLine2->text = L"ADDED2";
    buffer->insertLine(3, newLine2);

    uint32_t size;
    char* out;
    out = buffer->writeToMem(size);

    string expectedStr = "ADDED1\n" + g_testText + "\nADDED2";
    EXPECT_EQ(expectedStr.length(), size);
    EXPECT_EQ(expectedStr, string(out));

    EXPECT_TRUE(buffer->isDirty());

    delete buffer;
}

TEST(VideBufferTest, deleteLine)
{
    Buffer* buffer = Buffer::loadString("test.txt", g_testText);

    buffer->deleteLine(0);

    EXPECT_EQ(1lu, buffer->getLineCount());

    uint32_t size;
    char* out;
    out = buffer->writeToMem(size);

    string expectedStr = g_line2;
    EXPECT_EQ(expectedStr.length(), size);
    EXPECT_EQ(expectedStr, string(out));

    EXPECT_TRUE(buffer->isDirty());

    delete buffer;
}

