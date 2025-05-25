/* gtkmm example Copyright (C) 2023 gtkmm development team
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
#include "printformdialog.h"
#include <iostream>

ExampleWindow::ExampleWindow(const Glib::RefPtr<Gtk::Application>& app)
: m_VBox(Gtk::Orientation::VERTICAL),
  m_NameLabel("Name"),
  m_SurnameLabel("Surname"),
  m_CommentsLabel("Comments")
{
  set_title("gtkmm PrintDialog Example");
  set_default_size(400, 300);

#if HAS_PRINT_DIALOG
  // Create a PrintDialog. (We use our derived PrintDialog class.)
  m_refPrintFormDialog = PrintFormDialog::create();
#endif // HAS_PRINT_DIALOG

  set_child(m_VBox);

  build_main_menu(app);

  m_VBox.append(m_Grid);

  // Arrange the widgets inside the grid:
  m_Grid.set_expand(true);
  m_Grid.set_row_spacing(5);
  m_Grid.set_column_spacing(5);
  m_Grid.attach(m_NameLabel, 0, 0);
  m_Grid.attach(m_NameEntry, 1, 0);

  m_Grid.attach(m_SurnameLabel, 0, 1);
  m_Grid.attach(m_SurnameEntry, 1, 1);

  // Add the TextView, inside a ScrolledWindow:
  m_ScrolledWindow.set_child(m_TextView);

  // Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);

  m_Grid.attach(m_CommentsLabel, 0, 2);
  m_Grid.attach(m_ScrolledWindow, 1, 2);
  m_ScrolledWindow.set_expand(true);

  m_refTextBuffer = Gtk::TextBuffer::create();
  m_TextView.set_buffer(m_refTextBuffer);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::build_main_menu(const Glib::RefPtr<Gtk::Application>& app)
{
  // Create actions for menus and toolbars:
  auto refActionGroup = Gio::SimpleActionGroup::create();

  // File menu:
  refActionGroup->add_action("new",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_new));

  refActionGroup->add_action("printsetup",
    sigc::mem_fun(*this, &ExampleWindow::on_menu_file_print_setup));

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
    "          <attribute name='label' translatable='yes'>Print _Setup...</attribute>"
    "          <attribute name='action'>example.printsetup</attribute>"
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

void ExampleWindow::on_menu_file_new()
{
  // Clear entries and textview:
  m_NameEntry.set_text("");
  m_SurnameEntry.set_text("");
  m_refTextBuffer->set_text("");
  m_TextView.set_buffer(m_refTextBuffer);
}

void ExampleWindow::on_menu_file_print_setup()
{
#if HAS_PRINT_DIALOG
  m_refPrintFormDialog->do_setup(this);
#else
  std::cout << "Gtk::PrintDialog is not available.\n";
#endif // HAS_PRINT_DIALOG
}

void ExampleWindow::on_menu_file_print()
{
#if HAS_PRINT_DIALOG
  m_refPrintFormDialog->set_name(m_NameEntry.get_text() + " " + m_SurnameEntry.get_text());
  m_refPrintFormDialog->set_comments(m_refTextBuffer->get_text(false /*Don't include hidden*/));
  m_refPrintFormDialog->do_print(this);
#else
  std::cout << "Gtk::PrintDialog is not available.\n";
#endif // HAS_PRINT_DIALOG
}

void ExampleWindow::on_menu_file_quit()
{
  set_visible(false);
}
