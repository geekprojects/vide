
#include <gtest/gtest.h>

#include <vide/vide.h>
#include <vide/editor.h>

using namespace std;

string TEST_TEXT = "  \n  Hello world!  \nAnother line!   \n  ";

struct EditorTestData
{
    Vide* vide;
    Buffer* buffer;
    Editor* editor;
    TextFileTypeManager* ftm;

    EditorTestData()
    {
        init(TEST_TEXT);
    }

    EditorTestData(string text)
    {
        init(text);
    }

    void init(string text)
    {
        vide = new Vide();
        vide->init();

        buffer = Buffer::loadString("test.txt", text);

        ftm = new TextFileTypeManager(vide);

        editor = new Editor(vide, buffer, ftm);

        ftm->tokenise(buffer);
    }

    ~EditorTestData()
    {
        delete editor;
        delete ftm;
        delete buffer;
        delete vide;
    }
};

#define EXPECT_EQ_POSITION(_line, _column, _pos) \
    EXPECT_EQ((unsigned)_line, (_pos).line); \
    EXPECT_EQ((unsigned)_column, (_pos).column);

TEST(VideEditorTest, findPrevWord)
{
    EditorTestData etd;

    Position pos;

    pos = etd.editor->findPrevWord(Position(1, 8));
    EXPECT_EQ_POSITION(1, 2, pos);

    pos = etd.editor->findPrevWord(Position(2, 8));
    EXPECT_EQ_POSITION(2, 0, pos);

    pos = etd.editor->findPrevWord(Position(1, 0));
    EXPECT_EQ_POSITION(0, 0, pos);

    pos = etd.editor->findPrevWord(Position(2, 3));
    EXPECT_EQ_POSITION(1, 8, pos);
}

TEST(VideEditorTest, findNextWord)
{
    EditorTestData etd;

    Position pos;

    pos = etd.editor->findNextWord(Position(1, 8));
    EXPECT_EQ_POSITION(2, 0, pos);

    pos = etd.editor->findNextWord(Position(0, 0));
    EXPECT_EQ_POSITION(1, 2, pos);

    pos = etd.editor->findNextWord(Position(2, 9));
    EXPECT_EQ_POSITION(3, 1, pos);
}

TEST(VideEditorTest, getCharAtCursor)
{
    EditorTestData etd;
    wchar_t c;

    etd.editor->moveCursor(Position(0, 0));
    c = etd.editor->getCharAtCursor();
    EXPECT_EQ(L' ', c);

    etd.editor->moveCursor(Position(1, 2));
    c = etd.editor->getCharAtCursor();
    EXPECT_EQ(L'H', c);

    etd.editor->moveCursor(Position(10, 10));
    c = etd.editor->getCharAtCursor();
    EXPECT_EQ(L' ', c);
}

TEST(VideEditorTest, moveCursor)
{
    Position pos;
    EditorTestData etd;

    etd.editor->moveCursor(Position(0, 0));
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 0, pos);

    etd.editor->moveCursor(Position(0, 10));
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);

    etd.editor->moveCursor(Position(10, 10));
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(3, 1, pos);
}

TEST(VideEditorTest, moveCursorX)
{
    Position pos;
    EditorTestData etd;

    etd.editor->moveCursor(Position(0, 0));

    etd.editor->moveCursorX(1);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);

    etd.editor->moveCursorX(2, false);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);

    etd.editor->moveCursorX(2, true);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 2, pos);

    etd.editor->moveCursorX(3, true);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 2, pos);

    etd.editor->moveCursorX(-1);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 0, pos);

    etd.editor->moveCursorX(-1, true);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 0, pos);
}

TEST(VideEditorTest, moveCursorY)
{
    Position pos;
    EditorTestData etd;

    etd.editor->moveCursor(Position(0, 0));

    etd.editor->moveCursorY(1);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(1, 0, pos);

    etd.editor->moveCursorX(5);
    etd.editor->moveCursorY(0);
    pos = etd.editor->getCursorPosition();

    // This looks wrong, but it isn't!
    // This means that we remember the X pos when moving up and down the buffer
    // Inserting to a shorter line will result in the text being appended
    EXPECT_EQ_POSITION(0, 5, pos);

    etd.editor->moveCursorY(100);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(3, 5, pos);
}

TEST(VideEditorTest, moveCursorDelta)
{
    Position pos;
    EditorTestData etd;

    etd.editor->moveCursor(Position(0, 0));

    etd.editor->moveCursorDelta(1, 0);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);

    etd.editor->moveCursorDelta(1, 0);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);

    etd.editor->moveCursorDelta(1, 0, true);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 2, pos);

    etd.editor->moveCursorDelta(1, 0, true);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 2, pos);

    etd.editor->moveCursorDelta(-1, 0);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);

    etd.editor->moveCursorDelta(0, 1);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(1, 1, pos);

    etd.editor->moveCursorDelta(0, 1);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(2, 1, pos);

    etd.editor->moveCursorDelta(0, 1);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(3, 1, pos);

    etd.editor->moveCursorDelta(0, 1);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(3, 1, pos);

    etd.editor->moveCursorDelta(0, 1, true);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(3, 1, pos);

    etd.editor->moveCursorDelta(0, -1, true);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(2, 1, pos);

    etd.editor->moveCursorDelta(5, 0);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(2, 6, pos);

    etd.editor->moveCursorDelta(0, -2);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 6, pos);

    etd.editor->moveCursorDelta(-1, 0);
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);
}

TEST(VideEditorTest, moveCursorXEnd)
{
    Position pos;
    EditorTestData etd;

    etd.editor->moveCursor(Position(0, 0));
    etd.editor->moveCursorXEnd();
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(0, 1, pos);

    etd.editor->moveCursor(Position(1, 0));
    etd.editor->moveCursorXEnd();
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(1, 15, pos);
}

TEST(VideEditorTest, moveCursorPage)
{
    Position pos;
    EditorTestData etd;

    etd.editor->moveCursor(Position(0, 0));
    etd.editor->moveCursorYEnd();
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(3, 0, pos);
}

TEST(VideEditorTest, moveCursorYEnd)
{
    Position pos;
    EditorTestData etd;

    etd.editor->moveCursor(Position(0, 0));
    etd.editor->moveCursorYEnd();
    pos = etd.editor->getCursorPosition();
    EXPECT_EQ_POSITION(3, 0, pos);
}

