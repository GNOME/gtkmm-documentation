/* gtkmm example Copyright (C) 2012 gtkmm development team
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

#include "myarea.h"

MyArea::MyArea()
: m_fix (0)
{
  set_content_width(200);
  set_content_height(100);
  set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
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
}

// Toogle between both values (0 or 0.5)
void MyArea::fix_lines(bool fix)
{
  // to get the width right, we have to draw in the middle of the pixel
  m_fix = fix ? 0.5 : 0.0;

  // force the redraw of the image
  queue_draw();
}
