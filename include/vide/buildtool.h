#ifndef __VIDE_BUILDTOOLS_BUILDTOOL_H_
#define __VIDE_BUILDTOOLS_BUILDTOOL_H_

#include <vide/project.h>
#include <vide/plugins.h>

#include <vector>

class ProjectModule;
class ProjectFile;

class BuildTool : public VidePlugin
{
 private:

 public:
    BuildTool(Vide* vide);
    virtual ~BuildTool();

    bool init();

    virtual FileHandlerPriority canHandle(ProjectModule* module);

    virtual std::vector<std::string> getFileFlags(ProjectFile* file);
};

#endif
