
#include "plugins/gitplugin.h"

#include "project/project.h"
#include "vide.h"
#include "ui/videwindow.h"

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
    printf("GitPlugin::onOpenProject: Here!\n");

    git_repository *repo = NULL;
    int error = git_repository_open_ext(&repo, project->getRootPath().c_str(), 0, NULL);
    if (error != 0)
    {
        printf("GitPlugin::onOpenProject: Error opening repository\n");
        return;
    }

    git_reference* repoRef;
    git_repository_head(&repoRef, repo);

    const char* name = git_reference_shorthand(repoRef);
    printf("GitPlugin::onOpenProject: head name: %s\n", name);

    VideWindow* window = getVide()->getProjectWindow(project);
    printf("GitPlugin::onOpenProject: VideWindow=%p\n", window);

    git_reference_free(repoRef);

    git_repository_free(repo);

    project->openEntrySignal().connect(sigc::mem_fun(*this, &GitPlugin::onOpenProjectEntry));
}

void GitPlugin::onOpenProjectEntry(ProjectEntry* projectEntry)
{
    int error;
    printf("GitPlugin::onOpenProjectEntry: Here!\n");

    git_repository *repo = NULL;
    error = git_repository_open_ext(&repo, projectEntry->getProject()->getRootPath().c_str(), 0, NULL);
    if (error != 0)
    {
        printf("GitPlugin::onOpenProjectEntry: Failed to open repository: %d\n", error);
        return;
    }

    git_blame* blame;
    error = git_blame_file(&blame, repo, projectEntry->getFilePath().c_str(), NULL);
    if (error != 0)
    {
        const git_error *e = giterr_last();
        printf("GitPlugin::onOpenProjectEntry: Failed to open blame: %d\n", error);
        printf("Error %d/%d: %s\n", error, e->klass, e->message);
        return;
    }
    printf("GitPlugin::onOpenProjectEntry: blame=%p\n", blame);

    const git_blame_hunk* hunk;
    hunk = git_blame_get_hunk_byline(blame, 1);
    printf("GitPlugin::onOpenProjectEntry: hunk=%p\n", hunk);

    git_commit* commit;
    git_commit_lookup(&commit, repo, &(hunk->final_commit_id));

    printf("GitPlugin::onOpenProjectEntry: 1: %s\n", git_commit_message(commit));

    git_blame_free(blame);
}

