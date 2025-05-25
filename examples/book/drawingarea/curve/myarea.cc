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

#include "myarea.h"
#include <cairomm/context.h>
#include <vector>

MyArea::MyArea()
{
  set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
  const double x0=0.1, y0=0.5, // start point
               x1=0.4, y1=0.9, // control point #1
               x2=0.6, y2=0.1, // control point #2
               x3=0.9, y3=0.5; // end point
  const std::vector<double> dashes = {0.08, 0.05};

  // scale to unit square (0 to 1 width and height)
  cr->scale(width, height);

  // draw curve
  cr->set_line_width(0.05);
  cr->move_to(x0, y0);
  cr->curve_to(x1, y1, x2, y2, x3, y3);
  cr->stroke();

  // show first control point (red)
  cr->set_line_width(0.03);
  cr->set_dash(dashes, 0.0);
  cr->set_source_rgba(1.0, 0.2, 0.2, 0.6);
  cr->set_line_cap(Cairo::Context::LineCap::ROUND);
  cr->move_to(x1, y1);
  cr->line_to (x0, y0);
  cr->stroke();

  // show second control point (blue)
  cr->set_source_rgba(0.2, 0.2, 1.0, 0.6);
  cr->set_line_cap(Cairo::Context::LineCap::BUTT);
  cr->move_to(x2, y2);
  cr->line_to (x3, y3);
  cr->stroke();
}
