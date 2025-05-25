/* gtkmm example Copyright (C) 2022 gtkmm development team
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

#include "examplewindow.h"
#include <iostream>
#include <gtkmm/version.h>

#define HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY GTKMM_CHECK_VERSION(4,9,1)

ExampleWindow::ExampleWindow()
: m_VBox(Gtk::Orientation::VERTICAL),
  m_Button_Child("Button with custom CSS node name"),
  m_Label_Child1("Label with custom name"),
  m_Label_Child2("Label with custom CSS class"),
  m_Button_Quit("Quit")
{
  set_title("Custom CSS name example");
  set_default_size(400, 200);

  m_VBox.set_margin(10);
  m_VBox.set_spacing(5);
  set_child(m_VBox);

  // There are 3 ways to set custom CSS data for a widget:
  // 1. The CSS name can be set for a GType with gtk_widget_class_set_css_name().
  // 2. The CSS name can be set for a widget instance with gtk_widget_set_name()
  //    (Gtk::Widget::set_name()).
  // 3. A CSS class can be set for a widget instance with
  //    gtk_widget_add_css_class() (Gtk::Widget::add_css_class()).
  //
  // gtk_widget_class_set_css_name(), if used, must be called in the class init
  // function. It has not been wrapped in a C++ function.
  // Gtk::Widget::set_name() and Gtk::Widget::add_css_class() can be called in
  // a C++ constructor.

  // CSS widget name, which must be used in the CSS file, preceded by "#".
  m_Label_Child1.set_name("my-label1");

  // CSS class name, which must be used in the CSS file, preceded by ".".
  m_Label_Child2.add_css_class("my-label2");

  // Add the child widgets to m_VBox:
  m_VBox.append(*Gtk::make_managed<Gtk::Label>("Ordinary label"));
  m_VBox.append(m_Button_Child);
  m_VBox.append(m_Label_Child1);
  m_VBox.append(m_Label_Child2);
  m_VBox.set_expand();
  m_VBox.append(m_ButtonBox);

  m_ButtonBox.append(m_Button_Quit);
  m_ButtonBox.set_margin(6);
  m_Button_Quit.set_hexpand(true);
  m_Button_Quit.set_halign(Gtk::Align::END);
  m_Button_Quit.signal_clicked().connect( sigc::mem_fun(*this,
              &ExampleWindow::on_button_quit) );

  // Load extra CSS file.
  m_refCssProvider = Gtk::CssProvider::create();
#if HAS_STYLE_PROVIDER_ADD_PROVIDER_FOR_DISPLAY
  Gtk::StyleProvider::add_provider_for_display(get_display(), m_refCssProvider,
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#else
  Gtk::StyleContext::add_provider_for_display(get_display(), m_refCssProvider,
    GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
#endif

  m_refCssProvider->signal_parsing_error().connect(
    [](const auto& section, const auto& error)
    { on_parsing_error(section, error); }
  );
  m_refCssProvider->load_from_path("custom_gtkmm.css");
}

ExampleWindow::~ExampleWindow()
{
}

void ExampleWindow::on_button_quit()
{
  set_visible(false);
}

void ExampleWindow::on_parsing_error(const Glib::RefPtr<const Gtk::CssSection>& section,
  const Glib::Error& error)
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
