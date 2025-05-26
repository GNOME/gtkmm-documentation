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

ExampleWindow::ExampleWindow()
: m_Label("A child widget.")
{
 /* Set some window properties */
  set_title("Expander Example");

  /* Sets the border width of the window. */
  set_border_width(6);

  add(m_Expander);
  m_Expander.add(m_Label);

  /* Set the label */
  m_Expander.set_label("Gtk::Expander Widget");

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

