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
: m_AspectFrame(
    Gtk::Align::CENTER, /* center x */
    Gtk::Align::CENTER, /* center y */
    2.0, /* xsize/ysize = 2 */
    false /* ignore child's aspect */),
  m_Frame("2x1" /* label */)
{
  set_title("Aspect Frame");

  // Set a child widget to the aspect frame */
  // Ask for a 200x200 window, but the AspectFrame will give us a 200x100
  // window since we are forcing a 2x1 aspect ratio */
  m_DrawingArea.set_content_width(200);
  m_DrawingArea.set_content_height(200);
  m_Frame.set_child(m_DrawingArea);
  m_AspectFrame.set_child(m_Frame);
  m_AspectFrame.set_margin(10);

  // Add the aspect frame to our toplevel window:
  set_child(m_AspectFrame);
}

ExampleWindow::~ExampleWindow()
{
}

