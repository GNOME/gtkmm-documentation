/* gtkmm example Copyright (C) 2002 gtkmm development team
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

#ifndef GTKMM_EXAMPLEWINDOW_H_
#define GTKMM_EXAMPLEWINDOW_H_

#include <gtkmm.h>

class ExampleWindow: public Gtk::ApplicationWindow
{
public:

  //We do not take the file as a constructor parameter,
  //so we can separate window creation and hiding of the window
  //when loading fails.
  explicit ExampleWindow();

  bool load_file(const Glib::RefPtr<Gio::File>& file);

private:
  Gtk::ScrolledWindow m_scrolledwindow;
  Gtk::TextView m_view;
};

#endif /* GTKMM_EXAMPLEWINDOW_H */
