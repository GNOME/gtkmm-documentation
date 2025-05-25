/* gtkmm example Copyright (C) 2016 gtkmm development team
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
#include <ctime>
#include <cstdlib> // std::rand()
#include <algorithm> // std::max()

ExampleWindow::ExampleWindow()
:
m_store(Gio::ListStore<MyObject>::create()),
m_button_add_some("_Add some", true),
m_button_remove_some("_Remove some", true),
m_button_quit("_Quit", true)
{
  set_title("ListBox and FlowBox with ListModel");
  set_default_size(300, 300);

  for (int i = 0; i < 20; ++i)
  {
    const auto label = Glib::ustring::format("Item ", i);
    m_store->append(MyObject::create(i, label));
  }

  // Use current time as seed for random number generator.
  std::srand(std::time(nullptr));

  m_grid.set_margin(5);
  set_child(m_grid);

  // Select bind_model() or bind_list_store() randomly.
  const bool use_bind_model = std::rand() & 2;
  std::cout << "Using bind_" << (use_bind_model ? "model" : "list_store") << std::endl;

  // A ListBox to the left.
  m_scrolled_window_list_box.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_scrolled_window_list_box.set_hexpand(true);
  m_scrolled_window_list_box.set_vexpand(true);
  m_grid.attach(m_scrolled_window_list_box, 0, 0, 1 ,1);
  m_scrolled_window_list_box.set_child(m_list_box);
  if (use_bind_model)
    m_list_box.bind_model(m_store,
      [](const auto& item)
      { return on_create_widget1(item); }
    );
  else
    m_list_box.bind_list_store(m_store,
      [](const auto& item)
      { return on_create_widget2(item); }
    );

  // A FlowBox to the right.
  m_scrolled_window_flow_box.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_scrolled_window_flow_box.set_hexpand(true);
  m_scrolled_window_flow_box.set_vexpand(true);
  m_grid.attach(m_scrolled_window_flow_box, 1, 0, 1 ,1);
  m_scrolled_window_flow_box.set_child(m_flow_box);
  if (use_bind_model)
    m_flow_box.bind_model(m_store,
      [](const auto& item)
      { return on_create_widget1(item); }
    );
  else
    m_flow_box.bind_list_store(m_store,
      [](const auto& item)
      { return on_create_widget2(item); }
    );

  // Buttons at the bottom.
  m_button_add_some.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_add_some));
  m_grid.attach(m_button_add_some, 0, 1, 2, 1);
  m_button_remove_some.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_remove_some));
  m_grid.attach(m_button_remove_some, 0, 2, 2, 1);
  m_button_quit.signal_clicked().connect(sigc::mem_fun(*this, &ExampleWindow::on_quit));
  m_grid.attach(m_button_quit, 0, 3, 2, 1);
}

// static
Gtk::Widget* ExampleWindow::on_create_widget1(const Glib::RefPtr<Glib::Object>& item)
{
  auto obj = std::dynamic_pointer_cast<MyObject>(item);
  if (!obj)
  {
    std::cout << "on_create_widget1(): item is not a MyObject" << std::endl;
    return nullptr;
  }
  auto label = Gtk::make_managed<Gtk::Label>();
  Glib::Binding::bind_property(obj->property_label(), label->property_label(),
    Glib::Binding::Flags::SYNC_CREATE);
  return label;
}

// static
Gtk::Widget* ExampleWindow::on_create_widget2(const Glib::RefPtr<MyObject>& item)
{
  if (!item)
  {
    std::cout << "on_create_widget2(): item is empty" << std::endl;
    return nullptr;
  }
  auto label = Gtk::make_managed<Gtk::Label>();
  Glib::Binding::bind_property(item->property_label(), label->property_label(),
    Glib::Binding::Flags::SYNC_CREATE);
  return label;
}

void ExampleWindow::on_add_some()
{
  for (int n = 0; n < 10; ++n)
  {
    const auto n_items = m_store->get_n_items();
    const auto i = std::rand() % std::max(2*n_items, 4u);
    const auto label = Glib::ustring::format("Added ", i);
    m_store->insert_sorted(MyObject::create(i, label),
      [](const auto& a, const auto& b)
      { return MyObject::compare(a, b); }
    );
  }
}

void ExampleWindow::on_remove_some()
{
  for (int n = 0; n < 10; ++n)
  {
    const auto n_items = m_store->get_n_items();
    if (n_items == 0)
      return;
    const auto i = std::rand() % n_items;
    m_store->remove(i);
  }
}

void ExampleWindow::on_quit()
{
  set_visible(false);
}
