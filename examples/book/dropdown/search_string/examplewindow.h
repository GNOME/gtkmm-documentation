/* gtkmm example Copyright (C) 2023 gtkmm development team
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/dropdown.h>
#include <gtkmm/stringlist.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  // Signal handler:
  void on_dropdown_changed();

  Glib::ustring get_time(const Glib::RefPtr<Glib::ObjectBase>& item);

  // Child widget:
  Gtk::DropDown m_DropDown;
  
  Glib::RefPtr<Gtk::StringList> m_StringList;
};

#endif //GTKMM_EXAMPLEWINDOW_H
