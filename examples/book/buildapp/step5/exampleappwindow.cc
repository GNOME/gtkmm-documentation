/* gtkmm example Copyright (C) 2016 gtkmm development team
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

#include "exampleappwindow.h"
#include <iostream>
#include <stdexcept>

ExampleAppWindow::ExampleAppWindow(BaseObjectType* cobject,
  const Glib::RefPtr<Gtk::Builder>& refBuilder)
: Gtk::ApplicationWindow(cobject),
  m_refBuilder(refBuilder),
  m_settings(),
  m_stack(nullptr)
{
  m_refBuilder->get_widget("stack", m_stack);
  if (!m_stack)
    throw std::runtime_error("No \"stack\" object in window.ui");

  m_settings = Gio::Settings::create("org.gtkmm.exampleapp");
  m_settings->bind("transition", m_stack, "transition-type");
}

//static
ExampleAppWindow* ExampleAppWindow::create()
{
  // Load the Builder file and instantiate its widgets.
  auto refBuilder = Gtk::Builder::create_from_resource("/org/gtkmm/exampleapp/window.ui");

  ExampleAppWindow* window = nullptr;
  refBuilder->get_widget_derived("app_window", window);
  if (!window)
    throw std::runtime_error("No \"app_window\" object in window.ui");

  return window;
}

void ExampleAppWindow::open_file_view(const Glib::RefPtr<Gio::File>& file)
{
  const auto basename = file->get_basename();

  auto scrolled = Gtk::manage(new Gtk::ScrolledWindow());
  scrolled->set_hexpand(true);
  scrolled->set_vexpand(true);
  scrolled->show();
  auto view = Gtk::manage(new Gtk::TextView());
  view->set_editable(false);
  view->set_cursor_visible(false);
  view->show();
  scrolled->add(*view);
  m_stack->add(*scrolled, basename, basename);

  auto buffer = view->get_buffer();
  try
  {
    char* contents = nullptr;
    gsize length = 0;
    
    file->load_contents(contents, length);
    buffer->set_text(contents, contents+length);
    g_free(contents);
  }
  catch (const Glib::Error& ex)
  {
    std::cout << "ExampleAppWindow::open_file_view(\"" << file->get_parse_name()
      << "\"):\n  " << ex.what() << std::endl;
  }

  // tag is a Glib::RefPtr<Gtk::TextTag>. Gio::Settings::bind() requires a plain
  // pointer to the tag. It does not accept a RefPtr. There is no Glib::RefPtr::get()
  // or equivalent. We must use the unintuitive tag.operator->().
  auto tag = buffer->create_tag();
  m_settings->bind("font", tag.operator->(), "font");
  buffer->apply_tag(tag, buffer->begin(), buffer->end());
}
