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
  m_Button_File("Choose File"),
  m_Button_Folder("Choose Folder")
{
  set_title("Gtk::FileSelection example");

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
  auto dialog = new Gtk::FileChooserDialog("Please choose a file",
          Gtk::FileChooser::Action::OPEN);
  dialog->set_transient_for(*this);
  dialog->set_modal(true);
  dialog->signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &ExampleWindow::on_file_dialog_response), dialog));

  //Add response buttons to the dialog:
  dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
  dialog->add_button("_Open", Gtk::ResponseType::OK);

  //Add filters, so that only certain file types can be selected:

  auto filter_text = Gtk::FileFilter::create();
  filter_text->set_name("Text files");
  filter_text->add_mime_type("text/plain");
  dialog->add_filter(filter_text);

  auto filter_cpp = Gtk::FileFilter::create();
  filter_cpp->set_name("C/C++ files");
  filter_cpp->add_mime_type("text/x-c");
  filter_cpp->add_mime_type("text/x-c++");
  filter_cpp->add_mime_type("text/x-c-header");
  dialog->add_filter(filter_cpp);

  auto filter_any = Gtk::FileFilter::create();
  filter_any->set_name("Any files");
  filter_any->add_pattern("*");
  dialog->add_filter(filter_any);

  //Show the dialog and wait for a user response:
  dialog->show();
}

void ExampleWindow::on_file_dialog_response(int response_id, Gtk::FileChooserDialog* dialog)
{
  //Handle the response:
  switch (response_id)
  {
    case Gtk::ResponseType::OK:
    {
      std::cout << "Open clicked." << std::endl;

      //Notice that this is a std::string, not a Glib::ustring.
      auto filename = dialog->get_file()->get_path();
      std::cout << "File selected: " <<  filename << std::endl;
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
  delete dialog;
}

void ExampleWindow::on_button_folder_clicked()
{
  auto dialog = new Gtk::FileChooserDialog("Please choose a folder",
          Gtk::FileChooser::Action::SELECT_FOLDER);
  dialog->set_transient_for(*this);
  dialog->set_modal(true);
  dialog->signal_response().connect(sigc::bind(
    sigc::mem_fun(*this, &ExampleWindow::on_folder_dialog_response), dialog));

  //Add response buttons to the dialog:
  dialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
  dialog->add_button("Select", Gtk::ResponseType::OK);

  //Show the dialog and wait for a user response:
  dialog->show();
}

void ExampleWindow::on_folder_dialog_response(int response_id, Gtk::FileChooserDialog* dialog)
{
  //Handle the response:
  switch (response_id)
  {
    case Gtk::ResponseType::OK:
    {
      std::cout << "Select clicked." << std::endl;
      std::cout << "Folder selected: " << dialog->get_file()->get_path() << std::endl;
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
  delete dialog;
}
