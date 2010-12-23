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

#include "exampleapplication.h"
#include "examplewindow.h"

ExampleApplication::ExampleApplication(const Glib::ustring& appid, Gio::ApplicationFlags flags)
: Gtk::Application(appid, flags)
{
}

void ExampleApplication::new_window(const Glib::RefPtr<Gio::File>& file)
{
  Gtk::Window* window = new ExampleWindow(file);
  add_window(*window);
  window->signal_hide().connect(sigc::bind<Gtk::Window*>(sigc::mem_fun(*this,
    &ExampleApplication::on_window_hide), window));
  window->show();
}

void ExampleApplication::on_window_hide(Gtk::Window* window)
{
  delete window;
}

void ExampleApplication::on_activate()
{
  new_window(Glib::RefPtr<Gio::File>());
}

void ExampleApplication::on_open(const Gio::Application::type_vec_files& files,
  const Glib::ustring& hint)
{
  for (unsigned int i = 0; i < files.size(); i++)
  {
    new_window(files[i]);
  }
}
