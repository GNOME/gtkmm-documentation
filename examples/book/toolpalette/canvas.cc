//$Id: canvas.cc 870 2007-07-13 19:08:46Z murrayc $ -*- c++ -*-

/* gtkmm example Copyright (C) 2009 gtkmm development team
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

#include "canvas.h"
#include <iostream>

Canvas::Canvas()
: m_drop_item(0)
{
  set_app_paintable();
}

Canvas::~Canvas()
{
  while(!m_canvas_items.empty())
  {
    type_list_items::iterator iter = m_canvas_items.begin();
    CanvasItem* item = *iter;
    delete item;
    m_canvas_items.erase(iter);
  }
}

void Canvas::item_draw(const CanvasItem *item,
  const Cairo::RefPtr<Cairo::Context>& cr,
  bool preview)
{
  if(!item || !item->pixbuf)
    return;

  const double cx = item->pixbuf->get_width();
  const double cy = item->pixbuf->get_height();

  Gdk::Cairo::set_source_pixbuf(cr,
    item->pixbuf,
    item->x - cx * 0.5, item->y - cy * 0.5);

  if(preview)
    cr->paint_with_alpha(0.6);
  else
    cr->paint();
}

bool Canvas::on_expose_event(GdkEventExpose* event)
{
  // This is where we draw on the window
  Glib::RefPtr<Gdk::Window> window = get_window();
  if(!window)
   return false;

  Cairo::RefPtr<Cairo::Context> cr = window->create_cairo_context();
  const Gdk::Region region(event->region, true /* copy */);
  Gdk::Cairo::region(cr, region);
  cr->clip();

  cr->set_source_rgb(1.0, 1.0, 1.0);
  const Gtk::Allocation allocation = get_allocation();
  cr->rectangle(0, 0, allocation.get_width(), allocation.get_height());
  cr->fill();

  for(type_list_items::iterator iter = m_canvas_items.begin();
    iter != m_canvas_items.end(); ++iter )
  {
    item_draw(*iter, cr, false);
  }

  if(m_drop_item)
    item_draw (m_drop_item, cr, true);

  return true;
}

void  Canvas::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time)
{
  // Find the tool button which is the source of this DnD operation.
  Gtk::Widget* widget = drag_get_source_widget(context);

  Gtk::ToolPalette* drag_palette = dynamic_cast<Gtk::ToolPalette*>(widget);
  while(widget && !drag_palette)
  {
    widget = widget->get_parent();
    drag_palette = dynamic_cast<Gtk::ToolPalette*>(widget);
  }

  Gtk::ToolItem* drag_item = 0;
  if(drag_palette)
    drag_item = drag_palette->get_drag_item(selection_data);

  Gtk::ToolButton* button = dynamic_cast<Gtk::ToolButton*>(drag_item);
  if(!button)
    return;

  // Add a canvas item at the position,
  // to be drawn in our expose_event handler.
  CanvasItem* canvas_item = new CanvasItem(this, button, x, y);
  m_canvas_items.push_back(canvas_item);
  queue_draw();

  Gtk::DrawingArea::on_drag_data_received(context, x, y, selection_data, info, time);
}



