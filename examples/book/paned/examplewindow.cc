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
: m_VPaned(Gtk::ORIENTATION_VERTICAL)
{
  set_title ("Paned Windows");
  set_border_width(10);
  set_default_size(450, 400);

  /* Add a vpaned widget to our toplevel window */
  add(m_VPaned);

  /* Now add the contents of the two halves of the window */
  m_VPaned.add1(m_MessagesList);
  m_VPaned.add2(m_MessageText);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}
