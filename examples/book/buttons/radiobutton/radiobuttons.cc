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
  m_Box_Top(Gtk::Orientation::VERTICAL),
  m_Box1(Gtk::Orientation::VERTICAL, 10),
  m_Box2(Gtk::Orientation::VERTICAL, 10),
  m_RadioButton1("button1"),
  m_RadioButton2("button2"),
  m_RadioButton3("button3"),
  m_Button_Close("close")
{
  // Set title and border of the window
  set_title("radio buttons");

  // Gtk::CheckButton and Gtk::ToggleButton have set_group() methods.
  // They act as radio buttons, if they are included in a group.

  // Put radio buttons 2 and 3 in the same group as 1:
  m_RadioButton2.set_group(m_RadioButton1);
  m_RadioButton3.set_group(m_RadioButton1);

  // Add outer box to the window (because the window
  // can only contain a single widget)
  set_child(m_Box_Top);

  //Put the inner boxes and the separator in the outer box:
  m_Box_Top.append(m_Box1);
  m_Box_Top.append(m_Separator);
  m_Box_Top.append(m_Box2);
  m_Separator.set_expand();

  // Set the inner boxes' margins
  m_Box1.set_margin(10);
  m_Box2.set_margin(10);

  // Put the radio buttons in Box1:
  m_Box1.append(m_RadioButton1);
  m_Box1.append(m_RadioButton2);
  m_Box1.append(m_RadioButton3);
  m_RadioButton1.set_expand();
  m_RadioButton2.set_expand();
  m_RadioButton3.set_expand();

  // Set the second button active
  m_RadioButton2.set_active(true);

  // Put Close button in Box2:
  m_Box2.append(m_Button_Close);
  m_Button_Close.set_expand();

  // Make the button the default widget
  set_default_widget(m_Button_Close);

  // Connect the toggled signal of the button to
  // RadioButtons::on_button_toggled()
  m_Button_Close.signal_clicked().connect(sigc::mem_fun(*this,
              &RadioButtons::on_button_clicked) );
}

RadioButtons::~RadioButtons()
{
}

void RadioButtons::on_button_clicked()
{
  set_visible(false); //to close the application.
}
