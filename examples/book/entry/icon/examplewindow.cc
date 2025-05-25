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
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Close("Close")
{
  set_title("Gtk::Entry");

  set_child(m_VBox);

  m_Entry.set_max_length(50);
  m_Entry.set_text("Hello world");
  m_VBox.append(m_Entry);

  m_Entry.set_icon_from_icon_name("edit-find");
  m_Entry.signal_icon_press().connect( sigc::mem_fun(*this, &ExampleWindow::on_icon_pressed) );


  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );
  m_VBox.append(m_Button_Close);
  set_default_widget(m_Button_Close);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_icon_pressed(Gtk::Entry::IconPosition /* icon_pos */)
{
  std::cout << "Icon pressed." << std::endl;
}

void ExampleWindow::on_button_close()
{
  set_visible(false);
}

