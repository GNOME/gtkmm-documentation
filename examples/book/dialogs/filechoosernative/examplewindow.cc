/* gtkmm example Copyright (C) 2017 gtkmm development team
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
: m_ButtonBox(Gtk::Orientation::VERTICAL),
  m_Button_File_Open("Choose File To Open"),
  m_Button_File_Save("Choose File To Save")
{
  set_title("Gtk::FileChooserNative example");

  add(m_ButtonBox);

  m_ButtonBox.add(m_Button_File_Open);
  m_Button_File_Open.set_expand(true);
  m_Button_File_Open.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
    &ExampleWindow::on_button_file_clicked), Gtk::FileChooser::Action::OPEN));

  m_ButtonBox.add(m_Button_File_Save);
  m_Button_File_Save.set_expand(true);
  m_Button_File_Save.signal_clicked().connect(sigc::bind(sigc::mem_fun(*this,
    &ExampleWindow::on_button_file_clicked), Gtk::FileChooser::Action::SAVE));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_file_clicked(Gtk::FileChooser::Action action)
{
  const bool open = (action == Gtk::FileChooser::Action::OPEN);
  auto dialog = Gtk::FileChooserNative::create("Please choose a file", *this, action);

  // Show the dialog and wait for a user response:
  const int result = dialog->run();

  // Handle the response:
  switch (result)
  {
  case Gtk::ResponseType::ACCEPT:
  {
    std::cout << (open ? "Open" : "Save") << " clicked." << std::endl;

    // Notice that this is a std::string, not a Glib::ustring.
    auto filename = dialog->get_file()->get_path();
    std::cout << "File selected: " <<  filename << std::endl;
    break;
  }

  case Gtk::ResponseType::CANCEL:
    std::cout << "Cancel clicked." << std::endl;
    break;

  case Gtk::ResponseType::DELETE_EVENT:
    std::cout << "Dialog closed." << std::endl;
    break;

  default:
    std::cout << "Unexpected button clicked." << std::endl;
    break;
  }
}
