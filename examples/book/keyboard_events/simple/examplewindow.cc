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

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
{
  set_title("Keyboard Events");
  set_border_width(10);
  add(m_container);
  
  // Radio buttons:
  m_first.set_label("First");
  m_second.set_label("Second");

  Gtk::RadioButton::Group group = m_first.get_group();
  m_second.set_group(group);
  m_first.set_active();

  // Main Container:
  m_container.add(m_first);
  m_container.add(m_second);

  // Events.
  // We override the default event signal handler.
  add_events(Gdk::KEY_PRESS_MASK);

  show_all_children();
}

bool ExampleWindow::on_key_press_event(GdkEventKey* event)
{
  //GDK_MOD1_MASK -> the 'alt' key(mask)
  //GDK_KEY_1 -> the '1' key
  //GDK_KEY_2 -> the '2' key

  //select the first radio button, when we press alt + 1
  if((event->keyval == GDK_KEY_1) &&
    (event->state &(GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_MOD1_MASK)
  {
    m_first.set_active();
    //returning true, cancels the propagation of the event
    return true;
  }
  else if((event->keyval == GDK_KEY_2) &&
    (event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_MOD1_MASK)
  {
    //and the second radio button, when we press alt + 2
    m_second.set_active();
    return true;
  }
  else if(event->keyval == GDK_KEY_Escape)
  {
    //close the window, when the 'esc' key is pressed
    hide();
    return true;
  }

  //if the event has not been handled, call the base class
  return Gtk::Window::on_key_press_event(event);
}

ExampleWindow::~ExampleWindow()
{
}

