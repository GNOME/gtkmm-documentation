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
: m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Button_Close("Close")
{
  set_title("Gtk::Entry");

  add(m_VBox);

  m_Entry.set_max_length(50);
  m_Entry.set_text("Hello world");
  m_VBox.pack_start(m_Entry, Gtk::PACK_SHRINK);

  m_Entry.set_icon_from_icon_name("edit-find");
  m_Entry.signal_icon_press().connect( sigc::mem_fun(*this, &ExampleWindow::on_icon_pressed) );
 

  m_Button_Close.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );
  m_VBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);
  m_Button_Close.set_can_default();
  m_Button_Close.grab_default();

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_icon_pressed(Gtk::EntryIconPosition /* icon_pos */, const GdkEventButton* /* event */)
{
  std::cout << "Icon pressed." << std::endl;
}

void ExampleWindow::on_button_close()
{
  hide();
}

