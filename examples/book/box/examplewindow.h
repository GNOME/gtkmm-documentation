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
  ExampleWindow(int which);
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_button_quit_clicked();

  //Child widgets:
  Gtk::Button m_button;
  Gtk::Box m_box1;
  Gtk::Box m_boxQuit;
  Gtk::Button m_buttonQuit;

  Gtk::Label m_Label1, m_Label2;

  Gtk::Separator m_separator1, m_separator2;
};

#endif //GTKMM_EXAMPLEWINDOW_H
