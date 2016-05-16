/* gtkmm example Copyright (C) 2006 gtkmm development team
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
#include "printformoperation.h"

#include <iostream>

#include <pangomm.h>

const Glib::ustring app_title = "gtkmm Printing Example";

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_NameLabel("Name"),
  m_SurnameLabel("Surname"),
  m_CommentsLabel("Comments")
{
  m_refPageSetup = Gtk::PageSetup::create();
  m_refSettings = Gtk::PrintSettings::create();

  m_ContextId = m_Statusbar.get_context_id(app_title);

  set_title(app_title);
  set_default_size(400, 300);

  add(m_VBox);

  build_main_menu();

  m_VBox.pack_start(m_Grid);

  //Arrange the widgets inside the grid:
  m_Grid.set_row_spacing(5);
  m_Grid.set_column_spacing(5);
  m_Grid.attach(m_NameLabel, 0, 0, 1, 1);
  m_Grid.attach(m_NameEntry, 1, 0, 1, 1);

  m_Grid.attach(m_SurnameLabel, 0, 1, 1, 1);
  m_Grid.attach(m_SurnameEntry, 1, 1, 1, 1);

  //Add the TextView, inside a ScrolledWindow:
  m_ScrolledWindow.add(m_TextView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::POLICY_AUTOMATIC, Gtk::POLICY_AUTOMATIC);

  m_Grid.attach(m_CommentsLabel, 0, 2, 1, 1);
  m_Grid.attach(m_ScrolledWindow, 1, 2, 1, 1);
  m_ScrolledWindow.set_hexpand(true);
  m_ScrolledWindow.set_vexpand(true);

  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);

  m_VBox.pack_start(m_Statusbar);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::build_main_menu()
{
  //Create actions for menus and toolbars:
  auto refActionGroup =
   Gio::SimpleActionGroup::create();

  //File menu:
  refActionGroup->add_action("new",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));

  refActionGroup->add_action("pagesetup",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_page_setup));

  refActionGroup->add_action("printpreview",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_print_preview));

  refActionGroup->add_action("print",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_print));

  refActionGroup->add_action("quit",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_quit));

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
    "          <attribute name='label' translatable='yes'>Page _Setup</attribute>"
    "          <attribute name='action'>example.pagesetup</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Print Preview</attribute>"
    "          <attribute name='action'>example.printpreview</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Print</attribute>"
    "          <attribute name='action'>example.print</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
/* TODO:
      "  <toolbar  name='ToolBar'>"
        "    <toolitem action='New'/>"
        "    <toolitem action='Print'/>"
        "      <separator/>"
        "    <toolitem action='Quit'/>"
        "  </toolbar>"
*/
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " << ex.what();
  }


  //Get the menubar and toolbar widgets, and add them to a container widget:
  auto object =
    m_refBuilder->get_object("menu-example");
  auto gmenu =
    Glib::RefPtr<Gio::Menu>::cast_dynamic(object);
  if(!gmenu)
    g_warning("GMenu not found");

  auto pMenubar = new Gtk::MenuBar(gmenu);
  m_VBox.pack_start(*pMenubar, Gtk::PACK_SHRINK);

/* TODO:
  auto pToolbar = m_refBuilder->get_widget("/ToolBar") ;
  if(pToolbar)
    m_VBox.pack_start(*pToolbar, Gtk::PACK_SHRINK);
*/
}

void ExampleWindow::on_printoperation_status_changed(
        const Glib::RefPtr<PrintFormOperation>& operation)
{
  Glib::ustring status_msg;

  if (operation->is_finished())
  {
    status_msg = "Print job completed.";
  }
  else
  {
    //You could also use get_status().
    status_msg = operation->get_status_string();
  }

  m_Statusbar.push(status_msg, m_ContextId);
}

void ExampleWindow::on_printoperation_done(Gtk::PrintOperationResult result,
        const Glib::RefPtr<PrintFormOperation>& operation)
{
  //Printing is "done" when the print data is spooled.

  if (result == Gtk::PRINT_OPERATION_RESULT_ERROR)
  {
    Gtk::MessageDialog err_dialog(*this, "Error printing form", false,
            Gtk::MESSAGE_ERROR, Gtk::BUTTONS_OK, true);
    err_dialog.run();
  }
  else if (result == Gtk::PRINT_OPERATION_RESULT_APPLY)
  {
    //Update PrintSettings with the ones used in this PrintOperation:
    m_refSettings = operation->get_print_settings();
  }

  if (! operation->is_finished())
  {
    //We will connect to the status-changed signal to track status
    //and update a status bar. In addition, you can, for example,
    //keep a list of active print operations, or provide a progress dialog.
    operation->signal_status_changed().connect(sigc::bind(sigc::mem_fun(*this,
                    &ExampleWindow::on_printoperation_status_changed),
                operation));
  }
}

void ExampleWindow::print_or_preview(Gtk::PrintOperationAction print_action)
{
  //Create a new PrintOperation with our PageSetup and PrintSettings:
  //(We use our derived PrintOperation class)
  auto print = PrintFormOperation::create();

  print->set_name(m_NameEntry.get_text() + " " + m_SurnameEntry.get_text());
  print->set_comments(m_refTextBuffer->get_text(false /*Don't include hidden*/));

  print->set_track_print_status();
  print->set_default_page_setup(m_refPageSetup);
  print->set_print_settings(m_refSettings);

  print->signal_done().connect(sigc::bind(sigc::mem_fun(*this,
                  &ExampleWindow::on_printoperation_done), print));
  try
  {
    print->run(print_action /* print or preview */, *this);
  }
  catch (const Gtk::PrintError& ex)
  {
    //See documentation for exact Gtk::PrintError error codes.
    std::cerr << "An error occurred while trying to run a print operation:"
        << ex.what() << std::endl;
  }
}

void ExampleWindow::on_menu_file_new()
{
  //Clear entries and textview:
  m_NameEntry.set_text("");
  m_SurnameEntry.set_text("");
  m_refTextBuffer->set_text("");
  m_TextView.set_buffer(m_refTextBuffer);
}

void ExampleWindow::on_menu_file_page_setup()
{
  //Show the page setup dialog, asking it to start with the existing settings:
  auto new_page_setup =
      Gtk::run_page_setup_dialog(*this, m_refPageSetup, m_refSettings);

  //Save the chosen page setup dialog for use when printing, previewing, or
  //showing the page setup dialog again:
  m_refPageSetup = new_page_setup;
}

void ExampleWindow::on_menu_file_print_preview()
{
  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PREVIEW);
}

void ExampleWindow::on_menu_file_print()
{
  print_or_preview(Gtk::PRINT_OPERATION_ACTION_PRINT_DIALOG);
}

void ExampleWindow::on_menu_file_quit()
{
  hide();
}
