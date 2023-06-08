/*******************************************************************************
 *
 *  Copyright (c) 2007 Jonathon Jongsma
 *
 *  This file is part of gtkmm
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, see <http://www.gnu.org/licenses/>
 *
 *******************************************************************************/
#include <iostream>
#include <utility>
#include <giomm.h>

// How to connect on_directory_changed() to a signal:
// 1. sigc::ptr_fun()
// 2. C++11 lambda expression with explicit parameters
// 3. C++14 variadic lambda expression with perfect forwarding
#define LAMBDA_EXPRESSION_OR_PTR_FUN 1

namespace
{

Glib::RefPtr<Glib::MainLoop> mainloop;
const std::string FILENAME = "./temp-file";

void
on_directory_changed(const Glib::RefPtr<Gio::File>& file,
           const Glib::RefPtr<Gio::File>& other_file,
           Gio::FileMonitor::Event event)
{
  std::cout << "** Directory changed **" << std::endl;

  if(file)
    std::cout << "   File 1: " << file->get_path() << std::endl;

  if(other_file)
    std::cout << "   File 2: " << other_file->get_path() << std::endl;

  std::cout << "   Event: ";

  switch(event)
  {
    case Gio::FileMonitor::Event::CHANGED:
      std::cout << "A file changed" << std::endl;
      break;
    case Gio::FileMonitor::Event::CHANGES_DONE_HINT:
      std::cout << "A hint that this was probably the last change in a set of changes" << std::endl;
      break;
    case Gio::FileMonitor::Event::DELETED:
      std::cout << "A file was deleted" << std::endl;
      break;
    case Gio::FileMonitor::Event::CREATED:
      std::cout << "A file was created" << std::endl;
      break;
    case Gio::FileMonitor::Event::ATTRIBUTE_CHANGED:
      std::cout << "A file attribute was changed" << std::endl;
      break;
    case Gio::FileMonitor::Event::PRE_UNMOUNT:
      std::cout << "The file location will soon be unmounted" << std::endl;
      break;
    case Gio::FileMonitor::Event::UNMOUNTED:
      std::cout << "The file location was unmounted" << std::endl;
      break;
    case Gio::FileMonitor::Event::MOVED:
      std::cout << "The file was moved" << std::endl;
      break;
    case Gio::FileMonitor::Event::RENAMED:
      std::cout << "The file was renamed within the current directory" << std::endl;
      break;
    case Gio::FileMonitor::Event::MOVED_IN:
      std::cout << "The file was moved into the monitored directory from another location" << std::endl;
      break;
    case Gio::FileMonitor::Event::MOVED_OUT:
      std::cout << "The file was moved out of the monitored directory to another location" << std::endl;
      break;
    default:
      std::cout << "Unknown event "  << static_cast<int>(event) << std::endl;
  }
}

bool create_temp_file()
{
  try
  {
    auto temp_file = Gio::File::create_for_path(FILENAME);

    auto stream = temp_file->create_file ();
    stream->write("This is only a test.");
    stream->close();
  }
  catch (const Gio::Error& ex)
  {
    std::cout << ex.what () << std::endl;
  }

  // Stop future timeouts from repeating:
  return false;
}

bool quit()
{
  try
  {
    auto temp_file = Gio::File::create_for_path(FILENAME);
    temp_file->remove();
  }
  catch (const Gio::Error& ex)
  {
    std::cout << ex.what () << std::endl;
  }

  // Stop future timeouts from repeating:
  mainloop->quit();

  return false;
}

} // anomymous namespace

int main(int /* argc */, char** /* argv */)
{
  Gio::init();
  mainloop = Glib::MainLoop::create();

  auto current_dir = Glib::get_current_dir();
  auto dir = Gio::File::create_for_path(current_dir);
  auto monitor = dir->monitor_directory(Gio::FileMonitorFlags::WATCH_MOVES);

  std::cout << "Monitoring directory '" << current_dir << "'..."
    << std::endl << std::endl;
#if LAMBDA_EXPRESSION_OR_PTR_FUN == 1
  // sigc::ptr_fun() can sometimes be nicer than a lambda expression.
  monitor->signal_changed().connect(sigc::ptr_fun(on_directory_changed));
#elif LAMBDA_EXPRESSION_OR_PTR_FUN == 2
  monitor->signal_changed().connect(
    [](const Glib::RefPtr<Gio::File>& file,
    const Glib::RefPtr<Gio::File>& other_file,
    Gio::FileMonitor::Event event)
    { on_directory_changed(file, other_file, event); }
  );
#elif LAMBDA_EXPRESSION_OR_PTR_FUN == 3
  monitor->signal_changed().connect(
    [](auto&&... pars)
    { on_directory_changed(std::forward<decltype(pars)>(pars)...); }
  );
#else
  #error Unknown value of LAMBDA_EXPRESSION_OR_PTR_FUN
#endif
  std::cout << "Creating test file '" << FILENAME << "' to see what happens..."
    << std::endl << std::endl;

  // Wait a couple seconds and then create a temp file to trigger the
  // directory monitor.
  Glib::signal_timeout().connect_seconds([](){ return create_temp_file(); }, 2);

  // Then exit when the user has had some time to make changes in
  // the monitored directory.
  Glib::signal_timeout().connect_seconds([](){ return quit(); }, 30);
  mainloop->run();
  return 0;
}
