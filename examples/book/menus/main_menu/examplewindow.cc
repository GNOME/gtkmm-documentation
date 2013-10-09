//$Id: examplewindow.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

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
: m_Box(Gtk::ORIENTATION_VERTICAL)
{
  set_title("main menu example");
  set_default_size(200, 200);

  add(m_Box); // put a MenuBar at the top of the box and other stuff below it.

  //Create actions for menus and toolbars:
  Glib::RefPtr<Gio::SimpleActionGroup> refActionGroup =
    Gio::SimpleActionGroup::create();

  //File|New sub menu:
  refActionGroup->add_action("newstandard",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new_generic));

  refActionGroup->add_action("newfoo",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new_generic));

  refActionGroup->add_action("newgoo",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new_generic));

  //File menu:
  refActionGroup->add_action("quit",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));

  //Edit menu:
  refActionGroup->add_action("copy",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  refActionGroup->add_action("paste",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_others));
  refActionGroup->add_action("something",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_others));


  //Choices menus, to demonstrate Radio items,
  //using our convenience methods for string and int radio values:
  m_refChoice = refActionGroup->add_action_radio_string("choice",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_choices),
    "a");

  m_refChoiceOther = refActionGroup->add_action_radio_integer("choiceother",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_choices_other),
    1);

  m_refToggle = refActionGroup->add_action_bool("sometoggle",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_toggle),
    false);


  //Help menu:
  refActionGroup->add_action("about",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_others) );

  insert_action_group("example", refActionGroup);

  m_refBuilder = Gtk::Builder::create();

  //TODO: add_accel_group(m_refBuilder->get_accel_group());

  //Layout the actions in a menubar and toolbar:
  Glib::ustring ui_info =
    "<interface>"
    "  <menu id='menu-example'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Standard</attribute>"
    "          <attribute name='action'>example.newstandard</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;n</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Foo</attribute>"
    "          <attribute name='action'>example.newfoo</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>New _Goo</attribute>"
    "          <attribute name='action'>example.newgoo</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>example.quit</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;q</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Edit</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Copy</attribute>"
    "          <attribute name='action'>example.copy</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;c</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Paste</attribute>"
    "          <attribute name='action'>example.paste</attribute>"
    "          <attribute name='accel'>&lt;Primary&gt;v</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Something</attribute>"
    "          <attribute name='action'>example.something</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Choices</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice _A</attribute>"
    "          <attribute name='action'>example.choice</attribute>"
    "          <attribute name='target'>a</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice _B</attribute>"
    "          <attribute name='action'>example.choice</attribute>"
    "          <attribute name='target'>b</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Other Choices</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice 1</attribute>"
    "          <attribute name='action'>example.choiceother</attribute>"
    "          <attribute name='target' type='i'>1</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Choice 2</attribute>"
    "          <attribute name='action'>example.choiceother</attribute>"
    "          <attribute name='target' type='i'>2</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Some Toggle</attribute>"
    "          <attribute name='action'>example.sometoggle</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_Help</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_About</attribute>"
    "          <attribute name='action'>example.about</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
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

  //Get the menubar and add it to a container widget:
  Glib::RefPtr<Glib::Object> object =
    m_refBuilder->get_object("menu-example");
  Glib::RefPtr<Gio::Menu> gmenu =
    Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  if(!gmenu)
    g_warning("GMenu not found");

  //Menubar:
  Gtk::MenuBar* pMenubar = Gtk::manage(new Gtk::MenuBar(gmenu));
  m_Box.pack_start(*pMenubar, Gtk::PACK_SHRINK);


  //Create the toolbar and add it to a container widget:
  Gtk::Toolbar* toolbar = Gtk::manage(new Gtk::Toolbar());
  Gtk::ToolButton* button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("document-new");
  //We can't do this until we can break the ToolButton ABI: button->set_detailed_action_name("example.new");
  gtk_actionable_set_detailed_action_name (GTK_ACTIONABLE (button->gobj()), "example.newstandard");
  toolbar->add(*button);

  button = Gtk::manage(new Gtk::ToolButton());
  button->set_icon_name("application-exit");
  //We can't do this until we can break the ToolButton ABI: button->set_detailed_action_name("example.quit");
  gtk_actionable_set_detailed_action_name (GTK_ACTIONABLE (button->gobj()), "example.quit");
  toolbar->add(*button);

  m_Box.pack_start(*toolbar, Gtk::PACK_SHRINK);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_menu_file_quit()
{
  hide(); //Closes the main window to stop the app->run().
}

void ExampleWindow::on_menu_file_new_generic()
{
   std::cout << "A File|New menu item was selected." << std::endl;
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
  if(parameter == "a")
    message = "Choice a was selected.";
  else
    message = "Choice b was selected";

  std::cout << message << std::endl;
}

void ExampleWindow::on_menu_choices_other(int parameter)
{
  //The radio action's state does not change automatically:
  m_refChoiceOther->change_state(parameter);

  Glib::ustring message;
  if(parameter == 1)
    message = "Choice 1 was selected.";
  else
    message = "Choice 2 was selected";

  std::cout << message << std::endl;
}

void ExampleWindow::on_menu_toggle()
{
  bool active = false;
  m_refToggle->get_state(active);

  //The toggle action's state does not change automatically:
  m_refToggle->change_state(!active);
  active = !active;

  Glib::ustring message;
  if(active)
    message = "Toggle is active.";
  else
    message = "Toggle is not active";

  std::cout << message << std::endl;
}
