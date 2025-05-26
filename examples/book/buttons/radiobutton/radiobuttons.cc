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

#include "radiobuttons.h"


RadioButtons::RadioButtons() :
  m_Box_Top(Gtk::ORIENTATION_VERTICAL),
  m_Box1(Gtk::ORIENTATION_VERTICAL, 10),
  m_Box2(Gtk::ORIENTATION_VERTICAL, 10),
  m_RadioButton1("button1"),
  m_RadioButton2("button2"),
  m_RadioButton3("button3"),
  m_Button_Close("close")
{
  // Set title and border of the window
  set_title("radio buttons");
  set_border_width(0);

  // Put radio buttons 2 and 3 in the same group as 1:
  m_RadioButton2.join_group(m_RadioButton1);
  m_RadioButton3.join_group(m_RadioButton1);

  // Add outer box to the window (because the window
  // can only contain a single widget)
  add(m_Box_Top);

  //Put the inner boxes and the separator in the outer box:
  m_Box_Top.pack_start(m_Box1);
  m_Box_Top.pack_start(m_Separator);
  m_Box_Top.pack_start(m_Box2);

  // Set the inner boxes' borders
  m_Box2.set_border_width(10);
  m_Box1.set_border_width(10);

  // Put the radio buttons in Box1:
  m_Box1.pack_start(m_RadioButton1);
  m_Box1.pack_start(m_RadioButton2);
  m_Box1.pack_start(m_RadioButton3);

  // Set the second button active
  m_RadioButton2.set_active();

  // Put Close button in Box2:
  m_Box2.pack_start(m_Button_Close);

  // Make the button the default widget
  m_Button_Close.set_can_default();
  m_Button_Close.grab_default();

  // Connect the clicked signal of the button to
  // RadioButtons::on_button_clicked()
  m_Button_Close.signal_clicked().connect(sigc::mem_fun(*this,
              &RadioButtons::on_button_clicked) );

  // Show all children of the window
  show_all_children();
}

RadioButtons::~RadioButtons()
{
}

void RadioButtons::on_button_clicked()
{
  hide(); //to close the application.
}
