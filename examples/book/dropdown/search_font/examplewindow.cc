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
#include <pangomm/cairofontmap.h>
#include <iostream>
//#include <typeinfo>

ExampleWindow::ExampleWindow()
{
  set_title("Searchable DropDown example");

  // Add the DropDown to the window.
  set_child(m_DropDown);

  // Show a search entry.
  m_DropDown.set_enable_search(true);
  auto expression = Gtk::ClosureExpression<Glib::ustring>::create(
    sigc::mem_fun(*this, &ExampleWindow::get_family_name));
  m_DropDown.set_expression(expression);

  // Pango::FontMap is a Gio::ListModel.
  auto model = Pango::CairoFontMap::get_default();
  m_DropDown.set_model(model);
  m_DropDown.set_selected(0);

  // Connect signal handler.
  m_DropDown.property_selected().signal_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_dropdown_changed));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_dropdown_changed()
{
  const auto selected = m_DropDown.get_selected();
  const auto item = m_DropDown.get_selected_item();
  std::cout << "DropDown changed: Row=" << selected
    << ", Font=" << get_family_name(item) << std::endl;

  // Pango::FontMap is often a list of items of type Pango::FontFamily.
  // From the description of Pango::CairoFontMap: "The actual type of the font map
  // will depend on the particular font technology Cairo was compiled to use."
  // If get_family_name() does not return a family name, you can add
  // #include <typeinfo> and query the type of the items with:
  //   std::cout << typeid(*item.get()).name() << std::endl;
}

Glib::ustring ExampleWindow::get_family_name(const Glib::RefPtr<Glib::ObjectBase>& item)
{
  auto family = std::dynamic_pointer_cast<Pango::FontFamily>(item);
  return family ? family->get_name() : "";
}
