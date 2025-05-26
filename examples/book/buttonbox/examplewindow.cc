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
#include "examplebuttonbox.h"

ExampleWindow::ExampleWindow()
: m_VBox_Main(Gtk::ORIENTATION_VERTICAL),
  m_VBox(Gtk::ORIENTATION_VERTICAL),
  m_Frame_Horizontal("Horizontal Button Boxes"),
  m_Frame_Vertical("Vertical Button Boxes")
{
  set_title("Gtk::ButtonBox");
  add(m_VBox_Main);

  m_VBox_Main.pack_start(m_Frame_Horizontal, Gtk::PACK_EXPAND_WIDGET, 10);

  //The horizontal ButtonBoxes:
  m_VBox.set_border_width(10);
  m_Frame_Horizontal.add(m_VBox);

  m_VBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (true, "Spread (spacing 40)", 40, Gtk::BUTTONBOX_SPREAD),
    Gtk::PACK_EXPAND_WIDGET);

  m_VBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (true, "Edge (spacing 30)", 30, Gtk::BUTTONBOX_EDGE),
    Gtk::PACK_EXPAND_WIDGET, 5);

  m_VBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (true, "Start (spacing 20)", 20, Gtk::BUTTONBOX_START),
    Gtk::PACK_EXPAND_WIDGET, 5);

  m_VBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (true, "End (spacing 10)", 10, Gtk::BUTTONBOX_END),
    Gtk::PACK_EXPAND_WIDGET, 5);


  //The vertical ButtonBoxes:
  m_VBox_Main.pack_start(m_Frame_Vertical, Gtk::PACK_EXPAND_WIDGET, 10);

  m_HBox.set_border_width(10);
  m_Frame_Vertical.add(m_HBox);

  m_HBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (false, "Spread (spacing 5)", 5, Gtk::BUTTONBOX_SPREAD),
    Gtk::PACK_EXPAND_WIDGET);

  m_HBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (false, "Edge (spacing 30)", 30, Gtk::BUTTONBOX_EDGE),
    Gtk::PACK_EXPAND_WIDGET, 5);

  m_HBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (false, "Start (spacing 20)", 20, Gtk::BUTTONBOX_START),
    Gtk::PACK_EXPAND_WIDGET, 5);

  m_HBox.pack_start(*Gtk::make_managed<ExampleButtonBox>
    (false, "End (spacing 10)", 10, Gtk::BUTTONBOX_END),
    Gtk::PACK_EXPAND_WIDGET, 5);

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_clicked()
{
  hide();
}
