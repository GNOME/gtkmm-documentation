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

#include "exampleapplication.h"
#include "exampleappwindow.h"

int main(int argc, char* argv[])
{
#if HAS_SEARCH_ENTRY2
  // A GtkSearchEntry (e.g. from window.ui) shall be wrapped in
  // a Gtk::SearhcEntry2 and not in a deprecated Gtk::SearchEntry.
  Gtk::Application::wrap_in_search_entry2(true);
#endif

  // Since this example is running uninstalled, we have to help it find its
  // schema. This is *not* necessary in a properly installed application.
  Glib::setenv ("GSETTINGS_SCHEMA_DIR", ".", false);

  auto application = ExampleApplication::create();

  // Start the application, showing the initial window,
  // and opening extra views for any files that it is asked to open,
  // for instance as a command-line parameter.
  // run() will return when the last window has been closed.
  return application->run(argc, argv);
}
