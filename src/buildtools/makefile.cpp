
#include "buildtools/gnu.h"
#include "utils.h"

#include <geek/core-string.h>

using namespace std;

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

    printf("MakefileBuildTool::canHandle: Found Makefile: %s\n", makefile.c_str());

    return PRIORITY_MEDIUM;
}

vector<string> MakefileBuildTool::getFileFlags(ProjectFile* file)
{
    vector<string> flags;

    if (!Utils::fileIsReadable(file->getFileDir() + "/Makefile"))
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
    printf("MakefileBuildTool::getFileFlags: %s -> %s\n", name.c_str(), obj.c_str());

    std::string makeDB = Utils::exec(file->getFileDir(), "make -n -W " + name + " " + obj);
    printf("MakefileBuildTool::getFileFlags: makeDB:\n%s\n", makeDB.c_str());

    vector<string> result = Geek::Core::splitString(makeDB, ' ');
    if (!result.empty())
    {
        result.erase(result.begin());

        for (string arg : result)
        {
            printf("MakefileBuildTool::getFileFlags: arg: %s\n", arg.c_str());
            if (arg.at(0) == '-' &&
                (arg.at(1) == 'I' ||
                 arg.at(1) == 'W' ||
                 /*arg.at(1) == 'f' ||*/
                 arg.at(1) == 'D' ||
                 arg.find("-std") == 0
                ))
            {
                printf("MakefileBuildTool::getFileFlags:  -> Returning arg: %s\n", arg.c_str());
                flags.push_back(arg);
            }
        }
    }

    return flags;
}

