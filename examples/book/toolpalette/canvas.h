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
      Glib::ustring icon_name(button->get_icon_name());
      if (icon_name.empty())
        icon_name = button->get_label();

      auto icon_theme = Gtk::IconTheme::get_for_screen(canvas->get_screen());
      int width = 0;
      int height = 0; //ignored
      Gtk::IconSize::lookup(Gtk::ICON_SIZE_DIALOG, width, height);
      this->m_pixbuf = icon_theme->load_icon(icon_name, width, Gtk::ICON_LOOKUP_GENERIC_FALLBACK);
      this->m_x = x;
      this->m_y = y;
    }

    Glib::RefPtr<Gdk::Pixbuf> m_pixbuf;
    double m_x, m_y;
  };

  void item_draw(const CanvasItem *item,
    const Cairo::RefPtr<Cairo::Context>& cr,
    bool preview);

  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) override;
  void on_drag_data_received(const Glib::RefPtr<Gdk::DragContext>& context,
    int x, int y, const Gtk::SelectionData& selection_data, guint info, guint time) override;
  bool on_drag_motion(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time) override;
  bool on_drag_drop(const Glib::RefPtr<Gdk::DragContext>& context, int x, int y, guint time) override;
  void on_drag_leave(const Glib::RefPtr<Gdk::DragContext>& context, guint time) override;

  bool m_drag_data_requested_for_drop; //So we know what to do in on_drag_data_received().
  CanvasItem* m_drop_item;

  typedef std::vector<CanvasItem*> type_vec_items;
  type_vec_items m_canvas_items;
};

#endif //GTKMM_EXAMPLE_CANVAS_H
