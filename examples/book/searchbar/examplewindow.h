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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm.h>

#define HAS_SEARCH_ENTRY2 GTKMM_CHECK_VERSION(4,13,2)

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

private:
  // Signal handlers
  void on_search_mode_changed();
  void on_show_close_button_changed();
  void on_search_bar_reveal_changed();

  // Containers
  Gtk::Box m_vbox;
  Gtk::Box m_search_box;
  Gtk::Box m_up_down_box;
  Gtk::Grid m_options_grid;

  // Widgets
  Gtk::SearchBar m_search_bar;
#if HAS_SEARCH_ENTRY2
  Gtk::SearchEntry2 m_entry;
#else
  Gtk::SearchEntry m_entry;
#endif
  Gtk::Button m_go_up_button;
  Gtk::Button m_go_down_button;
  Gtk::Label m_label;
  Gtk::Switch m_search_mode_switch;
  Gtk::Label m_search_mode_label;
  Gtk::Switch m_close_button_switch;
  Gtk::Label m_close_button_label;
  Gtk::Separator m_separator;
};

#endif // GTKMM_EXAMPLEWINDOW_H
