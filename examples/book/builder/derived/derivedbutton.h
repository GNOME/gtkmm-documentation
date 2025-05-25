/* gtkmm example Copyright (C) 2019 gtkmm development team
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

#ifndef GTKMM_EXAMPLE_DERIVED_BUTTON_H
#define GTKMM_EXAMPLE_DERIVED_BUTTON_H

#include <gtkmm.h>

class DerivedButton : public Gtk::Button
{
public:
  DerivedButton();
  DerivedButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& refBuilder);
  virtual ~DerivedButton();

  // Provide proxies for the properties. The proxy allows you to connect to
  // the 'changed' signal, etc.
  Glib::PropertyProxy<Glib::ustring> property_ustring() { return prop_ustring.get_proxy(); }
  Glib::PropertyProxy<int> property_int() { return prop_int.get_proxy(); }

private:
  Glib::Property<Glib::ustring> prop_ustring;
  Glib::Property<int> prop_int;
};

#endif //GTKMM_EXAMPLE_DERIVED_BUTTON_H
