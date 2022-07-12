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
#include <iostream>

ExampleWindow::ExampleWindow()
: m_ButtonBox(Gtk::Orientation::VERTICAL),
  m_FontButton("Sans 10"),
  m_Button_Dialog("Choose Font")
{
  set_title("Gtk::FontChooserDialog example");

  set_child(m_ButtonBox);

  m_ButtonBox.append(m_FontButton);
  m_FontButton.set_expand(true);
  m_FontButton.set_use_font(true);
  m_FontButton.set_use_size(true);
  m_FontButton.signal_font_set().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_font_button_font_set) );

  m_ButtonBox.append(m_Button_Dialog);
  m_Button_Dialog.set_expand(true);
  m_Button_Dialog.signal_clicked().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_button_dialog_clicked) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_font_button_font_set()
{
  auto font_name = m_FontButton.get_font();
  std::cout << "Font chosen: " << font_name << std::endl;
}

void ExampleWindow::on_button_dialog_clicked()
{
  if (!m_pDialog)
  {
    m_pDialog = std::make_unique<Gtk::FontChooserDialog>("Please choose a font", *this);
    m_pDialog->set_modal(true);
    m_pDialog->set_hide_on_close(true);
    m_pDialog->signal_response().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_dialog_response));
  }

  //Get the previously selected font name from the FontButton:
  m_pDialog->set_font(m_FontButton.get_font());

  m_pDialog->show();
}

void ExampleWindow::on_dialog_response(int response_id)
{
  m_pDialog->hide();

  //Handle the response:
  switch (response_id)
  {
    case Gtk::ResponseType::OK:
    {
      auto font_name = m_pDialog->get_font();
      std::cout << "Font chosen: " << font_name << std::endl;
      m_FontButton.set_font(font_name);
      break;
    }
    case Gtk::ResponseType::CANCEL:
    {
      std::cout << "Cancel clicked." << std::endl;
      break;
    }
    default:
    {
      std::cout << "Unexpected button clicked: " << response_id << std::endl;
      break;
    }
  }
}
