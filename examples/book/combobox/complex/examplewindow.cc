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
{
  set_title("ComboBox example");

  //Create the Tree model:
  //m_refTreeModel = Gtk::TreeStore::create(m_Columns);
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_Combo.set_model(m_refTreeModel);

  //Fill the ComboBox's Tree Model:
  auto iter = m_refTreeModel->append();
  auto row = *iter;
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Billy Bob";
  row[m_Columns.m_col_extra] = "something";
  m_Combo.set_active(iter);
  /*
  auto childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 11;
  childrow[m_Columns.m_col_name] = "Billy Bob Junior";

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 12;
  childrow[m_Columns.m_col_name] = "Sue Bob";
  */

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Joey Jojo";
  row[m_Columns.m_col_extra] = "yadda";


  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  row[m_Columns.m_col_extra] = "";

  /*
  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_Columns.m_col_id] = 31;
  childrow[m_Columns.m_col_name] = "Xavier McRoberts";
  */

  //Add the model columns to the Combo (which is a kind of view),
  //rendering them in the default way:
  m_Combo.pack_start(m_Columns.m_col_id);
  m_Combo.pack_start(m_Columns.m_col_name);

  //An example of adding a cell renderer manually,
  //instead of using pack_start(model_column, Gtk::PackOptions::EXPAND_WIDGET)
  //so we have more control:
  m_Combo.set_cell_data_func(m_cell,
    sigc::mem_fun(*this, &ExampleWindow::on_cell_data_extra));
  m_Combo.pack_start(m_cell);

  //Add the ComboBox to the window.
  set_child(m_Combo);

  //Connect signal handler:
  m_Combo.signal_changed().connect( sigc::mem_fun(*this, &ExampleWindow::on_combo_changed) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_cell_data_extra(const Gtk::TreeModel::const_iterator& iter)
{
  auto row = *iter;
  const Glib::ustring extra = row[m_Columns.m_col_extra];

  //Some arbitrary logic just to show that this is where you can do such things:

  //Transform the value, deciding how to represent it as text:
  if(extra.empty())
    m_cell.property_text() = "(none)";
  else
    m_cell.property_text() = "-" + extra + "-";

  //Change other cell renderer properties too:
  m_cell.property_foreground() = (extra == "yadda" ? "red" : "green");
}

void ExampleWindow::on_combo_changed()
{
  const auto iter = m_Combo.get_active();
  if(iter)
  {
    const auto row = *iter;
    if(row)
    {
      //Get the data for the selected row, using our knowledge of the tree
      //model:
      int id = row[m_Columns.m_col_id];
      Glib::ustring name = row[m_Columns.m_col_name];

      std::cout << " ID=" << id << ", name=" << name << std::endl;
    }
  }
  else
    std::cout << "invalid iter" << std::endl;
}

