/* gtkmm example Copyright (C) 2002 gtkmm development team
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
#include <iostream>

ExampleWindow::ExampleWindow()
: m_Combo(true /* has_entry */)
{
  set_title("ComboBoxText example");

  //Fill the combo:
  m_Combo.append("something");
  m_Combo.append("something else");
  m_Combo.append("something or other");
  m_Combo.set_active(0);

  add(m_Combo);

  //Connect signal handlers:
  auto entry = m_Combo.get_entry();
  // Alternatively you can connect to entry->signal_changed().
  m_Combo.signal_changed().connect(sigc::mem_fun(*this,
    &ExampleWindow::on_combo_changed) );
  if (entry)
  {
    // The Entry shall receive focus-out events.
    entry->add_events(Gdk::FOCUS_CHANGE_MASK);
    entry->signal_activate().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_activate) );
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

void ExampleWindow::on_entry_activate()
{
  std::cout << "on_entry_activate(): Row=" << m_Combo.get_active_row_number()
    << ", Text=" << m_Combo.get_active_text() << std::endl;
}

bool ExampleWindow::on_entry_focus_out_event(GdkEventFocus* /* event */)
{
  std::cout << "on_entry_focus_out_event(): Row=" << m_Combo.get_active_row_number()
    << ", Text=" << m_Combo.get_active_text() << std::endl;
  return true;
}
