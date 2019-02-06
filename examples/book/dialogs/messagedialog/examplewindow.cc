/* gtkmm example Copyright (C) 2002 gtkmm development team
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */

#include "examplewindow.h"
#include <gtkmm/messagedialog.h>
#include <iostream>


ExampleWindow::ExampleWindow()
: m_ButtonBox(Gtk::Orientation::VERTICAL),
  m_Button_Info("Show Info MessageDialog"),
  m_Button_Question("Show Question MessageDialog")
{
  set_title("Gtk::MessageDialog example");

  add(m_ButtonBox);

  m_ButtonBox.add(m_Button_Info);
  m_Button_Info.set_expand(true);
  m_Button_Info.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_info_clicked) );

  m_ButtonBox.add(m_Button_Question);
  m_Button_Question.set_expand(true);
  m_Button_Question.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_question_clicked) );
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
          false /* use_markup */, Gtk::MessageType::QUESTION,
          Gtk::ButtonsType::OK_CANCEL);
  dialog.set_secondary_text(
          "And this is the secondary text that explains things.");

  int result = dialog.run();

  //Handle the response:
  switch(result)
  {
    case Gtk::ResponseType::OK:
    {
      std::cout << "OK clicked." << std::endl;
      break;
    }
    case Gtk::ResponseType::CANCEL:
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
