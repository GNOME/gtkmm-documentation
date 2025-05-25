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
: m_ButtonBox(Gtk::Orientation::VERTICAL),
  m_Button_Info("Show Info AlertDialog"),
  m_Button_Question("Show Question AlertDialog")
{
  set_title("Gtk::AlertDialog example");

  set_child(m_ButtonBox);

  m_ButtonBox.append(m_Button_Info);
  m_Button_Info.set_expand(true);
  m_Button_Info.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_info_clicked) );

  m_ButtonBox.append(m_Button_Question);
  m_Button_Question.set_expand(true);
  m_Button_Question.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_question_clicked) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_info_clicked()
{
  if (!m_pDialog)
    m_pDialog = Gtk::AlertDialog::create();
  else
  {
    // Reset values that may have been set by on_button_question_clicked().
    m_pDialog->set_buttons({});
    m_pDialog->set_default_button(-1);
    m_pDialog->set_cancel_button(-1);
  }

  m_pDialog->set_message("This is an INFO AlertDialog.");
  m_pDialog->set_detail("And this is the secondary text that explains things.");
  m_pDialog->show(*this);
}

void ExampleWindow::on_button_question_clicked()
{
  if (!m_pDialog)
    m_pDialog = Gtk::AlertDialog::create();
  m_pDialog->set_message("This is a QUESTION AlertDialog.");
  m_pDialog->set_detail("And this is the secondary text that explains things.");
  m_pDialog->set_buttons({"Cancel", "Retry", "OK"});
  m_pDialog->set_default_button(2); // OK button or Return key
  m_pDialog->set_cancel_button(0); // Cancel button or Escape key
  m_pDialog->choose(*this,
    sigc::mem_fun(*this, &ExampleWindow::on_question_dialog_finish));
}

void ExampleWindow::on_question_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result)
{
  try
  {
    const int response_id = m_pDialog->choose_finish(result);
    switch (response_id)
    {
    case 0:
      std::cout << "Cancel clicked." << std::endl;
      break;
    case 1:
      std::cout << "Retry clicked." << std::endl;
      break;
    case 2:
      std::cout << "OK clicked." << std::endl;
      break;
    default:
      std::cout << "Unexpected response: " << response_id << std::endl;
      break;
    }
  }
  catch (const Gtk::DialogError& err)
  {
    // Can be thrown by m_pDialog->choose_finish(result).
    std::cout << "DialogError, " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}
