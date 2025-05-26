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

#ifndef GTKMM_EXAMPLE_MYOBJECT_H
#define GTKMM_EXAMPLE_MYOBJECT_H

#include <glibmm.h>

class MyObject : public Glib::Object
{
protected:
  MyObject(int id, const Glib::ustring& label);

public:
  static Glib::RefPtr<MyObject> create(int id, const Glib::ustring& label);

  int get_id() const { return m_id; }
  Glib::PropertyProxy<Glib::ustring> property_label();

  static int compare(const Glib::RefPtr<const MyObject>& a,
    const Glib::RefPtr<const MyObject>& b);

private:
  int m_id;
  Glib::Property<Glib::ustring> m_property_label;
};

#endif //GTKMM_EXAMPLE_MYOBJECT_H
