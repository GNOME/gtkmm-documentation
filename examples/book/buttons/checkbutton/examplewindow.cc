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
: m_button("something")
{
  set_title("checkbutton example");

  m_button.signal_toggled().connect(sigc::mem_fun(*this,
              &ExampleWindow::on_button_toggled) );

  m_button.set_margin(10);
  set_child(m_button);
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_toggled()
{
  std::cout << "The Button was toggled: state="
      << (m_button.get_active() ? "true" : "false")
      << std::endl;
}
