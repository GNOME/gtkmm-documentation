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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  // Signal handlers:
  void on_button_file_clicked(Gtk::FileChooser::Action action);
  void on_dialog_response(int response_id);

  // Child widgets:
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_File_Open;
  Gtk::Button m_Button_File_Save;

  Glib::RefPtr<Gtk::FileChooserNative> m_pDialog;
};

#endif // GTKMM_EXAMPLEWINDOW_H
