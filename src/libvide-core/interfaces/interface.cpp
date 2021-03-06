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

#include <vide/vide.h>
#include <vide/interface.h>

using namespace std;

InterfacePlugin::InterfacePlugin(Vide* vide, std::string pluginName)
    : VidePlugin(vide, string("Interface::") + pluginName)
{
}

InterfacePlugin::~InterfacePlugin()
{
}

Interface::Interface(Editor* editor)
{
    m_editor = editor;
}

Interface::~Interface()
{
}

void Interface::key(Frontier::KeyEvent* keyEvent)
{
}


CursorType Interface::getCursorType()
{
    return CURSOR_BLOCK;
}

std::wstring Interface::getStatus()
{
    return L"";
}



