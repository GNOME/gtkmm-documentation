/* gtkmm example Copyright (C) 2023 gtkmm development team
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

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Quit("Quit")
{
  set_title("Gtk::ColumnView (Gtk::TreeListModel) example");
  set_default_size(300, 350);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  // Add the ColumnView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.set_child(m_ColumnView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(5);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_quit));

  // Create the root model:
  auto root = create_model();

  // Set list model and selection model.
  // passthrough must be false when Gtk::TreeExpander is used in the view.
  m_TreeListModel = Gtk::TreeListModel::create(root,
    sigc::mem_fun(*this, &ExampleWindow::create_model),
    /* passthrough */ false, /* autoexpand */ false);
  auto selection_model = Gtk::MultiSelection::create(m_TreeListModel);
  m_ColumnView.set_model(selection_model);
  m_ColumnView.add_css_class("data-table"); // high density table

  // Make the columns reorderable.
  // This is not necessary, but it's nice to show the feature.
  m_ColumnView.set_reorderable(true);

  // Add the ColumnView's columns:

  // Id column
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_id));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_id));
  auto column = Gtk::ColumnViewColumn::create("ID", factory);
  m_ColumnView.append_column(column);

  // Name column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_name));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_name));
  column = Gtk::ColumnViewColumn::create("Name", factory);
  m_ColumnView.append_column(column);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

Glib::RefPtr<Gio::ListModel> ExampleWindow::create_model(
  const Glib::RefPtr<Glib::ObjectBase>& item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(item);
  auto result = Gio::ListStore<ModelColumns>::create();
  if (!col)
  {
    // Top names
    result->append(ModelColumns::create(1, "Billy Bob"));
    result->append(ModelColumns::create(2, "Joey Jojo"));
    result->append(ModelColumns::create(3, "Rob McRoberts"));
  }
  else
  {
    switch (col->m_col_id)
    {
    case 1:
      result->append(ModelColumns::create(11, "Billy Bob Junior"));
      result->append(ModelColumns::create(12, "Sue Bob"));
      break;
    case 3:
      result->append(ModelColumns::create(31, "Xavier McRoberts"));
      break;
    }
  }

  // If result is empty, it's a leaf in the tree, i.e. an item without children.
  // Returning an empty RefPtr (not a RefPtr with an empty Gio::ListModel)
  // signals that the item is not expandable.
  return (result->get_n_items() > 0) ? result : Glib::RefPtr<Gio::ListModel>();
}

void ExampleWindow::on_setup_id(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  // Each ListItem contains a TreeExpander, which contains a Label.
  // The Label shows the ModelColumns::m_col_id. That's done in on_bind_id(). 
  auto expander = Gtk::make_managed<Gtk::TreeExpander>();
  auto label = Gtk::make_managed<Gtk::Label>();
  label->set_halign(Gtk::Align::END);
  expander->set_child(*label);
  list_item->set_child(*expander);
}

void ExampleWindow::on_setup_name(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}

void ExampleWindow::on_bind_id(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  // When TreeListModel::property_passthrough() is false, ListItem::get_item()
  // is a TreeListRow. TreeExpander needs the TreeListRow.
  // The ModelColumns item is returned by TreeListRow::get_item().
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(list_item->get_item());
  if (!row)
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(row->get_item());
  if (!col)
    return;
  auto expander = dynamic_cast<Gtk::TreeExpander*>(list_item->get_child());
  if (!expander)
    return;
  expander->set_list_row(row);
  auto label = dynamic_cast<Gtk::Label*>(expander->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->m_col_id));
}

void ExampleWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto row = std::dynamic_pointer_cast<Gtk::TreeListRow>(list_item->get_item());
  if (!row)
    return;
  auto col = std::dynamic_pointer_cast<ModelColumns>(row->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(col->m_col_name);
}
