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

#include "myobject.h"
#include <iostream>

MyObject::MyObject(int id, const Glib::ustring& label)
:
Glib::ObjectBase(typeid(MyObject)), // because MyObject contains Glib::Property<>
m_id(id),
m_property_label(*this, "label", label)
{
}

Glib::RefPtr<MyObject> MyObject::create(int id, const Glib::ustring& label)
{
  return Glib::make_refptr_for_instance(new MyObject(id, label));
}

Glib::PropertyProxy<Glib::ustring> MyObject::property_label()
{
  return m_property_label.get_proxy();
}

int MyObject::compare(const Glib::RefPtr<const MyObject>& a,
  const Glib::RefPtr<const MyObject>& b)
{
  if (!a || !b)
  {
    std::cout << "MyObject::compare(): Empty RefPtr" << std::endl;
    return 0;
  }
  return a->get_id() - b->get_id();
}
