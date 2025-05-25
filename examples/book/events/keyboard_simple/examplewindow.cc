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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
{
  set_title("Keyboard Events");
  m_container.set_margin(10);
  set_child(m_container);

  // Radio buttons:
  m_first.set_label("First");
  m_second.set_label("Second");

  m_second.set_group(m_first);
  m_first.set_active();

  // Main Container:
  m_container.set_orientation(Gtk::Orientation::HORIZONTAL);
  m_container.append(m_first);
  m_container.append(m_second);

  // Events.
  auto controller = Gtk::EventControllerKey::create();
  controller->signal_key_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_window_key_pressed), false);
  add_controller(controller);
}

bool ExampleWindow::on_window_key_pressed(guint keyval, guint, Gdk::ModifierType state)
{
  //Gdk::ModifierType::ALT_MASK -> the 'Alt' key(mask)
  //GDK_KEY_1 -> the '1' key
  //GDK_KEY_2 -> the '2' key

  //select the first radio button, when we press alt + 1
  if((keyval == GDK_KEY_1) &&
    (state & (Gdk::ModifierType::SHIFT_MASK | Gdk::ModifierType::CONTROL_MASK | Gdk::ModifierType::ALT_MASK)) == Gdk::ModifierType::ALT_MASK)
  {
    m_first.set_active();
    //returning true, cancels the propagation of the event
    return true;
  }
  else if((keyval == GDK_KEY_2) &&
    (state & (Gdk::ModifierType::SHIFT_MASK | Gdk::ModifierType::CONTROL_MASK | Gdk::ModifierType::ALT_MASK)) == Gdk::ModifierType::ALT_MASK)
  {
    //and the second radio button, when we press alt + 2
    m_second.set_active();
    return true;
  }
  else if(keyval == GDK_KEY_Escape)
  {
    //close the window, when the 'esc' key is pressed
    set_visible(false);
    return true;
  }

  //the event has not been handled
  return false;
}

ExampleWindow::~ExampleWindow()
{
}

