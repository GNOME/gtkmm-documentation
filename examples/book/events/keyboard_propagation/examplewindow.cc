/* gtkmm example Copyright (C) 2011 gtkmm development team
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

// In gtkmm3, this example used an Entry instead of m_label2. This would not work
// as intended in gtkmm4. GtkEntry in gtk4 marks a key press signal as handled
// in the target phase. It's not propagated further up to the Box and the Window.

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("Event Propagation");
  m_container.set_margin(10);
  set_child(m_container);

  m_frame.set_child(m_label2);
  m_label2.set_selectable();
  m_checkbutton_can_propagate_down.set_active();
  m_checkbutton_can_propagate_up.set_active();

  // Main container
  m_container.set_orientation(Gtk::Orientation::VERTICAL);
  m_container.append(m_label1);
  m_container.append(m_frame);
  m_container.append(m_checkbutton_can_propagate_down);
  m_container.append(m_checkbutton_can_propagate_up);

  // Event controllers
  const bool after = false; // Run before or after the default signal handlers.

  // Called in the capture phase of the event handling.
  auto controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::label2_key_pressed), "capture"), after);
  m_label2.add_controller(controller);

  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::box_key_pressed), "capture"), after);
  m_container.add_controller(controller);

  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::CAPTURE);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::window_key_pressed), "capture"), after);
  add_controller(controller);

  // Called in the target phase of the event handling.
  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::TARGET);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::label2_key_pressed), "target"), after);
  m_label2.add_controller(controller);

  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::TARGET);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::box_key_pressed), "target"), after);
  m_container.add_controller(controller);

  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::TARGET);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::window_key_pressed), "target"), after);
  add_controller(controller);

  // Called in the bubble phase of the event handling.
  // This is the default, if set_propagation_phase() is not called.
  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::label2_key_pressed), "bubble"), after);
  m_label2.add_controller(controller);

  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::box_key_pressed), "bubble"), after);
  m_container.add_controller(controller);

  controller = Gtk::EventControllerKey::create();
  controller->set_propagation_phase(Gtk::PropagationPhase::BUBBLE);
  controller->signal_key_pressed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::window_key_pressed), "bubble"), after);
  add_controller(controller);
}

// By changing the return value we allow, or don't allow, the event to propagate to other elements.
bool ExampleWindow::label2_key_pressed(guint keyval, guint, Gdk::ModifierType, const Glib::ustring& phase)
{
  std::cout << "Label,  " << phase << " phase" << std::endl;

  if (phase == "bubble")
  {
    const gunichar unichar = gdk_keyval_to_unicode(keyval);
    if (unichar != 0)
    {
      if (m_first)
      {
        m_label2.set_label("");
        m_first = false;
      }
      if (unichar == '\b')
        m_label2.set_label("");
      else
      {
        const Glib::ustring newchar(1, unichar);
        m_label2.set_label(m_label2.get_label() + newchar);
      }
    }

    if (!m_checkbutton_can_propagate_up.get_active())
      return true; // Don't propagate
  }
  return false;
}

bool ExampleWindow::box_key_pressed(guint, guint, Gdk::ModifierType, const Glib::ustring& phase)
{
  std::cout << "Box,    " << phase << " phase" << std::endl;

  // Let it propagate
  return false;
}

// This will set the second label's text in the first label every time a key is pressed.
bool ExampleWindow::window_key_pressed(guint, guint, Gdk::ModifierType, const Glib::ustring& phase)
{
  if (phase == "capture")
    std::cout << std::endl;
  std::cout << "Window, " << phase << " phase";

  // Checking if the second label is on focus, otherwise the label would get
  // changed by pressing keys on the window (when the label is not on focus),
  // even if m_checkbutton_can_propagate_up wasn't active.
  if (phase == "bubble" && m_label2.has_focus())
  {
    m_label1.set_label(m_label2.get_label());
    std::cout << ", " << m_label2.get_label();
  }
  std::cout << std::endl;

  if (phase == "capture" && !m_checkbutton_can_propagate_down.get_active())
    return true; // Don't propagate
  return false;
}

ExampleWindow::~ExampleWindow()
{
}
