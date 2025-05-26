/* gtkmm example Copyright (C) 2011 gtkmm development team
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

#ifndef GTKMM_EVENT_PROPAGATION_H
#define GTKMM_EVENT_PROPAGATION_H

#include <gtkmm.h>

class ExampleWindow : public Gtk::Window
{
public:

  ExampleWindow();
  virtual ~ExampleWindow();

private:
  //Override default signal handler:
  bool on_key_release_event(GdkEventKey* event) override;

  bool entryKeyRelease(GdkEventKey* event);
  bool gridKeyRelease(GdkEventKey* event);
  bool windowKeyReleaseBefore(GdkEventKey* event);
  bool windowKeyRelease(GdkEventKey* event);

  Gtk::Grid m_container;

  Gtk::Label m_label;
  Gtk::Entry m_entry;
  Gtk::CheckButton m_checkbutton_can_propagate;
};

#endif //GTKMM_EVENT_PROPAGATION_H
