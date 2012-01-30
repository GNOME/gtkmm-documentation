/* gtkmm example Copyright (C) 2012 gtkmm development team
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA.
 */

#include "myarea.h"

MyArea::MyArea()
: m_fix (0)
{
  set_size_request (200, 100);
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  Gtk::Allocation allocation = get_allocation();
  const int width = allocation.get_width();
  const int height = allocation.get_height();

  cr->set_line_width(1.0);

  // draw one line, every two pixels
  // without the 'fix', you won't notice any space between the lines,
  // since each one will occupy two pixels (width)
  for (int i = 0; i < width; i += 2)
  {
    cr->move_to(i + m_fix, 0);
    cr->line_to(i + m_fix, height);
  }

  cr->stroke();

  return true;
}

// Toogle between both values (0 or 0.5)
void MyArea::fix_lines(bool fix)
{
  // to get the width right, we have to draw in the middle of the pixel
  m_fix = fix ? 0.5 : 0.0;

  force_redraw();
}

// force the redraw of the image
void MyArea::force_redraw()
{
  Glib::RefPtr<Gdk::Window> win = get_window();
  if (win)
  {
    Gdk::Rectangle r(0, 0, get_allocation().get_width(), get_allocation().get_height());
    win->invalidate_rect(r, false);
  }
}
