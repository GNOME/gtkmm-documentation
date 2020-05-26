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
  set_title("ComboBox example");

  //Create the Tree model:
  //m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_Combo.set_model(m_refTreeModel);

  //Fill the ComboBox's Tree Model:
  auto row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = "1";
  row[m_Columns.m_col_name] = "Billy Bob";
  /*
  auto childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 11;
  childrow[m_Columns.m_col_name] = "Billy Bob Junior";

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 12;
  childrow[m_Columns.m_col_name] = "Sue Bob";
  */

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = "2";
  row[m_Columns.m_col_name] = "Joey Jojo";

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = "3";
  row[m_Columns.m_col_name] = "Rob McRoberts";

  /*
  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 31;
  childrow[m_Columns.m_col_name] = "Xavier McRoberts";
  */

  //Add the model columns to the Combo (which is a kind of view),
  //rendering them in the default way:
  //This is automatically rendered when we use set_entry_text_column().
  //m_Combo.pack_start(m_Columns.m_col_id, Gtk::PackOptions::EXPAND_WIDGET);
  m_Combo.pack_start(m_Columns.m_col_name);

  m_Combo.set_entry_text_column(m_Columns.m_col_id);
  m_Combo.set_active(1);

  //Add the ComboBox to the window.
  set_child(m_Combo);

  //Connect signal handlers:
  m_Combo.signal_changed().connect(sigc::mem_fun(*this, &ExampleWindow::on_combo_changed));

  auto entry = m_Combo.get_entry();
  if (entry)
  {
    entry->signal_changed().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_changed) );
    m_ConnectionHasFocusChanged = entry->property_has_focus().signal_changed().
      connect(sigc::mem_fun(*this, &ExampleWindow::on_entry_has_focus_changed));
  }
  else
    std::cout << "No Entry ???" << std::endl;
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
  auto entry = m_Combo.get_entry();
  if (entry)
  {
    std::cout << "on_combo_changed(): Row=" << m_Combo.get_active_row_number()
      << ", ID=" << entry->get_text() << std::endl;
  }
}

void ExampleWindow::on_entry_changed()
{
  auto entry = m_Combo.get_entry();
  if (entry)
  {
    std::cout << "on_entry_changed(): Row=" << m_Combo.get_active_row_number()
      << ", ID=" << entry->get_text() << std::endl;
  }
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
