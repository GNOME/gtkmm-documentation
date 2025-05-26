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
: m_ButtonBox(Gtk::ORIENTATION_VERTICAL),
  m_FontButton("Sans 10"),
  m_Button_Dialog("Choose Font")
{
  set_title("Gtk::FontChooserDialog example");

  add(m_ButtonBox);

  m_ButtonBox.pack_start(m_FontButton);
  m_FontButton.set_use_font(true);
  m_FontButton.set_use_size(true);
  m_FontButton.signal_font_set().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_font_button_font_set) );

  m_ButtonBox.pack_start(m_Button_Dialog);
  m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_dialog_clicked) );
  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_font_button_font_set()
{
  Glib::ustring font_name = m_FontButton.get_font_name();
  std::cout << "Font chosen: " << font_name << std::endl;
}

void ExampleWindow::on_button_dialog_clicked()
{
  Gtk::FontChooserDialog dialog("Please choose a font", *this);

  //Get the previously selected font name from the FontButton:
  dialog.set_font(m_FontButton.get_font_name());

  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case Gtk::RESPONSE_OK:
    {
      Glib::ustring font_name = dialog.get_font();
      std::cout << "Font chosen: " << font_name << std::endl;
      m_FontButton.set_font_name(font_name);
      break;
    }
    case Gtk::RESPONSE_CANCEL:
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked: " << result << std::endl;
      break;
    }
  }
}
