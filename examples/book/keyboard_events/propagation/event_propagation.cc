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

#include "event_propagation.h"


EventPropagation::EventPropagation()
{
  m_label.set_label ("A label");

  m_canPropagate.set_label ("Can Propagate");

  m_canPropagate.set_active (true);


    // Main Container

  m_container.set_orientation (Gtk::ORIENTATION_VERTICAL);

  m_container.add (m_label);
  m_container.add (m_entry);
  m_container.add (m_canPropagate);


    // Window

  add (m_container);

  set_title ("Event Propagation");

  set_border_width (10);

  show_all_children();


    // Events

  add_events (Gdk::KEY_RELEASE_MASK);


  m_entry.signal_key_release_event().connect(sigc::mem_fun(*this,
                                         &EventPropagation::entryKeyRelease));

  m_container.signal_key_release_event().connect(sigc::mem_fun(*this,
                                         &EventPropagation::gridKeyRelease));

  signal_key_release_event().connect(sigc::mem_fun(*this,
                                         &EventPropagation::windowKeyRelease));
}




/*
    By changing the return value, we allow or not the event to propagate to other elements
 */

bool EventPropagation::entryKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Entry" << std::endl;

  if (m_canPropagate.get_active() == true)
  {
    return false;
  }

  return true;
}




bool EventPropagation::gridKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Grid" << std::endl;

    //let it propagate
  return false;
}




/*
    This will set the entry's text in the label, everytime a key is pressed
 */

bool EventPropagation::windowKeyRelease(GdkEventKey* /* event */ )
{
  std::cout << "Window" << std::endl;

      //checking if the entry is on focus, otherwise the label would get changed by pressing keys
      //on the window (when the entry is not on focus), even if canPropagate wasn't active
  if (m_entry.has_focus() == true)
  {
    m_label.set_text (m_entry.get_text());
  }


  return true;
}



EventPropagation::~EventPropagation()
{

}

