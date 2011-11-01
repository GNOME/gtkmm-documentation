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

#include "keyboard_events.h"


KeyboardEvents::KeyboardEvents()
{
    // Radio buttons

  m_first.set_label ("First");
  m_second.set_label ("Second");

  Gtk::RadioButton::Group group = m_first.get_group();

  m_second.set_group (group);


  m_first.set_active();


    // Main Container

  m_container.add (m_first);
  m_container.add (m_second);


    // Window

  add (m_container);

  set_title ("Keyboard Events");

  set_border_width (10);

  show_all_children();


    // Events

  add_events (Gdk::KEY_PRESS_MASK);


  signal_key_press_event().connect(sigc::mem_fun(*this,
                                   &KeyboardEvents::onKeyPress));
}




bool KeyboardEvents::onKeyPress (GdkEventKey *event)
{
    //GDK_MOD1_MASK -> the 'alt' key (mask)
    //GDK_KEY_1     -> the '1' key
    //GDK_KEY_2     -> the '2' key

    //select the first radio button, when we press alt + 1
  if ((event->keyval == GDK_KEY_1) &&
     (event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_MOD1_MASK)
  {
    m_first.set_active();
  }

    //and the second radio button, when we press alt + 2
  else if ((event->keyval == GDK_KEY_2) &&
          (event->state & (GDK_SHIFT_MASK | GDK_CONTROL_MASK | GDK_MOD1_MASK)) == GDK_MOD1_MASK)
  {
    m_second.set_active();
  }


    //close the window, when the 'esc' key is pressed
  else if (event->keyval == GDK_KEY_Escape)
  {
    hide();
  }


    //returning true, cancels the propagation of the event
  return true;
}


KeyboardEvents::~KeyboardEvents()
{

}
