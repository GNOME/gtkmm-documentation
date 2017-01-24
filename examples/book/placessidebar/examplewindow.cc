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
  m_show_desktop_check("Show \"Desktop\""),
  m_show_enter_location("Show \"Enter Location\"")
{
  // Window properties
  set_title("PlacesSidebar Example");
  set_size_request(500, 600);

  // Options
  m_controls_frame.set_shadow_type(Gtk::SHADOW_NONE);
  m_frame_label.set_markup("<b>Options</b>");
  m_controls_frame.set_label_widget(m_frame_label);
  m_controls.set_margin_top(6);
  m_controls.set_margin_start(12);

  m_show_desktop_check.signal_toggled().connect(sigc::mem_fun(*this, &ExampleWindow::on_show_desktop_toggled));
  m_show_desktop_check.set_active();

  m_show_enter_location.signal_toggled().connect(sigc::mem_fun(*this, &ExampleWindow::on_show_enter_location_toggled));
  m_show_enter_location.set_active(false);

  m_places_sidebar.property_populate_all() = true;
  m_places_sidebar.signal_open_location().connect(sigc::mem_fun(*this, &ExampleWindow::on_placessidebar_open_location));
  m_places_sidebar.signal_populate_popup().connect(sigc::mem_fun(*this, &ExampleWindow::on_placessidebar_populate_popup));
  //m_places_sidebar.signal_drag_action_requested().connect(sigc::mem_fun(*this, &ExampleWindow::on_placessidebar_drag_action_requested));

  m_controls.attach(m_show_desktop_check, 0, 0, 1, 1);
  m_controls.attach(m_show_enter_location, 0, 1, 1, 1);

  std::cout << "Shortcuts:" << std::endl;
  std::vector<Glib::RefPtr<Gio::File > > shortcuts = m_places_sidebar.list_shortcuts();
  for(std::vector<Glib::RefPtr<Gio::File > >::const_iterator it = shortcuts.begin();
    it != shortcuts.end(); ++it)
  {
    std::cout << "basename: " << (*it)->get_basename() << std::endl;
  }

  // Layout
  m_controls_frame.add(m_controls);
  m_hbox.pack_start(m_places_sidebar, Gtk::PACK_EXPAND_WIDGET);
  m_hbox.pack_start(m_controls_frame, Gtk::PACK_SHRINK);
  m_hbox.set_margin(12);
  add(m_hbox);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_show_desktop_toggled()
{
  const bool show_desktop = m_show_desktop_check.get_active();

  m_places_sidebar.set_show_desktop(show_desktop);
}

void ExampleWindow::on_show_enter_location_toggled()
{
  const bool show_enter_location = m_show_enter_location.get_active();

  m_places_sidebar.set_show_enter_location(show_enter_location);
}

void ExampleWindow::on_placessidebar_open_location(const Glib::RefPtr<Gio::File>& location, Gtk::PlacesOpenFlags /* open_flags */)
{
  Gtk::MessageDialog dialog(*this, "<b>open-location</b> event triggered", true);
  Gtk::Grid location_information_grid;
  Gtk::Label basename_label("Basename:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER);
  Gtk::Label path_label("Path:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER);
  Gtk::Label uri_label("URI:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER);
  Gtk::Label file_basename_label, file_path_label, file_uri_label;

  file_basename_label.set_text(location->get_basename());
  file_basename_label.set_halign(Gtk::ALIGN_START);
  file_basename_label.set_valign(Gtk::ALIGN_CENTER);
  file_path_label.set_text(location->get_path());
  file_path_label.set_halign(Gtk::ALIGN_START);
  file_path_label.set_valign(Gtk::ALIGN_CENTER);
  file_uri_label.set_text(location->get_uri());
  file_uri_label.set_halign(Gtk::ALIGN_START);
  file_uri_label.set_valign(Gtk::ALIGN_CENTER);

  location_information_grid.attach(basename_label, 0, 0, 1, 1);
  location_information_grid.attach(file_basename_label, 1, 0, 1, 1);
  location_information_grid.attach(path_label, 0, 1, 1, 1);
  location_information_grid.attach(file_path_label, 1, 1, 1, 1);
  location_information_grid.attach(uri_label, 0, 2, 1, 1);
  location_information_grid.attach(file_uri_label, 1, 2, 1, 1);

  location_information_grid.set_column_spacing(6);
  location_information_grid.set_margin_start(6);
  location_information_grid.set_margin_end(6);

  dialog.get_content_area()->pack_end(location_information_grid, true, true);
  dialog.run();
}

void ExampleWindow::on_placessidebar_populate_popup(Gtk::Container* container, const Glib::RefPtr<Gio::File>& /* selected_item */, const Glib::RefPtr<Gio::Volume>& /* selected_volume */)
{
  if (auto menu = dynamic_cast<Gtk::Menu*>(container))
  {
    auto properties_menu_item = Gtk::manage(new Gtk::MenuItem("Properties..."));

    properties_menu_item->signal_activate().connect(sigc::mem_fun(*this, &ExampleWindow::on_menu_properties_activate));
    properties_menu_item->show();

    menu->attach(*properties_menu_item, 0, 1, 0, 1);
  }
  else if (auto box = dynamic_cast<Gtk::Box*>(container))
  {
    auto properties_button = Gtk::manage(new Gtk::ModelButton());
    properties_button->property_text() = "Properties...";

    properties_button->signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_menu_properties_activate));
    properties_button->show();

    box->pack_end(*properties_button);
  }
  else
  {
    std::cout << "on_placessidebar_populate_popup(): Unknown type of container." << std::endl;
  }
}

void ExampleWindow::on_menu_properties_activate()
{
  auto selected_item = m_places_sidebar.get_location();

  on_placessidebar_open_location(selected_item, Gtk::PLACES_OPEN_NORMAL);
}


int ExampleWindow::on_placessidebar_drag_action_requested(const Glib::RefPtr<Gdk::DragContext>& /* context */, const Glib::RefPtr<Gio::File>& /* dest_file */, const std::vector< Glib::RefPtr<Gio::File> >& /* source_file_list */)
{
  return false;
}

