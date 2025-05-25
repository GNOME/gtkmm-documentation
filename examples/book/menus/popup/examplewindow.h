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

#include <memory>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow(const Glib::RefPtr<Gtk::Application>& app);
  virtual ~ExampleWindow();

protected:
  //Signal handlers:
  void on_label_pressed(int n_press, double x, double y);

  void on_menu_file_popup_generic();

  //Child widgets:
  Gtk::Box m_Box;
  Gtk::Label m_Label;
  Gtk::PopoverMenu m_MenuPopup;

  Glib::RefPtr<Gtk::Builder> m_refBuilder;
  Glib::RefPtr<Gtk::GestureClick> m_refGesture;
};

#endif //GTKMM_EXAMPLEWINDOW_H
