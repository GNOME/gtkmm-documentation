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
  explicit ExampleWindow();

private:
  void on_action_something();
  void on_action_close();
  void on_action_send_notification();
  void on_action_withdraw_notification();

  Gtk::Box m_box;
};

#endif /* GTKMM_EXAMPLEWINDOW_H */
