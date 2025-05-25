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
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("DropDown example");

  // Add the DropDown to the window.
  set_child(m_DropDown);

  // Factory for presenting the selected item.
  auto factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_selected_item));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_selected_item));
  m_DropDown.set_factory(factory);

  // Factory for presenting the items in the dropdown list.
  factory = Gtk::SignalListItemFactory::create();
  factory->signal_setup().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_setup_list_item));
  factory->signal_bind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_bind_list_item));
  factory->signal_unbind().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_unbind_list_item));
  m_DropDown.set_list_factory(factory);

  // Create the model and fill it.
  create_model();
  m_DropDown.set_model(m_ListStore);
  m_DropDown.set_selected(0);

  // Connect signal handler:
  m_DropDown.property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_dropdown_changed));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_dropdown_changed()
{
  const auto selected = m_DropDown.get_selected();
  std::cout << "DropDown changed: Row=" << selected
    << ", Title=" << m_ListStore->get_item(selected)->m_title << std::endl;
}

void ExampleWindow::create_model()
{
  m_ListStore = Gio::ListStore<ModelColumns>::create();

  liststore_add_item("Digital Output", "audio-card-symbolic", "Built-in Audio");
  liststore_add_item("Headphones", "audio-headphones-symbolic", "Built-in Audio");
  liststore_add_item("Digital Output", "audio-card-symbolic", "Thinkpad Tunderbolt 3 Dock USB Audio");
  liststore_add_item("Analog Output", "audio-card-symbolic", "Thinkpad Tunderbolt 3 Dock USB Audio");
}

void ExampleWindow::liststore_add_item(const Glib::ustring& title,
  const Glib::ustring& icon, const Glib::ustring& description)
{
  m_ListStore->append(ModelColumns::create(title, icon, description));
}

void ExampleWindow::on_setup_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto box = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  box->append(*Gtk::make_managed<Gtk::Image>());
  box->append(*Gtk::make_managed<Gtk::Label>());
  list_item->set_child(*box);
}

void ExampleWindow::on_bind_selected_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto box = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!box)
    return;
  auto image = dynamic_cast<Gtk::Image*>(box->get_first_child());
  if (!image)
    return;
  image->set_from_icon_name(col->m_icon);
  auto label = dynamic_cast<Gtk::Label*>(image->get_next_sibling());
  if (!label)
    return;
  label->set_text(col->m_title);
}

void ExampleWindow::on_setup_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto hbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::HORIZONTAL, 10);
  auto vbox = Gtk::make_managed<Gtk::Box>(Gtk::Orientation::VERTICAL, 2);

  hbox->append(*Gtk::make_managed<Gtk::Image>());
  hbox->append(*vbox);
  auto title = Gtk::make_managed<Gtk::Label>();
  title->set_xalign(0.0);
  vbox->append(*title);
  auto description = Gtk::make_managed<Gtk::Label>();
  description->set_xalign(0.0);
  description->add_css_class("dim-label");
  vbox->append(*description);
  auto checkmark = Gtk::make_managed<Gtk::Image>();
  checkmark->set_from_icon_name("object-select-symbolic");
  checkmark->set_visible(false);
  hbox->append(*checkmark);

  list_item->set_child(*hbox);
}

void ExampleWindow::on_bind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto col = std::dynamic_pointer_cast<ModelColumns>(list_item->get_item());
  if (!col)
    return;
  auto hbox = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!hbox)
    return;
  auto image = dynamic_cast<Gtk::Image*>(hbox->get_first_child());
  if (!image)
    return;
  image->set_from_icon_name(col->m_icon);
  auto vbox = dynamic_cast<Gtk::Box*>(image->get_next_sibling());
  if (!vbox)
    return;
  auto title = dynamic_cast<Gtk::Label*>(vbox->get_first_child());
  if (!title)
    return;
  title->set_text(col->m_title);
  auto description = dynamic_cast<Gtk::Label*>(title->get_next_sibling());
  if (!description)
    return;
  description->set_text(col->m_description);

  auto connection = m_DropDown.property_selected_item().signal_changed().connect(
    sigc::bind(sigc::mem_fun(*this, &ExampleWindow::on_selected_item_changed),
    list_item));
  list_item->set_data("connection", new sigc::connection(connection),
    Glib::destroy_notify_delete<sigc::connection>);
  on_selected_item_changed(list_item);
}

void ExampleWindow::on_unbind_list_item(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  if (auto connection = static_cast<sigc::connection*>(list_item->get_data("connection")))
  {
    connection->disconnect();
    list_item->set_data("connection", nullptr);
  }
}

void ExampleWindow::on_selected_item_changed(const Glib::RefPtr<Gtk::ListItem>& list_item)
{
  auto hbox = dynamic_cast<Gtk::Box*>(list_item->get_child());
  if (!hbox)
    return;
  auto checkmark = dynamic_cast<Gtk::Image*>(hbox->get_last_child());
  if (!checkmark)
    return;
  checkmark->set_visible(m_DropDown.get_selected_item() == list_item->get_item());
}
