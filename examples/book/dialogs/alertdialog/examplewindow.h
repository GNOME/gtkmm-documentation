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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  //Signal handlers:
  void on_button_info_clicked();
  void on_button_question_clicked();
  void on_question_dialog_finish(const Glib::RefPtr<Gio::AsyncResult>& result);

  //Child widgets:
  Gtk::Box m_ButtonBox;
  Gtk::Button m_Button_Info;
  Gtk::Button m_Button_Question;

  Glib::RefPtr<Gtk::AlertDialog> m_pDialog;
};

#endif //GTKMM_EXAMPLEWINDOW_H
