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

#ifndef GTKMM_REVEALERWINDOW_H
#define GTKMM_REVEALERWINDOW_H

#include <gtkmm.h>

class RevealerWindow : public Gtk::Window
{
public:
  RevealerWindow();
  virtual ~RevealerWindow();

protected:
  // Slots
  void on_switch_active_changed();

  // Containers 
  Gtk::Box m_vbox;
  Gtk::Frame m_transition_selector_frame;
  Gtk::Frame m_transition_duration_frame;
  Gtk::VBox m_transition_type_selector;

  // Widgets
  Gtk::Revealer m_revealer;
  Gtk::Label m_label;
  Gtk::Separator m_separator;
  Gtk::RadioButton m_transition_type_buttons[6];
  Gtk::SpinButton m_transition_duration;
  Gtk::Switch m_switch;

private:
  void group_transition_type_buttons();
  void format_transition_labels();
  void compose_transition_selector();
  Gtk::RevealerTransitionType get_selected_transition_type();
};

#endif // GTKMM_REVEALERWINDOW_H

