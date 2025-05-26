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
: m_Label("Click here to quit, quit, quit, quit, quit")
{
  set_title ("EventBox");
  set_border_width(10);

  add(m_EventBox);

  m_EventBox.add(m_Label);

  //Clip the label short:
  set_default_size(110, 20);
  m_Label.set_size_request(110, 20);
  m_Label.set_ellipsize(Pango::ELLIPSIZE_END);

  //And bind an action to it:
  m_EventBox.set_events(Gdk::BUTTON_PRESS_MASK);
  m_EventBox.signal_button_press_event().connect(
    sigc::mem_fun(*this, &ExampleWindow::on_eventbox_button_press) );

  m_EventBox.set_tooltip_text("Click me!");

  show_all_children();
}

ExampleWindow::~ExampleWindow()
{
}

bool ExampleWindow::on_eventbox_button_press(GdkEventButton*)
{
  hide();
  return true;
}
