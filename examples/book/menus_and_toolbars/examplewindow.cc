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
#include <gtkmm.h>
#include <iostream>

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_Box(Gtk::Orientation::VERTICAL)
{
  set_title("main_menu example");
  set_default_size(200, 200);

  set_child(m_Box); //We can put a MenuBar at the top of the box and other stuff below it.

  //Define the actions:
  m_refActionGroup = Gio::SimpleActionGroup::create();

  m_refActionGroup->add_action("new",
    sigc::mem_fun(*this, &ExampleWindow::on_action_file_new) );
  m_refActionGroup->add_action("open",
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );

  m_refActionRain = m_refActionGroup->add_action_bool("rain",
    sigc::mem_fun(*this, &ExampleWindow::on_action_toggle), false);

  m_refActionGroup->add_action("quit",
    sigc::mem_fun(*this, &ExampleWindow::on_action_file_quit) );

  m_refActionGroup->add_action("cut",
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );
  m_refActionGroup->add_action("copy",
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );
  m_refActionGroup->add_action("paste",
    sigc::mem_fun(*this, &ExampleWindow::on_action_others) );

  insert_action_group("example", m_refActionGroup);

  //Define how the actions are presented in the menus and toolbars:
  m_refBuilder = Gtk::Builder::create();

  //Layout the actions in a menubar and toolbar:
  const Glib::ustring ui_info =
    "<interface>"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_New</attribute>"
    "          <attribute name='action'>example.new</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Open</attribute>"
    "          <attribute name='action'>example.open</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Rain</attribute>"
    "          <attribute name='action'>example.rain</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>example.quit</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Edit</attribute>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Cut</attribute>"
    "        <attribute name='action'>example.cut</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Copy</attribute>"
    "        <attribute name='action'>example.copy</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Paste</attribute>"
    "        <attribute name='action'>example.paste</attribute>"
    "      </item>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

  // Set accelerator keys:
  app->set_accel_for_action("example.new", "<Primary>n");
  app->set_accel_for_action("example.open", "<Primary>o");
  app->set_accel_for_action("example.quit", "<Primary>q");
  app->set_accel_for_action("example.cut", "<Primary>x");
  app->set_accel_for_action("example.copy", "<Primary>c");
  app->set_accel_for_action("example.paste", "<Primary>v");

  try
  {
    m_refBuilder->add_from_string(ui_info);
    m_refBuilder->add_from_resource("/toolbar/toolbar.glade");
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Building menus and toolbar failed: " <<  ex.what();
  }

  //Get the menubar:
  auto gmenu = m_refBuilder->get_object<Gio::Menu>("menubar");
  if (!gmenu)
    g_warning("GMenu not found");
  else
  {
    auto pMenuBar = Gtk::make_managed<Gtk::PopoverMenuBar>(gmenu);

    //Add the PopoverMenuBar to the window:
    m_Box.append(*pMenuBar);
  }

  //Get the toolbar and add it to a container widget:
  auto toolbar = m_refBuilder->get_widget<Gtk::Box>("toolbar");
  if (!toolbar)
    g_warning("toolbar not found");
  else
    m_Box.append(*toolbar);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_action_file_quit()
{
  hide(); //Closes the main window to stop the app->make_window_and_run().
}

void ExampleWindow::on_action_file_new()
{
   std::cout << "A File|New menu item was selected." << std::endl;
}

void ExampleWindow::on_action_others()
{
  std::cout << "A menu item was selected." << std::endl;
}

void ExampleWindow::on_action_toggle()
{
  std::cout << "The toggle menu item was selected." << std::endl;

  bool active = false;
  m_refActionRain->get_state(active);

  //The toggle action's state does not change automatically:
  active = !active;
  m_refActionRain->change_state(active);

  Glib::ustring message;
  if(active)
    message = "Toggle is active.";
  else
    message = "Toggle is not active";

  std::cout << message << std::endl;
}
