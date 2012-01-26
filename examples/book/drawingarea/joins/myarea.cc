//$Id: myarea.cc 836 2007-05-09 03:02:38Z jjongsma $ -*- c++ -*-

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

#include "myarea.h"
#include <cairomm/context.h>

MyArea::MyArea()
{
}

MyArea::~MyArea()
{
}

bool MyArea::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window();
  if(window)
  {
    Gtk::Allocation allocation = get_allocation();
    const int width = allocation.get_width();
    const int height = allocation.get_height();

    cr->set_line_width(10.0);

    // Scale to unit square
    cr->scale(width, height);
    cr->save();
    cr->set_source_rgb(1, 1, 1);
    cr->paint();
    cr->restore();
    cr->set_line_width(0.12);
    cr->move_to(0.3, 0.3);
    cr->rel_line_to(0.2, -0.2);
    cr->rel_line_to(0.2, 0.2);
    cr->set_line_join(Cairo::LINE_JOIN_MITER); /* default */
    cr->stroke();
    cr->move_to(0.3, 0.6);
    cr->rel_line_to(0.2, -0.2);
    cr->rel_line_to(0.2, 0.2);
    cr->set_line_join(Cairo::LINE_JOIN_BEVEL);
    cr->stroke();
    cr->move_to(0.3, 0.9);
    cr->rel_line_to(0.2, -0.2);
    cr->rel_line_to(0.2, 0.2);
    cr->set_line_join(Cairo::LINE_JOIN_ROUND);
    cr->stroke();
  }

  return true;
}
