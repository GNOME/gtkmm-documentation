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
#include <gtkmm/expression.h>
#include <gtkmm/stringobject.h>
#include <iostream>

ExampleWindow::ExampleWindow()
{
  set_title("Searchable DropDown example");

  set_child(m_DropDown);

  // Fill the dropdown:
  const std::vector<Glib::ustring> many_times{
    "1 minute", "2 minutes", "5 minutes", "10 minutes", "15 minutes", "20 minutes",
    "25 minutes", "30 minutes", "35 minutes", "40 minutes", "45 minutes", "50 minutes",
    "55 minutes", "1 hour", "2 hours", "3 hours", "5 hours", "6 hours", "7 hours",
    "8 hours", "9 hours", "10 hours", "11 hours", "12 hours"
  };
  m_StringList = Gtk::StringList::create(many_times);
  m_DropDown.set_model(m_StringList);
  m_DropDown.set_selected(0);

  // Show a search entry.
  m_DropDown.set_enable_search(true);
  auto expression = Gtk::ClosureExpression<Glib::ustring>::create(
    [](const Glib::RefPtr<Glib::ObjectBase>& item)->Glib::ustring
    {
      // An item in a StringList is a StringObject.
      const auto string_object = std::dynamic_pointer_cast<Gtk::StringObject>(item);
      return string_object ? string_object->get_string() : "";
    });
  m_DropDown.set_expression(expression);

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
    << ", String=" << m_StringList->get_string(selected) << std::endl;
}
