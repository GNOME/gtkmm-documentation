/* gtkmm example Copyright (C) 2025 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, see <https://www.gnu.org/licenses/>.
 */

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>
#include "exampleglarea.h" // Include our custom GLArea

class ExampleWindow : public Gtk::Window
{
public:
    ExampleWindow();

protected:
    // Signal handlers:
    void on_quit_button_clicked();

private:
    Gtk::Box m_main_vbox; // Main container for widgets
    ExampleGLArea m_gl_area;  // Our OpenGL area
    Gtk::Button m_quit_button; // Quit button
};

#endif // GTKMM_EXAMPLEWINDOW_H
