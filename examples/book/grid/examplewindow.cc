/* gtkmm example Copyright (C) 2011 gtkmm development team
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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_button_1("button 1"),
  m_button_2("button 2"),
  m_button_quit("Quit")
{
  set_title("Gtk::Grid");

  m_grid.set_margin(12);
  set_child(m_grid);

  m_grid.attach(m_button_1, 0, 0);
  m_grid.attach(m_button_2, 1, 0);
  m_grid.attach_next_to(m_button_quit, m_button_1, Gtk::PositionType::BOTTOM, 2, 1);

  m_button_1.signal_clicked().connect(
    sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 1") );
  m_button_2.signal_clicked().connect(
    sigc::bind( sigc::mem_fun(*this, &ExampleWindow::on_button_numbered), "button 2") );

  m_button_quit.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_quit) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void
ExampleWindow::on_button_numbered(const Glib::ustring& data)
{
  std::cout << data << " was pressed" << std::endl;
}
