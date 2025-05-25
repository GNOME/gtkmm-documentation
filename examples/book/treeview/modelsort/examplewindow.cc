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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Quit("Quit")
{
  set_title("Gtk::TreeView (TreeModelSort) example");
  set_default_size(400, 400);

  m_VBox.set_margin(6);
  m_VBox.set_spacing(6);
  set_child(m_VBox);

  //Add the TreeViews, inside ScrolledWindows, with the button underneath:
  m_ScrolledWindow1.set_child(m_TreeView1);
  m_ScrolledWindow2.set_child(m_TreeView2);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow1.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow2.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow1.set_expand();
  m_ScrolledWindow2.set_expand();

  m_VBox.append(m_ScrolledWindow1);
  m_VBox.append(m_ScrolledWindow2);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(5);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);

  //Put the TreeModel inside sort models:
  //Note that you can just call set_sort_column() on the normal model if you
  //only want to display one sorted view.
  //This example shows how to use SortModel to show two views of the same model,
  //with different sort columns.
  m_refTreeModelSort1 = Gtk::TreeModelSort::create(m_refTreeModel);
  m_refTreeModelSort1->set_sort_column(m_Columns.m_col_id, Gtk::SortType::ASCENDING);
  m_TreeView1.set_model(m_refTreeModelSort1);

  m_refTreeModelSort2 = Gtk::TreeModelSort::create(m_refTreeModel);
  m_refTreeModelSort2->set_sort_column(m_Columns.m_col_name,
          Gtk::SortType::ASCENDING);
  m_TreeView2.set_model(m_refTreeModelSort2);


  //Fill the tree model
  auto row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Zebede Aardvark";
  row[m_Columns.m_col_something] = true;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  row[m_Columns.m_col_something] = true;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Joey Jojo";
  //This should cause this row to be filtered out (now shown).
  row[m_Columns.m_col_something] = false;

  //Add the TreeViews' view columns:
  m_TreeView1.append_column("ID", m_Columns.m_col_id);
  m_TreeView1.append_column("Name", m_Columns.m_col_name);
  m_TreeView1.append_column_editable("Something", m_Columns.m_col_something);

  m_TreeView2.append_column("ID", m_Columns.m_col_id);
  m_TreeView2.append_column("Name", m_Columns.m_col_name);
  m_TreeView2.append_column_editable("Something", m_Columns.m_col_something);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

