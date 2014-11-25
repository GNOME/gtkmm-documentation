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

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
: Gtk::ApplicationWindow(),
  m_Box(Gtk::ORIENTATION_VERTICAL)
{
  set_title("Main menu example");
  set_default_size(300, 100);

  // ExampleApplication displays the menubar. Other stuff, such as a toolbar,
  // is put into the box.
  add(m_Box);

  // Create actions for menus and toolbars.
  // We can use add_action() because Gtk::ApplicationWindow derives from Gio::ActionMap.
  // This Action Map uses a "win." prefix for the actions.
  // Therefore, for instance, "win.copy", is used in ExampleApplication::on_startup()
  // to layout the menu. 

  //Edit menu:
  add_action("copy", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  add_action("paste", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  add_action("something", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

  //Choices menus, to demonstrate Radio items,
  //using our convenience methods for string and int radio values:
  m_refChoice = add_action_radio_string("choice",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_choices), "a");

  m_refChoiceOther = add_action_radio_integer("choiceother",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_choices_other), 1);

  m_refToggle = add_action_bool("sometoggle",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_toggle), false);

  //Help menu:
  add_action("about", sigc::mem_fun(*this, &ExampleWindow::on_menu_others));

  //Create the toolbar and add it to a container widget:
  Gtk::Toolbar* toolbar = Gtk::manage(new Gtk::Toolbar());
  Gtk::ToolButton* button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("document-new");
  // We can't do this until we can break the ToolButton ABI:
  //   button->set_detailed_action_name("app.newstandard");
  gtk_actionable_set_detailed_action_name(GTK_ACTIONABLE(button->gobj()),
    "app.newstandard");
  toolbar->add(*button);

  button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("application-exit");
  // We can't do this until we can break the ToolButton ABI:
  //   button->set_detailed_action_name("app.quit");
  gtk_actionable_set_detailed_action_name(GTK_ACTIONABLE(button->gobj()),
    "app.quit");
  toolbar->add(*button);

  m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_others()
{
  std::cout << "A menu item was selected." << std::endl;
}

void ExampleWindow::on_menu_choices(const Glib::ustring& parameter)
{
  //The radio action's state does not change automatically:
  m_refChoice->change_state(parameter);

  Glib::ustring message;
  if (parameter == "a")
    message = "Choice a was selected.";
  else
    message = "Choice b was selected.";

  std::cout << message << std::endl;
}

void ExampleWindow::on_menu_choices_other(int parameter)
{
  //The radio action's state does not change automatically:
  m_refChoiceOther->change_state(parameter);

  Glib::ustring message;
  if (parameter == 1)
    message = "Choice 1 was selected.";
  else
    message = "Choice 2 was selected.";

  std::cout << message << std::endl;
}

void ExampleWindow::on_menu_toggle()
{
  bool active = false;
  m_refToggle->get_state(active);

  //The toggle action's state does not change automatically:
  active = !active;
  m_refToggle->change_state(active);

  Glib::ustring message;
  if (active)
    message = "Toggle is active.";
  else
    message = "Toggle is not active.";

  std::cout << message << std::endl;
}
