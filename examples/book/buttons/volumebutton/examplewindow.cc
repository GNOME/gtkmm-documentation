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
{
  //Make the window big enough to show the popup scale from the GtkVolumeButton.
  //Otherwise it will be truncated.
  set_default_size(300, 300);

  set_title("VolumeButton Example");

  m_grid.set_margin(12);
  set_child(m_grid);
  m_button.set_vexpand(true);
  m_button.set_hexpand(true);

  m_grid.attach(m_button, 1, 1, 1, 1);
  m_button.set_valign(Gtk::Align::END);
  m_button.set_halign(Gtk::Align::END);

  m_button.set_value(0.4);
  m_button.signal_value_changed().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_value_changed));
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_value_changed(double value)
{
  std::cout << "Value: " << value << std::endl;
}

