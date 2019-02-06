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
: m_vbox(Gtk::Orientation::VERTICAL),
  m_search_box(Gtk::Orientation::HORIZONTAL),
  m_up_down_box(Gtk::Orientation::HORIZONTAL),
  m_label("Press any key to start searching"),
  m_search_mode_label("Show search bar:", Gtk::Align::END, Gtk::Align::CENTER),
  m_close_button_label("Show close button:", Gtk::Align::END, Gtk::Align::CENTER)
{
  // Window properties
  set_title("SearchBar Example");
  set_size_request(500, -1); // To provide space for the searchbar when it appears.

  // Search bar properties
  m_search_bar.set_show_close_button();

  // Connect search entry
  m_search_bar.connect_entry(m_entry);

  // Connect signals
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_window_key_pressed), true);
  add_controller(controller);
  m_search_bar.property_search_mode_enabled().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_search_bar_reveal_changed));

  // Switches
  m_search_mode_switch.set_active(false);
  m_close_button_switch.set_active();
  m_search_mode_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_search_mode_changed));
  m_close_button_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_show_close_button_changed));

  // Options panel layout:
  m_options_grid.set_halign(Gtk::Align::START);
  m_options_grid.set_column_spacing(6);
  m_options_grid.attach(m_search_mode_label, 0, 0);
  m_options_grid.attach(m_search_mode_switch, 1, 0);
  m_options_grid.attach(m_close_button_label, 0, 1);
  m_options_grid.attach(m_close_button_switch, 1, 1);

  // Searchbar Layout
  m_search_box.add(m_entry);
  m_entry.set_expand();
  m_up_down_box.add(m_go_down_button);
  m_up_down_box.add(m_go_up_button);
  m_search_box.add(m_up_down_box);
  m_search_box.set_spacing(6);
  m_search_bar.add(m_search_box);

  // Match style of epiphany's search bar
  m_up_down_box.get_style_context()->add_class("raised");
  m_up_down_box.get_style_context()->add_class("linked");

  // Buttons
  m_go_up_button.set_image_from_icon_name("go-up-symbolic", Gtk::IconSize::INHERIT, true);
  m_go_down_button.set_image_from_icon_name("go-down-symbolic", Gtk::IconSize::INHERIT, true);

  m_vbox.set_spacing(6);
  m_vbox.add(m_search_bar);
  m_vbox.add(m_label);
  m_vbox.add(m_separator);
  m_separator.set_margin_start(6);
  m_separator.set_margin_end(6);
  m_vbox.add(m_options_grid);
  m_options_grid.set_margin_start(6);
  m_options_grid.set_margin_end(6);
  m_vbox.set_margin(12);
  add(m_vbox);
}

ExampleWindow::~ExampleWindow()
{
}

bool ExampleWindow::on_window_key_pressed(guint, guint, Gdk::ModifierType)
{
  Glib::RefPtr<Gdk::Event> current_event = Glib::wrap(gtk_get_current_event());
  if (current_event->get_event_type() == Gdk::Event::Type::KEY_PRESS)
    return m_search_bar.handle_event(std::static_pointer_cast<Gdk::EventKey>(current_event));
  else
    return false;
}

void ExampleWindow::on_search_bar_reveal_changed()
{
  const bool revealed = m_search_bar.get_search_mode();
  m_search_mode_switch.set_active(revealed);
}

void ExampleWindow::on_search_mode_changed()
{
  const bool search_mode = m_search_mode_switch.get_active();
  m_search_bar.set_search_mode(search_mode);
}

void ExampleWindow::on_show_close_button_changed()
{
  const bool show_close_button = m_close_button_switch.get_active();
  m_search_bar.set_show_close_button(show_close_button);
}

