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

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gtk::Application>& app)
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

  // When the menubar is a child of a Gtk::Window, keyboard accelerators are not
  // automatically fetched from the Gio::Menu.
  // See the examples/book/menus/main_menu example for an alternative way of
  // adding the menubar when using Gtk::ApplicationWindow.
  app->set_accel_for_action("example.new", "<Primary>n");
  app->set_accel_for_action("example.recent-files-dialog", "<Primary>o");
  app->set_accel_for_action("example.quit", "<Primary>q");

  //Layout the actions in a menubar and a toolbar:
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
    "  </menu>"
    "  <object class='GtkToolbar' id='toolbar'>"
    "    <property name='visible'>True</property>"
    "    <property name='can_focus'>False</property>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_new'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>New</property>"
    "        <property name='action_name'>example.new</property>"
    "        <property name='icon_name'>document-new</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "    <child>"
    "      <object class='GtkToolButton' id='toolbutton_quit'>"
    "        <property name='visible'>True</property>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Quit</property>"
    "        <property name='action_name'>example.quit</property>"
    "        <property name='icon_name'>application-exit</property>"
    "      </object>"
    "      <packing>"
    "        <property name='expand'>False</property>"
    "        <property name='homogeneous'>True</property>"
    "      </packing>"
    "    </child>"
    "  </object>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menubar and toolbar failed: " <<  ex.what();
  }

  //Get the menubar and toolbar widgets, and add them to a container widget:
  auto object = m_refBuilder->get_object("menubar");
  auto gmenu = Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  if (gmenu)
  {
    //Menubar:
    auto pMenubar = Gtk::manage(new Gtk::MenuBar(gmenu));
    m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);
  }
  else
    g_warning("GMenu not found");

  Gtk::Toolbar* pToolbar = nullptr;
  m_refBuilder->get_widget("toolbar", pToolbar);
  if (pToolbar)
    //Toolbar:
    m_Box.pack_start(*pToolbar, Gtk::PACK_SHRINK);
  else
    g_warning("GtkToolbar not found");
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

