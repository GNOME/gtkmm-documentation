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
: m_drag_data_requested_for_drop(false),
  m_drop_item(0)
{
  set_app_paintable();
}

Canvas::~Canvas()
{
  while(!m_canvas_items.empty())
  {
    type_vec_items::iterator iter = m_canvas_items.begin();
    CanvasItem* item = *iter;
    delete item;
    m_canvas_items.erase(iter);
  }

  delete m_drop_item;
}

void Canvas::item_draw(const CanvasItem *item,
  const Cairo::RefPtr<Cairo::Context>& cr,
  bool preview)
{
  if(!item || !item->m_pixbuf)
    return;

  const double cx = item->m_pixbuf->get_width();
  const double cy = item->m_pixbuf->get_height();

  Gdk::Cairo::set_source_pixbuf(cr,
    item->m_pixbuf,
    item->m_x - cx * 0.5, item->m_y - cy * 0.5);

  if(preview)
    cr->paint_with_alpha(0.6);
  else
    cr->paint();
}

bool Canvas::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  cr->set_source_rgb(1.0, 1.0, 1.0);
  const Gtk::Allocation allocation = get_allocation();
  cr->rectangle(0, 0, allocation.get_width(), allocation.get_height());
  cr->fill();

  for(type_vec_items::iterator iter = m_canvas_items.begin();
    iter != m_canvas_items.end(); ++iter )
  {
    item_draw(*iter, cr, false);
  }

  if(m_drop_item)
    item_draw (m_drop_item, cr, true);

  return true;
}


bool Canvas::on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context,
  int x, int y, guint time)
{
  m_drag_data_requested_for_drop = false; //It's for drag-motion instead.

  if(m_drop_item)
  {
    // We already have a drop indicator so just update its position.

    m_drop_item->m_x = x;
    m_drop_item->m_y = y;

    queue_draw();
    context->drag_status(Gdk::ACTION_COPY, time);
  }
  else
  {
    // Request DnD data for creating a drop indicator.
    // This will cause on_drag_data_received() to be called.
    const Glib::ustring target = drag_dest_find_target(context);

    if (target.empty())
      return false;

    drag_get_data(context, target, time);
  }

  Gtk::DrawingArea::on_drag_motion(context, x, y, time);
  return true;
}


void Canvas::on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
  int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time)
{
  // Find the tool button which is the source of this DnD operation.
  Gtk::Widget* widget = drag_get_source_widget(context);

  Gtk::ToolPalette* drag_palette = dynamic_cast<Gtk::ToolPalette*>(widget);
  while(widget && !drag_palette)
  {
    widget = widget->get_parent();
    drag_palette = dynamic_cast<Gtk::ToolPalette*>(widget);
  }

  Gtk::ToolItem* drag_item = nullptr;
  if(drag_palette)
    drag_item = drag_palette->get_drag_item(selection_data);

  // Create a drop indicator when a tool button was found:
  Gtk::ToolButton* button = dynamic_cast<Gtk::ToolButton*>(drag_item);
  if(!button)
    return;

  delete m_drop_item;
  m_drop_item = nullptr;

  try
  {
    CanvasItem* item = new CanvasItem(this, button, x, y);

    if(m_drag_data_requested_for_drop)
    {
      m_canvas_items.push_back(item);

      // Signal that the item was accepted and then redraw.
      context->drag_finish(true /* success */, false /* del */, time);
    }
    else
    {
      m_drop_item = item;

      // We are getting this data due to a request in drag_motion,
      // rather than due to a request in drag_drop, so we are just
      // supposed to call gdk_drag_status (), not actually paste in
      // the data.
      context->drag_status(Gdk::ACTION_COPY, time);
    }

    queue_draw();
  }
  catch (const Gtk::IconThemeError& ex)
  {
    std::cerr << "IconThemeError: " << ex.what() << std::endl;
  }

  Gtk::DrawingArea::on_drag_data_received(context, x, y, selection_data, info, time);
}


bool Canvas::on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int /* x */, int /* y */, guint time)
{
  // Request DnD data for creating a dopped item.
  // This will cause on_drag_data_received() to be called.
  const Glib::ustring target = drag_dest_find_target(context);

  if (target.empty())
    return false;

  m_drag_data_requested_for_drop = true;
  drag_get_data(context, target, time);

  return true;
}

void Canvas::on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint time)
{
  //This signal is emitted to clean up the item used for drag-motion,
  //either when the cursor moves out of the widget or when we drop.

  if(!m_drop_item)
    return;

  delete m_drop_item;
  m_drop_item = nullptr;

  queue_draw();

  Gtk::DrawingArea::on_drag_leave(context, time);
}
