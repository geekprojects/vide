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

#include "ui/videwindow.h"
#include "filetypes/filetypemanager.h"
#include "project.h"

class VideWindow;

class Vide : public Frontier::FrontierApp
{
 private:
    std::string m_projectDir;
    Project* m_project;
    VideWindow* m_mainWindow;
    FontHandle* m_textFont;

    std::vector<std::wstring> m_buffer;

 public:
    Vide(std::string projectDir);
    virtual ~Vide();

    virtual bool init();

    FontHandle* getTextFont() { return m_textFont; }

    VideWindow* getWindow() { return m_mainWindow; }
    Project* getProject() { return m_project; }

    void setBuffer(std::vector<std::wstring> buffer) { m_buffer = buffer; }
    std::vector<std::wstring> getBuffer() { return m_buffer; }
};

#endif
