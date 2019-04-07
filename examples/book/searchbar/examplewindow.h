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
  Gtk::SearchEntry m_entry;
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
