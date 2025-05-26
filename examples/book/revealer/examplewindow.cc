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
  m_label("A child widget."),
  m_transition_type_label("Transition type:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER),
  m_transition_duration(1.0, 0),
  m_transition_duration_label("Duration (in ms):", Gtk::ALIGN_END, Gtk::ALIGN_CENTER),
  m_switch_label("Reveal child:", Gtk::ALIGN_END, Gtk::ALIGN_CENTER)
{
  // Window properties
  set_title("Revealer Example");
  set_border_width(12);
  set_resizable(false);

  // Transition type selector
  compose_transition_selector();
  m_controls.attach(m_transition_type_label, 0, 0, 1, 1);
  m_controls.attach(m_transition_type, 1, 0, 1, 1);

  // Transition duration selector
  m_transition_duration.set_range(10.0, 10000.0); // Up to 10 secs
  m_transition_duration.set_value(1000.0);
  m_controls.attach(m_transition_duration_label, 0, 1, 1, 1);
  m_controls.attach(m_transition_duration, 1, 1, 1, 1);

  // Switch
  m_switch.set_active(true);
  m_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_switch_active_changed));
  m_controls.attach(m_switch_label, 0, 2, 1, 1);
  m_controls.attach(m_switch, 1, 2, 1, 1);

  // Revealer
  m_revealer.add(m_label);
  m_revealer.set_reveal_child(true);

  // Layout
  m_controls.set_row_spacing(6);
  m_controls.set_column_spacing(12);
  m_vbox.pack_start(m_controls, Gtk::PACK_SHRINK, 0);
  m_vbox.pack_start(m_separator, Gtk::PACK_SHRINK, 12);
  m_vbox.pack_start(m_revealer, Gtk::PACK_EXPAND_WIDGET, 6);
  add(m_vbox);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::compose_transition_selector()
{
  m_transition_type.append("None (NONE)");
  m_transition_type.append("Fade in (CROSSFADE)");
  m_transition_type.append("Slide in from the left (SLIDE_RIGHT)");
  m_transition_type.append("Slide in from the right (SLIDE_LEFT)");
  m_transition_type.append("Slide in from the bottom (SLIDE_UP)");
  m_transition_type.append("Slide in from the top (SLIDE_DOWN)");

  m_transition_type.set_active(0);
}

void ExampleWindow::on_switch_active_changed()
{
  const bool reveal_child = m_switch.get_active();
  const Gtk::RevealerTransitionType transition_type = get_selected_transition_type();
  const guint transition_duration = m_transition_duration.get_value_as_int();

  m_revealer.set_transition_type(transition_type);
  m_revealer.set_transition_duration(transition_duration);
  m_revealer.set_reveal_child(reveal_child);
}

Gtk::RevealerTransitionType ExampleWindow::get_selected_transition_type()
{
  Gtk::RevealerTransitionType transition_type = Gtk::REVEALER_TRANSITION_TYPE_NONE;
  const int active_row = m_transition_type.get_active_row_number();

  switch (active_row)
  {
    case 0:
    default:
      transition_type = Gtk::REVEALER_TRANSITION_TYPE_NONE;
      break;
    case 1:
      transition_type = Gtk::REVEALER_TRANSITION_TYPE_CROSSFADE;
      break;
    case 2:
      transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_RIGHT;
      break;
    case 3:
      transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_LEFT;
      break;
    case 4:
      transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_UP;
      break;
    case 5:
      transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_DOWN;
      break;
  }

  return transition_type;
}
