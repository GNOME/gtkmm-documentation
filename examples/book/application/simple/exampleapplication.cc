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

#include "exampleapplication.h"
#include "examplewindow.h"
#include <iostream>

ExampleApplication::ExampleApplication()
: Gtk::Application("org.gtkmm.examples.application", Gio::Application::Flags::HANDLES_OPEN)
{
  Glib::set_application_name("Gtk::Application Example");
}

Glib::RefPtr<ExampleApplication> ExampleApplication::create()
{
  return Glib::make_refptr_for_instance<ExampleApplication>( new ExampleApplication() );
}

void ExampleApplication::create_window(const Glib::RefPtr<Gio::File>& file)
{
  auto window = new ExampleWindow();

  //Make sure that the application runs for as long this window is still open:
  add_window(*window);

  //Delete the window when it is hidden.
  //That's enough for this simple example.
  window->signal_hide().connect([window]() { delete window; });

  window->set_visible(true);

  if(!file)
  {
    //This is probably a new empty file, as a result of an activation rather
    //than an open.
    return;
  }

  const bool loaded = window->load_file(file);
  if(!loaded)
    std::cerr << "This file could not be loaded: " << file->get_path() << std::endl;
}

void ExampleApplication::on_activate()
{
  //std::cout << "debug1: " << G_STRFUNC << std::endl;
  // The application has been started, so let's show a window.
  // A real application might want to reuse this "empty" window in on_open(),
  // when asked to open a file, if no changes have been made yet.
  create_window();
}

void ExampleApplication::on_open(const Gio::Application::type_vec_files& files,
  const Glib::ustring& hint)
{
  // The application has been asked to open some files,
  // so let's open a new window for each one.
  //std::cout << "debug: files.size()=" << files.size() << std::endl;
  for(guint i = 0; i < files.size(); i++)
  {
    auto file = files[i];
    if(!file)
    {
      std::cerr << G_STRFUNC << ": file is null." << std::endl;
    }
    else
      create_window(file);
  }

  //Call the base class's implementation:
  Gtk::Application::on_open(files, hint);
}
