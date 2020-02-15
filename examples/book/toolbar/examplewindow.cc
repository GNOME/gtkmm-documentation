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
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Close("_Close", true)
{
  set_title("Gtk::Toolbar example");
  //The toolbar will not demand any size, because it has an overflow menu.
  set_size_request(300, 200);

  add(m_VBox);

  //Put a toolbar at the top, and a button underneath:
  m_VBox.add(m_Toolbar);
  m_ButtonBox.set_margin(5);
  m_VBox.add(m_ButtonBox);

  m_ButtonBox.add(m_Button_Close);
  m_Button_Close.set_expand(true);
  m_Button_Close.set_halign(Gtk::Align::END);
  m_Button_Close.set_valign(Gtk::Align::END);

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );

  //Add the toolbar items:
  {
    //You would normally use the Builder and Gio::Actions to create the menus and
    //toolbars together, because toolbar items should just be a way to do what
    //is also in a menu.

    auto item = Gtk::make_managed<Gtk::Button>("Click me");
    item->set_tooltip_text("Toolbar item");
    m_Toolbar.add(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    m_Toolbar.add(*Gtk::make_managed<Gtk::Separator>());

    item = Gtk::make_managed<Gtk::Button>("_Save");
    item->set_use_underline();
    item->set_tooltip_text("Save");
    item->set_icon_name("document-save");
    m_Toolbar.add(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    item = Gtk::make_managed<Gtk::ToggleButton>("Toggle me");
    item->set_tooltip_text("toggle duh");
    m_Toolbar.add(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    Gtk::RadioButtonGroup group;
    m_Toolbar.add(*Gtk::make_managed<Gtk::RadioButton>(group, "Radio 1"));
    m_Toolbar.add(*Gtk::make_managed<Gtk::RadioButton>(group, "Radio 2"));
    m_Toolbar.add(*Gtk::make_managed<Gtk::RadioButton>(group, "Radio 3"));
  }
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

