/* gtkmm example Copyright (C) 2013 gtkmm development team
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

#ifndef GTKMM_EXAMPLEROW_H
#define GTKMM_EXAMPLEROW_H

#include <gtkmm.h>

class ExampleRow : public Gtk::ListBoxRow
{
public:
  ExampleRow(const Glib::ustring& text, int sort_id);

  Glib::ustring get_text() const { return m_label.get_text(); }
  void set_text(const Glib::ustring & text) { m_label.set_text(text); }

  int get_sort_id() const { return m_sort_id; }
  void set_sort_id(int sort_id) { m_sort_id = sort_id; }

private:
  Gtk::Label m_label;
  int m_sort_id;
};

#endif // GTKMM_EXAMPLEROW_H
