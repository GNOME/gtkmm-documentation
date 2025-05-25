/* gtkmm example Copyright (C) 2024 gtkmm development team
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
  ~ExampleWindow() override;

private:
  // Signal handlers:
  void on_window_mouse_pressed(int n_press, double x, double y);
  void on_first_button_mouse_pressed(int n_press, double x, double y);
  void on_second_button_mouse_pressed(int n_press, double x, double y);
  void on_third_button_mouse_pressed(int n_press, double x, double y);
  void on_third_button_clicked();
  void on_mouse_released(int n_press, double x, double y);
  void on_mouse_motion(double x, double y);
  bool on_mouse_scroll(double dx, double dy);
  bool on_key_pressed(guint keyval, guint keycode, Gdk::ModifierType state);

  Gtk::Box m_box;
  Gtk::CheckButton m_first;
  Gtk::CheckButton m_second;
  Gtk::Button m_third;

  Glib::RefPtr<Gtk::GestureClick> m_window_click;
  Glib::RefPtr<Gtk::GestureClick> m_first_button_click;
  Glib::RefPtr<Gtk::GestureClick> m_second_button_click;
};

#endif //GTKMM_EXAMPLEWINDOW_H
