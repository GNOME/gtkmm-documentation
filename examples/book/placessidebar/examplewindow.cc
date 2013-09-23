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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_hbox(Gtk::ORIENTATION_HORIZONTAL, 6),
  m_show_desktop_check("Show desktop"),
  m_show_connect_to_server_check("Show connect to server")
{
  // Window properties
  set_title("PlacesSidebar Example");
  set_border_width(12);
  set_size_request(300, 600);

  // Options
  m_controls_frame.set_shadow_type(Gtk::SHADOW_NONE);
  m_frame_label.set_markup("<b>Options</b>");
  m_controls_frame.set_label_widget(m_frame_label);
  m_alignment.set_padding(6, 0, 12, 0);

  m_show_desktop_check.signal_toggled().connect(sigc::mem_fun(*this, &ExampleWindow::on_show_desktop_toggled));
  m_show_desktop_check.set_active(true);

  m_show_connect_to_server_check.signal_toggled().connect(sigc::mem_fun(*this, &ExampleWindow::on_show_connect_to_server_toggled));
  m_show_connect_to_server_check.set_active(true);

  m_places_sidebar.signal_open_location().connect(sigc::mem_fun(*this, &ExampleWindow::on_open_location));
  m_places_sidebar.signal_populate_popup().connect(sigc::mem_fun(*this, &ExampleWindow::on_populate_popup));
  m_places_sidebar.signal_drag_action_requested().connect(sigc::mem_fun(*this, &ExampleWindow::on_drag_action_requested));

  m_controls.attach(m_show_desktop_check, 0, 0, 1, 1);
  m_controls.attach(m_show_connect_to_server_check, 0, 1, 1, 1);

  std::cout << "Shortcuts:" << std::endl;
  std::vector<Glib::RefPtr<Gio::File > > shortcuts = m_places_sidebar.list_shortcuts();
  for (std::vector<Glib::RefPtr<Gio::File > >::const_iterator it = shortcuts.begin();
          it != shortcuts.end(); ++it) {
      std::cout << "basename: " << (*it)->get_basename() << std::endl;
  }

  // Layout
  m_controls_frame.add(m_alignment);
  m_alignment.add(m_controls);
  m_hbox.pack_start(m_places_sidebar, true, true, 0);
  m_hbox.pack_start(m_controls_frame, false, false, 0);
  add(m_hbox);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_show_desktop_toggled()
{
  bool show_desktop = m_show_desktop_check.get_active();

  m_places_sidebar.set_show_desktop(show_desktop);
}

void ExampleWindow::on_show_connect_to_server_toggled()
{
  bool show_connect_to_server = m_show_connect_to_server_check.get_active();

  m_places_sidebar.set_show_connect_to_server(show_connect_to_server);
}

void ExampleWindow::on_open_location(const Glib::RefPtr<Gio::File>& location, Gtk::PlacesOpenFlags /* open_flags */)
{
  Gtk::MessageDialog dialog(*this, "<b>open-location</b> event triggered", true);
  Gtk::Grid location_information_grid;
  Gtk::Label basename_label("Basename:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER);
  Gtk::Label path_label("Path:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER);
  Gtk::Label uri_label("URI:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER);
  Gtk::Label file_basename_label, file_path_label, file_uri_label;

  file_basename_label.set_text(location->get_basename());
  file_basename_label.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  file_path_label.set_text(location->get_path());
  file_path_label.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);
  file_uri_label.set_text(location->get_uri());
  file_uri_label.set_alignment(Gtk::ALIGN_START, Gtk::ALIGN_CENTER);

  location_information_grid.attach(basename_label, 0, 0, 1, 1);
  location_information_grid.attach(file_basename_label, 1, 0, 1, 1);
  location_information_grid.attach(path_label, 0, 1, 1, 1);
  location_information_grid.attach(file_path_label, 1, 1, 1, 1);
  location_information_grid.attach(uri_label, 0, 2, 1, 1);
  location_information_grid.attach(file_uri_label, 1, 2, 1, 1);

  location_information_grid.set_column_spacing(6);

  dialog.get_content_area()->pack_end(location_information_grid, true, true, 6);
  dialog.show_all();
  dialog.run();
}

void ExampleWindow::on_populate_popup(Gtk::Menu* menu, const Glib::RefPtr<Gio::File>& /* selected_item */, const Glib::RefPtr<Gio::Volume>& /* selected_volume */)
{
  Gtk::MenuItem* properties_menu_item = new Gtk::MenuItem("Properties...");

  properties_menu_item->signal_activate().connect(sigc::mem_fun(*this, &ExampleWindow::on_properties_activate));
  properties_menu_item->show();

  menu->attach(*properties_menu_item, 0, 1, 0, 1);
}

void ExampleWindow::on_properties_activate()
{
  Glib::RefPtr< Gio::File> selected_item = m_places_sidebar.get_location();

  on_open_location(selected_item, Gtk::PLACES_OPEN_NORMAL);
}


int ExampleWindow::on_drag_action_requested(const Glib::RefPtr<Gdk::DragContext>& /* context */, const Glib::RefPtr<Gio::File>& /* dest_file */, const std::vector< Glib::RefPtr<Gio::File> >& /* source_file_list */)
{
  return false;
}

