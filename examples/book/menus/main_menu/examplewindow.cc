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

#include "examplewindow.h"
#include <iostream>

ExampleWindow::ExampleWindow()
: Gtk::ApplicationWindow(),
  m_Box(Gtk::Orientation::VERTICAL)
{
  set_title("Main menu example");
  set_default_size(300, 100);

  // ExampleApplication displays the menubar. Other stuff, such as a toolbar,
  // is put into the box.
  set_child(m_Box);

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

  m_refBuilder = Gtk::Builder::create();

  Glib::ustring ui_info =
    "<!-- Generated with glade 3.18.3 and then changed manually -->"
    "<interface>"
    "  <object class='GtkBox' id='toolbar'>"
    "    <property name='can_focus'>False</property>"
    "    <child>"
    "      <object class='GtkButton' id='toolbutton_new'>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>New Standard</property>"
    "        <property name='action_name'>app.newstandard</property>"
    "        <property name='icon_name'>document-new</property>"
    "        <property name='hexpand'>False</property>"
    "        <property name='vexpand'>False</property>"
    "      </object>"
    "    </child>"
    "    <child>"
    "      <object class='GtkButton' id='toolbutton_quit'>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Quit</property>"
    "        <property name='action_name'>app.quit</property>"
    "        <property name='icon_name'>application-exit</property>"
    "        <property name='hexpand'>False</property>"
    "        <property name='vexpand'>False</property>"
    "      </object>"
    "    </child>"
    "  </object>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch (const Glib::Error& ex)
  {
    std::cerr << "Building toolbar failed: " <<  ex.what();
  }

  auto toolbar = m_refBuilder->get_widget<Gtk::Box>("toolbar");
  if (!toolbar)
    g_warning("toolbar not found");
  else
    m_Box.append(*toolbar);
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
