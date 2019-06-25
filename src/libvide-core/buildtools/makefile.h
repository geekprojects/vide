#ifndef __VIDE_BUILDTOOLS_Makefile_H_
#define __VIDE_BUILDTOOLS_Makefile_H_

#include <vide/buildtool.h>

class MakefileBuildTool : public BuildTool
{
 private:

 public:
    MakefileBuildTool(Vide* vide);
    virtual ~MakefileBuildTool();

    virtual FileHandlerPriority canHandle(ProjectModule* project);

    virtual std::vector<std::string> getFileFlags(ProjectFile* file);
};

#endif
