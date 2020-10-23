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
: m_Box(Gtk::Orientation::VERTICAL),
  m_refRecentManager(Gtk::RecentManager::get_default())
{
  set_title("Recent files example");
  set_default_size(300, 150);

  //We can put a PopoverMenuBar at the top of the box and other stuff below it.
  set_child(m_Box);

  //Create actions for menus and toolbars:
  m_refActionGroup = Gio::SimpleActionGroup::create();

  //File menu:
  m_refActionGroup->add_action("new",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));

  //A menu item to open the file chooser dialog:
  m_refActionGroup->add_action("files-dialog",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_files_dialog));

  m_refActionGroup->add_action("quit",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit) );

  insert_action_group("example", m_refActionGroup);


  m_refBuilder = Gtk::Builder::create();

  // When the menubar is a child of a Gtk::Window, keyboard accelerators are not
  // automatically fetched from the Gio::Menu.
  // See the examples/book/menus/main_menu example for an alternative way of
  // adding the menubar when using Gtk::ApplicationWindow.
  app->set_accel_for_action("example.new", "<Primary>n");
  app->set_accel_for_action("example.files-dialog", "<Primary>o");
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
    "        <attribute name='label' translatable='yes'>File Chooser _Dialog</attribute>"
    "        <attribute name='action'>example.files-dialog</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;o</attribute>"
    "      </item>"
    "      <item>"
    "        <attribute name='label' translatable='yes'>_Quit</attribute>"
    "        <attribute name='action'>example.quit</attribute>"
    "        <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "      </item>"
    "    </submenu>"
    "  </menu>"
    "  <object class='GtkBox' id='toolbar'>"
    "    <property name='can_focus'>False</property>"
    "    <child>"
    "      <object class='GtkButton' id='toolbutton_new'>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>New</property>"
    "        <property name='action_name'>example.new</property>"
    "        <property name='icon_name'>document-new</property>"
    "        <property name='hexpand'>False</property>"
    "        <property name='vexpand'>False</property>"
    "      </object>"
    "    </child>"
    "    <child>"
    "      <object class='GtkButton' id='toolbutton_quit'>"
    "        <property name='can_focus'>False</property>"
    "        <property name='tooltip_text' translatable='yes'>Quit</property>"
    "        <property name='action_name'>example.quit</property>"
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
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menubar and toolbar failed: " <<  ex.what();
  }

  //Get the menubar and toolbar widgets, and add them to a container widget:
  auto object = m_refBuilder->get_object("menubar");
  auto gmenu = std::dynamic_pointer_cast<Gio::Menu>(object);
  if (gmenu)
  {
    //Menubar:
    auto pMenubar = Gtk::make_managed<Gtk::PopoverMenuBar>(gmenu);
    m_Box.append(*pMenubar);
  }
  else
    g_warning("GMenu not found");

  auto pToolbar = m_refBuilder->get_widget<Gtk::Box>("toolbar");
  if (pToolbar)
    //Toolbar:
    m_Box.append(*pToolbar);
  else
    g_warning("toolbar not found");
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
  hide(); //Closes the main window to stop the app->make_window_and_run().
}

void ExampleWindow::on_menu_file_files_dialog()
{
  if (!m_pDialog)
  {
    m_pDialog.reset(new Gtk::FileChooserDialog(*this, "Files",
      Gtk::FileChooser::Action::OPEN, /* use_header_bar= */ true));
    m_pDialog->set_transient_for(*this);
    m_pDialog->set_modal(true);
    m_pDialog->signal_response().connect(
      sigc::mem_fun(*this, &ExampleWindow::on_dialog_response));

    m_pDialog->add_button("Select File", Gtk::ResponseType::OK);
    m_pDialog->add_button("_Cancel", Gtk::ResponseType::CANCEL);
  }
  m_pDialog->show();
}

void ExampleWindow::on_dialog_response(int response_id)
{
  m_pDialog->hide();

  if (response_id == Gtk::ResponseType::OK)
  {
    auto selected_uri = m_pDialog->get_file()->get_uri();
    std::cout << "URI selected = " << selected_uri << std::endl;
    std::cout << (m_refRecentManager->has_item(selected_uri) ? "A" : "Not a")
      << " recently used file" << std::endl;
  }
}
