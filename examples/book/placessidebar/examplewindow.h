/* gtkmm example Copyright (C) 2013 gtkmm development team
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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

#include <iostream>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  // Slots
  void on_show_desktop_toggled();
  void on_show_enter_location_toggled();
  void on_placessidebar_open_location(const Glib::RefPtr<Gio::File>& location, Gtk::PlacesOpenFlags open_flags);
  void on_placessidebar_populate_popup(Gtk::Menu* menu, const Glib::RefPtr<Gio::File>& selected_item, const Glib::RefPtr<Gio::Volume>& selected_volume);
  int on_placessidebar_drag_action_requested(const Glib::RefPtr<Gdk::DragContext>& context, const Glib::RefPtr<Gio::File>& dest_file, const std::vector< Glib::RefPtr<Gio::File> >& source_file_list);
  void on_menu_properties_activate();

  // Containers 
  Gtk::Box m_hbox;
  Gtk::Grid m_controls;
  Gtk::Frame m_controls_frame;
  Gtk::Label m_frame_label;

  // Widgets
  Gtk::PlacesSidebar m_places_sidebar;
  Gtk::CheckButton m_show_desktop_check;
  Gtk::CheckButton m_show_enter_location;

private:
};

#endif // GTKMM_EXAMPLEWINDOW_H

