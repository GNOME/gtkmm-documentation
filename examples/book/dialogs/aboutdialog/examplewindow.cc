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
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Label("The AboutDialog is non-modal. "
    "You can select parts of this text while the AboutDialog is shown."),
  m_ButtonBox(Gtk::Orientation::VERTICAL),
  m_Button("Show AboutDialog")
{
  set_title("Gtk::AboutDialog example");

  add(m_VBox);

  m_VBox.pack_start(m_Label, Gtk::PackOptions::EXPAND_WIDGET);
  m_Label.set_line_wrap(true);
  m_Label.set_selectable(true);

  m_VBox.pack_start(m_ButtonBox, Gtk::PackOptions::EXPAND_WIDGET);
  m_ButtonBox.pack_start(m_Button, Gtk::PackOptions::EXPAND_WIDGET);
  m_Button.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_clicked) );

  m_Dialog.set_transient_for(*this);

  m_Dialog.set_logo(Gdk::Pixbuf::create_from_resource("/about/gtkmm_logo.gif", -1, 40, true));
  m_Dialog.set_program_name("Example application");
  m_Dialog.set_version("1.0.0");
  m_Dialog.set_copyright("Murray Cumming");
  m_Dialog.set_comments("This is just an example application.");
  m_Dialog.set_license("LGPL");

  m_Dialog.set_website("http://www.gtkmm.org");
  m_Dialog.set_website_label("gtkmm website");

  std::vector<Glib::ustring> list_authors;
  list_authors.push_back("Murray Cumming");
  list_authors.push_back("Somebody Else");
  list_authors.push_back("AN Other");
  m_Dialog.set_authors(list_authors);

  m_Dialog.signal_response().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_about_dialog_response) );

  m_Button.grab_focus();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_about_dialog_response(int response_id)
{
  std::cout << response_id
    << ", close=" << static_cast<int>(Gtk::ResponseType::CLOSE)
    << ", cancel=" << static_cast<int>(Gtk::ResponseType::CANCEL)
    << ", delete_event=" << static_cast<int>(Gtk::ResponseType::DELETE_EVENT)
    << std::endl;

  switch (response_id)
  {
  case static_cast<int>(Gtk::ResponseType::CLOSE):
  case static_cast<int>(Gtk::ResponseType::CANCEL):
  case static_cast<int>(Gtk::ResponseType::DELETE_EVENT):
    m_Dialog.hide();
    break;
  default:
    std::cout << "Unexpected response!" << std::endl;
    break;
  }
}

void ExampleWindow::on_button_clicked()
{
  m_Dialog.show();

  //Bring it to the front, in case it was already shown:
  m_Dialog.present();
}
