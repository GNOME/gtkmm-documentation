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
  m_Button_NoSort("Don't Sort"),
  m_Button_SortHeadings("Sort Headings"),
  m_Button_SortLength("Sort Length"),
  m_Button_Quit("Quit")
{
  set_title("Gtk::ColumnView (Gtk::SortListModel) example");
  set_default_size(400, 350);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  // Add the ColumnView, inside a ScrolledWindow, with the buttons underneath:
  m_ScrolledWindow.set_child(m_ColumnView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.set_margin(5);
  m_ButtonBox.set_spacing(10);
  m_ButtonBox.append(m_Button_NoSort);
  m_ButtonBox.append(m_Button_SortHeadings);
  m_ButtonBox.append(m_Button_SortLength);
  m_ButtonBox.append(m_Button_Quit);
  m_Button_NoSort.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_nosort));
  m_Button_SortHeadings.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_sortheadings));
  m_Button_SortLength.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_sortlength));
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_quit));

  // Gtk::CheckButton and Gtk::ToggleButton have set_group() methods.
  // They act as radio buttons, if they are included in a group.
  m_Button_SortHeadings.set_group(m_Button_NoSort);
  m_Button_SortLength.set_group(m_Button_NoSort);

  // Create the List model.
  m_ListStore = Gio::ListStore<ModelColumns>::create();
  m_ListStore->append(ModelColumns::create(1, "Billy Bob"));
  m_ListStore->append(ModelColumns::create(11, "Billy Bob Junior"));
  m_ListStore->append(ModelColumns::create(12, "Sue Bob"));
  m_ListStore->append(ModelColumns::create(2, "Joey Jojo"));
  m_ListStore->append(ModelColumns::create(3, "Rob McRoberts"));
  m_ListStore->append(ModelColumns::create(31, "Xavier McRoberts"));

  // Create the sort model.
  auto size_expression = Gtk::ClosureExpression<Glib::ustring::size_type>::create(
    [](const Glib::RefPtr<Glib::ObjectBase>& item)->Glib::ustring::size_type
    {
      const auto col = std::dynamic_pointer_cast<ModelColumns>(item);
      return col ? col->m_col_name.size() : 0;
    });
  m_LengthSorter = Gtk::NumericSorter<Glib::ustring::size_type>::create(size_expression);
  m_LengthSorter->set_sort_order(Gtk::SortType::ASCENDING);
  m_SortListModel = Gtk::SortListModel::create(m_ListStore, m_LengthSorter);

  // Set list model and selection model.
  m_SelectionModel = Gtk::SingleSelection::create(m_ListStore);
  m_SelectionModel->set_autoselect(false);
  m_SelectionModel->set_can_unselect(true);
  m_ColumnView.set_model(m_SelectionModel);
  m_ColumnView.add_css_class("data-table"); // high density table

  // Make the columns reorderable.
  // This is not necessary, but it's nice to show the feature.
  m_ColumnView.set_reorderable(true);

  // Add the ColumnView's columns:

  // Id column
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
    &ExampleWindow::on_setup_label), Gtk::Align::END));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_id));
  m_IdColumn = Gtk::ColumnViewColumn::create("ID", factory);
  m_ColumnView.append_column(m_IdColumn);
  auto uint_expression = Gtk::ClosureExpression<unsigned int>::create(
    [](const Glib::RefPtr<Glib::ObjectBase>& item)->unsigned int
    {
      const auto col = std::dynamic_pointer_cast<ModelColumns>(item);
      return col ? col->m_col_id : 0;
    });
  m_IdSorter = Gtk::NumericSorter<unsigned int>::create(uint_expression);

  // Name column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
    &ExampleWindow::on_setup_label), Gtk::Align::START));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_name));
  m_NameColumn = Gtk::ColumnViewColumn::create("Name", factory);
  m_ColumnView.append_column(m_NameColumn);
  auto ustring_expression = Gtk::ClosureExpression<Glib::ustring>::create(
    [](const Glib::RefPtr<Glib::ObjectBase>& item)->Glib::ustring
    {
      const auto col = std::dynamic_pointer_cast<ModelColumns>(item);
      return col ? col->m_col_name : "";
    });
  m_NameSorter = Gtk::StringSorter::create(ustring_expression);

  // Show the list model without sorting.
  m_Button_NoSort.set_active(true);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_nosort()
{
  if (m_Button_NoSort.get_active())
  {
    m_SelectionModel->set_model(m_ListStore);
    m_IdColumn->set_sorter({});
    m_NameColumn->set_sorter({});
  }
}

void ExampleWindow::on_button_sortheadings()
{
  if (m_Button_SortHeadings.get_active())
  {
    m_SortListModel->set_sorter(m_ColumnView.get_sorter());
    m_SelectionModel->set_model(m_SortListModel);
    m_IdColumn->set_sorter(m_IdSorter);
    m_NameColumn->set_sorter(m_NameSorter);
  }
}

void ExampleWindow::on_button_sortlength()
{
  if (m_Button_SortLength.get_active())
  {
    m_SortListModel->set_sorter(m_LengthSorter);
    m_SelectionModel->set_model(m_SortListModel);
    m_IdColumn->set_sorter({});
    m_NameColumn->set_sorter({});
  }
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_setup_label(
  const Glib::RefPtr<Gtk::ListItem>& list_item, Gtk::Align halign)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", halign));
}

void ExampleWindow::on_bind_id(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(Glib::ustring::format(col->m_col_id));
}

void ExampleWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(col->m_col_name);
}
