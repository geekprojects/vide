
#include <vide/vide.h>

#include <stdio.h>
#include <getopt.h>

#include <string>

using namespace std;

static struct option g_globalOptions[] =
{
    {"project", required_argument, 0, 'p'},
    {0, 0, 0, 0}
};

void commandTokenise(int argc, char** argv, Vide* vide, string projectPath)
{
    if (argc < 1)
    {
        printf("tokenise: Expected path to file\n");
        return;
    }

    string file = argv[0];

    Project* project = vide->openProject(projectPath);

    ProjectEntry* entry = project->getEntry(file);
    Buffer* buffer = entry->open();

    FileTypeManager* ftm = entry->getFileTypeManager();
    printf("tokenise: ftm=%p\n", ftm);
    ftm->tokenise(buffer);
}

void commandIndex(int argc, char** argv, Vide* vide, string projectPath)
{
    if (argc < 1)
    {
        printf("index: Expected path to file\n");
        return;
    }

    string file = argv[0];

    Project* project = vide->openProject(projectPath);

    ProjectEntry* entry = project->getEntry(file);

    FileTypeManager* ftm = entry->getFileTypeManager();
    printf("index: ftm=%p\n", ftm);
    ftm->index((ProjectFile*)entry);
}


int main(int argc, char** argv)
{
    string projectPath = ".";
    while (true)
    {
        int optionIndex = 0;
        int c;

        c = getopt_long(argc, argv, "p:", g_globalOptions, &optionIndex);
        if (c == -1)
        {
            break;
        }

        switch (c)
        {
            case 'p':
                projectPath = string(optarg);
                break;
        }
    }

    if (optind >= argc)
    {
        printf("%s: Expected command\n", argv[0]);
        exit(-1);
    }

    string command = argv[optind++];

    printf("ProjectPath: %s\n", projectPath.c_str());
    printf("Command: %s\n", command.c_str());

    Vide* vide = new Vide();
    vide->init();

    if (command == "tokenise")
    {
        commandTokenise(argc - optind, argv + optind, vide, projectPath);
    }
    else if (command == "index")
    {
        commandIndex(argc - optind, argv + optind, vide, projectPath);
    }

    delete vide;

    return 0;
}

