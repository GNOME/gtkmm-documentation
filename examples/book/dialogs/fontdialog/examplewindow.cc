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
: m_ButtonBox(Gtk::Orientation::VERTICAL),
  m_Button_Dialog("Choose Font")
{
  set_title("Gtk::FontDialog example");

  set_child(m_ButtonBox);

  m_pDialog = Gtk::FontDialog::create();

  m_ButtonBox.append(m_FontDialogButton);
  m_FontDialogButton.set_dialog(m_pDialog);
  m_FontDialogButton.set_font_desc(Pango::FontDescription("Sans 10"));
  m_FontDialogButton.set_expand(true);
  m_FontDialogButton.set_use_font(true);
  m_FontDialogButton.set_use_size(true);
  m_FontDialogButton.property_font_desc().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_font_button_font_set));

  m_ButtonBox.append(m_Button_Dialog);
  m_Button_Dialog.set_expand(true);
  m_Button_Dialog.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_dialog_clicked));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_font_button_font_set()
{
  auto font_name = m_FontDialogButton.get_font_desc().to_string();
  std::cout << "Font chosen: " << font_name << std::endl;
}

void ExampleWindow::on_button_dialog_clicked()
{
  // Get the previously selected font description from the FontDialogButton.
  m_pDialog->choose_font(*this,
    sigc::mem_fun(*this, &ExampleWindow::on_dialog_finish),
    m_FontDialogButton.get_font_desc());
}

void ExampleWindow::on_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result)
{
  try
  {
    // If this call changes the font, it will trigger a call to
    // on_font_button_font_set().
    m_FontDialogButton.set_font_desc(m_pDialog->choose_font_finish(result));
  }
  catch (const Gtk::DialogError& err)
  {
    // Can be thrown by m_pDialog->choose_font_finish(result).
    std::cout << "No font selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}
