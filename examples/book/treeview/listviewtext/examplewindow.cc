/* gtkmm example Copyright (C) 2006 gtkmm development team
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

#include <iostream>
#include "examplewindow.h"

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_ListViewText(3),
  m_Button_Quit("Quit")
{
  set_title("Gtk::ListViewText example");
  set_default_size(400, 200);

  m_VBox.set_margin(6);
  set_child(m_VBox);

  //Add the TreeView, inside a ScrolledWindow, with the button underneath:
  m_ScrolledWindow.set_child(m_ListViewText);

  //Only show the scrollbars when they are necessary:
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(5);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  //Fill the ListViewText:
  m_ListViewText.set_column_title(0, "City");
  // Obviously, you would want to use a real Gtk::TreeView to store a numeric
  // (non-text) value.
  m_ListViewText.set_column_title(1, "Temperature (celsius)");
  m_ListViewText.set_column_title(2, "Forecast");

  guint row_number = m_ListViewText.append();
  m_ListViewText.set_text(row_number, 0, "Madrid");
  m_ListViewText.set_text(row_number, 1, "30");   // degrees for Madrid
  m_ListViewText.set_text(row_number, 2, "cloudy"); // forecast for Madrid

  row_number = m_ListViewText.append();
  m_ListViewText.set_text(row_number,  0, "Lisbon");
  m_ListViewText.set_text(row_number, 1, "25");   // degrees for Lisbon
  m_ListViewText.set_text(row_number, 2, "rainy");  // forecast for Lisbon
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}
