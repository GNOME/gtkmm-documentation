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
: m_vbox(Gtk::Orientation::VERTICAL),
  m_label("A child widget."),
  m_transition_type_label("Transition type:", Gtk::Align::END, Gtk::Align::CENTER),
  m_transition_duration(1.0, 0),
  m_transition_duration_label("Duration (in ms):", Gtk::Align::END, Gtk::Align::CENTER),
  m_switch_label("Reveal child:", Gtk::Align::END, Gtk::Align::CENTER)
{
  // Window properties
  set_title("Revealer Example");

  // Transition type selector
  compose_transition_selector();
  m_controls.attach(m_transition_type_label, 0, 0);
  m_controls.attach(m_transition_type, 1, 0);

  // Transition duration selector
  m_transition_duration.set_range(10.0, 10000.0); // Up to 10 secs
  m_transition_duration.set_increments(10.0, 100.0);
  m_transition_duration.set_value(1000.0);
  m_controls.attach(m_transition_duration_label, 0, 1);
  m_controls.attach(m_transition_duration, 1, 1);

  // Switch
  m_switch.set_active(true);
  m_switch.set_halign(Gtk::Align::START);
  m_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_switch_active_changed));
  m_controls.attach(m_switch_label, 0, 2);
  m_controls.attach(m_switch, 1, 2);

  // Revealer
  m_revealer.set_child(m_label);
  m_revealer.set_reveal_child(true);

  // Layout
  m_controls.set_row_spacing(6);
  m_controls.set_column_spacing(12);
  m_vbox.append(m_controls);
  m_vbox.append(m_separator);
  m_separator.set_margin_start(12);
  m_separator.set_margin_end(18);
  m_vbox.append(m_revealer);
  m_revealer.set_expand(true);
  m_vbox.set_margin(12);
  set_child(m_vbox);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::compose_transition_selector()
{
  const std::vector<Glib::ustring> strings{
    "None (NONE)",
    "Fade in (CROSSFADE)",
    "Slide in from the left (SLIDE_RIGHT)",
    "Slide in from the right (SLIDE_LEFT)",
    "Slide in from the bottom (SLIDE_UP)",
    "Slide in from the top (SLIDE_DOWN)"
  };
  m_transition_type.set_model(Gtk::StringList::create(strings));

  m_transition_type.set_selected(0);
}

void ExampleWindow::on_switch_active_changed()
{
  const bool reveal_child = m_switch.get_active();
  const auto transition_type = get_selected_transition_type();
  const guint transition_duration = m_transition_duration.get_value_as_int();

  m_revealer.set_transition_type(transition_type);
  m_revealer.set_transition_duration(transition_duration);
  m_revealer.set_reveal_child(reveal_child);
}

Gtk::RevealerTransitionType ExampleWindow::get_selected_transition_type()
{
  auto transition_type = Gtk::RevealerTransitionType::NONE;
  const auto active_row = m_transition_type.get_selected();

  switch (active_row)
  {
    case 0:
    default:
      transition_type = Gtk::RevealerTransitionType::NONE;
      break;
    case 1:
      transition_type = Gtk::RevealerTransitionType::CROSSFADE;
      break;
    case 2:
      transition_type = Gtk::RevealerTransitionType::SLIDE_RIGHT;
      break;
    case 3:
      transition_type = Gtk::RevealerTransitionType::SLIDE_LEFT;
      break;
    case 4:
      transition_type = Gtk::RevealerTransitionType::SLIDE_UP;
      break;
    case 5:
      transition_type = Gtk::RevealerTransitionType::SLIDE_DOWN;
      break;
  }

  return transition_type;
}
