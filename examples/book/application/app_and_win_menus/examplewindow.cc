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

#include <iostream>

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
{
  set_title("Gtk::Application example");

  // We can use add_action because Gtk::ApplicationWindow derives from ActionMap.
  // This Action Map uses a "win." prefix for the actions.
  // Therefore, for instance, "win.new", is used in ExampleApplication::on_startup()
  // to layout the menu. 
  add_action("new",
    sigc::mem_fun(*this, &ExampleWindow::on_action_something) );
  add_action("close",
    sigc::mem_fun(*this, &ExampleWindow::on_action_close) );
  add_action("cut",
    sigc::mem_fun(*this, &ExampleWindow::on_action_something) );
  add_action("copy",
    sigc::mem_fun(*this, &ExampleWindow::on_action_something) );
  add_action("paste",
    sigc::mem_fun(*this, &ExampleWindow::on_action_something) );
}

void ExampleWindow::on_action_something()
{
  std::cout << G_STRFUNC << std::endl;
}

void ExampleWindow::on_action_close()
{
  std::cout << G_STRFUNC << std::endl;

  hide();
}
