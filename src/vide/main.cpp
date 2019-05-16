/*
 * Vide - Vi IDE
 * Copyright (C) 2018 Ian Parker <ian@geekprojects.com>
 *
 * This file is part of Vide.
 *
 * Vide is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Vide is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Vide.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "videapp.h"

using namespace std;
using namespace Frontier;

int main(int argc, char** argv)
{
    VideApp vide;
    vide.init();

    if (argc == 3 && !strcmp(argv[1], "project"))
    {
        Project* project = new Project(&vide, argv[2]);
        project->load();
        project->scan();
        project->index();
        project->dumpStructure();
        return 0;
    }

    const char* project = NULL;
    if (argc == 2)
    {
        project = argv[1];
    }


    if (project != NULL)
    {
        vide.hideWelcomeWindow();
        bool res;
        res = vide.openProject(project);
        if (!res)
        {
            vide.showWelcomeWindow();
        }
    }
    else
    {
        vide.showWelcomeWindow();
    }

    vide.main();

    return 0;
}

