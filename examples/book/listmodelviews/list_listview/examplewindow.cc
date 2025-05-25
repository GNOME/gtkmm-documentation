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
  m_Heading("<b>Name</b>", Gtk::Align::START),
  m_Button_Quit("Quit")
{
  set_title("Gtk::ListView (Gtk::StringList) example");
  set_default_size(300, 200);

  m_VBox.set_margin(5);
  set_child(m_VBox);

  // Add the ListView, inside a ScrolledWindow, with the heading above
  // and the button underneath.
  m_Heading.set_use_markup();
  m_VBox.append(m_Heading);
  m_ScrolledWindow.set_child(m_ListView);

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

  // Create the list model:
  m_StringList = Gtk::StringList::create({"Billy Bob", "Joey Jojo", "Rob McRoberts"});

  // Set list model and selection model.
  auto selection_model = Gtk::SingleSelection::create(m_StringList);
  selection_model->set_autoselect(false);
  selection_model->set_can_unselect(true);
  m_ListView.set_model(selection_model);
  m_ListView.add_css_class("data-table"); // high density table

  // Add the factory for the ListView's single column.
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_label));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_name));
  m_ListView.set_factory(factory);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_setup_label(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  list_item->set_child(*Gtk::make_managed<Gtk::Label>("", Gtk::Align::START));
}

void ExampleWindow::on_bind_name(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto pos = list_item->get_position();
  if (pos == GTK_INVALID_LIST_POSITION)
    return;
  auto label = dynamic_cast<Gtk::Label*>(list_item->get_child());
  if (!label)
    return;
  label->set_text(m_StringList->get_string(pos));
}
