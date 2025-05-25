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

  //Change the progress fraction every 0.1 second:
  Glib::signal_timeout().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_timeout),
    100
  );

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );
  m_VBox.append(m_Button_Close);
  set_default_widget(m_Button_Close);
}

ExampleWindow::~ExampleWindow()
{
}

bool ExampleWindow::on_timeout()
{
  static double fraction = 0;
  m_Entry.set_progress_fraction(fraction);

  fraction += 0.01;
  if(fraction > 1)
    fraction = 0;

  return true;
}

void ExampleWindow::on_button_close()
{
  set_visible(false);
}

