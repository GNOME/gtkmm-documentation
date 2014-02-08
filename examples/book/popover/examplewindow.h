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
  void on_button_toggled();
  void on_combo_changed();
  void on_day_selected();

  // Containers 
  Gtk::Grid m_grid;
  Gtk::Grid m_toggle_form_grid;
  Gtk::Box m_format_buttons_box;
  Gtk::Grid m_calendar_form_grid;

  // Widgets
  Gtk::ToggleButton m_toggle_button;

  Gtk::Popover m_toggle_form_popover;
  Gtk::Label m_toggle_form_label;
  Gtk::RadioButton m_toggle_form_buttons[3];
  Gtk::Label m_toggle_form_combo_label;
  Gtk::ComboBoxText m_toggle_form_combo;

  Gtk::Calendar m_calendar;
  Gtk::Popover m_calendar_popover;
  Gtk::Label m_calendar_popover_label;
  Gtk::Entry m_calendar_popover_entry;

private:
  void configure_form_popover();
  void configure_form_buttons();
  void configure_form_combo();

  void configure_cal_popover();
};

#endif // GTKMM_EXAMPLEWINDOW_H

