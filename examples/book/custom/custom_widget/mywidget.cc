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

#include "mywidget.h"
#include <gdkmm/general.h>  // for cairo helper functions
#include <gtkmm/snapshot.h>
#include <iostream>
//#include <gtk/gtkwidget.h> //For GTK_IS_WIDGET()
#include <cstring>


MyWidget::MyWidget() :
  //The GType name will actually be gtkmm__CustomObject_MyWidget
  Glib::ObjectBase("MyWidget"),
  MyExtraInit("my-widget"), // CSS node name, which must be used in the CSS file.
  Gtk::Widget(),
  m_padding()
{
  // Expand, if there is extra space.
  set_expand(true);

  //This shows the GType name.
  std::cout << "GType name: " << G_OBJECT_TYPE_NAME(gobj()) << std::endl;

  //This shows that the GType still derives from GtkWidget:
  //std::cout << "Gtype is a GtkWidget?:" << GTK_IS_WIDGET(gobj()) << std::endl;

  // The CSS name can be set either
  // - for a GType (in this case for your custom class) with gtk_widget_class_set_css_name(), or
  // - for a widget instance with gtk_widget_set_name() (Gtk::Widget::set_name()).
  //
  // gtk_widget_class_set_css_name(), if used, must be called in the class init function.
  // It has not been wrapped in a C++ function.
  // Gtk::Widget::set_name() can be called in a C++ constructor.
  //
  // Another alternative: The custom widget inherits the CSS name "widget" from
  // GtkWidget. That name can be used in the CSS file. This is not a very good
  // alternative. GtkWidget's CSS name is not documented. It can probably be
  // changed or removed in the future.

  m_refCssProvider = Gtk::CssProvider::create();
  auto refStyleContext = get_style_context();
  refStyleContext->add_provider(m_refCssProvider,
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
  m_refCssProvider->signal_parsing_error().connect(
    sigc::mem_fun(*this, &MyWidget::on_parsing_error));

  m_refCssProvider->load_from_path("custom_gtk.css");
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
  //Get the themed padding from the CSS file:
  m_padding = get_style_context()->get_padding();
  std::cout << "m_padding from the theme/css-file is"
    << ": top=" << m_padding.get_top()
    << ", right=" << m_padding.get_right()
    << ", bottom=" << m_padding.get_bottom()
    << ", left=" << m_padding.get_left() << std::endl;

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
  auto refStyleContext = get_style_context();

  // Create a cairo context to draw on.
  auto cr = snapshot->append_cairo(rect);

  // paint the background
  refStyleContext->render_background(cr,
    -m_padding.get_left(), -m_padding.get_top(), allocation.get_width(), allocation.get_height());

  // draw the foreground
  const double scale_x = 0.001 * (allocation.get_width() - m_padding.get_left() - m_padding.get_right());
  const double scale_y = 0.001 * (allocation.get_height() - m_padding.get_top() - m_padding.get_bottom());
  Gdk::Cairo::set_source_rgba(cr, refStyleContext->get_color());
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

void MyWidget::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error)
{
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section)
  {
    const auto file = section->get_file();
    if (file)
    {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    auto start_location = section->get_start_location();
    auto end_location = section->get_end_location();
    std::cerr << "  start_line = " << start_location.get_lines()+1
              << ", end_line = " << end_location.get_lines()+1 << std::endl;
    std::cerr << "  start_position = " << start_location.get_line_chars()
              << ", end_position = " << end_location.get_line_chars() << std::endl;
  }
}
