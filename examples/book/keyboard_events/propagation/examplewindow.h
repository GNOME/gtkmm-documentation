/* gtkmm example Copyright (C) 2011 gtkmm development team
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#ifndef GTKMM_EVENT_PROPAGATION_H
#define GTKMM_EVENT_PROPAGATION_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:

  ExampleWindow();
  virtual ~ExampleWindow();

private:
  // Signal handlers:
  bool label2_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state, const Glib::ustring& phase);
  bool grid_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state, const Glib::ustring& phase);
  bool window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state, const Glib::ustring& phase);

  bool m_first = true;
  Gtk::Grid m_container;
  Gtk::Frame m_frame;
  Gtk::Label m_label1;
  Gtk::Label m_label2;
  Gtk::CheckButton m_checkbutton_can_propagate_down;
  Gtk::CheckButton m_checkbutton_can_propagate_up;
};

#endif //GTKMM_EVENT_PROPAGATION_H
