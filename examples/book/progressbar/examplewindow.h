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
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_checkbutton_text();
  void on_checkbutton_activity();
  void on_checkbutton_inverted();

  bool on_timeout();
  void on_button_close();

  //Child widgets:
  Gtk::Box m_VBox;
  Gtk::Grid m_Grid;
  Gtk::ProgressBar m_ProgressBar;
  Gtk::Separator m_Separator;
  Gtk::CheckButton m_CheckButton_Text, m_CheckButton_Activity, m_CheckButton_Inverted;
  Gtk::Button m_Button_Close;

  sigc::connection m_connection_timeout;
  bool m_bActivityMode;
};

#endif //GTKMM_EXAMPLEWINDOW_H
