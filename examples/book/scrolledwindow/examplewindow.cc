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
: m_VBox(Gtk::Orientation::VERTICAL, 10),
  m_ButtonClose("_Close", true)
{
  set_title("Gtk::ScrolledWindow example");
  set_size_request(300, 300);

  set_child(m_VBox);
  m_VBox.set_margin(10);

  /* The policy is one of Gtk::PolicyType::AUTOMATIC, or Gtk::PolicyType::ALWAYS.
   * Gtk::PolicyType::AUTOMATIC will automatically decide whether you need
   * scrollbars, whereas Gtk::PolicyType::ALWAYS will always leave the scrollbars
   * there. The first one is the horizontal scrollbar, the second, the vertical. */
  m_ScrolledWindow.set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::ALWAYS);
  m_ScrolledWindow.set_expand();

  m_VBox.append(m_ScrolledWindow);

  /* set the spacing to 10 on x and 10 on y */
  m_Grid.set_row_spacing(10);
  m_Grid.set_column_spacing(10);

  /* pack the grid into the scrolled window */
  m_ScrolledWindow.set_child(m_Grid);

  /* this simply creates a grid of toggle buttons
   * to demonstrate the scrolled window. */
  for (int i = 0; i < 10; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      auto s = Glib::ustring::compose("button (%1,%2)", i, j);
      auto pButton = Gtk::make_managed<Gtk::ToggleButton>(s);
      m_Grid.attach(*pButton, i, j);
    }
  }

  /* Add a "close" button to the bottom of the dialog */
  m_VBox.append(m_ButtonClose);
  m_ButtonClose.set_halign(Gtk::Align::END);
  m_ButtonClose.signal_clicked().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_button_close));

  /* Hitting the "Enter" key will cause this button to activate. */
  m_ButtonClose.grab_focus();
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_close()
{
  set_visible(false);
}
