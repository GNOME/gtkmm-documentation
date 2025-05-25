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
  set_title("Gtk::ColumnView (Gio::ListStore) example");
  set_default_size(500, 250);

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

  // Create the List model:
  m_ListStore = Gio::ListStore<ModelColumns>::create();
  m_ListStore->append(ModelColumns::create(1, "Billy Bob", 10, 15));
  m_ListStore->append(ModelColumns::create(2, "Joey Jojo", 20, 40));
  m_ListStore->append(ModelColumns::create(3, "Rob McRoberts", 30, 70));

  // Set list model and selection model.
  auto selection_model = Gtk::SingleSelection::create(m_ListStore);
  selection_model->set_autoselect(false);
  selection_model->set_can_unselect(true);
  m_ColumnView.set_model(selection_model);
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

  // Number column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(sigc::bind(sigc::mem_fun(*this,
    &ExampleWindow::on_setup_label), Gtk::Align::END));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_number));
  column = Gtk::ColumnViewColumn::create("Formatted number", factory);
  m_ColumnView.append_column(column);

  // Percentage column
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_progressbar));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_percentage));
  column = Gtk::ColumnViewColumn::create("Some percentage", factory);
  m_ColumnView.append_column(column);
}

ExampleWindow::~ExampleWindow()
{
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

void ExampleWindow::on_setup_progressbar(
  const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto progressbar = Gtk::make_managed<Gtk::ProgressBar>();
  progressbar->set_show_text(true);
  list_item->set_child(*progressbar);
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

void ExampleWindow::on_bind_number(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  // 10 digits, using leading zeroes.
  label->set_text(Glib::ustring::sprintf("%010d", col->m_col_number));
}

void ExampleWindow::on_bind_percentage(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto progressbar = dynamic_cast<Gtk::ProgressBar*>(list_item->get_child());
  if (!progressbar)
    return;
  progressbar->set_fraction(col->m_col_percentage * 0.01);
}
