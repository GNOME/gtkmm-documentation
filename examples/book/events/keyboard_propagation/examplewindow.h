/* gtkmm example Copyright (C) 2011 gtkmm development team
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

#ifndef GTKMM_EVENT_PROPAGATION_H
#define GTKMM_EVENT_PROPAGATION_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:

  ExampleWindow();
  ~ExampleWindow() override;

private:
  // Signal handlers:
  bool label2_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state, const Glib::ustring& phase);
  bool box_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state, const Glib::ustring& phase);
  bool window_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state, const Glib::ustring& phase);

  bool m_first = true;
  Gtk::Box m_container;
  Gtk::Frame m_frame;
  Gtk::Label m_label1 {"A label"};
  Gtk::Label m_label2 {"Write here"};
  Gtk::CheckButton m_checkbutton_can_propagate_down {"Can propagate down in the capture phase"};
  Gtk::CheckButton m_checkbutton_can_propagate_up {"Can propagate up in the bubble phase"};
};

#endif //GTKMM_EVENT_PROPAGATION_H
