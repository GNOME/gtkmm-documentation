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
  set_title("Gtk::TreeView (ListStore) example");
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
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Create and fill the combo models
  //You could also use set_cell_data_func() to choose or fill these later.
  m_refTreeModelCombo1 = Gtk::ListStore::create(m_ColumnsCombo);

  auto row = *(m_refTreeModelCombo1->append());
  row[m_ColumnsCombo.m_col_choice] = "abc";
  row = *(m_refTreeModelCombo1->append());
  row[m_ColumnsCombo.m_col_choice] = "def";

  m_refTreeModelCombo2 = Gtk::ListStore::create(m_ColumnsCombo);

  row = *(m_refTreeModelCombo2->append());
  //The value that can be chosen from the combo, to use in the model.
  row[m_ColumnsCombo.m_col_choice] = "foo";
  //A description, to help the user to choose the value from the combo.
  row[m_ColumnsCombo.m_col_description] = "The Foo item";
  row = *(m_refTreeModelCombo2->append());
  row[m_ColumnsCombo.m_col_choice] = "bar";
  row[m_ColumnsCombo.m_col_description] = "The item known as bar";
  row = *(m_refTreeModelCombo2->append());
  row[m_ColumnsCombo.m_col_choice] = "goo";
  row[m_ColumnsCombo.m_col_description] = "goo, goo, goo, goo";

  //Create the Tree model:
  m_refTreeModel = Gtk::ListStore::create(m_Columns);
  m_TreeView.set_model(m_refTreeModel);

  //Fill the TreeView's model
  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 1;
  row[m_Columns.m_col_name] = "Billy Bob";
  row[m_Columns.m_col_itemchosen] = "click to choose";
  //Choose from this list to set the value in m_col_itemchosen.
  row[m_Columns.m_col_choices] = m_refTreeModelCombo1;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 2;
  row[m_Columns.m_col_name] = "Joey Jojo";
  row[m_Columns.m_col_choices] = m_refTreeModelCombo2;

  row = *(m_refTreeModel->append());
  row[m_Columns.m_col_id] = 3;
  row[m_Columns.m_col_name] = "Rob McRoberts";
  row[m_Columns.m_col_choices] = m_refTreeModelCombo1;

  //Add the TreeView's view columns:
  m_TreeView.append_column("ID", m_Columns.m_col_id);
  m_TreeView.append_column("Name", m_Columns.m_col_name);

  //Create a Combo CellRenderer, instead of the default Text CellRenderer:
  auto pColumn = Gtk::make_managed<Gtk::TreeView::Column>("Item Chosen");
  auto pRenderer = Gtk::make_managed<Gtk::CellRendererCombo>();
  pColumn->pack_start(*pRenderer);
  m_TreeView.append_column(*pColumn);

  //Make this View column represent the m_col_itemchosen model column:
  pColumn->add_attribute(pRenderer->property_text(),
          m_Columns.m_col_itemchosen);

  // Allow the user to choose from this list to set the value in
  // m_col_itemchosen:
  pColumn->add_attribute(pRenderer->property_model(), m_Columns.m_col_choices);

  // Alternatively, you could use just one combo model, in all rows, instead of
  // mapping it to a model column:
  // pRenderer->property_model() = m_refTreeModelCombo1;

  // This must be a text column, in m_refTreeModelCombo1, or
  // m_refTreeModelCombo:
  pRenderer->property_text_column() = 0;

  //Allow the user to edit the column:
  //This is done automatically when we use View::append_column(model_column),
  //but that uses a simple Text CellRenderer.
  pRenderer->property_editable() = true;

  pRenderer->signal_edited().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_cellrenderer_choice_edited) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_cellrenderer_choice_edited(
        const Glib::ustring& path_string, const Glib::ustring& new_text)
{
  Gtk::TreePath path(path_string);

  //Get the row from the path:
  auto iter = m_refTreeModel->get_iter(path);
  if(iter)
  {
      //Store the user's new text in the model:
      auto row = *iter;
      row[m_Columns.m_col_itemchosen] = new_text;
  }
}

