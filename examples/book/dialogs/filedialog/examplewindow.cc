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
  m_Button_File("Choose File"),
  m_Button_Folder("Choose Folder")
{
  set_title("Gtk::FileDialog example");

  set_child(m_ButtonBox);

  m_ButtonBox.append(m_Button_File);
  m_Button_File.set_expand(true);
  m_Button_File.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_file_clicked) );

  m_ButtonBox.append(m_Button_Folder);
  m_Button_Folder.set_expand(true);
  m_Button_Folder.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_folder_clicked) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_file_clicked()
{
  auto dialog = Gtk::FileDialog::create();

  // Add filters, so that only certain file types can be selected:
  auto filters = Gio::ListStore<Gtk::FileFilter>::create();

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  filters->append(filter_text);

  auto filter_cpp = Gtk::FileFilter::create();
  filter_cpp->set_name("C/C++ files");
  filter_cpp->add_mime_type("text/x-c");
  filter_cpp->add_mime_type("text/x-c++");
  filter_cpp->add_mime_type("text/x-c-header");
  filters->append(filter_cpp);

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  filters->append(filter_any);

  dialog->set_filters(filters);

  // Show the dialog and wait for a user response:
  dialog->open(sigc::bind(sigc::mem_fun(
    *this, &ExampleWindow::on_file_dialog_finish), dialog));
}

void ExampleWindow::on_file_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gtk::FileDialog>& dialog)
{
  // Handle the response:
  try
  {
    auto file = dialog->open_finish(result);

    // Notice that this is a std::string, not a Glib::ustring.
    auto filename = file->get_path();
    std::cout << "File selected: " <<  filename << std::endl;
  }
  catch (const Gtk::DialogError& err)
  {
    // Can be thrown by dialog->open_finish(result).
    std::cout << "No file selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}

void ExampleWindow::on_button_folder_clicked()
{
  auto dialog = Gtk::FileDialog::create();

  // Show the dialog and wait for a user response:
  dialog->select_folder(sigc::bind(sigc::mem_fun(
    *this, &ExampleWindow::on_folder_dialog_finish), dialog));
}

void ExampleWindow::on_folder_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result,
  const Glib::RefPtr<Gtk::FileDialog>& dialog)
{
  // Handle the response:
  try
  {
    auto folder = dialog->select_folder_finish(result);
    std::cout << "Folder selected: " << folder->get_path() << std::endl;
  }
  catch (const Gtk::DialogError& err)
  {
    // Can be thrown by dialog->select_folder_finish(result).
    std::cout << "No folder selected. " << err.what() << std::endl;
  }
  catch (const Glib::Error& err)
  {
    std::cout << "Unexpected exception. " << err.what() << std::endl;
  }
}
