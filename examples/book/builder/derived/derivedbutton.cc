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

#include "derivedbutton.h"
#include <iostream>

// For creating a dummy object in main.cc.
DerivedButton::DerivedButton()
: Glib::ObjectBase("MyButton"),
  prop_ustring(*this, "button-ustring"),
  prop_int(*this, "button-int", 10)
{
}

DerivedButton::DerivedButton(BaseObjectType* cobject, const Glib::RefPtr<Gtk::Builder>& /* refBuilder */)
: // To register custom properties, you must register a custom GType.  If
  // you don't know what that means, don't worry, just remember to add
  // this Glib::ObjectBase constructor call to your class' constructor.
  // The GType name will be gtkmm__CustomObject_MyButton.
  Glib::ObjectBase("MyButton"),
  Gtk::Button(cobject),
  // register the properties with the object and give them names
  prop_ustring(*this, "button-ustring"),
  // this one has a default value
  prop_int(*this, "button-int", 10)
{
  // Register some handlers that will be called when the values of the
  // specified parameters are changed.
  property_ustring().signal_changed().connect(
    [](){ std::cout << "- ustring property changed!" << std::endl; }
  );
  property_int().signal_changed().connect(
    [](){ std::cout << "- int property changed!" << std::endl; }
  );
}

DerivedButton::~DerivedButton()
{
}
