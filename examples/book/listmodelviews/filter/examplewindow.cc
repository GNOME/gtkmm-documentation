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
  m_Button_ShowAll("Show All"),
  m_Button_ShowJ("Show J"),
  m_Button_ShowM("Show M"),
  m_Button_Quit("Quit")
{
  set_title("Gtk::ColumnView (Gtk::FilterListModel) example");
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
  m_ButtonBox.append(m_Button_ShowAll);
  m_ButtonBox.append(m_Button_ShowJ);
  m_ButtonBox.append(m_Button_ShowM);
  m_ButtonBox.append(m_Button_Quit);
  m_Button_ShowAll.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_showall));
  m_Button_ShowJ.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_showj));
  m_Button_ShowM.signal_toggled().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_showm));
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_quit));

  // Gtk::CheckButton and Gtk::ToggleButton have set_group() methods.
  // They act as radio buttons, if they are included in a group.
  m_Button_ShowJ.set_group(m_Button_ShowAll);
  m_Button_ShowM.set_group(m_Button_ShowAll);

  // Create the List model.
  m_ListStore = Gio::ListStore<ModelColumns>::create();
  m_ListStore->append(ModelColumns::create(1, "Billy Bob"));
  m_ListStore->append(ModelColumns::create(11, "Billy Bob Junior"));
  m_ListStore->append(ModelColumns::create(12, "Sue Bob"));
  m_ListStore->append(ModelColumns::create(2, "Joey Jojo"));
  m_ListStore->append(ModelColumns::create(3, "Rob McRoberts"));
  m_ListStore->append(ModelColumns::create(31, "Xavier McRoberts"));

  // Create the filter model.
  auto expression = Gtk::ClosureExpression<Glib::ustring>::create(
    [](const Glib::RefPtr<Glib::ObjectBase>& item)->Glib::ustring
    {
      const auto col = std::dynamic_pointer_cast<ModelColumns>(item);
      return col ? col->m_col_name : "";
    });
  m_StringFilter = Gtk::StringFilter::create(expression);
  m_StringFilter->set_ignore_case(false);
  m_StringFilter->set_match_mode(Gtk::StringFilter::MatchMode::SUBSTRING);
  m_FilterListModel = Gtk::FilterListModel::create(m_ListStore, m_StringFilter);

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
  auto column = Gtk::ColumnViewColumn::create("ID", factory);
  m_ColumnView.append_column(column);

  // Name column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
    &ExampleWindow::on_setup_label), Gtk::Align::START));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_name));
  column = Gtk::ColumnViewColumn::create("Name", factory);
  m_ColumnView.append_column(column);

  // Show the list model without filtering.
  m_Button_ShowAll.set_active(true);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_showall()
{
  if (m_Button_ShowAll.get_active())
    m_SelectionModel->set_model(m_ListStore);
}

void ExampleWindow::on_button_showj()
{
  if (m_Button_ShowJ.get_active())
  {
   m_StringFilter->set_search("J");
    m_SelectionModel->set_model(m_FilterListModel);
  }
}

void ExampleWindow::on_button_showm()
{
  if (m_Button_ShowM.get_active())
  {
   m_StringFilter->set_search("M");
    m_SelectionModel->set_model(m_FilterListModel);
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
