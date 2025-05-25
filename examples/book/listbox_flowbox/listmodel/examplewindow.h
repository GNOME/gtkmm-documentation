/* gtkmm example Copyright (C) 2016 gtkmm development team
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
#include "myobject.h"

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

private:
  // Callback functions.
  static Gtk::Widget* on_create_widget1(const Glib::RefPtr<Glib::Object>& item);
  static Gtk::Widget* on_create_widget2(const Glib::RefPtr<MyObject>& item);

  // Signal handlers.
  void on_add_some();
  void on_remove_some();
  void on_quit();

  // Member data.
  Glib::RefPtr<Gio::ListStore<MyObject>> m_store;
  Gtk::Grid m_grid;
  Gtk::ScrolledWindow m_scrolled_window_list_box;
  Gtk::ScrolledWindow m_scrolled_window_flow_box;
  Gtk::ListBox m_list_box;
  Gtk::FlowBox m_flow_box;
  Gtk::Button m_button_add_some;
  Gtk::Button m_button_remove_some;
  Gtk::Button m_button_quit;
};

#endif // GTKMM_EXAMPLEWINDOW_H
