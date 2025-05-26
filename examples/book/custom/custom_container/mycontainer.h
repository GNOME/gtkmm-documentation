/* gtkmm example Copyright (C) 2004 gtkmm development team
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

#ifndef GTKMM_CUSTOM_CONTAINER_MYCONTAINER_H
#define GTKMM_CUSTOM_CONTAINER_MYCONTAINER_H

#include <gtkmm/container.h>

class MyContainer : public Gtk::Container
{
public:
  MyContainer();
  virtual ~MyContainer();

  void set_child_widgets(Gtk::Widget& child_one, Gtk::Widget& child_two);

protected:

  //Overrides:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  void get_preferred_width_vfunc(int& minimum_width, int& natural_width) const override;
  void get_preferred_height_for_width_vfunc(int width, int& minimum_height, int& natural_height) const override;
  void get_preferred_height_vfunc(int& minimum_height, int& natural_height) const override;
  void get_preferred_width_for_height_vfunc(int height, int& minimum_width, int& natural_width) const override;
  void on_size_allocate(Gtk::Allocation& allocation) override;

  void forall_vfunc(gboolean include_internals, GtkCallback callback, gpointer callback_data) override;

  void on_add(Gtk::Widget* child) override;
  void on_remove(Gtk::Widget* child) override;
  GType child_type_vfunc() const override;

  Gtk::Widget* m_child_one;
  Gtk::Widget* m_child_two;
};

#endif //GTKMM_CUSTOM_CONTAINER_MYCONTAINER_H
