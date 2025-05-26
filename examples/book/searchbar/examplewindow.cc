/* gtkmm example Copyright (C) 2013 gtkmm development team
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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_vbox(Gtk::ORIENTATION_VERTICAL),
  m_search_box(Gtk::ORIENTATION_HORIZONTAL),
  m_up_down_box(Gtk::ORIENTATION_HORIZONTAL),
  m_label("Press any key to start searching"),
  m_search_mode_label("Show search bar:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER),
  m_close_button_label("Show close button:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER)
{
  // Window properties
  set_title("SearchBar Example");
  set_border_width(12);
  set_size_request(500, -1); // To provide space for the searchbar when it appears.

  // Search bar properties
  m_search_bar.set_show_close_button();

  // Connect search entry
  m_search_bar.connect_entry(m_entry);

  // Events
  add_events(Gdk::KEY_PRESS_MASK);

  // Connect signals
  signal_key_press_event().connect(sigc::mem_fun(*this, &ExampleWindow::on_window_key_press));
  m_search_bar.property_search_mode_enabled().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_search_bar_reveal_changed));

  // Switches
  m_search_mode_switch.set_active(false);
  m_close_button_switch.set_active();
  m_search_mode_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_search_mode_changed));
  m_close_button_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_show_close_button_changed));

  // Options panel layout:
  m_options_grid.set_halign(Gtk::ALIGN_START);
  m_options_grid.set_column_spacing(6);
  m_options_grid.attach(m_search_mode_label, 0, 0, 1, 1);
  m_options_grid.attach(m_search_mode_switch, 1, 0, 1, 1);
  m_options_grid.attach(m_close_button_label, 0, 1, 1, 1);
  m_options_grid.attach(m_close_button_switch, 1, 1, 1, 1);

  // Searchbar Layout
  m_up_down_box.pack_start(m_go_down_button, Gtk::PACK_SHRINK);
  m_up_down_box.pack_start(m_go_up_button, Gtk::PACK_SHRINK);
  m_search_box.pack_end(m_up_down_box, Gtk::PACK_SHRINK);
  m_search_box.pack_start(m_entry, Gtk::PACK_EXPAND_WIDGET, 6);
  m_search_bar.add(m_search_box);

  // Match style of epiphany's search bar
  m_up_down_box.get_style_context()->add_class("raised");
  m_up_down_box.get_style_context()->add_class("linked");

  // Buttons
  m_go_up_button.set_image_from_icon_name("go-up-symbolic", Gtk::ICON_SIZE_BUTTON, true);
  m_go_down_button.set_image_from_icon_name("go-down-symbolic", Gtk::ICON_SIZE_BUTTON, true);

  m_vbox.pack_start(m_search_bar, Gtk::PACK_SHRINK, 6);
  m_vbox.pack_start(m_label, Gtk::PACK_SHRINK, 6);
  m_vbox.pack_start(m_separator, Gtk::PACK_SHRINK, 12);
  m_vbox.pack_start(m_options_grid, Gtk::PACK_SHRINK, 12);
  add(m_vbox);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

bool ExampleWindow::on_window_key_press(GdkEventKey* key_event)
{
  return m_search_bar.handle_event(key_event);
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

