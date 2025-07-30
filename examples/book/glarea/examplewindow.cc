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

#include "examplewindow.h"

// Constructor implementation
ExampleWindow::ExampleWindow()
    : m_main_vbox(Gtk::Orientation::VERTICAL, 12), // Initialize vertical box with spacing
      m_gl_area(),                                 // Initialize GLArea
      m_quit_button("Quit")                        // Initialize Quit button
{
    set_title("GTKmm4 OpenGL Cube - Simplified (Mouse: Rotate, Zoom, Pan)");
    set_default_size(600, 700);

    m_main_vbox.set_margin(12);
    set_child(m_main_vbox);

    m_gl_area.set_hexpand(true);
    m_gl_area.set_vexpand(true);
    m_main_vbox.append(m_gl_area);

    m_main_vbox.append(m_quit_button);
    m_quit_button.set_hexpand(true);
    m_quit_button.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_quit_button_clicked));
}

void ExampleWindow::on_quit_button_clicked()
{
    set_visible(false); // Hide the window to gracefully exit the application
}
