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

#include "examplewindow.h"
#include <map>
#include <iostream>

namespace
{
std::map<unsigned int, Glib::ustring> mouse_buttons
{
  {0, "No button"},
  {GDK_BUTTON_PRIMARY, "Primary"},
  {GDK_BUTTON_MIDDLE, "Middle"},
  {GDK_BUTTON_SECONDARY, "Secondary"},
};
}

ExampleWindow::ExampleWindow()
: m_first("First"),
  m_second("Second"),
  m_third("Click me")
{
  set_title("Keyboard and Mouse Events");
  m_box.set_margin(10);
  set_child(m_box);

  // Radio buttons
  m_second.set_group(m_first);
  m_first.set_active();

  // Main container
  m_box.set_orientation(Gtk::Orientation::HORIZONTAL);
  m_box.append(m_first);
  m_box.append(m_second);
  m_box.append(m_third);

  // Keyboard events
  auto key_controller = Gtk::EventControllerKey::create();
  key_controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_key_pressed), false);
  add_controller(key_controller);

  // Mouse events, window
  auto motion_controller = Gtk::EventControllerMotion::create();
  motion_controller->signal_motion().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_mouse_motion));
  add_controller(motion_controller);

  m_window_click = Gtk::GestureClick::create();
  m_window_click->set_button(0); // All mouse buttons
  m_window_click->signal_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_window_mouse_pressed));
  add_controller(m_window_click);

  auto mouse_click = Gtk::GestureClick::create();
  mouse_click->set_button(GDK_BUTTON_PRIMARY);
  mouse_click->signal_released().connect(sigc::mem_fun(*this, &ExampleWindow::on_mouse_released));
  add_controller(mouse_click);

  auto mouse_scroll = Gtk::EventControllerScroll::create();
  mouse_scroll->set_flags(Gtk::EventControllerScroll::Flags::VERTICAL);
  // Handle mouse wheel rotations
  mouse_scroll->signal_scroll().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_mouse_scroll), true);
  add_controller(mouse_scroll);

  // Mouse events, buttons
  m_first_button_click = Gtk::GestureClick::create();
  m_first_button_click->set_button(GDK_BUTTON_PRIMARY);
  m_first_button_click->signal_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_first_button_mouse_pressed));
  m_first.add_controller(m_first_button_click);

  m_second_button_click = Gtk::GestureClick::create();
  m_second_button_click->set_button(GDK_BUTTON_PRIMARY);
  m_second_button_click->signal_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_second_button_mouse_pressed));
  m_second.add_controller(m_second_button_click);

  mouse_click = Gtk::GestureClick::create();
  // This mouse event must be handled in the capture phase.
  // The GtkButton C class handles the event in the capture phase and
  // does not let it propagate to the bubble phase where events are
  // handled by default.
  mouse_click->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  mouse_click->set_button(GDK_BUTTON_PRIMARY);
  mouse_click->signal_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_third_button_mouse_pressed));
  m_third.add_controller(mouse_click);
  m_third.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_third_button_clicked));
}

void ExampleWindow::on_window_mouse_pressed(int n_press, double x, double y)
{
  const auto current_button = mouse_buttons[m_window_click->get_current_button()];
  std::cout << "Mouse pressed in window: " << current_button
    << ", " << n_press << ", " << x << ", " << y << std::endl;
}

void ExampleWindow::on_first_button_mouse_pressed(int n_press, double x, double y)
{
  const auto current_button = mouse_buttons[m_first_button_click->get_current_button()];
  std::cout << "Mouse pressed in first button: " << current_button
    << ", " << n_press << ", " << x << ", " << y << std::endl;
}

void ExampleWindow::on_second_button_mouse_pressed(int n_press, double x, double y)
{
  const auto current_button = mouse_buttons[m_second_button_click->get_current_button()];
  std::cout << "Mouse pressed in second button: " << current_button
    << ", " << n_press << ", " << x << ", " << y << std::endl;
}

void ExampleWindow::on_third_button_mouse_pressed(int n_press, double x, double y)
{
  std::cout << "Mouse pressed in third button: "
    << n_press << ", " << x << ", " << y << std::endl;
}

void ExampleWindow::on_third_button_clicked()
{
  std::cout << "Third button clicked" << std::endl;
}

void ExampleWindow::on_mouse_released(int n_press, double x, double y)
{
  std::cout << "Mouse released: " << n_press << ", " << x << ", " << y << std::endl;
}

void ExampleWindow::on_mouse_motion(double x, double y)
{
  std::cout << "Mouse motion: "  << x << ", " << y << std::endl;
}

bool ExampleWindow::on_mouse_scroll(double dx, double dy)
{
  std::cout << "Mouse scroll: "  << dx << ", " << dy << std::endl;
  return true; // handled
}

bool ExampleWindow::on_key_pressed(guint keyval, guint, Gdk::ModifierType state)
{
  // Gdk::ModifierType::ALT_MASK -> the 'Alt' key(mask)
  // GDK_KEY_1 -> the '1' key
  // GDK_KEY_2 -> the '2' key

  // Select the first radio button, when we press Alt + 1
  if ((keyval == GDK_KEY_1) &&
    (state & (Gdk::ModifierType::SHIFT_MASK | Gdk::ModifierType::CONTROL_MASK | Gdk::ModifierType::ALT_MASK)) == Gdk::ModifierType::ALT_MASK)
  {
    m_first.set_active();
    // Returning true, cancels the propagation of the event
    return true;
  }
  else if ((keyval == GDK_KEY_2) &&
    (state & (Gdk::ModifierType::SHIFT_MASK | Gdk::ModifierType::CONTROL_MASK | Gdk::ModifierType::ALT_MASK)) == Gdk::ModifierType::ALT_MASK)
  {
    // and the second radio button, when we press Alt + 2
    m_second.set_active();
    return true;
  }
  else if (keyval == GDK_KEY_Escape)
  {
    // Close the window, when the 'Esc' key is pressed
    set_visible(false);
    return true;
  }

  // The event has not been handled
  return false;
}

ExampleWindow::~ExampleWindow()
{
}
