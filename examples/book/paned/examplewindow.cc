/* gtkmm example Copyright (C) 2002 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VPaned(Gtk::Orientation::VERTICAL)
{
  set_title ("Paned Windows");
  set_default_size(450, 400);
  m_VPaned.set_margin(10);

  /* Add a vpaned widget to our toplevel window */
  set_child(m_VPaned);

  /* Now add the contents of the two halves of the window */
  m_VPaned.set_start_child(m_MessagesList);
  m_VPaned.set_end_child(m_MessageText);
}

ExampleWindow::~ExampleWindow()
{
}
