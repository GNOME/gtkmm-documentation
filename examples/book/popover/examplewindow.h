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
  // Signal handlers
  void on_combo_changed();
  void on_day_selected();
  void on_button_pressed(int n_press, double x, double y);
  void on_button_released(int n_press, double x, double y);

  // Containers
  Gtk::Grid m_grid;
  Gtk::Grid m_toggle_form_grid;
  Gtk::Box m_format_buttons_box;
  Gtk::Grid m_calendar_form_grid;

  // Widgets
  Gtk::MenuButton m_menu_button;

  Gtk::Popover m_toggle_form_popover;
  Gtk::Label m_toggle_form_label;
  Gtk::ToggleButton m_toggle_form_buttons[3];
  Gtk::Label m_toggle_form_combo_label;
  Gtk::ComboBoxText m_toggle_form_combo;

  Gtk::Calendar m_calendar;
  Gtk::Popover m_calendar_popover;
  Gtk::Label m_calendar_popover_label;
  Gtk::Entry m_calendar_popover_entry;

  // Event controller
  Glib::RefPtr<Gtk::GestureClick> m_calendar_event_controller;

private:
  void configure_form_popover();
  void configure_form_buttons();
  void configure_form_combo();
  void configure_cal_popover();

  void show_calendar_popover(double x, double y);

  double m_button_pressed_x;
  double m_button_pressed_y;
  bool m_button_pressed_called = false;
  bool m_day_selected_called = false;
};

#endif // GTKMM_EXAMPLEWINDOW_H
