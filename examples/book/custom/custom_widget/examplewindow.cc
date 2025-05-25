/* gtkmm example Copyright (C) 2004 gtkmm development team
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
: m_Button_Quit("Quit")
{
  set_title("Custom Widget example");
  set_default_size(600, 400);

  m_Grid.set_margin(6);
  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  set_child(m_Grid);

  m_Grid.attach(m_MyWidgetS1, 0, 0);
  m_Grid.attach(m_MyWidgetS2, 1, 1);

  m_Grid.attach(m_ButtonBox, 0, 2, 2, 1);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(6);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this, &ExampleWindow::on_button_quit) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}
