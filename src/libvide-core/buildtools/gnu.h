#ifndef __VIDE_BUILDTOOLS_GNU_H_
#define __VIDE_BUILDTOOLS_GNU_H_

#include "makefile.h"

class GNUBuildTool : public MakefileBuildTool
{
 private:

 public:
    GNUBuildTool(Vide* vide);
    virtual ~GNUBuildTool();

    virtual FileHandlerPriority canHandle(Project* project);
};

#endif
