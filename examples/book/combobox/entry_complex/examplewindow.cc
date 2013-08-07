//$Id: examplewindow.cc 838 2007-05-10 01:35:59Z jjongsma $ -*- c++ -*-

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
  Gtk::TreeModel::Row row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = "1";
  row[m_Columns.m_col_name] = "Billy Bob";
  /*
  Gtk::TreeModel::Row childrow = *(m_refTreeModel->append(row.children()));
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
  //m_Combo.pack_start(m_Columns.m_col_id);
  m_Combo.pack_start(m_Columns.m_col_name);

  m_Combo.set_entry_text_column(m_Columns.m_col_id);
  m_Combo.set_active(1);

  //Add the ComboBox to the window.
  add(m_Combo);

  //Connect signal handlers:
  Gtk::Entry* entry = m_Combo.get_entry();
  if (entry)
  {
    // The Entry shall receive focus-out events.
    entry->add_events(Gdk::FOCUS_CHANGE_MASK);
    // Alternatively you can connect to m_Combo.signal_changed().
    entry->signal_changed().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_changed) );
    entry->signal_activate().connect(sigc::mem_fun(*this,
      &ExampleWindow::on_entry_activate) );
    m_ConnectionFocusOut = entry->signal_focus_out_event().
      connect(sigc::mem_fun(*this, &ExampleWindow::on_entry_focus_out_event) );
  }
  else
    std::cout << "No Entry ???" << std::endl;

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
  // The focus_out signal may be emitted while m_Combo is being destructed.
  // The signal handler can generate critical messages, if it's called when
  // m_Combo has been partly destructed.
  m_ConnectionFocusOut.disconnect();
}

void ExampleWindow::on_entry_changed()
{
  Gtk::Entry* entry = m_Combo.get_entry();
  if (entry)
  {
    std::cout << "on_entry_changed(): Row=" << m_Combo.get_active_row_number()
      << ", ID=" << entry->get_text() << std::endl;
  }
}

void ExampleWindow::on_entry_activate()
{
  Gtk::Entry* entry = m_Combo.get_entry();
  if (entry)
  {
    std::cout << "on_entry_activate(): Row=" << m_Combo.get_active_row_number()
      << ", ID=" << entry->get_text() << std::endl;
  }
}

bool ExampleWindow::on_entry_focus_out_event(GdkEventFocus* /* event */)
{
  Gtk::Entry* entry = m_Combo.get_entry();
  if (entry)
  {
    std::cout << "on_entry_focus_out_event(): Row=" << m_Combo.get_active_row_number()
      << ", ID=" << entry->get_text() << std::endl;
    return true;
  }
  return false;
}
