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
    entry->signal_activate().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_activate) );
    m_ConnectionHasFocusChanged = entry->property_has_focus().signal_changed().
      connect(sigc::mem_fun(*this, &ExampleWindow::on_entry_has_focus_changed));
  }
  else
    std::cout << "No Entry ???" << std::endl;

  m_Combo.property_has_frame() = false;
}

ExampleWindow::~ExampleWindow()
{
  // The has_focus changed signal may be emitted while m_Combo is being destructed.
  // The signal handler can generate critical messages, if it's called when
  // m_Combo has been partly destructed.
  m_ConnectionHasFocusChanged.disconnect();
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

void ExampleWindow::on_entry_has_focus_changed()
{
  auto entry = m_Combo.get_entry();
  if (entry)
  {
    const bool entry_has_focus = entry->has_focus();
    if (m_entry_had_focus && !entry_has_focus)
    {
      // entry->has_focus() has changed from true to false; entry has lost focus.
      std::cout << "on_entry_has_focus_changed() to not focused: Row="
        << m_Combo.get_active_row_number() << ", ID=" << entry->get_text() << std::endl;
    }
    m_entry_had_focus = entry_has_focus;
  }
}
