/* gtkmm example Copyright (C) 2011 gtkmm development team
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

//TODO: This example does not work as intended in gtkmm4. The propagation of
// event signal works differently in gtk+3 and gtk+4. GtkEntry in gtk+4 marks
// a key press signal as handled. It's not propagated further up to the Grid
// and the Window.

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("Event Propagation");
  m_container.set_margin(10);
  add(m_container);

  m_label.set_label("A label");
  m_checkbutton_can_propagate.set_label("Can Propagate");
  m_checkbutton_can_propagate.set_active();

  // Main Container
  m_container.set_orientation(Gtk::Orientation::VERTICAL);
  m_container.add(m_label);
  m_container.add(m_entry);
  m_container.add(m_checkbutton_can_propagate);

  // Events
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::entry_key_pressed), true);
  m_entry.add_controller(controller);

  controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::grid_key_pressed), true);
  m_container.add_controller(controller);

  // Called in the capture phase of the event handling.
  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::window_key_pressed_capture), false);
  add_controller(controller);

  // Called in the target phase of the event handling.
  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::TARGET);
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::window_key_pressed_target), false);
  add_controller(controller);

  // Called in the bubble phase of the event handling.
  // This is the default, if set_propagation_phase() is not called.
  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::window_key_pressed_bubble), true);
  add_controller(controller);
}

//By changing the return value we allow, or don't allow, the event to propagate to other elements.
bool ExampleWindow::entry_key_pressed(guint, guint, Gdk::ModifierType)
{
  std::cout << "Entry" << std::endl;

  if(m_checkbutton_can_propagate.get_active())
  {
    return false;
  }

  return true;
}

bool ExampleWindow::grid_key_pressed(guint, guint, Gdk::ModifierType)
{
  std::cout << "Grid" << std::endl;

  //Let it propagate:
  return false;
}

bool ExampleWindow::window_key_pressed_capture(guint, guint, Gdk::ModifierType)
{
  std::cout << "Window, capture phase" << std::endl;
  return false;
}

bool ExampleWindow::window_key_pressed_target(guint, guint, Gdk::ModifierType)
{
  std::cout << "Window, target phase" << std::endl;
  return false;
}

// This will set the entry's text in the label, every time a key is pressed.
bool ExampleWindow::window_key_pressed_bubble(guint, guint, Gdk::ModifierType)
{
  std::cout << "Window, bubble phase";

  //checking if the entry is on focus, otherwise the label would get changed by pressing keys
  //on the window (when the entry is not on focus), even if m_checkbutton_can_propagate wasn't active
  if(m_entry.has_focus())
  {
    m_label.set_text(m_entry.get_text());
    std::cout << ", " << m_entry.get_text();
  }
  std::cout << std::endl;

  return true;
}

ExampleWindow::~ExampleWindow()
{
}

