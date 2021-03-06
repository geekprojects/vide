
#include "gnu.h"
#include <vide/utils.h>

using namespace std;
using namespace Geek;

VIDE_PLUGIN(GNUBuildTool)

GNUBuildTool::GNUBuildTool(Vide* vide) : MakefileBuildTool(vide)
{
}

GNUBuildTool::~GNUBuildTool()
{
}

FileHandlerPriority GNUBuildTool::canHandle(ProjectModule* project)
{
    string confFile = project->getRootPath() + "/configure";
    if (!Utils::fileIsExecutable(confFile))
    {
        // No configure file found
        return PRIORITY_UNSUPPORTED;
    }

    log(DEBUG, "canHandle: Found configure file, checking version...");
    string version = Utils::exec(project->getRootPath(), "./configure --version");
    log(DEBUG, "canHandle: %s", version.c_str());

    string::size_type pos = version.find("generated by GNU Autoconf");
    log(DEBUG, "canHandle: Is Autoconf=%lu", pos);
    if (pos == string::npos)
    {
        return PRIORITY_UNSUPPORTED;
    }

    return PRIORITY_HIGH;
}


