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
: m_Button("Show Dialog"),
  m_Dialog()
{
  set_title("Custom Dialog example");

  set_child(m_Button);
  m_Button.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_clicked));

  m_Dialog.set_default_size(250, 100);
  m_Dialog.set_transient_for(*this);
  m_Dialog.set_modal();
  m_Dialog.set_hide_on_close();
  m_Dialog.buttons_clicked_connect(
    sigc::mem_fun(*this, &ExampleWindow::on_dialog_response));
  m_Dialog.signal_hide().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_dialog_hidden));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  m_Dialog.set_visible(true);
}

void ExampleWindow::on_dialog_response(const Glib::ustring& response)
{
  m_Dialog.set_visible(false);

  if (response == "OK")
    std::cout << "Name: " << m_Dialog.get_entry1() << " "
      << m_Dialog.get_entry2() << std::endl; 
  else
    std::cout << response << " button clicked" << std::endl;
}

void ExampleWindow::on_dialog_hidden()
{
  std::cout << "Dialog hidden" << std::endl;
}
