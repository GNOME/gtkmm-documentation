/* gtkmm example Copyright (C) 2002 gtkmm development team
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
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
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
};

#endif /* GTKMM_EXAMPLEWINDOW_H */
