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
#include <gtkmm/dialog.h>


ExampleWindow::ExampleWindow()
: m_Button("Show Dialog")
{
  set_title("Gtk::Dialog example");

  add(m_Button);
  m_Button.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_clicked) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  Gtk::Dialog dialog;
  dialog.set_default_size(100,100);
  dialog.run();
}
