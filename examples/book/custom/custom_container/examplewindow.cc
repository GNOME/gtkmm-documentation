/* gtkmm example Copyright (C) 2004 gtkmm development team
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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_One("Child One"),
  m_Label_Two("Child 2", Gtk::Align::END, Gtk::Align::CENTER),
  m_Button_Quit("Quit")
{
  set_title("Custom Container example");
  set_default_size(400, 200);

  m_VBox.set_margin(6);
  add(m_VBox);

  //Add the child widgets to the custom container:
  m_MyContainer.set_child_widgets(m_Button_One, m_Label_Two);

  m_VBox.pack_start(m_MyContainer, Gtk::PackOptions::EXPAND_WIDGET);
  m_VBox.pack_start(m_ButtonBox, Gtk::PackOptions::SHRINK);

  m_ButtonBox.pack_start(m_Button_Quit, Gtk::PackOptions::SHRINK);
  m_ButtonBox.set_margin(6);
  m_ButtonBox.set_layout(Gtk::ButtonBoxStyle::END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  hide();
}

