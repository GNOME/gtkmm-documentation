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
: m_button("Select file", Gtk::FILE_CHOOSER_ACTION_OPEN)
{
  set_default_size(200, -1);

  set_title("FileChooserButton example");
  set_border_width(10);

  add(m_button);

  //Allow our file chooser to select remote URIs,
  //for instance via bookmarked servers:
  m_button.set_local_only(false);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

