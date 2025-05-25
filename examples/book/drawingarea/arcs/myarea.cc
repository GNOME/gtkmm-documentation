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
#include <cmath>

MyArea::MyArea()
{
  set_draw_func(sigc::mem_fun(*this, &MyArea::on_draw));
}

MyArea::~MyArea()
{
}

void MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr, int width, int height)
{
  const int lesser = std::min(width, height);

  // coordinates for the center of the window
  const int xc = width / 2;
  const int yc = height / 2;

  cr->set_line_width(lesser * 0.02);  // outline thickness changes
                                      // with window size

  // first draw a simple unclosed arc
  cr->save();
  cr->arc(width / 3.0, height / 4.0, lesser / 4.0, -(M_PI / 5.0), M_PI);
  cr->close_path();   // line back to start point
  cr->set_source_rgb(0.0, 0.8, 0.0);
  cr->fill_preserve();
  cr->restore();  // back to opaque black
  cr->stroke();   // outline it

  // now draw a circle
  cr->save();
  cr->arc(xc, yc, lesser / 4.0, 0.0, 2.0 * M_PI); // full circle
  cr->set_source_rgba(0.0, 0.0, 0.8, 0.6);    // partially translucent
  cr->fill_preserve();
  cr->restore();  // back to opaque black
  cr->stroke();

  // and finally an ellipse
  double ex, ey, ew, eh;
  // center of ellipse
  ex = xc;
  ey = 3.0 * height / 4.0;
  // ellipse dimensions
  ew = 3.0 * width / 4.0;
  eh = height / 3.0;

  cr->save();

  cr->translate(ex, ey);  // make (ex, ey) == (0, 0)
  cr->scale(ew / 2.0, eh / 2.0);  // for width: ew / 2.0 == 1.0
                                  // for height: eh / 2.0 == 1.0

  cr->arc(0.0, 0.0, 1.0, 0.0, 2 * M_PI);  // 'circle' centered at (0, 0)
                                          // with 'radius' of 1.0

  cr->set_source_rgba(0.8, 0.0, 0.0, 0.7);
  cr->fill_preserve();
  cr->restore();  // back to opaque black
  cr->stroke();
}
