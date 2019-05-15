
#include <vide/buildtool.h>

using namespace std;

BuildTool::BuildTool(Vide* vide) : VidePlugin(vide)
{
}

BuildTool::~BuildTool()
{
}

bool BuildTool::init()
{
    getVide()->registerBuildTool(this);
    return true;
}

FileHandlerPriority BuildTool::canHandle(Project* project)
{
    return PRIORITY_UNSUPPORTED;
}

vector<string> BuildTool::getFileFlags(ProjectFile* file)
{
    vector<string> result;
    return result;
}

