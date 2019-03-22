
#include "buildtools/gnu.h"
#include "utils.h"

#include <geek/core-string.h>

using namespace std;
using namespace Geek;

VIDE_PLUGIN(MakefileBuildTool)

MakefileBuildTool::MakefileBuildTool(Vide* vide) : BuildTool(vide)
{
}

MakefileBuildTool::~MakefileBuildTool()
{
}

FileHandlerPriority MakefileBuildTool::canHandle(Project* project)
{
    string makefile = project->getRootPath() + "/Makefile";
    if (!Utils::fileIsReadable(makefile))
    {
        makefile = project->getRootPath() + "/makefile";
        if (!Utils::fileIsReadable(makefile))
        {
            // No configure file found
            return PRIORITY_UNSUPPORTED;
        }
    }

    log(DEBUG, "canHandle: Found Makefile: %s", makefile.c_str());

    return PRIORITY_MEDIUM;
}

vector<string> MakefileBuildTool::getFileFlags(ProjectFile* file)
{
    vector<string> flags;

    string dir = file->getProject()->getRootPath() + file->getFileDir();
    if (!Utils::fileIsReadable(dir + "/Makefile"))
    {
        return flags;
    }

    string name = file->getName();
    string obj = name;
    size_t pos = name.rfind(".");
    if (pos != string::npos)
    {
        obj = name.substr(0, pos) + ".o";
    }
    log(DEBUG, "getFileFlags: %s -> %s", name.c_str(), obj.c_str());

    std::string makeDB = Utils::exec(dir, "make -n -W " + name + " " + obj);
    log(DEBUG, "getFileFlags: makeDB:\n%s", makeDB.c_str());

    vector<string> result = Geek::Core::splitString(makeDB, ' ');
    if (!result.empty())
    {
        result.erase(result.begin());

        for (string arg : result)
        {
            log(DEBUG, "getFileFlags: arg: %s", arg.c_str());
            if (arg.at(0) == '-' &&
                (arg.at(1) == 'I' ||
                 arg.at(1) == 'W' ||
                 /*arg.at(1) == 'f' ||*/
                 arg.at(1) == 'D' ||
                 arg.find("-std") == 0
                ))
            {
                log(DEBUG, "getFileFlags:  -> Returning arg: %s", arg.c_str());
                flags.push_back(arg);
            }
        }
    }

    return flags;
}

