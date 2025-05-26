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
#include <gtkmm/messagedialog.h>
#include <iostream>


ExampleWindow::ExampleWindow()
: m_ButtonBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Info("Show Info MessageDialog"),
  m_Button_Question("Show Question MessageDialog")
{
  set_title("Gtk::MessageDialog example");

  add(m_ButtonBox);

  m_ButtonBox.pack_start(m_Button_Info);
  m_Button_Info.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_info_clicked) );

  m_ButtonBox.pack_start(m_Button_Question);
  m_Button_Question.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_question_clicked) );

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_info_clicked()
{
  Gtk::MessageDialog dialog(*this, "This is an INFO MessageDialog");
  dialog.set_secondary_text(
          "And this is the secondary text that explains things.");

  dialog.run();
}

void ExampleWindow::on_button_question_clicked()
{
  Gtk::MessageDialog dialog(*this, "This is a QUESTION MessageDialog",
          false /* use_markup */, Gtk::MESSAGE_QUESTION,
          Gtk::BUTTONS_OK_CANCEL);
  dialog.set_secondary_text(
          "And this is the secondary text that explains things.");

  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case(Gtk::RESPONSE_OK):
    {
      std::cout << "OK clicked." << std::endl;
      break;
    }
    case(Gtk::RESPONSE_CANCEL):
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked." << std::endl;
      break;
    }
  }
}
