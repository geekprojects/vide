
#include "vide.h"
#include "buffer.h"

using namespace std;
using namespace Frontier;

int main(int argc, char** argv)
{

    Vide app;

    app.init();

    app.main();
/*
Buffer* buffer = Buffer::loadFile("main.cpp");
buffer->dump();
delete buffer;
*/

    return 0;
}


