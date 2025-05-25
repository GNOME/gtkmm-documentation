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
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Close("_Close", true)
{
  set_title("Gtk::Toolbar example");
  //The toolbar will not demand any size, because it has an overflow menu.
  set_size_request(300, 200);

  set_child(m_VBox);

  //Put a toolbar at the top, and a button underneath:
  m_VBox.append(m_Toolbar);
  m_ButtonBox.set_margin(5);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Close);
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
    m_Toolbar.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    m_Toolbar.append(*Gtk::make_managed<Gtk::Separator>());

    item = Gtk::make_managed<Gtk::Button>("_Save");
    item->set_use_underline();
    item->set_tooltip_text("Save");
    item->set_icon_name("document-save");
    m_Toolbar.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    item = Gtk::make_managed<Gtk::ToggleButton>("Toggle me");
    item->set_tooltip_text("toggle duh");
    m_Toolbar.append(*item);
    item->signal_clicked().connect( sigc::mem_fun(*this,
                &ExampleWindow::on_toolbar_item) );

    auto radio1 = Gtk::make_managed<Gtk::ToggleButton>("Radio 1");
    auto radio2 = Gtk::make_managed<Gtk::ToggleButton>("Radio 2");
    auto radio3 = Gtk::make_managed<Gtk::ToggleButton>("Radio 3");
    m_Toolbar.append(*radio1);
    m_Toolbar.append(*radio2);
    m_Toolbar.append(*radio3);
    radio1->set_active();
    radio2->set_group(*radio1);
    radio3->set_group(*radio1);
  }
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
  set_visible(false);
}

void ExampleWindow::on_toolbar_item()
{
  std::cout << "Toolbar item clicked." << std::endl;
}

