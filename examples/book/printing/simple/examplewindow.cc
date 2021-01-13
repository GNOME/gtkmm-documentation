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

// This file is part of the printing/simple and printing/advanced examples

#include "examplewindow.h"
#include "printformoperation.h"
#include <iostream>

const Glib::ustring app_title = "gtkmm Printing Example";

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_VBox(Gtk::Orientation::VERTICAL),
  m_NameLabel("Name"),
  m_SurnameLabel("Surname"),
  m_CommentsLabel("Comments")
{
  m_refPageSetup = Gtk::PageSetup::create();
  m_refSettings = Gtk::PrintSettings::create();

  m_ContextId = m_Statusbar.get_context_id(app_title);

  set_title(app_title);
  set_default_size(400, 300);

  set_child(m_VBox);

  build_main_menu(app);

  m_VBox.append(m_Grid);

  //Arrange the widgets inside the grid:
  m_Grid.set_expand(true);
  m_Grid.set_row_spacing(5);
  m_Grid.set_column_spacing(5);
  m_Grid.attach(m_NameLabel, 0, 0);
  m_Grid.attach(m_NameEntry, 1, 0);

  m_Grid.attach(m_SurnameLabel, 0, 1);
  m_Grid.attach(m_SurnameEntry, 1, 1);

  //Add the TextView, inside a ScrolledWindow:
  m_ScrolledWindow.set_child(m_TextView);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);

  m_Grid.attach(m_CommentsLabel, 0, 2);
  m_Grid.attach(m_ScrolledWindow, 1, 2);
  m_ScrolledWindow.set_expand(true);

  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);

  m_Statusbar.set_expand(true);
  m_VBox.append(m_Statusbar);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::build_main_menu(const Glib::RefPtr<Gtk::Application>& app)
{
  //Create actions for menus and toolbars:
  auto refActionGroup = Gio::SimpleActionGroup::create();

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

  // When the menubar is a child of a Gtk::Window, keyboard accelerators are not
  // automatically fetched from the Gio::Menu.
  // See the examples/book/menus/main_menu example for an alternative way of
  // adding the menubar when using Gtk::ApplicationWindow.
  app->set_accel_for_action("example.new", "<Primary>n");
  app->set_accel_for_action("example.print", "<Primary>p");
  app->set_accel_for_action("example.quit", "<Primary>q");

  m_refBuilder = Gtk::Builder::create();

  // Layout the actions in a menubar:
  Glib::ustring ui_menu_info =
    "<interface>"
    "  <menu id='menu-example'>"
    "    <submenu>"
    "      <attribute name='label' translatable='yes'>_File</attribute>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_New</attribute>"
    "          <attribute name='action'>example.new</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Page _Setup...</attribute>"
    "          <attribute name='action'>example.pagesetup</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>Print Preview</attribute>"
    "          <attribute name='action'>example.printpreview</attribute>"
    "        </item>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Print...</attribute>"
    "          <attribute name='action'>example.print</attribute>"
    "        </item>"
    "      </section>"
    "      <section>"
    "        <item>"
    "          <attribute name='label' translatable='yes'>_Quit</attribute>"
    "          <attribute name='action'>example.quit</attribute>"
    "        </item>"
    "      </section>"
    "    </submenu>"
    "  </menu>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_menu_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building menus failed: " << ex.what();
  }

  // Layout the actions in a toolbar:
  Glib::ustring ui_toolbar_info =
    "<!-- Generated with glade 3.18.3 and then changed manually -->"
    "<interface>"
      "<object class='GtkBox' id='toolbar'>"
        "<property name='can_focus'>False</property>"
        "<property name='spacing'>3</property>"
        "<child>"
          "<object class='GtkButton' id='toolbutton_new'>"
            "<property name='can_focus'>False</property>"
            "<property name='tooltip_text' translatable='yes'>New</property>"
            "<property name='action_name'>example.new</property>"
            "<property name='icon_name'>document-new</property>"
            "<property name='hexpand'>False</property>"
            "<property name='vexpand'>False</property>"
          "</object>"
        "</child>"
        "<child>"
          "<object class='GtkButton' id='toolbutton_print'>"
            "<property name='can_focus'>False</property>"
            "<property name='tooltip_text' translatable='yes'>Print</property>"
            "<property name='action_name'>example.print</property>"
            "<property name='icon_name'>document-print</property>"
            "<property name='hexpand'>False</property>"
            "<property name='vexpand'>False</property>"
          "</object>"
        "</child>"
        "<child>"
          "<object class='GtkSeparator' id='separator1'>"
            "<property name='can_focus'>False</property>"
            "<property name='hexpand'>False</property>"
            "<property name='vexpand'>False</property>"
          "</object>"
        "</child>"
        "<child>"
          "<object class='GtkButton' id='toolbutton_quit'>"
            "<property name='can_focus'>False</property>"
            "<property name='tooltip_text' translatable='yes'>Quit</property>"
            "<property name='action_name'>example.quit</property>"
            "<property name='icon_name'>application-exit</property>"
            "<property name='hexpand'>False</property>"
            "<property name='vexpand'>False</property>"
          "</object>"
        "</child>"
      "</object>"
    "</interface>";

  try
  {
    m_refBuilder->add_from_string(ui_toolbar_info);
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "building toolbar failed: " << ex.what();
  }

  // Get the menubar and add it to a container widget:
  auto object = m_refBuilder->get_object("menu-example");
  auto gmenu = std::dynamic_pointer_cast<Gio::Menu>(object);
  if (!gmenu)
    g_warning("GMenu not found");
  else
  {
    auto pMenuBar = Gtk::make_managed<Gtk::PopoverMenuBar>(gmenu);

    // Add the PopoverMenuBar to the window:
    m_VBox.append(*pMenuBar);
  }

  // Get the toolbar and add it to a container widget:
  auto toolbar = m_refBuilder->get_widget<Gtk::Box>("toolbar");
  if (!toolbar)
    g_warning("toolbar not found");
  else
    m_VBox.append(*toolbar);
}

