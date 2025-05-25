/* gtkmm example Copyright (C) 2002-2013 gtkmm development team
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

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_Box(Gtk::Orientation::VERTICAL),
  m_Label("Right-click to see the popup menu.")
{
  set_title("popup example");
  set_default_size(200, 200);

  set_child(m_Box);

  // Catch button_press events:
  m_Box.append(m_Label);
  m_Label.set_expand();
  m_refGesture = Gtk::GestureClick::create();
  m_refGesture->set_button(GDK_BUTTON_SECONDARY);
  m_refGesture->signal_pressed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_label_pressed));
  m_Label.add_controller(m_refGesture);

  //Create actions:
  auto refActionGroup = Gio::SimpleActionGroup::create();

  //File|New sub menu:
  //These menu actions would normally already exist for a main menu, because a
  //context menu should not normally contain menu items that are only available
  //via a context menu.

  refActionGroup->add_action("edit",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_popup_generic));

  refActionGroup->add_action("process",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_popup_generic));

  refActionGroup->add_action("remove",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_popup_generic));

  insert_action_group("examplepopup", refActionGroup);

  // Set accelerator keys:
  app->set_accel_for_action("examplepopup.edit", "<Primary>e");
  app->set_accel_for_action("examplepopup.process", "<Primary>p");
  app->set_accel_for_action("examplepopup.remove", "<Primary>r");

  m_refBuilder = Gtk::Builder::create();

  //Layout the actions in a menubar and toolbar:
  Glib::ustring ui_info =
    "<interface>"
    "  <menu id='menu-examplepopup'>"
    "    <section>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>Edit</attribute>"
    "        <attribute name='action'>examplepopup.edit</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>Process</attribute>"
    "        <attribute name='action'>examplepopup.process</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>Remove</attribute>"
    "        <attribute name='action'>examplepopup.remove</attribute>"
    "      </item>"
    "    </section>"
    "  </menu>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }

  //Get the menu:
  auto gmenu = m_refBuilder->get_object<Gio::Menu>("menu-examplepopup");
  if(!gmenu)
    g_warning("GMenu not found");

  m_MenuPopup.set_parent(m_Label);
  m_MenuPopup.set_menu_model(gmenu);
  m_MenuPopup.set_has_arrow(false);
}

ExampleWindow::~ExampleWindow()
{
  m_MenuPopup.unparent();
}

void ExampleWindow::on_menu_file_popup_generic()
{
   std::cout << "A popup menu item was selected." << std::endl;
}

void ExampleWindow::on_label_pressed(int /* n_press */, double x, double y)
{
  const Gdk::Rectangle rect(x, y, 1, 1);
  m_MenuPopup.set_pointing_to(rect);
  m_MenuPopup.popup();
}
