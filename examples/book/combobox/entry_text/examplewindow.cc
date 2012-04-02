//$Id: examplewindow.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

/* gtkmm example Copyright (C) 2002 gtkmm development team
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

#include "examplewindow.h"
#include <gtkmm/stock.h>
#include <iostream>

ExampleWindow::ExampleWindow()
: m_Combo(true /* has_entry */)
{
  set_title("ComboBoxText example");

  //Fill the combo:
  m_Combo.append("something");
  m_Combo.append("something else");
  m_Combo.append("something or other");

  add(m_Combo);

  //Connect signal handlers:
  Gtk::Entry* entry = m_Combo.get_entry();
  // Alternatively you can connect to entry->signal_changed().
  m_Combo.signal_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_combo_changed) );
  if (entry)
  {
    // The Entry shall receive key-press events and focus-out events.
    entry->add_events(Gdk::KEY_PRESS_MASK | Gdk::FOCUS_CHANGE_MASK);
    // This signal handler must be called before the default signal handler,
    // or else it will not be called, if the default signal handler returns true.
    entry->signal_key_press_event().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_key_press_event), false );
    m_ConnectionFocusOut = entry->signal_focus_out_event().
      connect(sigc::mem_fun(*this, &ExampleWindow::on_entry_focus_out_event) );
  }
  else
    std::cout << "No Entry ???" << std::endl;

  m_Combo.property_has_frame() = false;
  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
  // The focus_out signal may be emitted while m_Combo is being destructed.
  // The signal handler can generate critical messages, if it's called when
  // m_Combo has been partly destructed.
  m_ConnectionFocusOut.disconnect();
}

void ExampleWindow::on_combo_changed()
{
  std::cout << "on_combo_changed(): Row=" << m_Combo.get_active_row_number()
    << ", Text=" << m_Combo.get_active_text() << std::endl;
}

bool ExampleWindow::on_entry_key_press_event(GdkEventKey* event)
{
  if (event->keyval == GDK_KEY_Return ||
      event->keyval == GDK_KEY_ISO_Enter ||
      event->keyval == GDK_KEY_KP_Enter)
  {
    std::cout << "on_entry_key_press_event(): Row=" << m_Combo.get_active_row_number()
      << ", Text=" << m_Combo.get_active_text() << std::endl;
    return true;
  }
  return false;
}

bool ExampleWindow::on_entry_focus_out_event(GdkEventFocus* /* event */)
{
  std::cout << "on_entry_focus_out_event(): Row=" << m_Combo.get_active_row_number()
    << ", Text=" << m_Combo.get_active_text() << std::endl;
  return true;
}
