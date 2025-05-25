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
  m_Button_Quit("_Quit", true)
{
  set_title("Gtk::TreeView (Drag and Drop) example");
  set_default_size(400, 200);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.set_child(m_TreeView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(5);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Create the Tree model:
  //Use our derived model, which overrides some Gtk::TreeDragDest and
  //Gtk::TreeDragSource virtual functions:
  //The columns are declared in the overridden TreeModel.
  m_refTreeModel = TreeModel_Dnd::create();
  m_TreeView.set_model(m_refTreeModel);

  //Enable Drag-and-Drop of TreeView rows:
  //See also the derived TreeModel's *_vfunc overrides.
  m_TreeView.enable_model_drag_source();
  m_TreeView.enable_model_drag_dest();

  //Fill the TreeView's model
  auto row = *(m_refTreeModel->append());
  row[m_refTreeModel->m_Columns.m_col_id] = 1;
  row[m_refTreeModel->m_Columns.m_col_name] = "Billy Bob";
  row[m_refTreeModel->m_Columns.m_col_draggable] = true;
  row[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  auto childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_refTreeModel->m_Columns.m_col_id] = 11;
  childrow[m_refTreeModel->m_Columns.m_col_name] = "Billy Bob Junior";
  childrow[m_refTreeModel->m_Columns.m_col_draggable] = true;
  childrow[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_refTreeModel->m_Columns.m_col_id] = 12;
  childrow[m_refTreeModel->m_Columns.m_col_name] = "Sue Bob";
  childrow[m_refTreeModel->m_Columns.m_col_draggable] = true;
  childrow[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  row = *(m_refTreeModel->append());
  row[m_refTreeModel->m_Columns.m_col_id] = 2;
  row[m_refTreeModel->m_Columns.m_col_name] = "Joey Jojo";
  row[m_refTreeModel->m_Columns.m_col_draggable] = true;
  row[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  row = *(m_refTreeModel->append());
  row[m_refTreeModel->m_Columns.m_col_id] = 3;
  row[m_refTreeModel->m_Columns.m_col_name] = "Rob McRoberts";
  row[m_refTreeModel->m_Columns.m_col_draggable] = true;
  row[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  childrow = *(m_refTreeModel->append(row.children()));
  childrow[m_refTreeModel->m_Columns.m_col_id] = 31;
  childrow[m_refTreeModel->m_Columns.m_col_name] = "Xavier McRoberts";
  childrow[m_refTreeModel->m_Columns.m_col_draggable] = true;
  childrow[m_refTreeModel->m_Columns.m_col_receivesdrags] = true;

  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_refTreeModel->m_Columns.m_col_id);
  m_TreeView.append_column("Name", m_refTreeModel->m_Columns.m_col_name);
  m_TreeView.append_column_editable("Draggable",
          m_refTreeModel->m_Columns.m_col_draggable);
  m_TreeView.append_column_editable("Receives Drags",
          m_refTreeModel->m_Columns.m_col_receivesdrags);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

