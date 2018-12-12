#ifndef __VIDE_PLUGINS_GITPLUGIN_H_
#define __VIDE_PLUGINS_GITPLUGIN_H_

#include "plugins/plugins.h"

#include <git2.h>

class Project;
class ProjectEntry;

class GitPlugin : public VidePlugin
{
 private:

 public:
    GitPlugin(Vide* vide);
    virtual ~GitPlugin();

    virtual bool init();
    virtual bool shutdown();

    void onOpenProject(Project* project);
    void onOpenProjectEntry(ProjectEntry* project);
};

#endif
