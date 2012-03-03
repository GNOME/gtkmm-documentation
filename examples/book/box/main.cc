//$Id: main.cc 2 2003-01-21 13:41:59Z murrayc $ -*- c++ -*-

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

#include "examplewindow.h"
#include <gtkmm/application.h>
#include <iostream>
#include <cstdlib>

using std::atoi;

int main(int argc, char *argv[])
{
  Glib::RefPtr<Gtk::Application> app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

  if(argc != 2)
  {
    std::cerr << "usage: packbox num, where num is 1, 2, or 3." << std::endl;
    return 1;
  }

  ExampleWindow window( atoi(argv[1]) );
  return app->run(window); //Shows the window and returns when it is closed.
}
