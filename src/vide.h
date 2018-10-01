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

#ifndef __VIDE_VIDE_H_
#define __VIDE_VIDE_H_

#include <frontier/frontier.h>
#include <frontier/widgets.h>

#include "videwindow.h"
#include "project.h"

class VideWindow;

class Vide : public Frontier::FrontierApp
{
 private:
    Project* m_project;
    VideWindow* m_mainWindow;
    FontHandle* m_textFont;

 public:
    Vide();
    ~Vide();

    virtual bool init();

    FontHandle* getTextFont() { return m_textFont; }

    VideWindow* getWindow() { return m_mainWindow; }
    Project* getProject() { return m_project; }
};

#endif
