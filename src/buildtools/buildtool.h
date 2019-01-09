#ifndef __VIDE_BUILDTOOLS_BUILDTOOL_H_
#define __VIDE_BUILDTOOLS_BUILDTOOL_H_

#include "project/project.h"
#include "plugins/plugins.h"

#include <vector>

class BuildTool : public VidePlugin
{
 private:

 public:
    BuildTool(Vide* vide);
    virtual ~BuildTool();

    bool init();

    virtual FileHandlerPriority canHandle(Project* project);

    virtual std::vector<std::string> getFileFlags(ProjectFile* file);
};

#endif
