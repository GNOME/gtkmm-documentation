/* gtkmm example Copyright (C) 2024 gtkmm development team
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
  ExampleWindow();
  ~ExampleWindow() override;

  // Configuration file, showing configured locale.
  static const std::string config_file_name;

protected:
  void fill_text_tag_table();
  void fill_buffer();

  void on_dropdown_changed();

  // Child widgets
  Gtk::HeaderBar m_HeaderBar;
  Gtk::DropDown m_DropDown;
  Gtk::ScrolledWindow m_ScrolledWindow;
  Gtk::TextView m_TextView;

  Glib::RefPtr<Gtk::StringList> m_StringList;
  Glib::RefPtr<Gtk::TextTagTable> m_refTextTagTable;
  Glib::RefPtr<Gtk::TextBuffer> m_refTextBuffer;
};

#endif // GTKMM_EXAMPLEWINDOW_H
