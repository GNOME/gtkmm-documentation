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

#include "examplewindow.h"
#include <gtkmm/application.h>
#include <iostream>
#include <cstdlib>

#define GTK_APPLICATION_RECEIVES_COMMAND_LINE_ARGUMENTS 0

#if GTK_APPLICATION_RECEIVES_COMMAND_LINE_ARGUMENTS
namespace
{
int on_command_line(const Glib::RefPtr<Gio::ApplicationCommandLine>& command_line,
                    Glib::RefPtr<Gtk::Application>& app)
{
  int argc = 0;
  char** argv = command_line->get_arguments(argc);

  for (int i = 0; i < argc; ++i)
    std::cout << "argv[" << i << "] = " << argv[i] << std::endl;

  app->activate(); // Without activate() the window won't be shown.
  return EXIT_SUCCESS;
}
} // anonymous namespace
#endif


int main(int argc, char *argv[])
{
  if (argc != 2)
  {
    std::cerr << "Usage: example <num>, where <num> is 1, 2, or 3." << std::endl;
    return EXIT_FAILURE;
  }

  int argc1 = argc;

#if GTK_APPLICATION_RECEIVES_COMMAND_LINE_ARGUMENTS
  // The Gio::Application::Flags::HANDLES_COMMAND_LINE flag and the
  // on_command_line() signal handler are not necessary. This program is simpler
  // without them, and with argc = 1 in the call to Gtk::Application::make_window_and_run().
  // They are included to show a program with Gio::Application::Flags::HANDLES_COMMAND_LINE.
  // Gio::Application::Flags::NON_UNIQUE makes it possible to run several instances of
  // this application simultaneously.
  auto app = Gtk::Application::create(
    "org.gtkmm.example", Gio::Application::Flags::HANDLES_COMMAND_LINE | Gio::Application::Flags::NON_UNIQUE);

  // Note after = false.
  // Only one signal handler is invoked. This signal handler must run before
  // the default signal handler, or else it won't run at all.
  app->signal_command_line().connect(
    [&app](const auto& command_line)
    { return on_command_line(command_line, app); }, false);
#else
  // Gio::Application::Flags::NON_UNIQUE makes it possible to run several instances of
  // this application simultaneously.
  argc1 = 1; // Don't give the command line arguments to Gtk::Application.
  auto app = Gtk::Application::create("org.gtkmm.example", Gio::Application::Flags::NON_UNIQUE);
#endif

  // Shows the window and returns when it is closed.
  return app->make_window_and_run<ExampleWindow>(argc1, argv, std::atoi(argv[1]));
}
