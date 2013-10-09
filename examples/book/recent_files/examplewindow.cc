//$Id: examplewindow.cc 859 2007-06-22 12:28:06Z murrayc $ -*- c++ -*-

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
: m_Box(Gtk::ORIENTATION_VERTICAL),
  m_refRecentManager(Gtk::RecentManager::get_default())
{
  set_title("recent files example");
  set_default_size(200, 200);

  //We can put a MenuBar at the top of the box and other stuff below it.
  add(m_Box);

  //Create actions for menus and toolbars:
  m_refActionGroup = Gio::SimpleActionGroup::create();

  //File menu:
  m_refActionGroup->add_action("new",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));

  //A menu item to open the recent-files dialog:
  m_refActionGroup->add_action("recent-files-dialog",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_recent_files_dialog) );

  m_refActionGroup->add_action("quit",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit) );

  insert_action_group("example", m_refActionGroup);


  m_refBuilder = Gtk::Builder::create();

  //TODO: add_accel_group(m_refBuilder->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  const char* ui_info =
    "<interface>"
    "  <menu id='menubar'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_New</attribute>"
    "        <attribute name='action'>example.new</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>Recent Files _Dialog</attribute>"
    "        <attribute name='action'>example.recent-files-dialog</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;o</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Quit</attribute>"
    "        <attribute name='action'>example.quit</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "      </item>"
    "    </submenu>"
    "  </menu>";

/* TODO: 
        "  <toolbar  name='ToolBar'>"
        "    <toolitem action='FileNew'/>"
        "    <toolitem action='FileQuit'/>"
        "  </toolbar>"
        "</ui>";
*/

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " <<  ex.what();
  }

  //Get the menubar and toolbar widgets, and add them to a container widget:
  Glib::RefPtr<Glib::Object> object =
    m_refBuilder->get_object("menubar");
  Glib::RefPtr<Gio::Menu> gmenu =
    Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  if(!gmenu)
    g_warning("GMenu not found");

  //Menubar:
  Gtk::MenuBar* pMenubar = new Gtk::MenuBar(gmenu);
  m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);

/* TODO:
  Gtk::Widget* pToolbar = m_refBuilder->get_widget("/ToolBar");
  if(pToolbar)
    m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);
*/

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_file_new()
{
  std::cout << " New File" << std::endl;
}

void ExampleWindow::on_menu_file_quit()
{
  hide(); //Closes the main window to stop the app->run().
}

void ExampleWindow::on_menu_file_recent_files_dialog()
{
  Gtk::RecentChooserDialog dialog(*this, "Recent Files", m_refRecentManager);
  dialog.add_button("Select File", Gtk::RESPONSE_OK);
  dialog.add_button("_Cancel", Gtk::RESPONSE_CANCEL);

  const int response = dialog.run();
  dialog.hide();
  if(response == Gtk::RESPONSE_OK)
  {
    std::cout << "URI selected = " << dialog.get_current_uri() << std::endl;
  }
}

