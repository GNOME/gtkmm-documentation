/* gtkmm example Copyright (C) 2002 gtkmm development team
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
#include <iostream>

ExampleWindow::ExampleWindow()
: m_button(Gtk::ICON_SIZE_BUTTON, 0.0, 100.0, 10.0)
{
  //Make the window big enough to show the popup scale from the GtkVolumeButton.
  //Otherwise it will be truncated.
  set_default_size(300, 300);

  set_title("ScaleButton Example");
  set_border_width(12);

  std::vector<Glib::ustring> icons;
  icons.push_back("audio-volume-low");
  icons.push_back("audio-volume-high");
  icons.push_back("audio-volume-medium");
  m_button.set_icons(icons);

  add(m_grid);
  m_grid.set_vexpand(true);
  m_grid.set_hexpand(true);

  m_grid.attach(m_button, 1, 1, 1, 1);
  m_button.set_valign(Gtk::ALIGN_END);
  m_button.set_halign(Gtk::ALIGN_END);

  m_button.set_value(30.0);
  m_button.signal_value_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_value_changed));

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_value_changed(double value)
{
  std::cout << "Value: " << value << std::endl;
}


