/* gtkmm example Copyright (C) 2012 gtkmm development team
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

ExampleWindow::ExampleWindow()
: m_Button_FixLines("Fix lines")
{
  set_title("Thin lines example");

  m_Container.set_orientation(Gtk::ORIENTATION_HORIZONTAL);

  m_Container.add(m_Area_Lines);
  m_Container.add(m_Button_FixLines);

  add(m_Container);

  m_Button_FixLines.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_toggled));

  // Synchonize the drawing in m_Area_Lines with the state of the toggle button.
  on_button_toggled();

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_toggled()
{
  m_Area_Lines.fix_lines(m_Button_FixLines.get_active());
}
