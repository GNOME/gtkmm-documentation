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
: m_button(0.0, 100.0, 2.0)
{
  set_default_size(300, 200);

  set_title("ScaleButton Example");

  // These are the icons used by the deprecated VolumeButton widget,
  // although it can alternatively use the corresponding symbolic icons.
  std::vector<Glib::ustring> icons;
  icons.push_back("audio-volume-muted");  // lowest value
  icons.push_back("audio-volume-high");   // highest value
  icons.push_back("audio-volume-low");    // 0% < value < 50%
  icons.push_back("audio-volume-medium"); // 50% < value < 100%
  m_button.set_icons(icons);

  m_grid.set_margin(12);
  set_child(m_grid);
  m_grid.set_expand(true);

  m_grid.attach(m_button, 1, 1);
  m_button.set_valign(Gtk::Align::END);
  m_button.set_halign(Gtk::Align::END);

  m_button.set_value(30.0);
  m_button.signal_value_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_value_changed));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_value_changed(double value)
{
  std::cout << "Value: " << value << std::endl;
}
