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
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Close("_Close", true)
{
  set_title("Gtk::Toolbar example");
  //The toolbar will not demand any size, because it has an overflow menu.
  set_size_request(300, 200);

  add(m_VBox);

  //Put a toolbar at the top, and a button underneath:
  m_VBox.pack_start(m_Toolbar, Gtk::PACK_SHRINK);
  m_ButtonBox.set_border_width(5);
  m_ButtonBox.set_layout(Gtk::BUTTONBOX_END);
  m_VBox.pack_end(m_ButtonBox, Gtk::PACK_SHRINK);

  m_ButtonBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );

  //Add the toolbar items:
  {
    //You would normally use the Builder and Gio::Actions to create the menus and
    //toolbars together, because toolbar items should just be a way to do what
    //is also in a menu.

    m_Toolbar.set_toolbar_style(Gtk::TOOLBAR_BOTH);

    auto item = Gtk::make_managed<Gtk::ToolButton>("Click me");
    //item.set_tooltips(*tooltips, "Toolbar item");
    m_Toolbar.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    m_Toolbar.append(*Gtk::make_managed<Gtk::SeparatorToolItem>());

    item = Gtk::make_managed<Gtk::ToolButton>("_Save");
    item->set_use_underline();
    item->set_icon_name("document-save");
    item->set_homogeneous(false);
    m_Toolbar.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    item = Gtk::make_managed<Gtk::ToggleToolButton>("Toggle me");
    //item.set_tooltips(*tooltips, "toggle duh");
    m_Toolbar.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    Gtk::RadioButtonGroup group;
    m_Toolbar.append(*Gtk::make_managed<Gtk::RadioToolButton>(group, "Radio 1"));
    m_Toolbar.append(*Gtk::make_managed<Gtk::RadioToolButton>(group, "Radio 2"));
    m_Toolbar.append(*Gtk::make_managed<Gtk::RadioToolButton>(group, "Radio 3"));
  }

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
  hide();
}

void ExampleWindow::on_toolbar_item()
{
  std::cout << "Toolbar item clicked." << std::endl;
}

