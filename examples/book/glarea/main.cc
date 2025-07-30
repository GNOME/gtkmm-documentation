/* gtkmm example Copyright (C) 2025 gtkmm development team
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

#include <gtkmm/application.h>
#include "examplewindow.h" // Include our main window class

int main(int argc, char* argv[])
{
    // Create a GTKmm application instance.
    auto app = Gtk::Application::create("org.gtkmm.example.OpenGLCube");

    // Create and run the main application window.
    // make_window_and_run() creates an instance of ExampleWindow, shows it,
    // and runs the GTKmm main loop until the window is closed.
    return app->make_window_and_run<ExampleWindow>(argc, argv);
}
