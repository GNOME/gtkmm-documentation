/* gtkmm example Copyright (C) 2004 gtkmm development team
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

#include "mywidget.h"
#include <gdkmm/general.h>  // for Gdk::Cairo:: functions
#include <gtkmm/snapshot.h>

MyWidget::MyWidget()
{
  // Expand, if there is extra space.
  set_expand(true);

  m_padding.set_left(5);
  m_padding.set_right(15);
  m_padding.set_top(10);
  m_padding.set_bottom(20);
}

MyWidget::~MyWidget()
{
}

Gtk::SizeRequestMode MyWidget::get_request_mode_vfunc() const
{
  //Accept the default value supplied by the base class.
  return Gtk::Widget::get_request_mode_vfunc();
}

//Discover the total amount of minimum space and natural space needed by
//this widget.
//Let's make this simple example widget always need minimum 60 by 50 and
//natural 100 by 70.
void MyWidget::measure_vfunc(Gtk::Orientation orientation, int /* for_size */,
  int& minimum, int& natural, int& minimum_baseline, int& natural_baseline) const
{
  if (orientation == Gtk::Orientation::HORIZONTAL)
  {
    minimum = 60;
    natural = 100;
  }
  else
  {
    minimum = 50;
    natural = 70;
  }

  // Don't use baseline alignment.
  minimum_baseline = -1;
  natural_baseline = -1;
}

void MyWidget::on_map()
{
  //Call base class:
  Gtk::Widget::on_map();
}

void MyWidget::on_unmap()
{
  //Call base class:
  Gtk::Widget::on_unmap();
}

void MyWidget::on_realize()
{
  //Call base class:
  Gtk::Widget::on_realize();
}

void MyWidget::on_unrealize()
{
  //Call base class:
  Gtk::Widget::on_unrealize();
}

void MyWidget::snapshot_vfunc(const Glib::RefPtr<Gtk::Snapshot>& snapshot)
{
  const auto allocation = get_allocation();
  const Gdk::Rectangle rect(0, 0, allocation.get_width(), allocation.get_height());

  // Create a cairo context to draw on.
  auto cr = snapshot->append_cairo(rect);

  // paint the background
  Gdk::Cairo::set_source_rgba(cr, m_background);
  Gdk::Cairo::add_rectangle_to_path(cr, rect);
  cr->fill();

  // draw the foreground
  const double scale_x = 0.001 * (allocation.get_width() - m_padding.get_left() - m_padding.get_right());
  const double scale_y = 0.001 * (allocation.get_height() - m_padding.get_top() - m_padding.get_bottom());
  Gdk::Cairo::set_source_rgba(cr, m_foreground);
  cr->translate(m_padding.get_left(), m_padding.get_top());
  cr->rectangle(0.0, 0.0, 1000.0*scale_x, 1000.0*scale_y);
  cr->move_to(155.*scale_x, 165.*scale_y);
  cr->line_to(155.*scale_x, 838.*scale_y);
  cr->line_to(265.*scale_x, 900.*scale_y);
  cr->line_to(849.*scale_x, 564.*scale_y);
  cr->line_to(849.*scale_x, 438.*scale_y);
  cr->line_to(265.*scale_x, 100.*scale_y);
  cr->line_to(155.*scale_x, 165.*scale_y);
  cr->move_to(265.*scale_x, 100.*scale_y);
  cr->line_to(265.*scale_x, 652.*scale_y);
  cr->line_to(526.*scale_x, 502.*scale_y);
  cr->move_to(369.*scale_x, 411.*scale_y);
  cr->line_to(633.*scale_x, 564.*scale_y);
  cr->move_to(369.*scale_x, 286.*scale_y);
  cr->line_to(369.*scale_x, 592.*scale_y);
  cr->move_to(369.*scale_x, 286.*scale_y);
  cr->line_to(849.*scale_x, 564.*scale_y);
  cr->move_to(633.*scale_x, 564.*scale_y);
  cr->line_to(155.*scale_x, 838.*scale_y);
  cr->stroke();
}
