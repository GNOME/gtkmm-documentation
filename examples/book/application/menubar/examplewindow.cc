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

#include <iostream>

#include "examplewindow.h"

ExampleWindow::ExampleWindow()
{
  set_title("Gtk::Application example");
  set_default_size(350, 100);

  // Some GTK functions can misbehave if a window does not have a child.
  // An empty Box is acceptable.
  set_child(m_box);

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
  add_action("send-note",
    sigc::mem_fun(*this, &ExampleWindow::on_action_send_notification) );
  add_action("withdraw-note",
    sigc::mem_fun(*this, &ExampleWindow::on_action_withdraw_notification) );

  set_show_menubar(true);
}

void ExampleWindow::on_action_something()
{
  std::cout << G_STRFUNC << std::endl;
}

void ExampleWindow::on_action_close()
{
  std::cout << G_STRFUNC << std::endl;

  set_visible(false);
}

void ExampleWindow::on_action_send_notification()
{
  std::cout << G_STRFUNC << std::endl;

  auto note = Gio::Notification::create("Unimportant message!");
  note->set_body("Notification from " + Glib::get_application_name());
  note->add_button("Print", "app.print", Glib::ustring("Hello, world!"));
  note->add_button("Quit Application", "app.quit");
  get_application()->send_notification("note", note);
}

void ExampleWindow::on_action_withdraw_notification()
{
  std::cout << G_STRFUNC << std::endl;

  get_application()->withdraw_notification("note");
}
