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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Label1("Contents of tab 1"),
  m_Label2("Contents of tab 2"),
  m_Button_Quit("Quit")
{
  set_title("Gtk::Notebook example");
  set_default_size(400, 200);

  m_VBox.set_margin(10);
  set_child(m_VBox);

  //Add the Notebook, with the button underneath:
  m_Notebook.set_margin(10);
  m_Notebook.set_expand();
  m_VBox.append(m_Notebook);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::CENTER);
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Add the Notebook pages:
  m_Notebook.append_page(m_Label1, "First");
  m_Notebook.append_page(m_Label2, "Second");

  m_Notebook.signal_switch_page().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_notebook_switch_page) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_notebook_switch_page(Gtk::Widget* /* page */, guint page_num)
{
  std::cout << "Switched to tab with index " << page_num << std::endl;

  //You can also use m_Notebook.get_current_page() to get this index.
}
