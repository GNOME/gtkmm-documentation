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

#include "revealerwindow.h"

RevealerWindow::RevealerWindow()
: m_label("A child widget."),
  m_vbox(Gtk::ORIENTATION_VERTICAL),
  m_transition_duration(1.0, 0)
{
  // Window properties
  set_title("Revealer Example");
  set_border_width(6);
  set_resizable(false);

  // Transition type selector
  group_transition_type_buttons();
  format_transition_labels();
  compose_transition_selector();
  m_transition_selector_frame.set_label("Transition type");
  m_transition_selector_frame.add(m_transition_type_selector);

  // Duration selector
  m_transition_duration.set_range(10.0, 10000.0); // Up to 10 secs
  m_transition_duration.set_value(1000.0);
  m_transition_duration_frame.set_label("Transition duration (in ms)");
  m_transition_duration_frame.add(m_transition_duration);

  // Switch
  m_switch.set_active(true);
  m_switch.property_active().signal_changed().connect(sigc::mem_fun(*this, &RevealerWindow::on_switch_active_changed));

  // Revealer
  m_revealer.add(m_label);
  m_revealer.set_reveal_child(true);

  // Layout
  m_vbox.pack_start(m_transition_selector_frame, Gtk::PACK_SHRINK, 6);
  m_vbox.pack_start(m_transition_duration_frame, Gtk::PACK_SHRINK, 6);
  m_vbox.pack_start(m_switch, Gtk::PACK_SHRINK, 6);
  m_vbox.pack_start(m_separator, Gtk::PACK_SHRINK, 6);
  m_vbox.pack_start(m_revealer, Gtk::PACK_EXPAND_WIDGET, 6);
  add(m_vbox);

  show_all_children();
}

RevealerWindow::~RevealerWindow()
{
}

void RevealerWindow::group_transition_type_buttons()
{
  m_transition_type_buttons[1].join_group(m_transition_type_buttons[0]);
  m_transition_type_buttons[2].join_group(m_transition_type_buttons[0]);
  m_transition_type_buttons[3].join_group(m_transition_type_buttons[0]);
  m_transition_type_buttons[4].join_group(m_transition_type_buttons[0]);
  m_transition_type_buttons[5].join_group(m_transition_type_buttons[0]);
}

void RevealerWindow::format_transition_labels()
{
    m_transition_type_buttons[0].set_label("None (NONE)");
    m_transition_type_buttons[1].set_label("Fade in (CROSSFADE)");
    m_transition_type_buttons[2].set_label("Slide in from the left (SLIDE_RIGHT)");
    m_transition_type_buttons[3].set_label("Slide in from the right (SLIDE_LEFT)");
    m_transition_type_buttons[4].set_label("Slide in from the bottom (SLIDE_UP)");
    m_transition_type_buttons[5].set_label("Slide in from the top (SLIDE_DOWN)");
}

void RevealerWindow::compose_transition_selector()
{
  m_transition_type_selector.pack_start(m_transition_type_buttons[0]);
  m_transition_type_selector.pack_start(m_transition_type_buttons[1]);
  m_transition_type_selector.pack_start(m_transition_type_buttons[2]);
  m_transition_type_selector.pack_start(m_transition_type_buttons[3]);
  m_transition_type_selector.pack_start(m_transition_type_buttons[4]);
  m_transition_type_selector.pack_start(m_transition_type_buttons[5]);
}

void RevealerWindow::on_switch_active_changed()
{
    bool reveal_child = m_switch.get_active();
    Gtk::RevealerTransitionType transition_type = get_selected_transition_type();
    guint transition_duration = m_transition_duration.get_value_as_int();

    m_revealer.set_transition_type(transition_type);
    m_revealer.set_transition_duration(transition_duration);
    m_revealer.set_reveal_child(reveal_child);
}

Gtk::RevealerTransitionType RevealerWindow::get_selected_transition_type()
{
    Gtk::RevealerTransitionType transition_type = Gtk::REVEALER_TRANSITION_TYPE_NONE;

    if (m_transition_type_buttons[0].get_active()) {
        transition_type = Gtk::REVEALER_TRANSITION_TYPE_NONE;
    }
    else if (m_transition_type_buttons[1].get_active()) {
        transition_type = Gtk::REVEALER_TRANSITION_TYPE_CROSSFADE;
    }
    else if (m_transition_type_buttons[2].get_active()) {
        transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_RIGHT;
    }
    else if (m_transition_type_buttons[3].get_active()) {
        transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_LEFT;
    }
    else if (m_transition_type_buttons[4].get_active()) {
        transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_UP;
    }
    else if (m_transition_type_buttons[5].get_active()) {
        transition_type = Gtk::REVEALER_TRANSITION_TYPE_SLIDE_DOWN;
    }

    return transition_type;
}

