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

#ifndef GTKMM_EXAMPLEWINDOW_H
#define GTKMM_EXAMPLEWINDOW_H

#include <gtkmm/window.h>
#include <gtkmm/comboboxtext.h>
#include <gtkmm/version.h>

#define HAS_SIGNAL_ACTIVATE GTKMM_CHECK_VERSION(4,7,1)

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();
  ~ExampleWindow() override;

protected:
  //Signal handlers:
  void on_combo_changed();
#if HAS_SIGNAL_ACTIVATE
  void on_entry_activate();
#endif
  void on_entry_focus_leave();

  //Signal connection:
  sigc::connection m_ConnectionFocusLeave;

  //Child widgets:
  Gtk::ComboBoxText m_Combo;
};

#endif //GTKMM_EXAMPLEWINDOW_H
