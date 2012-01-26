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
: m_VBox(Gtk::ORIENTATION_VERTICAL, 5),
  m_Alignment(0.5, 0.5, 0, 0),
  m_CheckButton_Text("Show text"),
  m_CheckButton_Activity("Activity mode"),
  m_CheckButton_Inverted("Right to Left"),
  m_Button_Close("Close"),
  m_bActivityMode(false)
{
  set_resizable();
  set_title("Gtk::ProgressBar");

  m_VBox.set_border_width(10);
  add(m_VBox);

  m_VBox.pack_start(m_Alignment, Gtk::PACK_SHRINK, 5);
  m_Alignment.add(m_ProgressBar);
  m_ProgressBar.set_text("some text");
  m_ProgressBar.set_show_text(false);

  //Add a timer callback to update the value of the progress bar:
  m_connection_id_timeout = Glib::signal_timeout().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_timeout), 50 );

  m_VBox.pack_start(m_Separator, Gtk::PACK_SHRINK);
  m_VBox.pack_start(m_Grid);
  m_Grid.set_row_homogeneous(true);

  //Add a check button to select displaying of the trough text:
  m_Grid.attach(m_CheckButton_Text, 0, 0, 1, 1);
  m_CheckButton_Text.property_margin() = 5;
  m_CheckButton_Text.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_checkbutton_text) );

  //Add a check button to toggle activity mode:
  m_Grid.attach(m_CheckButton_Activity, 0, 1, 1, 1);
  m_CheckButton_Activity.property_margin() = 5;
  m_CheckButton_Activity.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_checkbutton_activity) );

  //Add a check button to select growth from left to right or from right to left:
  m_Grid.attach(m_CheckButton_Inverted, 0, 2, 1, 1);
  m_CheckButton_Inverted.property_margin() = 5;
  m_CheckButton_Inverted.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_checkbutton_inverted) );

  //Add a button to exit the program.
  m_VBox.pack_start(m_Button_Close, Gtk::PACK_SHRINK);
  m_Button_Close.signal_clicked().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_close) );
  m_Button_Close.set_can_default();
  m_Button_Close.grab_default();

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_checkbutton_text()
{
  const bool show_text = m_CheckButton_Text.get_active();
  m_ProgressBar.set_show_text(show_text);
}

void ExampleWindow::on_checkbutton_activity()
{
  m_bActivityMode = m_CheckButton_Activity.get_active();

  if(m_bActivityMode)
    m_ProgressBar.pulse();
  else
    m_ProgressBar.set_fraction(0.0);
}

void ExampleWindow::on_checkbutton_inverted()
{
  const bool inverted = m_CheckButton_Inverted.get_active();
  m_ProgressBar.set_inverted(inverted);
}

void ExampleWindow::on_button_close()
{
  hide();
}

/* Update the value of the progress bar so that we get
 * some movement */
bool ExampleWindow::on_timeout()
{
  if(m_bActivityMode)
    m_ProgressBar.pulse();
  else
  {
    double new_val = m_ProgressBar.get_fraction() + 0.01;

    if(new_val > 1.0)
      new_val = 0.0;

    //Set the new value:
    m_ProgressBar.set_fraction(new_val);
  }

  //As this is a timeout function, return true so that it
  //continues to get called
  return true;
}
