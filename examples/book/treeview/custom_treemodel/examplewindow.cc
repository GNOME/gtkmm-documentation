/* gtkmm example Copyright (C) 2020 gtkmm development team
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
: m_VBox(Gtk::Orientation::VERTICAL, 8),
  m_Label("Analysis Sheet"),
  m_Button_Add("Add Node"),
  m_Button_Remove("Remove Node"),
  m_Button_Quit("Quit")
{
  set_title("Gtk::TreeView (custom TreeModel) example");
  set_default_size(650, 400);

  m_VBox.set_margin(8);
  set_child(m_VBox);
  m_VBox.append(m_Label);

  // Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.set_child(m_TreeView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_has_frame(true);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_Button_Add.set_hexpand(true);
  m_Button_Add.set_halign(Gtk::Align::END);
  m_ButtonBox.append(m_Button_Add);
  m_ButtonBox.append(m_Button_Remove);
  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(5);
  m_ButtonBox.set_spacing(5);

  m_Button_Add.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_add));
  m_Button_Remove.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_remove));
  m_Button_Quit.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit));

  // Fill memory.
  fill_memory(2);

  // Create the Tree model:
  m_refTreeModel = MemoryTreeModel::create();
  m_Memory.set_model(m_refTreeModel);

  // TreeView
  m_TreeView.append_column("Integer", m_Columns.col_i);
  m_TreeView.append_column("String", m_Columns.col_s);
  m_TreeView.set_model(m_refTreeModel);

  m_TreeView.get_selection()->set_mode(Gtk::SelectionMode::MULTIPLE);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_add()
{
  m_Memory.emplace_back(m_Memory.size()+1);
  // Expand the appended row.
  m_TreeView.expand_row(Gtk::TreeModel::Path(1, m_Memory.size()-1), true);
}

void ExampleWindow::on_button_remove()
{
  m_Memory.pop_back();
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::fill_memory(int n_top_level_rows)
{
  for (int i = 1; i <= n_top_level_rows; ++i)
    m_Memory.emplace_back(i);
}

void ExampleWindow::on_realize()
{
  m_TreeView.expand_all();

  // Call base class:
  Window::on_realize();
}
