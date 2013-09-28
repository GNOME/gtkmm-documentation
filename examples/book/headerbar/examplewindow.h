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

protected:
  // Slots
  void on_switch_active_changed();
  void on_title_entry_activate();
  void on_subtitle_entry_activate();
  void on_button_clicked();

  // Containers 
  Gtk::Grid m_grid;

  // Widgets
  Gtk::HeaderBar m_header_bar;
  Gtk::Button m_button;
  Gtk::Label m_close_button_label;
  Gtk::Switch m_switch;
  Gtk::Label m_title_label;
  Gtk::Entry m_title_entry;
  Gtk::Label m_subtitle_label;
  Gtk::Entry m_subtitle_entry;

private:
};

#endif // GTKMM_EXAMPLEWINDOW_H

