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

#include <gtkmm/widget.h>
#include <gtkmm/version.h>

#define HAS_SIGNAL_DESTROY GTKMM_CHECK_VERSION(4,7,1)

class MyContainer : public Gtk::Widget
{
public:
  MyContainer();
  ~MyContainer() override;

  void append(Gtk::Widget& child);
  void prepend(Gtk::Widget& child);
  void remove(Gtk::Widget& child);

protected:
  int get_nvis_children() const;

  //Overrides:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  void measure_vfunc(Gtk::Orientation orientation, int for_size, int& minimum, int& natural,
    int& minimum_baseline, int& natural_baseline) const override;
  void size_allocate_vfunc(int width, int height, int baseline) override;

#if HAS_SIGNAL_DESTROY
  // Signal handler:
  void on_container_destroy();
#endif
};

#endif //GTKMM_CUSTOM_CONTAINER_MYCONTAINER_H
