/* gtkmm example Copyright (C) 2012 gtkmm development team
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

#include "myarea.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

class ExampleWindow : public Gtk::Window
{
public:
  ExampleWindow();

protected:
  MyArea m_area;
};

ExampleWindow::ExampleWindow()
{
  set_title("Drawing text example");
  set_child(m_area);
}

int main(int argc, char* argv[])
{
  auto app = Gtk::Application::create("org.gtkmm.example");

  return app->make_window_and_run<ExampleWindow>(argc, argv);
}
