/* gtkmm example Copyright (C) 2017 gtkmm development team
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
 * along with this program; if not, see <http://www.gnu.org/licenses/>.
 */

#include "mywidget2.h"
#include <gdkmm/general.h>  // for cairo helper functions
#include <iostream>
//#include <gtk/gtkwidget.h> //For GTK_IS_WIDGET()
#include <cstring>


MyWidget2::MyWidget2() :
  //The GType name will actually be gtkmm__CustomObject_MyWidget2
  Glib::ObjectBase("MyWidget2"),
  Gtk::WidgetCustomDraw(),
  MyExtraInit("my-widget2"),
  Gtk::Widget(),
  //Install a style property so that an aspect of this widget may be themed
  //via a CSS style sheet file:
  m_scale_prop(*this, "example_scale", 500),
  m_scale(1000)
{
  // Expand, if there is extra space.
  set_hexpand(true);
  set_vexpand(true);

  //This shows the GType name, which must be used in the CSS file.
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
    sigc::mem_fun(*this, &MyWidget2::on_parsing_error));

  try
  {
    m_refCssProvider->load_from_path("custom_gtk.css");
  }
  catch(const Gtk::CssProviderError& ex)
  {
    std::cerr << "CssProviderError, Gtk::CssProvider::load_from_path() failed: "
              << ex.what() << std::endl;
  }
  catch(const Glib::Error& ex)
  {
    std::cerr << "Error, Gtk::CssProvider::load_from_path() failed: "
              << ex.what() << std::endl;
  }
}

MyWidget2::~MyWidget2()
{
}

Gtk::SizeRequestMode MyWidget2::get_request_mode_vfunc() const
{
  //Accept the default value supplied by the base class.
  return Gtk::Widget::get_request_mode_vfunc();
}

//Discover the total amount of minimum space and natural space needed by
//this widget.
//Let's make this simple example widget always need minimum 60 by 50 and
//natural 100 by 70.
void MyWidget2::measure_vfunc(Gtk::Orientation orientation, int /* for_size */,
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

void MyWidget2::on_size_allocate(Gtk::Allocation& allocation)
{
  //Do something with the space that we have actually been given:
  //(We will not be given heights or widths less than we have requested, though
  //we might get more)

  //Use the offered allocation for this container:
  set_allocation(allocation);

  if(m_refGdkWindow)
  {
    m_refGdkWindow->move_resize( allocation.get_x(), allocation.get_y(),
            allocation.get_width(), allocation.get_height() );
  }
}

void MyWidget2::on_map()
{
  //Call base class:
  Gtk::Widget::on_map();
}

void MyWidget2::on_unmap()
{
  //Call base class:
  Gtk::Widget::on_unmap();
}

void MyWidget2::on_realize()
{
  //Do not call base class Gtk::Widget::on_realize().
  //It's intended only for widgets that set_has_window(false).

  set_realized();

  //Get the themed style from the CSS file:
  m_scale = m_scale_prop.get_value();
  std::cout << "m_scale (example_scale from the theme/css-file) is: "
      << m_scale << std::endl;

  if(!m_refGdkWindow)
  {
    //Create the GdkWindow:
    m_refGdkWindow = Gdk::Window::create_child(get_parent_window(),
      get_events () | Gdk::EventMask::EXPOSURE_MASK, get_allocation());
    set_window(m_refGdkWindow);

    //make the widget receive expose events
    m_refGdkWindow->set_user_data(gobj());
  }
}

void MyWidget2::on_unrealize()
{
  m_refGdkWindow.reset();

  //Call base class:
  Gtk::Widget::on_unrealize();
}

bool MyWidget2::on_draw(const Cairo::RefPtr<Cairo::Context>& cr)
{
  const auto allocation = get_allocation();
  auto clip = get_clip();
  clip.set_x(clip.get_x() - allocation.get_x());
  clip.set_y(clip.get_y() - allocation.get_y());
  const double scale_x = (double)clip.get_width() / m_scale;
  const double scale_y = (double)clip.get_height() / m_scale;
  auto refStyleContext = get_style_context();

  // paint the background
  refStyleContext->render_background(cr,
    clip.get_x(), clip.get_y(), clip.get_width(), clip.get_height());

  // draw the foreground
  Gdk::Cairo::set_source_rgba(cr, refStyleContext->get_color());
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

  return true;
}

void MyWidget2::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section, const Glib::Error& error)
{
  std::cerr << "on_parsing_error(): " << error.what() << std::endl;
  if (section)
  {
    const auto file = section->get_file();
    if (file)
    {
      std::cerr << "  URI = " << file->get_uri() << std::endl;
    }

    std::cerr << "  start_line = " << section->get_start_line()+1
              << ", end_line = " << section->get_end_line()+1 << std::endl;
    std::cerr << "  start_position = " << section->get_start_position()
              << ", end_position = " << section->get_end_position() << std::endl;
  }
}
