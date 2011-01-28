//$Id: examplewindow.h 705 2006-07-19 02:55:32Z jjongsma $ -*- c++ -*-

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

#ifndef GTKMM_EXAMPLE_CANVAS_H
#define GTKMM_EXAMPLE_CANVAS_H

#include <gtkmm.h>

// This little canvas class is only here 
// because gtkmm does not have a canvas class yet.
// Applications should probably use GooCanvas::Canvas (goocanvasmm) instead.
class Canvas : public Gtk::DrawingArea
{
public:
  Canvas();
  virtual ~Canvas();

private:

  class CanvasItem
  {
  public:
    CanvasItem(Gtk::Widget* canvas, Gtk::ToolButton* button, double x, double y)
    {
      const Gtk::StockID stock_id(button->get_stock_id()); 
      this->pixbuf = canvas->render_icon_pixbuf(stock_id, Gtk::ICON_SIZE_DIALOG);
      this->x = x;
      this->y = y;
    }

    Glib::RefPtr<Gdk::Pixbuf> pixbuf;
    double x, y;
  };

  void item_draw(const CanvasItem *item,
    const Cairo::RefPtr<Cairo::Context>& cr,
    bool preview);

  virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr);
  virtual void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context, 
    int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time);
  virtual bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time);
  virtual bool on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time);
  virtual void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint time);

  bool m_drag_data_requested_for_drop; //So we know what to do in on_drag_data_received().
  CanvasItem* m_drop_item;
  
  typedef std::vector<CanvasItem*> type_vec_items;
  type_vec_items m_canvas_items;
};

#endif //GTKMM_EXAMPLE_CANVAS_H
