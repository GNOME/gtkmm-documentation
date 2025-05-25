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
#include <gtkmm/eventcontrollerfocus.h>
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
  auto entry = m_Combo.get_entry();
  if (entry)
  {
    // Alternatively you can connect to m_Combo.signal_changed().
    entry->signal_changed().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_changed));
#if HAS_SIGNAL_ACTIVATE
    entry->signal_activate().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_activate));
#endif
    // The Entry shall receive focus-leave events.
    auto controller = Gtk::EventControllerFocus::create();
    m_ConnectionFocusLeave = controller->signal_leave().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_entry_focus_leave));
    entry->add_controller(controller);
  }
  else
    std::cout << "No Entry ???" << std::endl;
}

ExampleWindow::~ExampleWindow()
{
  // The focus-leave signal may be emitted while m_Combo is being destructed.
  // The signal handler can generate critical messages, if it's called when
  // m_Combo has been partly destructed.
  m_ConnectionFocusLeave.disconnect();
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

#if HAS_SIGNAL_ACTIVATE
void ExampleWindow::on_entry_activate()
{
  auto entry = m_Combo.get_entry();
  if (entry)
  {
    std::cout << "on_entry_activate(): Row=" << m_Combo.get_active_row_number()
      << ", ID=" << entry->get_text() << std::endl;
  }
}
#endif

void ExampleWindow::on_entry_focus_leave()
{
  auto entry = m_Combo.get_entry();
  if (entry)
  {
    std::cout << "on_entry_focus_leave(): Row=" << m_Combo.get_active_row_number()
      << ", ID=" << entry->get_text() << std::endl;
  }
}
