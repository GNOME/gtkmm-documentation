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

ExampleWindow::ExampleWindow()
{
 /* Set some window properties */
  set_title("Frame Example");
  set_size_request(300, 300);

  /* Sets the margin around the frame. */
  m_Frame.set_margin(10);

  set_child(m_Frame);

  /* Set the frames label */
  m_Frame.set_label("Gtk::Frame Widget");

  /* Align the label at the right of the frame */
  m_Frame.set_label_align(Gtk::Align::END);
}

ExampleWindow::~ExampleWindow()
{
}

