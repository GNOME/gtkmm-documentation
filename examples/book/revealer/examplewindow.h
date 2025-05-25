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

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  virtual ~ExampleWindow();

protected:
  // Slots
  void on_switch_active_changed();

  // Containers
  Gtk::Box m_vbox;
  Gtk::Grid m_controls;

  // Widgets
  Gtk::Revealer m_revealer;
  Gtk::Label m_label;
  Gtk::Separator m_separator;
  Gtk::DropDown m_transition_type;
  Gtk::Label m_transition_type_label;
  Gtk::SpinButton m_transition_duration;
  Gtk::Label m_transition_duration_label;
  Gtk::Switch m_switch;
  Gtk::Label m_switch_label;

private:
  void compose_transition_selector();
  Gtk::RevealerTransitionType get_selected_transition_type();
};

#endif // GTKMM_EXAMPLEWINDOW_H
