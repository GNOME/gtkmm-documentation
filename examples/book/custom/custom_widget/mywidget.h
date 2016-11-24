/* gtkmm example Copyright (C) 2004 gtkmm development team
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

#ifndef GTKMM_CUSTOM_WIDGET_MYWIDGET_H
#define GTKMM_CUSTOM_WIDGET_MYWIDGET_H

#include <gtkmm/widget.h>
#include <gtkmm/cssprovider.h>
#include <gtkmm/styleproperty.h>

class MyWidget : public Gtk::Widget
{
public:
  MyWidget();
  virtual ~MyWidget();

protected:

  //Overrides:
  Gtk::SizeRequestMode get_request_mode_vfunc() const override;
  void measure_vfunc(Gtk::Orientation orientation, int for_size, int& minimum, int& natural,
    int& minimum_baseline, int& natural_baseline) const override;
  void on_size_allocate(Gtk::Allocation& allocation) override;
  void on_map() override;
  void on_unmap() override;
  void on_realize() override;
  void on_unrealize() override;
  bool on_draw(const Cairo::RefPtr<Cairo::Context>& cr) /* override */;

  //Signal handler:
  void on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error);

  Gtk::StyleProperty<int> m_scale_prop;
  Glib::RefPtr<Gdk::Window> m_refGdkWindow;
  Glib::RefPtr<Gtk::CssProvider> m_refCssProvider;

  int m_scale;
};

#endif //GTKMM_CUSTOM_WIDGET_MYWIDGET_H