void ExampleWindow::on_printoperation_status_changed()
{
  Glib::ustring status_msg;

  if (m_refPrintFormOperation->is_finished())
  {
    status_msg = "Print job completed.";
  }
  else
  {
    //You could also use get_status().
    status_msg = m_refPrintFormOperation->get_status_string();
  }

  m_Statusbar.push(status_msg, m_ContextId);
}

void ExampleWindow::on_printoperation_done(Gtk::PrintOperation::Result result)
{
  //Printing is "done" when the print data is spooled.

  if (result == Gtk::PrintOperation::Result::ERROR)
  {
    if (!m_pDialog)
    {
      m_pDialog.reset(new Gtk::MessageDialog(*this, "Error printing form",
        false /* use_markup */, Gtk::MessageType::ERROR, Gtk::ButtonsType::OK,
        true /* modal */));
      m_pDialog->set_hide_on_close(true);
      m_pDialog->signal_response().connect(
        sigc::hide(sigc::mem_fun(*m_pDialog, &Gtk::Widget::hide)));
    }
    m_pDialog->show();
  }
  else if (result == Gtk::PrintOperation::Result::APPLY)
  {
    //Update PrintSettings with the ones used in this PrintOperation:
    m_refSettings = m_refPrintFormOperation->get_print_settings();
  }

  if (!m_refPrintFormOperation->is_finished())
  {
    //We will connect to the status-changed signal to track status
    //and update a status bar. In addition, you can, for example,
    //keep a list of active print operations, or provide a progress dialog.
    m_refPrintFormOperation->signal_status_changed().connect(sigc::mem_fun(*this,
                    &ExampleWindow::on_printoperation_status_changed));
  }
}

void ExampleWindow::print_or_preview(Gtk::PrintOperation::Action print_action)
{
  //Create a new PrintOperation with our PageSetup and PrintSettings:
  //(We use our derived PrintOperation class)
  m_refPrintFormOperation = PrintFormOperation::create();

  m_refPrintFormOperation->set_name(m_NameEntry.get_text() + " " + m_SurnameEntry.get_text());
  m_refPrintFormOperation->set_comments(m_refTextBuffer->get_text(false /*Don't include hidden*/));
  // In the printing/advanced example, the font will be set through a custom tab
  // in the print dialog.

  m_refPrintFormOperation->set_track_print_status();
  m_refPrintFormOperation->set_default_page_setup(m_refPageSetup);
  m_refPrintFormOperation->set_print_settings(m_refSettings);

  m_refPrintFormOperation->signal_done().connect(sigc::mem_fun(*this,
                  &ExampleWindow::on_printoperation_done));
  try
  {
    m_refPrintFormOperation->run(print_action /* print or preview */, *this);
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
  print_or_preview(Gtk::PrintOperation::Action::PREVIEW);
}

void ExampleWindow::on_menu_file_print()
{
  print_or_preview(Gtk::PrintOperation::Action::PRINT_DIALOG);
}

void ExampleWindow::on_menu_file_quit()
{
  hide();
}
