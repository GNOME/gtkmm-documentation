/* gtkmm example Copyright (C) 2016 gtkmm development team
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

#include "exampleappwindow.h"
#include <iostream>
#include <stdexcept>

ExampleAppWindow::ExampleAppWindow(BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::ApplicationWindow(cobject),
  m_refBuilder(refBuilder)
{
  m_stack = m_refBuilder->get_widget<Gtk::Stack>("stack");
  if (!m_stack)
    throw std::runtime_error("No \"stack\" object in window.ui");
}

//static
ExampleAppWindow* ExampleAppWindow::create()
{
  // Load the Builder file and instantiate its widgets.
  auto refBuilder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/window.ui");

  auto window = Gtk::Builder::get_widget_derived<ExampleAppWindow>(refBuilder, "app_window");
  if (!window)
    throw std::runtime_error("No \"app_window\" object in window.ui");

  return window;
}

void ExampleAppWindow::open_file_view(const Glib::RefPtr<Gio::File>& file)
{
  const Glib::ustring basename = file->get_basename();

  auto scrolled = Gtk::make_managed<Gtk::ScrolledWindow>();
  scrolled->set_expand(true);
  auto view = Gtk::make_managed<Gtk::TextView>();
  view->set_editable(false);
  view->set_cursor_visible(false);
  scrolled->set_child(*view);
  m_stack->add(*scrolled, basename, basename);

  try
  {
    char* contents = nullptr;
    gsize length = 0;
    
    file->load_contents(contents, length);
    view->get_buffer()->set_text(contents, contents+length);
    g_free(contents);
  }
  catch (const Glib::Error& ex)
  {
    std::cout << "ExampleAppWindow::open_file_view(\"" << file->get_parse_name()
      << "\"):\n  " << ex.what() << std::endl;
  }
}
