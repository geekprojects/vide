
#include "gitplugin.h"

#include <vide/project.h>
#include <vide/vide.h>
//#include "ui/videwindow.h"

using namespace std;
using namespace Geek;

VIDE_PLUGIN(GitPlugin);

GitPlugin::GitPlugin(Vide* vide) : VidePlugin(vide)
{
}

GitPlugin::~GitPlugin()
{
}

bool GitPlugin::init()
{
    git_libgit2_init();

    getVide()->openProjectSignal().connect(sigc::mem_fun(*this, &GitPlugin::onOpenProject));

    return true;
}


bool GitPlugin::shutdown()
{
    git_libgit2_shutdown();

    return true;
}

void GitPlugin::onOpenProject(Project* project)
{
    log(DEBUG, "onOpenProject: Opening: %s", project->getRootPath().c_str());

    git_repository *repo = NULL;
    int error = git_repository_open_ext(&repo, project->getRootPath().c_str(), 0, NULL);
    if (error != 0)
    {
        log(ERROR, "onOpenProject: Error opening repository");
        return;
    }

    git_reference* repoRef;
    git_repository_head(&repoRef, repo);

    const char* name = git_reference_shorthand(repoRef);
    log(DEBUG, "onOpenProject: head name: %s", name);

    //VideWindow* window = getVide()->getProjectWindow(project);
    //log(DEBUG, "onOpenProject: VideWindow=%p", window);

    git_reference_free(repoRef);

    git_repository_free(repo);

    project->openEntrySignal().connect(sigc::mem_fun(*this, &GitPlugin::onOpenProjectEntry));
}

void GitPlugin::onOpenProjectEntry(ProjectEntry* projectEntry)
{
    int error;
    log(DEBUG, "onOpenProjectEntry: Opening: %s", projectEntry->getFilePath().c_str());

    git_repository *repo = NULL;
    error = git_repository_open_ext(&repo, projectEntry->getProject()->getRootPath().c_str(), 0, NULL);
    if (error != 0)
    {
        log(ERROR, "onOpenProjectEntry: Failed to open repository: %d", error);
        return;
    }

    string path = projectEntry->getFilePath();
    if (path.at(0) == '/')
    {
        path = path.substr(1);
    }

    git_blame* blame;
    error = git_blame_file(&blame, repo, path.c_str(), NULL);
    if (error != 0)
    {
        const git_error *e = giterr_last();
        log(ERROR, "onOpenProjectEntry: Failed to open blame: %d/%d: %s", error, e->klass, e->message);
        return;
    }
    log(DEBUG, "onOpenProjectEntry: blame=%p", blame);

    int i = 0;
    for (i = 1; i <= 10; i++)
    {
        const git_blame_hunk* hunk;
        hunk = git_blame_get_hunk_byline(blame, i);
        log(DEBUG, "onOpenProjectEntry: hunk=%p", hunk);
        if (hunk == NULL)
        {
            break;
        }

        git_commit* commit;
        git_commit_lookup(&commit, repo, &(hunk->final_commit_id));

        log(DEBUG, "onOpenProjectEntry: %d: %s", i, git_commit_message(commit));
    }
    git_blame_free(blame);
}

